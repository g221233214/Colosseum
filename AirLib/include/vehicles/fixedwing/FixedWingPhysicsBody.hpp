#ifndef msr_airlib_fixedwingphysicsbody_hpp
#define msr_airlib_fixedwingphysicsbody_hpp

#include "common/Common.hpp"
#include "common/CommonStructs.hpp"
#include "physics/PhysicsBody.hpp"
#include "FixedWingParams.hpp"
#include "api/VehicleApiBase.hpp"
#include <vector>

namespace msr {
namespace airlib {

class FixedWingPhysicsBody : public PhysicsBody
{
public:
    FixedWingPhysicsBody(FixedWingParams* params, VehicleApiBase* vehicle_api,
                         Kinematics* kinematics, Environment* environment);

    virtual void update() override;
    virtual real_T getRestitution() const override;
    virtual real_T getFriction() const override;

    virtual uint wrenchVertexCount() const override;
    virtual PhysicsBodyVertex& getWrenchVertex(uint index) override;
    virtual const PhysicsBodyVertex& getWrenchVertex(uint index) const override;

    virtual uint dragVertexCount() const override;
    virtual PhysicsBodyVertex& getDragVertex(uint index) override;
    virtual const PhysicsBodyVertex& getDragVertex(uint index) const override;

    virtual ~FixedWingPhysicsBody() = default;

private:
    class AeroSurface : public PhysicsBodyVertex
    {
    public:
        void initialize(const Vector3r& position, const Vector3r& normal, real_T lift_factor,
                        const Kinematics* kinematics, const Environment* environment);
    protected:
        virtual void setWrench(Wrench& wrench) override;
    private:
        real_T lift_factor_ = 0;
        const Kinematics* kinematics_ = nullptr;
        const Environment* environment_ = nullptr;
    };

    void initializeBody(Kinematics* kinematics, Environment* environment);
    void createSurfaces();

private:
    FixedWingParams* params_;
    VehicleApiBase* vehicle_api_;
    Kinematics* kinematics_ptr_ = nullptr;
    Environment* environment_ptr_ = nullptr;
    std::vector<AeroSurface> lift_surfaces_;
    std::vector<PhysicsBodyVertex> drag_surfaces_;
};

}} //namespace

#endif
