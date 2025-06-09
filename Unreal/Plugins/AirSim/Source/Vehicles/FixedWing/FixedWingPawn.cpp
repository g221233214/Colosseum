#include "FixedWingPawn.h"
#include "AirBlueprintLib.h"
#include "Components/ChildActorComponent.h"

AFixedWingPawn::AFixedWingPawn()
{
    camera_front_center_ = nullptr;
}

void AFixedWingPawn::BeginPlay()
{
    Super::BeginPlay();
}

void AFixedWingPawn::initializeForBeginPlay()
{
    camera_front_center_ = Cast<APIPCamera>(
        (UAirBlueprintLib::GetActorComponent<UChildActorComponent>(this, TEXT("FrontCenterCamera")))->GetChildActor());
}

const common_utils::UniqueValueMap<std::string, APIPCamera*> AFixedWingPawn::getCameras() const
{
    common_utils::UniqueValueMap<std::string, APIPCamera*> cameras;
    cameras.insert_or_assign("front_center", camera_front_center_);
    cameras.insert_or_assign("0", camera_front_center_);
    cameras.insert_or_assign("fpv", camera_front_center_);
    cameras.insert_or_assign("", camera_front_center_);
    return cameras;
}

void AFixedWingPawn::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    pawn_events_.getPawnTickSignal().emit(DeltaSeconds);
}

void AFixedWingPawn::NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp,
                               bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse,
                               const FHitResult& Hit)
{
    pawn_events_.getCollisionSignal().emit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
}

