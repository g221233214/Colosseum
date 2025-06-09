#include "SimModeFixedWing.h"
#include "common/AirSimSettings.hpp"

void ASimModeFixedWing::BeginPlay()
{
    Super::BeginPlay();
}

bool ASimModeFixedWing::isVehicleTypeSupported(const std::string& vehicle_type) const
{
    return vehicle_type == AirSimSettings::kVehicleTypeFixedWing;
}
