#include "vehicles/fixedwing/api/FixedWingRpcLibServer.hpp"
#include "vehicles/fixedwing/api/FixedWingRpcLibAdaptors.hpp"
#include "rpc/server.h"

using namespace msr::airlib;

using namespace msr::airlib_rpclib;

FixedWingRpcLibServer::FixedWingRpcLibServer(ApiProvider* api_provider, const string& ip_address, uint16_t port)
    : MultirotorRpcLibServer(api_provider, ip_address, port)
{
    (static_cast<rpc::server*>(getServer()))->bind("setControlSurfaces", [&](const FixedWingRpcLibAdaptors::ControlSurfaces& c, const std::string& vehicle_name) -> void {
        getVehicleApi(vehicle_name)->setControlSurfaces(c.to());
    });
    (static_cast<rpc::server*>(getServer()))->bind("getControlSurfaces", [&](const std::string& vehicle_name) -> FixedWingRpcLibAdaptors::ControlSurfaces {
        return FixedWingRpcLibAdaptors::ControlSurfaces(getVehicleApi(vehicle_name)->getControlSurfaces());
    });
}
