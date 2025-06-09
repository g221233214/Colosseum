#include "vehicles/fixedwing/api/FixedWingRpcLibClient.hpp"

using namespace msr::airlib;

FixedWingRpcLibClient::FixedWingRpcLibClient(const std::string& ip, uint16_t port, float timeout_sec)
    : MultirotorRpcLibClient(ip, port, timeout_sec)
{
}
