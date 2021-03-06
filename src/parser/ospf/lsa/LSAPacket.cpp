//
// Created by rewbycraft on 2/25/19.
//

#include <tins/ip_address.h>
#include "LSAPacket.h"
#include "../../internal.h"
#include "RouterLSAPacket.h"
#include "../../../util.h"
#include "IntraAreaPrefixLSAPacket.h"
#include "LinkLSAPacket.h"
#include "ASExternalLSAPacket.h"
#include "lsa_checksum.h"


parser::LSAPacket::LSAPacket() : Packet() { }

parser::LSAPacket::LSAPacket(const parser::bytevector &data) : Packet(data) {
	const parser::bytevector remainder = parser::deserializeObject(header, data);
	
	if (sizeof(Header) > header.length) {
		throw parser::MalformedPacketException("Nonsensical LSA length field.");
	}
	
	//Is there a payload?
	if (!remainder.empty()) {
		//Erase all data that is not part of the payload. (Since this may be followed by more LSAs.)
		const size_t l = header.length - sizeof(Header);
		const parser::bytevector payload(remainder.begin(), remainder.begin() + l);

		uint16_t function = header.getFunction();
		switch (function) {
			case ROUTER_LSA:
				subpacket = std::make_shared<parser::RouterLSAPacket>(payload);
				break;
			case NETWORK_LSA:
				throw parser::MalformedPacketException("Unimplemented LSA type: " + std::to_string(function));
				break;
			case INTER_AREA_PREFIX_LSA:
				throw parser::MalformedPacketException("Unimplemented LSA type: " + std::to_string(function));
				break;
			case INTER_AREA_ROUTER_LSA:
				throw parser::MalformedPacketException("Unimplemented LSA type: " + std::to_string(function));
				break;
			case AS_EXTERNAL_LSA:
				subpacket = std::make_shared<parser::ASExternalLSAPacket>(payload);
				break;
			case GROUP_MEMBERSHIP_LSA:
				throw parser::MalformedPacketException("Unimplemented LSA type: " + std::to_string(function));
				break;
			case NSSA_LSA:
				throw parser::MalformedPacketException("Unimplemented LSA type: " + std::to_string(function));
				break;
			case LINK_LSA:
				subpacket = std::make_shared<parser::LinkLSAPacket>(payload);
				break;
			case INTRA_AREA_PREFIX_LSA:
				subpacket = std::make_shared<parser::IntraAreaPrefixLSAPacket>(payload);
				break;
			default:
				throw parser::MalformedPacketException("Invalid LSA type: " + std::to_string(function));
		}
	} else {
		subpacket = nullptr;
	}
}

const parser::bytevector parser::LSAPacket::serialize() const {
	parser::bytevector result;
	serializeObject(result, header);

	if (subpacket) {
		auto serializedSubpacket = subpacket->serialize();
		result.insert(result.end(), serializedSubpacket.begin(), serializedSubpacket.end());
	}
	return result;
}

const parser::LSAPacket::Header &parser::LSAPacket::getHeader() const {
	return header;
}

void parser::LSAPacket::setHeader(const parser::LSAPacket::Header &header) {
	LSAPacket::header = header;
}

const std::shared_ptr<parser::Packet> &parser::LSAPacket::getSubpacket() const {
	return subpacket;
}

void parser::LSAPacket::setSubpacket(const std::shared_ptr<parser::Packet> &subpacket) {
	LSAPacket::subpacket = subpacket;
}

void parser::LSAPacket::toString(const std::function<void(const std::string &)> &printer) const {
	printer("== LSA Packet Header ==");
	printer("Age: " + std::to_string(header.age));
	printer("Options: " + util::to_bin_string(header._options));
	printer("ID: " + std::to_string(header.id));
	printer("Advertising Router: " + Tins::IPv4Address(byteswap(header.advertising_router)).to_string());
	printer("Seq: " + std::to_string(header.seq));
	printer("Checksum: " + util::to_hex_string(header.checksum));
	printer("Length: " + std::to_string(header.length));
	if (subpacket) {
		printer("Subpacket:");
		subpacket->toString(util::prepend_printer(printer));
	}
}

void parser::LSAPacket::updateValues() {
	header.length = 20;
	if (subpacket) {
		header.length += subpacket->serialize().size();
		subpacket->updateValues();
	}

	updateChecksum();
}

void parser::LSAPacket::updateChecksum() {
    uint16_t age = header.age;
    header.age = 0;
    header.checksum = 0;
    header.checksum = parser::checksum::lsa::calcChecksum(this->serialize());
    header.age = age;
}

const std::optional<std::shared_ptr<parser::LSAPacket>> parser::LSAPacket::modToChecksum(uint16_t targetChecksum) {
	std::vector<std::size_t> targetIndices =
			std::dynamic_pointer_cast<parser::ChecksumInterface>(subpacket)->getEmptyByteIndices();
	for (std::size_t &targetIndex : targetIndices) {
		targetIndex += 20;
	}
	auto serialized = this->serialize();
	auto rtn = parser::checksum::lsa::modifyChecksum(serialized, targetIndices, targetChecksum); //parser::byteswap(targetChecksum));
	if (!rtn) {
		return std::nullopt;
	}

	for (auto pair : *rtn) {
		serialized[pair.first] = pair.second;
	}

	return { std::make_shared<LSAPacket>(serialized) };
}
