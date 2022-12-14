/* -*- c++ -*- */
/*
 * Copyright 2022 Yachen Mao.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_MYC_VARLEN_PACKET_TAGGER_IMPL_H
#define INCLUDED_MYC_VARLEN_PACKET_TAGGER_IMPL_H

#include <gnuradio/myc/varlen_packet_tagger.h>

namespace gr {
namespace myc {

class varlen_packet_tagger_impl : public varlen_packet_tagger
{
private:
    int d_header_length;       // bit size of packet length field
    int d_mtu;                 // maximum packet size in bits
    endianness_t d_endianness; // header endianness

    pmt::pmt_t d_sync_tag;   // marker tag on input for start of packet
    pmt::pmt_t d_packet_tag; // packet_len tag for output stream

    bool d_have_sync;            // interal state
    int d_ninput_items_required; // forecast

    int bits2len(const unsigned char* in);

public:
    varlen_packet_tagger_impl(const std::string& sync_key,
                              const std::string& packet_key,
                              int length_field_size,
                              int max_packet_size,
                              endianness_t endianness);
    ~varlen_packet_tagger_impl();

    void forecast(int noutput_items, gr_vector_int& ninput_itens_required);

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items);
};

} // namespace myc
} // namespace gr

#endif /* INCLUDED_MYC_VARLEN_PACKET_TAGGER_IMPL_H */
