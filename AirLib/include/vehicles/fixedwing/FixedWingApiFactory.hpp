#ifndef msr_airlib_vehicles_FixedWingApiFactory_hpp
#define msr_airlib_vehicles_FixedWingApiFactory_hpp

#include "FixedWingApiBase.hpp"

namespace msr {
namespace airlib {

class FixedWingApiFactory
{
public:
    static std::unique_ptr<FixedWingApiBase> createApi(const AirSimSettings::VehicleSetting* vehicle_setting,
                                                       std::shared_ptr<SensorFactory> sensor_factory,
                                                       const Kinematics::State& state, const Environment& environment)
    {
        return std::unique_ptr<FixedWingApiBase>(new FixedWingApiBase(vehicle_setting, sensor_factory, state, environment));
    }
};

}} //namespace

#endif
