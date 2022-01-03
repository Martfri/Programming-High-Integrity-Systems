from ctypes import *
import os
import sys

voterLibFile = os.getcwd()+'/phis.so'

class sensor_t(Structure):
    _fields_ = [("state", c_uint),
                   ("reading", c_uint8)]

Uint8Array4 = c_uint8 * 4
SensorArray3 = sensor_t * 3



def runVoterA(voterLib, sensor1, sensor2, sensor3) -> bool:
    sensorMsg = Uint8Array4(sensor1, sensor2, sensor3, 0)
    sensorReadings = SensorArray3()
    voterResult = c_bool()
    voterLib.evaluateSensors(sensorMsg, sensorReadings)
    voterLib.evaluateDistance_BlockA(sensorReadings, pointer(voterResult))
    if voterResult:
        return True
    else:
        return False

def testVoterA(voterLib, logFile) -> bool:
    expectedResult = True
    sensor1 = 100
    sensor2 = 100
    sensor3 = 200
    voterResult = runVoterA(voterLib, sensor1, sensor2, sensor3)
    if voterResult == expectedResult:
        return True
    else:
        logFile.write(f"Sensor values: ({sensor1}, {sensor1}, {sensor1}), Voter A returned {voterResult}, expected {expectedResult}\n")
        return False

def main() -> int:
    numFailedTests = 0
    numTests = 0
    voterLib = CDLL(voterLibFile)
    logFile = open("../results_test.txt", 'w')

    # unit test voter A
    print("Test voter A:")
    logFile.write("Failed Tests for voter A:\n")
    for _ in range(2):
        if testVoterA(voterLib, logFile):
            numTests = numTests + 1
        else:
            numFailedTests = numFailedTests + 1
            numTests = numTests + 1
    print(f"{numFailedTests} from {numTests} tests failed")
    logFile.write(f"{numFailedTests} from {numTests} tests failed\n\n")

    # unit test voter B

    # unit test voter 3

    # integration test

    if (numFailedTests == 0):
        print(f"Summary: All tests passed (With {numTests} tests in total)")
        logFile.write(f"Summary: All tests passed (With {numTests} tests in total)")
    else:
        print(f"Summary: {numFailedTests} from {numTests} tests failed")
        logFile.write(f"Summary: {numFailedTests} from {numTests} tests failed")
    return numFailedTests

if __name__ == "__main__":
    sys.exit(main())
