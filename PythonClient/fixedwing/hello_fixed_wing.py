import setup_path
import airsim
import pprint
import os
import tempfile

client = airsim.FixedWingClient()
client.confirmConnection()
client.enableApiControl(True)

state = client.getMultirotorState()
print("state: %s" % pprint.pformat(state))

airsim.wait_key('Press any key to takeoff')
client.takeoffAsync().join()

airsim.wait_key('Press any key to control surfaces and capture image')
client.setControlSurfaces(airsim.FixedWingControls(pitch=-0.2, throttle=0.6))
print('Controls:', client.getControlSurfaces())

responses = client.simGetImages([
    airsim.ImageRequest("0", airsim.ImageType.Scene),
    airsim.ImageRequest("0", airsim.ImageType.DepthVis)
])
tmp_dir = os.path.join(tempfile.gettempdir(), "airsim_fixedwing")
os.makedirs(tmp_dir, exist_ok=True)
for idx, response in enumerate(responses):
    if response.pixels_as_float:
        airsim.write_pfm(os.path.join(tmp_dir, f"{idx}.pfm"), airsim.get_pfm_array(response))
    else:
        airsim.write_file(os.path.join(tmp_dir, f"{idx}.png"), response.image_data_uint8)

airsim.wait_key('Press any key to land')
client.landAsync().join()

client.enableApiControl(False)
