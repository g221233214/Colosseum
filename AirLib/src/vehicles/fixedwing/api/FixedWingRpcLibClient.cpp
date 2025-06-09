#include "vehicles/fixedwing/api/FixedWingRpcLibClient.hpp"
#include "vehicles/fixedwing/api/FixedWingRpcLibAdaptors.hpp"

using namespace msr::airlib;

FixedWingRpcLibClient::FixedWingRpcLibClient(const std::string& ip, uint16_t port, float timeout_sec)
    : MultirotorRpcLibClient(ip, port, timeout_sec)
{
}

void FixedWingRpcLibClient::setControlSurfaces(const FixedWingApi::ControlSurfaces& controls, const std::string& vehicle_name)
{
    static_cast<rpc::client*>(getClient())->call("setControlSurfaces", airlib_rpclib::FixedWingRpcLibAdaptors::ControlSurfaces(controls), vehicle_name);
}

FixedWingApi::ControlSurfaces FixedWingRpcLibClient::getControlSurfaces(const std::string& vehicle_name)
{
    return static_cast<rpc::client*>(getClient())->call("getControlSurfaces", vehicle_name).as<airlib_rpclib::FixedWingRpcLibAdaptors::ControlSurfaces>().to();
}
