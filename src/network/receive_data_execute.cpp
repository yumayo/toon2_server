#include "receive_data_execute.h"
#include "string_utility.h"
#include "noticed.hpp"
namespace network
{
receive_data_execute::receive_data_execute( udp_connection & server )
    : network_factory( server )
{
    using namespace noticed;
    #define regist_operation(_CLASS) _noticed_objects.insert( std::make_pair( #_CLASS, std::make_unique<_CLASS>( _server ) ) )

    regist_operation( find_room );
    regist_operation( receive_data_resend );

    #undef regist_operation
}
void receive_data_execute::receive_entry_point( std::string const & ip_address, int const & port, Json::Value const & root )
{
    auto handle = make_with_timeout_restart( ip_address, port );

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
            log_with_time_stamp( "name と一致する命令が見つかりませんでした。" );
        }
    }
    else
    {
        log_with_time_stamp( "name が見つからない不正なデータです。" );
    }
}
}
