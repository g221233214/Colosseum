#pragma once

#include "vehicles/fixedwing/api/FixedWingApiBase.hpp"
#include "PawnEvents.h"
#include "PawnSimApi.h"
#include "PIPCamera.h"
#include "GameFramework/Pawn.h"
#include "common/common_utils/UniqueValueMap.hpp"
#include "FixedWingPawn.generated.h"

UCLASS()
class AIRSIM_API AFixedWingPawn : public APawn
{
    GENERATED_BODY()

public:
    AFixedWingPawn();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
    virtual void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp,
                           bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse,
                           const FHitResult& Hit) override;

    void initializeForBeginPlay();
    const common_utils::UniqueValueMap<std::string, APIPCamera*> getCameras() const;
    PawnEvents* getPawnEvents() { return &pawn_events_; }

private:
    UPROPERTY()
    APIPCamera* camera_front_center_;

    PawnEvents pawn_events_;
};

