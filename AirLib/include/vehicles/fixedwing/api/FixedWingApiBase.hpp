#ifndef msr_AirLib_FixedWingApiBase_hpp
#define msr_AirLib_FixedWingApiBase_hpp

#include "api/VehicleApiBase.hpp"
#include "sensors/SensorCollection.hpp"
#include "sensors/SensorFactory.hpp"

namespace msr {
namespace airlib {

class FixedWingApiBase : public VehicleApiBase
{
public:
    FixedWingApiBase(const AirSimSettings::VehicleSetting* vehicle_setting,
                     std::shared_ptr<SensorFactory> sensor_factory,
                     const Kinematics::State& state, const Environment& environment)
    {
        initialize(vehicle_setting, sensor_factory, state, environment);
    }

    virtual ~FixedWingApiBase() = default;

    virtual void update() override
    {
        VehicleApiBase::update();
        sensors_.update();
    }

    virtual const SensorCollection& getSensors() const override
    {
        return sensors_;
    }

    SensorCollection& getSensors()
    {
        return sensors_;
    }

    void initialize(const AirSimSettings::VehicleSetting* vehicle_setting,
                    std::shared_ptr<SensorFactory> sensor_factory,
                    const Kinematics::State& state, const Environment& environment)
    {
        sensor_factory_ = sensor_factory;
        sensor_storage_.clear();
        sensors_.clear();
        addSensorsFromSettings(vehicle_setting);
        sensors_.initialize(&state, &environment);
    }

    virtual void addSensorsFromSettings(const AirSimSettings::VehicleSetting* vehicle_setting)
    {
        const auto& sensor_settings = vehicle_setting->sensors;
        sensor_factory_->createSensorsFromSettings(sensor_settings, sensors_, sensor_storage_);
    }

protected:
    virtual void resetImplementation() override
    {
        sensors_.reset();
    }

    std::shared_ptr<const SensorFactory> sensor_factory_;
    SensorCollection sensors_;
    vector<shared_ptr<SensorBase>> sensor_storage_;
};

}} //namespace

#endif
