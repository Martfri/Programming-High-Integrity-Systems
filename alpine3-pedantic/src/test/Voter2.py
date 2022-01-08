

def voter2(SensorValues):
    if isSafeRange(SensorValues) == True:
        diff1 = abs(SensorValues[0] - SensorValues[1])
        diff2 = abs(SensorValues[1] - SensorValues[2])
        diff3 = abs(SensorValues[0] - SensorValues[2])

        if 2 < diff1 or 2 < diff2 or 2 < diff3:
            #Value = (SensorValues[0] + SensorValues[1] + SensorValues[2])/3
            #print("Voter2: Sensor values match and are operational")
            return True

        else:
            #print("Voter2: Sensor threshold is greater than allowed.\n")
             #If any diff is more than 2 means at least one of the sensors is faulty
            return False

    else:
        #print("Voter2: Sensors are not operational")
        return True



def isSafeRange(sensorvalues):
    for i in range(3):
        if 40 <= sensorvalues[i] <= 184:
            #print("Voter2: at least one faulty sensor detected")
            continue
        else:
            #print("Voter2: at least one sensor detected object in unsafe distance")
            return False
    return True
