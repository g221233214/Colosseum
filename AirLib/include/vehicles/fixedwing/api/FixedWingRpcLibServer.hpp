#ifndef msr_AirLib_FixedWingRpcLibServer_hpp
#define msr_AirLib_FixedWingRpcLibServer_hpp

#include "vehicles/multirotor/api/MultirotorRpcLibServer.hpp"
#include "vehicles/fixedwing/api/FixedWingApi.hpp"
#include "vehicles/fixedwing/api/FixedWingRpcLibAdaptors.hpp"

namespace msr {
namespace airlib {

class FixedWingRpcLibServer : public MultirotorRpcLibServer
{
public:
    FixedWingRpcLibServer(ApiProvider* api_provider, const string& ip_address="", uint16_t port=41451)
        : MultirotorRpcLibServer(api_provider, ip_address, port)
    {
    }

protected:
    virtual FixedWingApi* getVehicleApi(const std::string& vehicle_name) override
    {
        return static_cast<FixedWingApi*>(RpcLibServerBase::getVehicleApi(vehicle_name));
    }
};

}} //namespace

#endif
