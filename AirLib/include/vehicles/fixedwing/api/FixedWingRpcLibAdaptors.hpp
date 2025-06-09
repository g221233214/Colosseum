#ifndef msr_AirLib_FixedWingRpcLibAdaptors_hpp
#define msr_AirLib_FixedWingRpcLibAdaptors_hpp

#include "api/RpcLibAdaptorsBase.hpp"
#include "vehicles/fixedwing/api/FixedWingApi.hpp"
#include "common/common_utils/WindowsApisCommonPre.hpp"
#include "rpc/msgpack.hpp"
#include "common/common_utils/WindowsApisCommonPost.hpp"

namespace msr {
namespace airlib_rpclib {

class FixedWingRpcLibAdaptors : public RpcLibAdaptorsBase
{
public:
    struct ControlSurfaces
    {
        float pitch = 0;
        float roll = 0;
        float yaw = 0;
        float throttle = 0;

        MSGPACK_DEFINE_ARRAY(pitch, roll, yaw, throttle);

        ControlSurfaces() {}
        ControlSurfaces(const msr::airlib::FixedWingApi::ControlSurfaces& s)
        {
            pitch = s.pitch;
            roll = s.roll;
            yaw = s.yaw;
            throttle = s.throttle;
        }
        msr::airlib::FixedWingApi::ControlSurfaces to() const
        {
            msr::airlib::FixedWingApi::ControlSurfaces s;
            s.pitch = pitch;
            s.roll = roll;
            s.yaw = yaw;
            s.throttle = throttle;
            return s;
        }
    };
};

}} //namespace

#endif
