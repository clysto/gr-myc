/* -*- c++ -*- */
/*
 * Copyright 2022 Yachen Mao.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "varlen_packet_tagger_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace myc {
varlen_packet_tagger::sptr varlen_packet_tagger::make(const std::string& sync_key,
                                                      const std::string& packet_key,
                                                      int length_field_size,
                                                      int max_packet_size,
                                                      endianness_t endianness)
{
    return gnuradio::make_block_sptr<varlen_packet_tagger_impl>(
        sync_key, packet_key, length_field_size, max_packet_size, endianness);
}

varlen_packet_tagger_impl::varlen_packet_tagger_impl(const std::string& sync_key,
                                                     const std::string& packet_key,
                                                     int length_field_size,
                                                     int max_packet_size,
                                                     endianness_t endianness)
    : gr::block("varlen_packet_tagger",
                io_signature::make(1, 1, sizeof(char)),
                io_signature::make(1, 1, sizeof(char))),
      d_header_length(length_field_size),
      d_mtu(max_packet_size),
      d_endianness(endianness),
      d_have_sync(false)
{
    d_sync_tag = pmt::string_to_symbol(sync_key);
    d_packet_tag = pmt::string_to_symbol(packet_key);
    d_ninput_items_required = d_header_length + 1;

    set_tag_propagation_policy(TPP_DONT);
}


varlen_packet_tagger_impl::~varlen_packet_tagger_impl() {}

int varlen_packet_tagger_impl::bits2len(const unsigned char* in)
{
    // extract the packet length from the header
    int ret = 0;
    int i = 0;
    for (int j = 0; j < d_header_length / 8; j++) {
        u_char b = 0;
        if (d_endianness == GR_MSB_FIRST) {
            for (int k = 0; k < 8; k++) {
                b = (b << 1) + ((in[i] ^ in[i + 1]) ^ 1);
                i += 2;
            }
        } else {
            for (int k = 7; k >= 0; k--) {
                b = (b << 1) + ((in[i] ^ in[i + 1]) ^ 1);
                i += 2;
            }
        }
        ret = (b << (j * 8)) + ret;
    }
    return ret;
}

void varlen_packet_tagger_impl::forecast(int noutput_items,
                                         gr_vector_int& ninput_items_required)
{
    unsigned ninputs = ninput_items_required.size();
    for (unsigned i = 0; i < ninputs; i++)
        ninput_items_required[i] = d_ninput_items_required;
}

int varlen_packet_tagger_impl::general_work(int noutput_items,
                                            gr_vector_int& ninput_items,
                                            gr_vector_const_void_star& input_items,
                                            gr_vector_void_star& output_items)
{
    const unsigned char* in = (const unsigned char*)input_items[0];
    unsigned char* out = (unsigned char*)output_items[0];
    int packet_len = 0;
    std::vector<tag_t> tags;


    if (d_have_sync) {
        if (d_header_length * 2 > ninput_items[0]) {
            // not enough data yet
            return 0;
        }

        packet_len = 8 * 2 * bits2len(in) + 32;

        if (packet_len > d_mtu) {
            d_debug_logger->warn("Packet length {:d} > mtu {:d}.", packet_len, d_mtu);
            d_have_sync = false;
            consume_each(1); // skip ahead
            return 0;
        }

        d_ninput_items_required = (d_header_length * 2) + packet_len;

        if (noutput_items < packet_len) {
            set_min_noutput_items(packet_len);
            return 0;
        }
        set_min_noutput_items(1);

        if (ninput_items[0] >= packet_len + d_header_length * 2) {
            // TODO: header parse
            memcpy(out, &in[d_header_length * 2], packet_len);
            add_item_tag(0,
                         nitems_written(0),
                         d_packet_tag,
                         pmt::from_long(packet_len),
                         alias_pmt());
            d_have_sync = false;

            // consuming only the header allows for
            // ... multiple syncs per 'packet',
            // ... in case the sync was incorrectly tagged
            consume_each(d_header_length * 2);
            d_ninput_items_required = d_header_length * 2 + 1;
            return packet_len;
        }

    } else {
        // find the next sync tag, drop all other data
        get_tags_in_range(
            tags, 0, nitems_read(0), nitems_read(0) + ninput_items[0], d_sync_tag);
        if (tags.size() > 0) {
            d_have_sync = true;
            consume_each(tags[0].offset - nitems_read(0));
        } else {
            consume_each(ninput_items[0]);
        }
    }
    return 0;
}


} /* namespace myc */
} /* namespace gr */
