#include "receive_data_execute.h"
#include "string_utility.h"
#include "noticed.hpp"
#include "boost/lexical_cast.hpp"
namespace user
{
receive_data_execute::receive_data_execute( network::tcp_server& tcp_connection, network::udp_connection & udp_connection )
    : _tcp_connection( tcp_connection )
    , _udp_connection( udp_connection )
{
    using namespace noticed;
    #define regist_operation(_CLASS) _noticed_objects.insert( std::make_pair( #_CLASS, std::make_shared<_CLASS>( *this ) ) )

    regist_operation( find_room );
    regist_operation( close );
    regist_operation( feed_captured );
    regist_operation( check_handle );

    #undef regist_operation
}
void receive_data_execute::udp_receive_entry_point( network::network_handle handle, Json::Value const & root )
{
    auto& function_name = root["name"];
    if ( function_name.isString( ) )
    {
        auto name = function_name.asString( );
        auto itr = _noticed_objects.find( name );
        if ( itr != _noticed_objects.end( ) )
        {
            itr->second->udp_receive_entry_point( handle, root );
        }
        else
        {
            utility::log_network( handle->ip_address, handle->port,
                                  "name と一致する命令が見つかりませんでした。" );
        }
    }
    else
    {
        utility::log_network( handle->ip_address, handle->port,
                              "name が見つからない不正なデータです。" );
    }
}
void receive_data_execute::tcp_receive_entry_point( network::client_handle handle, Json::Value const & root )
{
    auto& function_name = root["name"];
    if ( function_name.isString( ) )
    {
        auto name = function_name.asString( );
        auto itr = _noticed_objects.find( name );
        if ( itr != _noticed_objects.end( ) )
        {
            itr->second->tcp_receive_entry_point( handle, root );
        }
        else
        {
            utility::log_network( handle.ip_address, boost::lexical_cast<int>( handle.port ),
                                  "name と一致する命令が見つかりませんでした。" );
        }
    }
    else
    {
        utility::log_network( handle.ip_address, boost::lexical_cast<int>( handle.port ),
                              "name が見つからない不正なデータです。" );
    }
}
std::shared_ptr<noticed::noticed_base> receive_data_execute::find( std::string name )
{
    auto itr = _noticed_objects.find( name );
    if ( itr != _noticed_objects.end( ) )
    {
        return itr->second;
    }
    return nullptr;
}
network::tcp_server & receive_data_execute::tcp( )
{
    return _tcp_connection;
}
network::udp_connection & receive_data_execute::udp( )
{
    return _udp_connection;
}
}
