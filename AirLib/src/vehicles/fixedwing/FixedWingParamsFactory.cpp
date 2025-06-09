#ifndef AIRLIB_HEADER_ONLY

#include "vehicles/fixedwing/FixedWingParams.hpp"
#include "common/Settings.hpp"
#include "common/Utils.hpp"

using namespace msr::airlib;

std::unique_ptr<FixedWingParams> FixedWingParamsFactory::createConfig(const AirSimSettings::VehicleSetting* vehicle_setting)
{
    unused(vehicle_setting);
    auto params = std::unique_ptr<FixedWingParams>(new FixedWingParams());

    const Settings& root = Settings::singleton();
    Settings vehicles;
    if (root.getChild("Vehicles", vehicles)) {
        Settings this_vehicle;
        if (vehicles.getChild(vehicle_setting->vehicle_name, this_vehicle)) {
            Settings pjson;
            if (this_vehicle.getChild("Parameters", pjson)) {
                params->mass = pjson.getFloat("Mass", params->mass);
                params->wing_area = pjson.getFloat("WingArea", params->wing_area);
                params->control_surface_limit_pitch = pjson.getFloat("PitchLimit", params->control_surface_limit_pitch);
                params->control_surface_limit_roll = pjson.getFloat("RollLimit", params->control_surface_limit_roll);
                params->control_surface_limit_yaw = pjson.getFloat("YawLimit", params->control_surface_limit_yaw);
                params->linear_drag_coefficient = pjson.getFloat("LinearDrag", params->linear_drag_coefficient);
                Settings inertia;
                if (pjson.getChild("Inertia", inertia)) {
                    params->inertia(0,0) = inertia.getFloat("Ixx", params->inertia(0,0));
                    params->inertia(1,1) = inertia.getFloat("Iyy", params->inertia(1,1));
                    params->inertia(2,2) = inertia.getFloat("Izz", params->inertia(2,2));
                }
            }
        }
    }

    return params;
}

#endif
