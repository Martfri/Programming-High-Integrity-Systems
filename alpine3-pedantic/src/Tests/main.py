import Voter1
import Voter2
import Voter3
import sys
import RandomNumberGenerator


def main():
    ConsideredValue = 0 
    SensorValues = RandomNumberGenerator.RandNum()
    SensorValues = [float(sys.argv[1]), float(sys.argv[2]), float(sys.argv[3])]
    print(SensorValues)
    Safestate = True
    Operational = False
    FlowControl = 0 

    OutcomeVoter1 = Voter1.voter1(SensorValues)
    OutcomeVoter2 = Voter2.voter2(SensorValues)

    OutcomeVoter3 = Voter3.voter3(OutcomeVoter1, OutcomeVoter2)

    if OutcomeVoter3 == True:
        Safestate = True
        Operational = False
    else:
        Safestate = False
        Operational = True

    print("Roboter is in Safestate: %s" %"True" if Safestate else "Roboter is in Safestate: False")
    print("h")

    return 0


main()






