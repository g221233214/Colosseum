#ifndef msr_AirLib_FixedWingApi_hpp
#define msr_AirLib_FixedWingApi_hpp

#include "vehicles/fixedwing/api/FixedWingApiBase.hpp"
#include "common/PidController.hpp"
#include "physics/PhysicsBody.hpp"

namespace msr {
namespace airlib {

class FixedWingApi : public FixedWingApiBase
{
public:
    struct ControlSurfaces
    {
        float pitch = 0; // desired pitch angle in radians
        float roll = 0;  // desired roll angle in radians
        float yaw = 0;   // desired yaw angle in radians
        float throttle = 0; // desired forward speed
    };

public:
    FixedWingApi(const AirSimSettings::VehicleSetting* vehicle_setting,
                 std::shared_ptr<SensorFactory> sensor_factory,
                 const Kinematics::State& state, const Environment& environment);

    virtual void update() override;

    void setControlSurfaces(const ControlSurfaces& controls);
    ControlSurfaces getControlSurfaces() const;

protected:
    ControlSurfaces target_controls_;
    ControlSurfaces current_controls_;

    PidController pitch_pid_;
    PidController roll_pid_;
    PidController yaw_pid_;
    PidController throttle_pid_;
};

}} //namespace

#endif
