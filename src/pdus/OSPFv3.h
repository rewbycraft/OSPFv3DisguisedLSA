//
// Created by rewbycraft on 2/22/19.
//

#ifndef ATTACK_OSPFV3_H
#define ATTACK_OSPFV3_H

#include "../parser/ospf/OSPFv3Packet.h"
#include <tins/tins.h>

using namespace Tins;

namespace pdu {
	class OSPFv3 : public Tins::PDU {
		std::shared_ptr<parser::OSPFv3Packet> packet;
	public:
		static const PDU::PDUType pdu_flag;
		
		OSPFv3(const uint8_t* data, uint32_t sz);
		
		OSPFv3();
		
		OSPFv3(const std::shared_ptr<parser::OSPFv3Packet> &packet);
		
		uint32_t header_size() const override;
		
		PDU *clone() const override;
		
		PDUType pdu_type() const override;
		
		uint32_t size() const;
		
		const std::shared_ptr<parser::OSPFv3Packet> getPacket() const;
		
		void updateValues(const Tins::IPv6 &pdu);
	
	protected:
		void write_serialization(uint8_t *buffer, uint32_t total_sz) override;
	};
}


#endif //ATTACK_OSPFV3_H
