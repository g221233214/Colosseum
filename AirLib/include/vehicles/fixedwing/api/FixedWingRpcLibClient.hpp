#ifndef msr_AirLib_FixedWingRpcLibClient_hpp
#define msr_AirLib_FixedWingRpcLibClient_hpp

#include "rpc/client.h"
#include "vehicles/multirotor/api/MultirotorRpcLibClient.hpp"
#include "vehicles/fixedwing/api/FixedWingApi.hpp"
#include "vehicles/fixedwing/api/FixedWingRpcLibAdaptors.hpp"

namespace msr {
namespace airlib {

class FixedWingRpcLibClient : public MultirotorRpcLibClient
{
public:
    FixedWingRpcLibClient(const std::string& ip="", uint16_t port=41451, float timeout_sec=3600)
        : MultirotorRpcLibClient(ip, port, timeout_sec)
    {
    }

    void setControlSurfaces(const FixedWingApi::ControlSurfaces& controls, const std::string& vehicle_name="");
    FixedWingApi::ControlSurfaces getControlSurfaces(const std::string& vehicle_name="");
};

}} //namespace

#endif
