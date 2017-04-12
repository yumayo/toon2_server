#pragma once
#include <memory>
template<class T>
class soft_pointer : public std::weak_ptr<T>
{
public:
    operator bool( ) const;
    T& operator->( ) const;
};
template<class T>
inline soft_pointer<T>::operator bool( ) const
{
    return lock( ) && expired( );
}
template<class T>
inline T & soft_pointer<T>::operator->( ) const
{
    return lock( );
}
