#pragma once
#include <memory>

// weak_ptr���g�p����Ƃ��ɁA�������� lock �Ƃ� expired ���g���̂����邢�̂Ń��b�s���O���܂��B

template<class T>
class soft_pointer : protected std::weak_ptr<T>
{
public:
    soft_pointer( ) = default;
    soft_pointer( std::shared_ptr<T> const& other ) noexcept;
    soft_pointer( std::shared_ptr<T>&& other ) noexcept;
    soft_pointer( std::weak_ptr<T> const& other ) noexcept;
    operator bool( ) const; // �|�C���^��null������؂�𔻒f���܂��B
    std::shared_ptr<T> operator->( ) const; // �|�C���^�̎��Ԃ�Ԃ��܂��B
    std::shared_ptr<T> operator*( ) const; // �|�C���^�̎��Ԃ�Ԃ��܂��B
    bool operator==( soft_pointer<T> const& other ) const; // �|�C���^���m���r���܂��B
    bool operator!=( soft_pointer<T> const& other ) const; // �|�C���^���m���r���܂��B
    bool operator!( ) const; // �|�C���^��not��^���܂��B
    soft_pointer<T> const& operator=( std::shared_ptr<T> const& other ) const;
    operator T( ) const; // �����I�Ƀ|�C���^�̎��Ԃ�Ԃ��܂��B
};
template<class T>
inline soft_pointer<T>::soft_pointer( std::shared_ptr<T> const & other ) noexcept
    : std::weak_ptr<T>( other )
{
}
template<class T>
inline soft_pointer<T>::soft_pointer( std::shared_ptr<T>&& other ) noexcept
    : std::weak_ptr<T>( std::move( other ) )
{
}
template<class T>
inline soft_pointer<T>::soft_pointer( std::weak_ptr<T> const & other ) noexcept
    : std::weak_ptr<T>( other )
{
}
template<class T>
inline soft_pointer<T>::operator bool( ) const
{
    return this->lock( ) && this->expired( );
}
template<class T>
inline std::shared_ptr<T> soft_pointer<T>::operator->( ) const
{
    return std::move( this->lock( ) );
}
template<class T>
inline std::shared_ptr<T> soft_pointer<T>::operator*( ) const
{
    return std::move( this->lock( ) );
}
template<class T>
inline bool soft_pointer<T>::operator==( soft_pointer<T> const & other ) const
{
    return this->lock( ) == other->lock( );
}
template<class T>
inline bool soft_pointer<T>::operator!=( soft_pointer<T> const & other ) const
{
    return this->lock( ) != other->lock( );
}
template<class T>
inline bool soft_pointer<T>::operator!( ) const
{
    return !this->lock( );
}
template<class T>
inline soft_pointer<T> const & soft_pointer<T>::operator=( std::shared_ptr<T> const & other ) const
{
    return *this = other;
}
template<class T>
inline soft_pointer<T>::operator T( ) const
{
    return *this->lock( );
}