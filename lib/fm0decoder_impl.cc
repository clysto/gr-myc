/* -*- c++ -*- */
/*
 * Copyright 2022 Yachen Mao.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "fm0decoder_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace myc {

fm0decoder::sptr fm0decoder::make() { return gnuradio::make_block_sptr<fm0decoder_impl>(); }


fm0decoder_impl::fm0decoder_impl()
    : gr::sync_decimator("fm0decoder",
                         gr::io_signature::make(1, 1, sizeof(char)),
                         gr::io_signature::make(1, 1, sizeof(char)),
                         2)
{
}

fm0decoder_impl::~fm0decoder_impl() {}

int fm0decoder_impl::work(int noutput_items,
                         gr_vector_const_void_star& input_items,
                         gr_vector_void_star& output_items)
{
    auto in = static_cast<const char*>(input_items[0]);
    auto out = static_cast<char*>(output_items[0]);

    for (int i = 0; i < noutput_items; i++) {
        out[i] = (in[2 * i] ^ in[2 * i + 1]) ^ 1;
    }

    return noutput_items;
}

} /* namespace myc */
} /* namespace gr */
