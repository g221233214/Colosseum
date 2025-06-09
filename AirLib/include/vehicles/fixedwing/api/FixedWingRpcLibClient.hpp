#ifndef msr_AirLib_FixedWingRpcLibClient_hpp
#define msr_AirLib_FixedWingRpcLibClient_hpp

#include "rpc/client.h"
#include "vehicles/multirotor/api/MultirotorRpcLibClient.hpp"

namespace msr {
namespace airlib {

class FixedWingRpcLibClient : public MultirotorRpcLibClient
{
public:
    FixedWingRpcLibClient(const std::string& ip="", uint16_t port=41451, float timeout_sec=3600)
        : MultirotorRpcLibClient(ip, port, timeout_sec)
    {
    }
};

}} //namespace

#endif
