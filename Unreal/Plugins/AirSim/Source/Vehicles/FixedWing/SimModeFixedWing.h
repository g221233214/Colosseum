#pragma once

#include "SimMode/SimModeBase.h"
#include "FixedWingPawn.h"
#include "SimModeFixedWing.generated.h"

UCLASS()
class AIRSIM_API ASimModeFixedWing : public ASimModeBase
{
    GENERATED_BODY()
public:
    virtual void BeginPlay() override;
protected:
    virtual bool isVehicleTypeSupported(const std::string& vehicle_type) const override;
};
