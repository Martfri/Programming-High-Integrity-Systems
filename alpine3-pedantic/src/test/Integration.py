import Voter1
import Voter2
import Voter3

global lastOutcome
lastOutcome = True

def Integration(s1, s2, s3) -> bool:
    global lastOutcome
    ConsideredValue = 0
    SensorValues = [s1, s2, s3]
    #print(SensorValues)
    Safestate = True
    Operational = False
    FlowControl = 0

    OutcomeVoter1 = Voter1.voter1(SensorValues)
    OutcomeVoter2 = Voter2.voter2(SensorValues)

    OutcomeVoter3 = Voter3.voter3(not OutcomeVoter1, not OutcomeVoter2)

    if OutcomeVoter3 == True:
        Safestate = True
        Operational = False
    else:
        Safestate = False
        Operational = True

    #print("Roboter is in Safestate: %s" %"True" if Safestate else "Roboter is in Safestate: False")
    #print("h")
    newOutcome = Safestate
    if newOutcome is not lastOutcome:
        Safestate = lastOutcome
    lastOutcome = newOutcome
    return Safestate
