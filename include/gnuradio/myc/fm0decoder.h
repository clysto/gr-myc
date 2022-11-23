/* -*- c++ -*- */
/*
 * Copyright 2022 Yachen Mao.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_MYC_FM0DECODER_H
#define INCLUDED_MYC_FM0DECODER_H

#include <gnuradio/myc/api.h>
#include <gnuradio/sync_decimator.h>

namespace gr {
namespace myc {

/*!
 * \brief <+description of block+>
 * \ingroup myc
 *
 */
class MYC_API fm0decoder : virtual public gr::sync_decimator
{
public:
    typedef std::shared_ptr<fm0decoder> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of myc::fm0decoder.
     *
     * To avoid accidental use of raw pointers, myc::fm0decoder's
     * constructor is in a private implementation
     * class. myc::fm0decoder::make is the public interface for
     * creating new instances.
     */
    static sptr make();
};

} // namespace myc
} // namespace gr

#endif /* INCLUDED_MYC_FM0DECODER_H */
