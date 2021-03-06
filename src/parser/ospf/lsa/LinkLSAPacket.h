//
// Created by rewbycraft on 3/18/19.
//

#ifndef ATTACK_LINKLSAPACKET_H
#define ATTACK_LINKLSAPACKET_H

#include "LSAPacket.h"
#include "PrefixLSAPacket.h"
#include "ChecksumInterface.h"


namespace parser {
	class LinkLSAPacket : public parser::Packet, parser::ChecksumInterface {
	public:
		typedef struct {
			uint32_t _options;
			uint128_t lladdr;
			uint32_t num_prefixes;
		} Header;

	private:
		Header header;
		std::vector<std::shared_ptr<parser::PrefixLSAPacket>> prefixes;

	public:
		LinkLSAPacket();

		explicit LinkLSAPacket(const bytevector &data);

		const bytevector serialize() const override;

		void toString(const std::function<void(const std::string &)> &printer) const override;

		/**
		 * @return the header of this packet.
		 */
		const Header &getHeader() const;

		/**
		 * Sets the header of this packet.
		 *
		 * @param header the new header.
		 */
		void setHeader(const Header &header);

		/**
		 * @return a vector containing the pointers of the LSA prefix packets of this packet.
		 */
		const std::vector<std::shared_ptr<PrefixLSAPacket>> &getPrefixes() const;

		/**
		 * Sets the LSA prefix packets of this packet.
		 *
		 * @param prefixes the vector containing the pointers of the new LSA prefix packets.
		 */
		void setPrefixes(const std::vector<std::shared_ptr<PrefixLSAPacket>> &prefixes);

		void updateValues() override;

    	std::vector<size_t> getEmptyByteIndices() override;
    };
}

BOOST_FUSION_ADAPT_STRUCT(parser::LinkLSAPacket::Header, (uint32_t, _options), (uint128_t, lladdr), (uint32_t, num_prefixes))

#endif //ATTACK_LINKLSAPACKET_H
