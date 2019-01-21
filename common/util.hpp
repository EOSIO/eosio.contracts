#pragma once

namespace commun {


template<typename T>
struct member_pointer_info;

template<typename C, typename V>
struct member_pointer_info<V C::*> {
    using value_type = V;
    using class_type = C;
};

} // commun
