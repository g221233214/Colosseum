#ifndef AIRLIB_HEADER_ONLY

#include "vehicles/fixedwing/FixedWingPhysicsBody.hpp"
#include "common/VectorMath.hpp"
#include "common/Utils.hpp"

using namespace msr::airlib;

void FixedWingPhysicsBody::AeroSurface::initialize(const Vector3r& position, const Vector3r& normal, real_T lift_factor,
                                                   const Kinematics* kinematics, const Environment* environment)
{
    PhysicsBodyVertex::initialize(position, normal);
    lift_factor_ = lift_factor;
    kinematics_ = kinematics;
    environment_ = environment;
}

void FixedWingPhysicsBody::AeroSurface::setWrench(Wrench& wrench)
{
    const Quaternionr& orientation = kinematics_->getPose().orientation;
    const Vector3r& linear_vel = kinematics_->getTwist().linear;
    const Vector3r& angular_vel = kinematics_->getTwist().angular;

    Vector3r vel_body = VectorMath::transformToBodyFrame(linear_vel, orientation);
    Vector3r vel_vertex = vel_body + angular_vel.cross(getPosition());
    real_T speed = vel_vertex.norm();
    if (Utils::isDefinitelyGreaterThan(speed, 0.1f)) {
        Vector3r lift_dir = getNormal().cross(vel_vertex).cross(vel_vertex);
        if (lift_dir.squaredNorm() > 0) {
            lift_dir.normalize();
            real_T air_density = environment_->getState().air_density;
            Vector3r force_body = lift_dir * (lift_factor_ * air_density * speed * speed);
            wrench.force = VectorMath::transformToWorldFrame(force_body, orientation);
            wrench.torque = getPosition().cross(force_body);
            return;
        }
    }
    wrench = Wrench::zero();
}

FixedWingPhysicsBody::FixedWingPhysicsBody(FixedWingParams* params, VehicleApiBase* vehicle_api,
                                           Kinematics* kinematics, Environment* environment)
    : params_(params), vehicle_api_(vehicle_api)
{
    setName("FixedWingPhysicsBody");
    vehicle_api_->setParent(this);
    initializeBody(kinematics, environment);
}

void FixedWingPhysicsBody::initializeBody(Kinematics* kinematics, Environment* environment)
{
    kinematics_ptr_ = kinematics;
    environment_ptr_ = environment;
    PhysicsBody::initialize(params_->mass, params_->inertia, kinematics, environment);
    createSurfaces();
}

void FixedWingPhysicsBody::createSurfaces()
{
    lift_surfaces_.clear();
    AeroSurface wing;
    wing.initialize(Vector3r::Zero(), Vector3r(0, 0, 1), params_->wing_area, kinematics_ptr_, environment_ptr_);
    lift_surfaces_.push_back(wing);

    drag_surfaces_.clear();
    drag_surfaces_.emplace_back(Vector3r::Zero(), Vector3r(1, 0, 0), params_->wing_area * params_->linear_drag_coefficient);
}

void FixedWingPhysicsBody::update()
{
    PhysicsBody::update();
    vehicle_api_->update();
}

real_T FixedWingPhysicsBody::getRestitution() const
{
    return params_->restitution;
}

real_T FixedWingPhysicsBody::getFriction() const
{
    return params_->friction;
}

uint FixedWingPhysicsBody::wrenchVertexCount() const
{
    return static_cast<uint>(lift_surfaces_.size());
}

PhysicsBodyVertex& FixedWingPhysicsBody::getWrenchVertex(uint index)
{
    return lift_surfaces_.at(index);
}

const PhysicsBodyVertex& FixedWingPhysicsBody::getWrenchVertex(uint index) const
{
    return lift_surfaces_.at(index);
}

uint FixedWingPhysicsBody::dragVertexCount() const
{
    return static_cast<uint>(drag_surfaces_.size());
}

PhysicsBodyVertex& FixedWingPhysicsBody::getDragVertex(uint index)
{
    return drag_surfaces_.at(index);
}

const PhysicsBodyVertex& FixedWingPhysicsBody::getDragVertex(uint index) const
{
    return drag_surfaces_.at(index);
}

#endif
