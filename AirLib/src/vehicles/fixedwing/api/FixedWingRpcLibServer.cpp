#include "vehicles/fixedwing/api/FixedWingRpcLibServer.hpp"

using namespace msr::airlib;

FixedWingRpcLibServer::FixedWingRpcLibServer(ApiProvider* api_provider, const string& ip_address, uint16_t port)
    : MultirotorRpcLibServer(api_provider, ip_address, port)
{
}
