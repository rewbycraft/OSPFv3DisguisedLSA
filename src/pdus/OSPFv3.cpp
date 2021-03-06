#include <utility>

//
// Created by rewbycraft on 2/22/19.
//

#include "OSPFv3.h"
#include "../tinshelper.h"

using namespace Tins;

const PDU::PDUType pdu::OSPFv3::pdu_flag = PDU::USER_DEFINED_PDU;

uint32_t pdu::OSPFv3::header_size() const {
	return size();
}

uint32_t pdu::OSPFv3::size() const {
	return static_cast<uint32_t>(packet->serialize().size());
}

Tins::PDU *pdu::OSPFv3::clone() const {
	return new OSPFv3(*this);
}

Tins::PDU::PDUType pdu::OSPFv3::pdu_type() const {
	return USER_DEFINED_PDU;
}

void pdu::OSPFv3::write_serialization(uint8_t *buffer, uint32_t total_sz) {
	parser::bytevector result = packet->serialize();
	if (result.size() > total_sz)
		throw parser::MalformedPacketException("Unable to write serialization. Buffer too small.");
	memcpy(buffer, result.data(), result.size());
}

pdu::OSPFv3::OSPFv3(const uint8_t *data, uint32_t sz) : packet(std::make_shared<parser::OSPFv3Packet>(parser::bytevector(data, data + sz))) {
}

pdu::OSPFv3::OSPFv3() : PDU() {

}

const std::shared_ptr<parser::OSPFv3Packet> pdu::OSPFv3::getPacket() const {
	return packet;
}

void pdu::OSPFv3::updateValues(const Tins::IPv6 &pdu) {
	packet->setDest(tinshelper::tins_to_raw(pdu.dst_addr()));
	packet->setSource(tinshelper::tins_to_raw(pdu.src_addr()));
	packet->updateValues();
}

pdu::OSPFv3::OSPFv3(const std::shared_ptr<parser::OSPFv3Packet> &packet) : packet(packet) {

}
