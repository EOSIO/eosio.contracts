#pragma once
#include "parameter.hpp"
#include "parameter_ops_spec.hpp"
#include <eosiolib/datastream.hpp>
#include <variant>

namespace commun {


////////////////////////////////////////////////////////////////////////////////
// param wrapper ops

// compare
template<typename T, int I>
bool operator<(const param_wrapper<T,I>& a, const param_wrapper<T,I>& b) {
    auto l = to_tuple(a, nop_t<I>{});
    auto r = to_tuple(b, nop_t<I>{});
    return l < r;
}

template<typename T, int I>
bool operator==(const param_wrapper<T,I>& a, const param_wrapper<T,I>& b) {
    auto l = to_tuple(a, nop_t<I>{});
    auto r = to_tuple(b, nop_t<I>{});
    return l == r;
}
template<typename T, int I>
bool operator==(const T& a, const param_wrapper<T,I>& b) {
    auto l = to_tuple(a, nop_t<I>{});
    auto r = to_tuple(b, nop_t<I>{});
    return l == r;
}
template<typename T, int I>
bool operator!=(const param_wrapper<T,I>& a, const param_wrapper<T,I>& b) {
    return !(a == b);
}
template<typename T, int I>
bool operator!=(const T& a, const param_wrapper<T,I>& b) {
    return !(a == b);
}

// deserialize
template<typename Stream, typename T, int I>
inline datastream<Stream>& operator>>(datastream<Stream>& ds, param_wrapper<T,I>& var) {
    T obj;
    // auto fields = to_tuple(obj, nop_t<I>{});
    // ds >> fields;    // need tuple of references for that
    deserialize(ds, obj, nop_t<I>{});
    var = std::move(obj);
    return ds;
}

template<typename Stream, typename T, int I>
inline datastream<Stream>& operator<<(datastream<Stream>& ds, const param_wrapper<T,I>& var) {
    auto fields = to_tuple(var, nop_t<I>{});
    ds << fields;
    return ds;
}


} // commun
