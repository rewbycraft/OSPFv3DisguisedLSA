//
// Created by kaj on 27-3-19.
//

#include "gtest/gtest.h"
#include <parser/internal.h>
#include <parser/ospf/OSPFv3Packet.h>
#include <parser/ospf/lsa/LSAPacket.h>
#include <parser/ospf/lsa/IntraAreaPrefixLSAPacket.h>
#include <parser/ospf/lsa/PrefixLSAPacket.h>
#include <parser/ospf/LinkStateUpdatePacket.h>


TEST(checksumtest, recalcChecksumTest01) {
    parser::bytevector data = {0x03, 0x04, 0x04, 0x50, 0x01, 0x01, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x65, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x04, 0x83, 0x20, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x01, 0x80, 0x00, 0x00, 0x06, 0xff, 0x05, 0x00, 0x48, 0x02, 0x00, 0x01, 0x13, 0x01, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x14, 0x01, 0x01, 0x02, 0x01, 0x01, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x1b, 0x01, 0x01, 0x03, 0x02, 0x01, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x26, 0x01, 0x01, 0x06, 0x01, 0x04, 0xa9, 0x20, 0x09, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x01, 0x80, 0x00, 0x00, 0x04, 0xa2, 0xb6, 0x00, 0x70, 0x00, 0x04, 0x20, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x01, 0x7c, 0x00, 0x00, 0x64, 0x2a, 0x0b, 0x6b, 0x83, 0x2c, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0xc2, 0x00, 0xd1, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x64, 0x2a, 0x0b, 0x6b, 0x83, 0x2c, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0xc1, 0x00, 0xd1, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x64, 0x2a, 0x0b, 0x6b, 0x83, 0x2c, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0xd1, 0x00, 0xd2, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x64, 0x2a, 0x0b, 0x6b, 0x83, 0x2c, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0xf1, 0x00, 0xd1, 0x00, 0x00, 0x04, 0xaf, 0x00, 0x08, 0x00, 0x00, 0x00, 0x17, 0x01, 0x01, 0x03, 0x01, 0x80, 0x00, 0x00, 0x03, 0x1c, 0x70, 0x00, 0x40, 0x01, 0x00, 0x01, 0x13, 0xfe, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0xb0, 0xed, 0xff, 0xfe, 0x38, 0x9f, 0x81, 0x00, 0x00, 0x00, 0x01, 0x7c, 0x00, 0x00, 0x00, 0x2a, 0x0b, 0x6b, 0x83, 0x2c, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0xc2, 0x00, 0xd1, 0x00, 0x00, 0x04, 0x83, 0x20, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x01, 0x80, 0x00, 0x00, 0x06, 0x4d, 0x6b, 0x00, 0x58, 0x02, 0x00, 0x01, 0x13, 0x01, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x0e, 0x01, 0x01, 0x01, 0x02, 0x01, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x13, 0x01, 0x01, 0x03, 0x01, 0x01, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x0a, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x15, 0x01, 0x01, 0x03, 0x02, 0x04, 0xaa, 0x20, 0x09, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x01, 0x80, 0x00, 0x00, 0x04, 0xe1, 0x4e, 0x00, 0x84, 0x00, 0x05, 0x20, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x01, 0x7c, 0x00, 0x00, 0x64, 0x2a, 0x0b, 0x6b, 0x83, 0x2c, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0xe2, 0x00, 0xc1, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x64, 0x2a, 0x0b, 0x6b, 0x83, 0x2c, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0xc1, 0x00, 0xc2, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x64, 0x2a, 0x0b, 0x6b, 0x83, 0x2c, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0xc1, 0x00, 0xd1, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x64, 0x2a, 0x0b, 0x6b, 0x83, 0x2c, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0xe1, 0x00, 0xc1, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x64, 0x2a, 0x0b, 0x6b, 0x83, 0x2c, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0xc1, 0x00, 0xd2, 0x00, 0x00, 0x04, 0x83, 0x20, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x02, 0x80, 0x00, 0x00, 0x06, 0x35, 0x5a, 0x00, 0x28, 0x02, 0x00, 0x01, 0x13, 0x01, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x0d, 0x01, 0x01, 0x02, 0x01, 0x04, 0xab, 0x20, 0x09, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x02, 0x80, 0x00, 0x00, 0x04, 0x0f, 0x98, 0x00, 0x48, 0x00, 0x02, 0x20, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x02, 0x7c, 0x00, 0x00, 0x64, 0x2a, 0x0b, 0x6b, 0x83, 0x2c, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0xe2, 0x00, 0xc1, 0x00, 0x00, 0x7c, 0x00, 0x03, 0xe8, 0x2a, 0x0b, 0x6b, 0x83, 0x2c, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0xe2, 0x00, 0xc2, 0x00, 0x00, 0x04, 0x84, 0x20, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x80, 0x00, 0x00, 0x06, 0xba, 0xdd, 0x00, 0x28, 0x02, 0x00, 0x01, 0x13, 0x01, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x09, 0x01, 0x01, 0x02, 0x01, 0x04, 0xab, 0x20, 0x09, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x80, 0x00, 0x00, 0x04, 0x0c, 0x9f, 0x00, 0x48, 0x00, 0x02, 0x20, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x7c, 0x00, 0x03, 0xe8, 0x2a, 0x0b, 0x6b, 0x83, 0x2c, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0xe1, 0x00, 0xc2, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x64, 0x2a, 0x0b, 0x6b, 0x83, 0x2c, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0xe1, 0x00, 0xc1, 0x00, 0x00, 0x04, 0xab, 0x40, 0x05, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x80, 0x00, 0x00, 0x03, 0xf6, 0x84, 0x00, 0x24, 0x04, 0x00, 0x27, 0x10, 0x40, 0x00, 0x00, 0x00, 0x2a, 0x0b, 0x6b, 0x83, 0x2c, 0x80, 0x12, 0x34, 0x04, 0x84, 0x20, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x02, 0x80, 0x00, 0x00, 0x06, 0xd8, 0x24, 0x00, 0x48, 0x02, 0x00, 0x01, 0x13, 0x01, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x16, 0x01, 0x01, 0x02, 0x01, 0x01, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x1b, 0x00, 0x00, 0x00, 0x1c, 0x01, 0x01, 0x03, 0x01, 0x01, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00, 0x28, 0x01, 0x01, 0x06, 0x01, 0x04, 0xab, 0x20, 0x09, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x02, 0x80, 0x00, 0x00, 0x04, 0x42, 0x12, 0x00, 0x70, 0x00, 0x04, 0x20, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x02, 0x7c, 0x00, 0x00, 0x64, 0x2a, 0x0b, 0x6b, 0x83, 0x2c, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0xc1, 0x00, 0xd2, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x64, 0x2a, 0x0b, 0x6b, 0x83, 0x2c, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0xd1, 0x00, 0xd2, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x64, 0x2a, 0x0b, 0x6b, 0x83, 0x2c, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0xc2, 0x00, 0xd2, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x64, 0x2a, 0x0b, 0x6b, 0x83, 0x2c, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0xf1, 0x00, 0xd2, 0x00, 0x00, 0x04, 0x9f, 0x20, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x06, 0x01, 0x80, 0x00, 0x00, 0x05, 0x86, 0x09, 0x00, 0x38, 0x02, 0x00, 0x01, 0x13, 0x01, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00, 0x25, 0x01, 0x01, 0x03, 0x01, 0x01, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x27, 0x01, 0x01, 0x03, 0x02, 0x04, 0xaa, 0x20, 0x09, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x06, 0x01, 0x80, 0x00, 0x00, 0x04, 0x04, 0xe4, 0x00, 0x48, 0x00, 0x02, 0x20, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x06, 0x01, 0x7c, 0x00, 0x00, 0x64, 0x2a, 0x0b, 0x6b, 0x83, 0x2c, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0xf1, 0x00, 0xd1, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x64, 0x2a, 0x0b, 0x6b, 0x83, 0x2c, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0xf1, 0x00, 0xd2, 0x00, 0x00, 0x04, 0xb0, 0x40, 0x05, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x06, 0x01, 0x80, 0x00, 0x00, 0x03, 0x9e, 0x36, 0x00, 0x2c, 0x04, 0x00, 0x27, 0x10, 0x7c, 0x00, 0x00, 0x00, 0x2a, 0x0b, 0x6b, 0x83, 0x2c, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0xb1, 0x00, 0xf1, 0x00, 0x00};
    parser::OSPFv3Packet packet(data);
    packet.setSource(std::make_uint128(18338657682652659712u,2067413912700624769u));
    packet.setDest(std::make_uint128(18338657682652659712u,8940765662646544802u));
    packet.updateValues();

    std::optional<std::shared_ptr<parser::LSAPacket>> newPacket = std::nullopt;
    std::shared_ptr<parser::LinkStateUpdatePacket> lsu = std::dynamic_pointer_cast<parser::LinkStateUpdatePacket>(
            packet.getSubpacket());
    std::vector<std::shared_ptr<parser::LSAPacket>> lsas = lsu-> getLsas();
    std::shared_ptr<parser::LSAPacket> lsa = lsas[1];
    const uint16_t oldChecksum = lsa->getHeader().checksum;
    std::shared_ptr<parser::IntraAreaPrefixLSAPacket> iapLSA = std::dynamic_pointer_cast<parser::IntraAreaPrefixLSAPacket>(
            lsa->getSubpacket());
    std::shared_ptr<parser::PrefixLSAPacket> prefixLSA = std::dynamic_pointer_cast<parser::PrefixLSAPacket>(
            iapLSA->getPrefixes()[0]);
    const parser::PrefixLSAPacket::Header &origHeader = prefixLSA->getHeader();

    const std::uint16_t targetChecksum = 41653; // oldChecksum;
    for (std::uint16_t metric = 100; !newPacket; metric++) { // 28939
        const parser::PrefixLSAPacket::Header newHeader = {
                origHeader.length, origHeader.options, uint16_t(metric), origHeader.address
        };
        prefixLSA->setHeader(newHeader);
        newPacket = lsa->modToChecksum(targetChecksum);
    }

    lsas[1] = newPacket.value();
    lsas[1]->updateValues();
    lsu->setLsas(lsas);
    packet.updateValues();
    const std::uint16_t newChecksum = newPacket.value()->getHeader().checksum;

    EXPECT_EQ(targetChecksum, newChecksum);
}


