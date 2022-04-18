#This code was adapted from LeapMotion test code
#Code is written by Gregory Osha
import Leap, sys, thread, time, math, cmath, serial

#These are the lengths of each arm segment in mm, and the coordinates of the base
ArmBicep = 139.7
ArmForearm = 177.8
ClawBase_x = 0
ClawBase_y = 200
ClawBase_z = 0


#Connecting to the arduino
port = 'COM4'
arduinoData = serial.Serial(port, 9600, timeout=5)
time.sleep(2)

class LeapMotionListener(Leap.Listener):

    finger_names = ['Thumb', 'Index', 'Middle', 'Ring', 'Pinky']
    bone_names = ['Metacarpal', 'Proximal', 'Intermediate', 'Distal']

    def on_init(self, controller):
        print ("Initialized")

    def on_connect(self, controller):
        print ("Leap motion connected")


    def on_disconnect(self, controller):
        # Note: not dispatched when running in a debugger.
        print  ("Leap motion disconnected")

    def on_exit(self, controller):
        print ("Exited")

    #This code runs on every frame a hand is detected
    def on_frame(self, controller):

        # Get the most recent frame and report some basic information
        frame = controller.frame()
        #Frame object that is sent from leap motion

        indexTipPos = frame.finger

        for hand in frame.hands:
            #Stores the x, y, z coordinates for the tip of the index
            #finger_type returns list with only specified types: Finger types (thumb = 0, index = 1, etc)
            #joint_positions: (0 = knuckle, 1 = middle joint, 2 = farther joint, 3 = tip)
            indexTipPos = hand.fingers.finger_type(1)[0].joint_position(3)
            thumbTipPos = hand.fingers.finger_type(0)[0].joint_position(3)

            ServoAngles = angleAdjust(findAngles(indexTipPos, thumbTipPos))
            ServoNames = ["clawAngle", "elbowAngle", "shoulderAngle", "baseAngle"]
            angleEnd = ['c', 'e', 's', 'b']
            index = 0

            print("Python Values:")
            for i in ServoAngles:
                 i = i + angleEnd[index]

                 print(ServoNames[index] + ": " + i)
                 arduinoData.write(i)
                 time.sleep(0.07)
                 index += 1

            #arduinoData.flush()

                #print("Python value: ")
                #print(ard_RotateA + ";")
                #arduinoData.write(ard_RotateA + ";")
                #time.sleep(0.1)


            msg = arduinoData.read(arduinoData.inWaiting())
            print ("\nMessage from arduino: ")
            print (msg)

def findAngles(index, thumb):

    #LENGTHS:

    # Finding bottom distance to end of claw
    flatDistance = math.sqrt(math.pow(thumb.x - ClawBase_x, 2) + math.pow(thumb.z - ClawBase_z, 2))

    # 3D distance to claw end
    # Uses flat distance as base and difference between claw base and claw height
    tipDistance = math.sqrt(math.pow(flatDistance, 2) + math.pow(thumb.y - ClawBase_y, 2))

    # Finger distance in 3D space
    fingerDistance = math.sqrt(
        math.pow(thumb.x - index.x, 2) + math.pow(thumb.y - index.y, 2) + math.pow(thumb.z - index.z, 2))

    #ANGLES:
    # acos function prints out in radians to conversion to degrees is necessary
    # Calculations within the triangle of ArmForearm, ArmBicep, and Tip_distance

    elbowAngle = math.degrees(math.acos(
        (math.pow(ArmForearm, 2) + math.pow(ArmBicep, 2) - math.pow(tipDistance, 2)) / (2 * ArmForearm * ArmBicep)))

    #Upper shoulder angle
    upperShoulderAngle = math.acos(
        (math.pow(ArmBicep, 2) + math.pow(tipDistance, 2) - math.pow(ArmForearm, 2)) / (2 * ArmBicep * tipDistance))
    #Lower shoulder angle
    lowerShoulderAngle = math.atan((thumb.y - ClawBase_y) / flatDistance)
    #Combined angle for shoulder
    shoulderAngle = math.degrees(lowerShoulderAngle + upperShoulderAngle)

    #Base rotation
    baseRotateAngle = math.degrees(math.atan((thumb.x - ClawBase_x) / (thumb.z - ClawBase_z)))

    angles = [fingerDistance, elbowAngle, shoulderAngle, baseRotateAngle]
    return angles

def angleAdjust(angles):
    if (angles[0] < 35):
         clawAngle = 30
    else:
         clawAngle = angles[0]
    elbowAngle = (180 - angles[1]) + 45
    shoulderAngle = angles[2]
    baseAngle = (-1 * angles[3]) + 90

    servoAngles = [str(int(clawAngle)), str(int(elbowAngle)), str(int(shoulderAngle)), str(int(baseAngle))]
    return servoAngles

#def arduinoWriteAngles(servoAngles)

def main():
    # Create a sample listener and controller
    listener = LeapMotionListener()
    controller = Leap.Controller()

    # Have the sample listener receive events from the controller
    controller.add_listener(listener)
    #Need to find thumb distal end and index finger distal end

    # Keep this process running until Enter is pressed
    print "Press Enter to quit..."
    try:
        sys.stdin.readline()
    except KeyboardInterrupt:
        pass
    finally:
        # Remove the sample listener when done
        controller.remove_listener(listener)
        #Resets the arm when finished
        arduinoData.write("90c45e90s90b")





if __name__ == "__main__":
    main()
