

def voter1(SensorValues):
    if isOperational(SensorValues) == True:
        diff1 = abs(SensorValues[0] - SensorValues[1])
        diff2 = abs(SensorValues[1] - SensorValues[2])
        diff3 = abs(SensorValues[0] - SensorValues[2])

        if 0.2 >= diff1 and 0.2 >= diff2 and 0.2 >= diff3:
            Value = (SensorValues[0] + SensorValues[1] + SensorValues[2])/3
            #print("Voter1: Sensor values match and are operational")
            return True

        else:
            #print("Voter1: Sensor threshold is greater than allowed.\n")
             #If any diff is more than 2 means at least one of the sensors is faulty
            return False

    else:
        #print("Voter1: Sensors are not operational")
        return False



def isOperational(sensorvalues):
    for i in range(3):
        if sensorvalues[i] == 0 or sensorvalues[i] == 2:
            #print("Voter1: at least one faulty sensor detected")
            return False
        elif 4 <= sensorvalues[i] <= 18.4:
            continue
        else:
            #print("Voter1: at least one sensor detected object in unsafe distance")
            return False
    return True
