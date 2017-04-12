#include "user_pointer/hard_pointer.hpp"
#include "user_pointer/soft_pointer.hpp"

template<class T>
using hardptr = hard_pointer<T>;
template<class T>
using softptr = soft_pointer<T>;