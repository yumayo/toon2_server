#pragma once
#include <memory>
namespace utility
{
template<class T>
using hard_pointer = std::shared_ptr<T>;
template<class T>
using hardptr = hard_pointer<T>;
template<class T, class ...ARGS>
hard_pointer<T> make_hard_pointer( ARGS ...args )
{
    return std::make_shared( args... );
}

// weak_ptr���g�p����Ƃ��ɁA�������� lock �Ƃ� expired ���g���̂����邢�̂Ń��b�s���O���܂��B

template<class T>
class soft_pointer : protected std::weak_ptr<T>
{
public:
    soft_pointer( ) = default;
    soft_pointer( hard_pointer<T> const& other ) noexcept;
    soft_pointer( hard_pointer<T>&& other ) noexcept;

    soft_pointer<T>& operator=( hard_pointer<T> const& other ) const;
    soft_pointer<T>& operator=( hard_pointer<T>&& other ) const;

    operator bool( ) const; // �|�C���^��null������؂�𔻒f���܂��B
    bool operator!( ) const; // �|�C���^��not��^���܂��B

    hard_pointer<T> operator->( ) const; // �|�C���^�̎��Ԃ�Ԃ��܂��B
    hard_pointer<T> operator*( ) const;

    bool operator==( soft_pointer<T> const& other ) const; // �|�C���^���m���r���܂��B
    bool operator!=( soft_pointer<T> const& other ) const;
    bool operator==( hard_pointer<T> const& other ) const;
    bool operator!=( hard_pointer<T> const& other ) const;

    operator T( ) const; // �����I�Ƀ|�C���^�̎��Ԃ�Ԃ��܂��B
    operator T&( ) const;
    operator T const&( ) const;
};
template<class T>
inline soft_pointer<T>::soft_pointer( hard_pointer<T> const & other ) noexcept
    : std::weak_ptr<T>( other )
{
}
template<class T>
inline soft_pointer<T>::soft_pointer( hard_pointer<T>&& other ) noexcept
    : std::weak_ptr<T>( std::move( other ) )
{
}
template<class T>
inline soft_pointer<T>::operator bool( ) const
{
    return this->lock( ) && this->expired( );
}
template<class T>
inline hard_pointer<T> soft_pointer<T>::operator->( ) const
{
    return std::move( this->lock( ) );
}
template<class T>
inline hard_pointer<T> soft_pointer<T>::operator*( ) const
{
    return std::move( this->lock( ) );
}
template<class T>
inline bool soft_pointer<T>::operator==( soft_pointer<T> const & other ) const
{
    return this->lock( ) == other.lock( );
}
template<class T>
inline bool soft_pointer<T>::operator!=( soft_pointer<T> const & other ) const
{
    return this->lock( ) != other.lock( );
}
template<class T>
inline bool soft_pointer<T>::operator==( hard_pointer<T> const & other ) const
{
    return this->lock( ) == other;
}
template<class T>
inline bool soft_pointer<T>::operator!=( hard_pointer<T> const & other ) const
{
    return this->lock( ) != other;
}
template<class T>
inline bool soft_pointer<T>::operator!( ) const
{
    return !this->lock( );
}
template<class T>
inline soft_pointer<T>& soft_pointer<T>::operator=( hard_pointer<T> const & other ) const
{
    return *this = other;
}
template<class T>
inline soft_pointer<T>& soft_pointer<T>::operator=( hard_pointer<T>&& other ) const
{
    return *this = std::move( other );
}
template<class T>
inline soft_pointer<T>::operator T( ) const
{
    return *this->lock( );
}
template<class T>
inline soft_pointer<T>::operator T&( ) const
{
    return *this->lock( );
}
template<class T>
inline soft_pointer<T>::operator T const&( ) const
{
    return *this->lock( );
}
template<class T>
using softptr = soft_pointer<T>;
}
