#ifndef msr_AirLib_FixedWingRpcLibServer_hpp
#define msr_AirLib_FixedWingRpcLibServer_hpp

#include "vehicles/multirotor/api/MultirotorRpcLibServer.hpp"

namespace msr {
namespace airlib {

class FixedWingRpcLibServer : public MultirotorRpcLibServer
{
public:
    FixedWingRpcLibServer(ApiProvider* api_provider, const string& ip_address="", uint16_t port=41451)
        : MultirotorRpcLibServer(api_provider, ip_address, port)
    {
    }
};

}} //namespace

#endif
