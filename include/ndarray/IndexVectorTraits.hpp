// -*- c++ -*-
/*
 * Copyright (c) 2010-2016, Jim Bosch
 * All rights reserved.
 *
 * ndarray is distributed under a simple BSD-like license;
 * see the LICENSE file that should be present in the root
 * of the source distribution, or alternately available at:
 * https://github.com/ndarray/ndarray
 */
#ifndef NDARRAY_IndexVectorTraits_hpp_INCLUDED
#define NDARRAY_IndexVectorTraits_hpp_INCLUDED

#include <array>
#include <vector>
#include <type_traits>

#include "ndarray/common.hpp"
#include "ndarray/errors.hpp"

namespace ndarray {

template <typename T>
struct IndexVectorTraits {

    static constexpr bool is_specialized = false;

};

template <typename U, std::size_t N>
struct IndexVectorTraits<std::array<U, N>> {

    static constexpr bool is_specialized = true;

    template <Size M>
    static void check_dims(std::array<U, N> const & v) {
        static_assert(
            M == N,
            "Index vector has wrong number of elements."
        );
    }

    static Size get_size(std::array<U, N> const & v, Size n) {
        return v[n];
    }

    static Offset get_offset(std::array<U, N> const & v, Size n) {
        return v[n];
    }

};

template <typename U>
struct IndexVectorTraits<std::initializer_list<U>> {

    static constexpr bool is_specialized = true;

    template <Size M>
    static void check_dims(std::initializer_list<U> const & v) {
        NDARRAY_ASSERT_CHECK(M == v.size(),
                             "Shape vector size ({:d}) does not match number of dimensions ({:d}).",
                             v.size(), M);
    }

    static Size get_size(std::initializer_list<U> const & v, Size n) {
        return v.begin()[n];
    }

    static Offset get_offset(std::initializer_list<U> const & v, Size n) {
        return v.begin()[n];
    }

};

template <typename U>
struct IndexVectorTraits<std::vector<U>> {

    static constexpr bool is_specialized = true;

    template <Size M>
    static void check_dims(std::vector<U> const & v) {
        NDARRAY_ASSERT_CHECK(M == v.size(),
                             "Shape vector size ({:d}) does not match number of dimensions ({:d}).",
                             v.size(), M);
    }

    static Size get_size(std::vector<U> const & v, Size n) {
        return v[n];
    }

    static Offset get_offset(std::vector<U> const & v, Size n) {
        return v[n];
    }

};


template <typename V1, typename ...Vn>
struct IsIndexVector {
    static constexpr bool value = IndexVectorTraits<V1>::is_specialized && IsIndexVector<Vn...>::value;
};


template <typename V>
struct IsIndexVector<V> {
    static constexpr bool value = IndexVectorTraits<V>::is_specialized;
};


template <typename Arg, typename ...V>
using EnableIfIndexVector = typename std::enable_if<IsIndexVector<V...>::value, Arg>::type;


} // ndarray

#endif // !NDARRAY_IndexVectorTraits_hpp_INCLUDED