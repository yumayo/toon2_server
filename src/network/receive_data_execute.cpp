#include "receive_data_execute.h"
#include "string_utility.h"
#include "noticed/noticed_base.h"
#include "noticed.hpp"
namespace network
{
receive_data_execute::receive_data_execute( udp_connection & connection )
    : network_factory( connection )
{
    using namespace noticed;
    #define regist_operation(_CLASS) _noticed_objects.insert( std::make_pair( #_CLASS, std::make_shared<_CLASS>( _server, *this ) ) )

    regist_operation( find_room );
    regist_operation( receive_data_resend );

    #undef regist_operation
}
void receive_data_execute::receive_entry_point( std::string const & ip_address, int const & port, Json::Value const & root )
{
    auto handle = regist( ip_address, port, root );

    auto& function_name = handle->user_data["name"];
    if ( function_name.isString( ) )
    {
        auto name = function_name.asString( );
        auto itr = _noticed_objects.find( name );
        if ( itr != _noticed_objects.end( ) )
        {
            itr->second->receive_entry_point( handle );
        }
        else
        {
            utility::log_network( ip_address, port, 
                                  "name と一致する命令が見つかりませんでした。" );
        }
    }
    else
    {
        utility::log_network( ip_address, port, 
                              "name が見つからない不正なデータです。" );
    }
}
}
