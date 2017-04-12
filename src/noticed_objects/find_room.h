#pragma once
#include "noticed_base_object.h"
#include <boost/optional.hpp>
class find_room : public noticed_base_object
{
    // 試験的に部屋は一つとします。
    boost::optional<network_handle> _host;
public:
    find_room( connection_server& server );
public:
    void receive_entry_point( network_handle const& handle, Json::Value const& data ) override;
};