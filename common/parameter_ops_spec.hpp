#pragma once
#include <eosiolib/datastream.hpp>

namespace cyber {


template<int N> struct nop_t {};    // TODO: is there better way?

////////////////////////////////////////////////////////////////////////////////
// generated code for different fields' counts
template<typename T> auto to_tuple(T& obj, nop_t<1>) {
    auto& [a] = obj;
    return std::make_tuple(a);
}
template<typename T> auto to_tuple(T& obj, nop_t<2>) {
    auto& [a, b] = obj;
    return std::make_tuple(a, b);
}
template<typename T> auto to_tuple(T& obj, nop_t<3>) {
    auto& [a, b, c] = obj;
    return std::make_tuple(a, b, c);
}
template<typename T> auto to_tuple(T& obj, nop_t<4>) {
    auto& [a, b, c, d] = obj;
    return std::make_tuple(a, b, c, d);
}
template<typename T> auto to_tuple(T& obj, nop_t<5>) {
    auto& [a, b, c, d, e] = obj;
    return std::make_tuple(a, b, c, d, e);
}

// separate deserialize functions, because std::make_tuple drops references and we can't fill original struct. TODO: make_tuple_of_references
template<typename S, typename T> void deserialize(datastream<S>& ds, T& obj, nop_t<1>) {
    auto& [a] = obj;
    ds >> a;
}
template<typename S, typename T> void deserialize(datastream<S>& ds, T& obj, nop_t<2>) {
    auto& [a, b] = obj;
    ds >> a >> b;
}
template<typename S, typename T> void deserialize(datastream<S>& ds, T& obj, nop_t<3>) {
    auto& [a, b, c] = obj;
    ds >> a >> b >> c;
}
template<typename S, typename T> void deserialize(datastream<S>& ds, T& obj, nop_t<4>) {
    auto& [a, b, c, d] = obj;
    ds >> a >> b >> c >> d;
}
template<typename S, typename T> void deserialize(datastream<S>& ds, T& obj, nop_t<5>) {
    auto& [a, b, c, d, e] = obj;
    ds >> a >> b >> c >> d >> e;
}


} // commun
