import setup_path
import airsim
import pprint

client = airsim.FixedWingClient()
client.confirmConnection()
client.enableApiControl(True)

state = client.getMultirotorState()
print("state: %s" % pprint.pformat(state))

airsim.wait_key('Press any key to takeoff')
client.takeoffAsync().join()

airsim.wait_key('Press any key to land')
client.landAsync().join()

client.enableApiControl(False)
