#ifndef msr_airlib_fixedwingparams_hpp
#define msr_airlib_fixedwingparams_hpp

#include "common/Common.hpp"
#include "common/CommonStructs.hpp"
#include "common/AirSimSettings.hpp"
#include <memory>

namespace msr {
namespace airlib {

struct FixedWingParams
{
    real_T mass = 1.0f;
    Matrix3x3r inertia = Matrix3x3r::Identity();
    real_T wing_area = 1.0f;
    real_T control_surface_limit_pitch = 20.0f; // degrees
    real_T control_surface_limit_roll = 20.0f;  // degrees
    real_T control_surface_limit_yaw = 20.0f;   // degrees
    real_T linear_drag_coefficient = 1.0f;
    real_T restitution = 0.1f;
    real_T friction = 0.5f;
};

class FixedWingParamsFactory
{
public:
    static std::unique_ptr<FixedWingParams> createConfig(const AirSimSettings::VehicleSetting* vehicle_setting);
};

}} //namespace

#endif
