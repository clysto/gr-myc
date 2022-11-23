/* -*- c++ -*- */
/*
 * Copyright 2022 Yachen Mao.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_MYC_FM0DECODER_IMPL_H
#define INCLUDED_MYC_FM0DECODER_IMPL_H

#include <gnuradio/myc/fm0decoder.h>

namespace gr {
namespace myc {

class fm0decoder_impl : public fm0decoder
{
private:
    // Nothing to declare in this block.

public:
    fm0decoder_impl();
    ~fm0decoder_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace myc
} // namespace gr

#endif /* INCLUDED_MYC_FM0DECODER_IMPL_H */
