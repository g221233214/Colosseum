#include "vehicles/fixedwing/api/FixedWingApi.hpp"
#include "common/VectorMath.hpp"

using namespace msr::airlib;

FixedWingApi::FixedWingApi(const AirSimSettings::VehicleSetting* vehicle_setting,
                           std::shared_ptr<SensorFactory> sensor_factory,
                           const Kinematics::State& state, const Environment& environment)
    : FixedWingApiBase(vehicle_setting, sensor_factory, state, environment)
{
    pitch_pid_.setPoint(0, 0.5f, 0.0f, 0.05f);
    roll_pid_.setPoint(0, 0.5f, 0.0f, 0.05f);
    yaw_pid_.setPoint(0, 0.5f, 0.0f, 0.05f);
    throttle_pid_.setPoint(0, 1.0f, 0.0f, 0.0f);
}

void FixedWingApi::setControlSurfaces(const ControlSurfaces& controls)
{
    target_controls_ = controls;
    pitch_pid_.setPoint(controls.pitch, 0.5f, 0.0f, 0.05f);
    roll_pid_.setPoint(controls.roll, 0.5f, 0.0f, 0.05f);
    yaw_pid_.setPoint(controls.yaw, 0.5f, 0.0f, 0.05f);
    throttle_pid_.setPoint(controls.throttle, 1.0f, 0.0f, 0.0f);
}

FixedWingApi::ControlSurfaces FixedWingApi::getControlSurfaces() const
{
    return current_controls_;
}

void FixedWingApi::update()
{
    FixedWingApiBase::update();

    auto* body = static_cast<PhysicsBody*>(getParent());
    if (body == nullptr)
        return;

    const auto& kin = body->getKinematics();
    float pitch, roll, yaw;
    VectorMath::toEulerianAngle(kin.pose.orientation, pitch, roll, yaw);
    Vector3r vel_body = VectorMath::transformToBodyFrame(kin.twist.linear, kin.pose.orientation);

    current_controls_.pitch = pitch_pid_.control(pitch);
    current_controls_.roll = roll_pid_.control(roll);
    current_controls_.yaw = yaw_pid_.control(yaw);
    current_controls_.throttle = throttle_pid_.control(vel_body.x());

    Wrench wrench = body->getWrench();
    wrench.torque += Vector3r(current_controls_.roll, current_controls_.pitch, current_controls_.yaw);
    wrench.force += VectorMath::transformToWorldFrame(Vector3r(current_controls_.throttle, 0, 0), kin.pose.orientation);
    body->setWrench(wrench);
}

