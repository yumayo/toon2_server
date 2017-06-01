#include "receive_data_execute.h"
#include "string_utility.h"
#include "noticed.hpp"
namespace user
{
receive_data_execute::receive_data_execute( network::udp_connection & connection )
    : _connection( connection )
{
    using namespace noticed;
    #define regist_operation(_CLASS) _noticed_objects.insert( std::make_pair( #_CLASS, std::make_shared<_CLASS>( _connection ) ) )

    regist_operation( find_room );
    regist_operation( receive_data_resend );
    regist_operation( host_connection );
    regist_operation( close );

    #undef regist_operation
}
void receive_data_execute::receive_entry_point( network::network_handle handle, Json::Value root )
{
    auto& function_name = root["name"];
    if ( function_name.isString( ) )
    {
        auto name = function_name.asString( );
        auto itr = _noticed_objects.find( name );
        if ( itr != _noticed_objects.end( ) )
        {
            itr->second->receive_entry_point( handle, root );
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
}
