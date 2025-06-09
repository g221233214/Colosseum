#pragma once

#include "CoreMinimal.h"

#include "PawnSimApi.h"
#include "vehicles/fixedwing/FixedWingPhysicsBody.hpp"
#include "vehicles/fixedwing/FixedWingParams.hpp"
#include "vehicles/fixedwing/FixedWingApiFactory.hpp"
#include "vehicles/fixedwing/api/FixedWingApi.hpp"

class FixedWingPawnSimApi : public PawnSimApi
{
public:
    typedef msr::airlib::Utils Utils;
    typedef msr::airlib::StateReporter StateReporter;
    typedef msr::airlib::UpdatableObject UpdatableObject;
    typedef msr::airlib::Pose Pose;

public:
    FixedWingPawnSimApi(const Params& params);
    virtual void initialize() override;
    virtual ~FixedWingPawnSimApi() = default;

    virtual void updateRenderedState(float dt) override;
    virtual void updateRendering(float dt) override;

    virtual void resetImplementation() override;
    virtual void update() override;
    virtual void reportState(StateReporter& reporter) override;
    virtual UpdatableObject* getPhysicsBody() override;

    msr::airlib::FixedWingApi* getVehicleApi() const { return vehicle_api_.get(); }
    virtual msr::airlib::VehicleApiBase* getVehicleApiBase() const override { return vehicle_api_.get(); }

private:
    std::unique_ptr<msr::airlib::FixedWingApi> vehicle_api_;
    std::unique_ptr<msr::airlib::FixedWingParams> vehicle_params_;
    std::unique_ptr<msr::airlib::FixedWingPhysicsBody> physics_body_;

    msr::airlib::Pose last_phys_pose_;
};

