/* -*- c++ -*- */
/*
 * Copyright 2022 Yachen Mao.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_MYC_VARLEN_PACKET_TAGGER_H
#define INCLUDED_MYC_VARLEN_PACKET_TAGGER_H

#include <gnuradio/block.h>
#include <gnuradio/endianness.h>
#include <gnuradio/myc/api.h>

namespace gr {
namespace myc {

class MYC_API varlen_packet_tagger : virtual public gr::block
{
public:
    typedef std::shared_ptr<varlen_packet_tagger> sptr;

    /*!
     * \param sync_key
     * \param packet_key
     * \param length_field_size
     * \param max_packet_size
     * \param endianness
     */
    static sptr make(const std::string& sync_key,
                     const std::string& packet_key,
                     int length_field_size,
                     int max_packet_size,
                     endianness_t endianness);
};

} // namespace myc
} // namespace gr

#endif /* INCLUDED_MYC_VARLEN_PACKET_TAGGER_H */
