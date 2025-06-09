#include "FixedWingPawnSimApi.h"
#include "AirBlueprintLib.h"
#include "UnrealSensors/UnrealSensorFactory.h"
#include <exception>

using namespace msr::airlib;

FixedWingPawnSimApi::FixedWingPawnSimApi(const Params& params)
    : PawnSimApi(params)
{
}

void FixedWingPawnSimApi::initialize()
{
    PawnSimApi::initialize();

    std::shared_ptr<UnrealSensorFactory> sensor_factory = std::make_shared<UnrealSensorFactory>(getPawn(), &getNedTransform());
    vehicle_params_ = FixedWingParamsFactory::createConfig(getVehicleSetting());
    auto api_base = FixedWingApiFactory::createApi(getVehicleSetting(), sensor_factory, *getGroundTruthKinematics(), *getGroundTruthEnvironment());
    vehicle_api_.reset(static_cast<FixedWingApi*>(api_base.release()));

    physics_body_ = std::unique_ptr<FixedWingPhysicsBody>(new FixedWingPhysicsBody(vehicle_params_.get(), vehicle_api_.get(), getKinematics(), getEnvironment()));

    vehicle_api_->setSimulatedGroundTruth(getGroundTruthKinematics(), getGroundTruthEnvironment());

    last_phys_pose_ = Pose::nanPose();
}

void FixedWingPawnSimApi::updateRenderedState(float dt)
{
    PawnSimApi::updateRenderedState(dt);

    const CollisionInfo& collision_info = getCollisionInfo();
    physics_body_->setCollisionInfo(collision_info);

    last_phys_pose_ = physics_body_->getPose();
}

void FixedWingPawnSimApi::updateRendering(float dt)
{
    PawnSimApi::updateRendering(dt);

    if (!VectorMath::hasNan(last_phys_pose_))
        PawnSimApi::setPose(last_phys_pose_, false);

    try {
        vehicle_api_->sendTelemetry(dt);
    }
    catch (std::exception& e) {
        UAirBlueprintLib::LogMessage(FString(e.what()), TEXT(""), LogDebugLevel::Failure, 30);
    }
}

void FixedWingPawnSimApi::resetImplementation()
{
    PawnSimApi::resetImplementation();

    vehicle_api_->reset();
    physics_body_->reset();
}

void FixedWingPawnSimApi::update()
{
    PawnSimApi::update();

    physics_body_->update();
}

void FixedWingPawnSimApi::reportState(StateReporter& reporter)
{
    PawnSimApi::reportState(reporter);

    physics_body_->reportState(reporter);
}

FixedWingPawnSimApi::UpdatableObject* FixedWingPawnSimApi::getPhysicsBody()
{
    return physics_body_->getPhysicsBody();
}

