//
// Created by rewbycraft on 3/24/19.
//

#include "tinshelper.h"

const uint128_t tinshelper::tins_to_raw(const Tins::IPv6Address& addr) {
	uint128_t v = 0;
	static_assert(sizeof(uint128_t) == Tins::IPv6Address::address_size, "Not enough space.");
	Tins::IPv6Address::const_iterator iter = addr.begin();
	for (int i = 0; i < 16; i++) {
		v <<= 8;
		v |= iter[i];
	}
	return v;
}

const Tins::IPv6Address tinshelper::raw_to_tins(uint128_t addr) {
	auto rc = Tins::IPv6Address::from_prefix_length(128);
	static_assert(sizeof(uint128_t) == Tins::IPv6Address::address_size, "Not enough space.");
	Tins::IPv6Address::iterator iter = rc.begin();
	for (int i = 15; i >= 0; i--) {
		iter[i] = static_cast<uint8_t>(addr & 0xFF);
		addr >>= 8;
	}
	return rc;
}
