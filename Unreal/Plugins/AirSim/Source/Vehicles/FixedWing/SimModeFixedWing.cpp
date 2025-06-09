#include "SimModeFixedWing.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "AirBlueprintLib.h"
#include "common/AirSimSettings.hpp"
#include "FixedWingPawnSimApi.h"
#include "vehicles/fixedwing/api/FixedWingRpcLibServer.hpp"

void ASimModeFixedWing::BeginPlay()
{
    Super::BeginPlay();
}

std::unique_ptr<msr::airlib::ApiServerBase> ASimModeFixedWing::createApiServer() const
{
#ifdef AIRLIB_NO_RPC
    return ASimModeBase::createApiServer();
#else
    return std::unique_ptr<msr::airlib::ApiServerBase>(new msr::airlib::FixedWingRpcLibServer(
        getApiProvider(), getSettings().api_server_address, getSettings().api_port));
#endif
}

void ASimModeFixedWing::getExistingVehiclePawns(TArray<AActor*>& pawns) const
{
    UAirBlueprintLib::FindAllActor<AFixedWingPawn>(this, pawns);
}

bool ASimModeFixedWing::isVehicleTypeSupported(const std::string& vehicle_type) const
{
    return vehicle_type == AirSimSettings::kVehicleTypeFixedWing;
}

std::string ASimModeFixedWing::getVehiclePawnPathName(const AirSimSettings::VehicleSetting& vehicle_setting) const
{
    std::string pawn_path = vehicle_setting.pawn_path;
    if (pawn_path == "")
        pawn_path = "DefaultFixedWing";
    return pawn_path;
}

PawnEvents* ASimModeFixedWing::getVehiclePawnEvents(APawn* pawn) const
{
    return static_cast<AFixedWingPawn*>(pawn)->getPawnEvents();
}

const common_utils::UniqueValueMap<std::string, APIPCamera*> ASimModeFixedWing::getVehiclePawnCameras(APawn* pawn) const
{
    return static_cast<const AFixedWingPawn*>(pawn)->getCameras();
}

void ASimModeFixedWing::initializeVehiclePawn(APawn* pawn)
{
    static_cast<AFixedWingPawn*>(pawn)->initializeForBeginPlay();
}

std::unique_ptr<PawnSimApi> ASimModeFixedWing::createVehicleSimApi(const PawnSimApi::Params& pawn_sim_api_params) const
{
    auto vehicle_sim_api = std::unique_ptr<PawnSimApi>(new FixedWingPawnSimApi(pawn_sim_api_params));
    vehicle_sim_api->initialize();
    vehicle_sim_api->reset();
    return vehicle_sim_api;
}

msr::airlib::VehicleApiBase* ASimModeFixedWing::getVehicleApi(const PawnSimApi::Params& pawn_sim_api_params,
                                                              const PawnSimApi* sim_api) const
{
    const auto fixed_sim_api = static_cast<const FixedWingPawnSimApi*>(sim_api);
    return fixed_sim_api->getVehicleApi();
}

