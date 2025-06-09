#pragma once

#include "vehicles/fixedwing/api/FixedWingApiBase.hpp"
#include "PawnSimApi.h"
#include "GameFramework/Pawn.h"
#include "FixedWingPawn.generated.h"

UCLASS()
class AIRSIM_API AFixedWingPawn : public APawn
{
    GENERATED_BODY()

public:
    AFixedWingPawn();
};

