#pragma once
#include <memory>
template<class T>
class hard_pointer : public std::shared_ptr<T>
{
public:
    hard_pointer( hard_pointer&& ) = default;
};
template<class T, class ...ARGS>
hard_pointer<T>&& make_hard_pointer( ARGS ...args )
{
    return std::move( hard_pointer<T>( args... ) );
}