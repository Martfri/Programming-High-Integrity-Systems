Implementation of a safety system for a robot. The safety system puts the robot in a crouching position (safety position) if a person approaches the robot. Sensor values to measure the proximity are simulated with the help of a random number generator.


# Requirements

SF1: If a person is in proximity (2m), the robot shall go into the safe state
R1.2: The sensors give as an output a current value between 0 mA and 20 mA
R1.3: The sensor has the following input to output characteristics, which is linear:
R1.4: If the sensor has a failure, it outputs a value between 0 mA and 4 mA (excluding 4 mA)
R1.7: The sensor output values must be refreshed every 100 ms
R2.0: The logic part consists of 2 independent voters A and B
R2.1: Both voter A and B implement following 1oo3 behaviour:
If any sensor returns a current smaller than 4 mA (< 4 mA) or greater than 18.4 mA (> 18.4 mA) return isDistanceSafe = False (0)
If any 2 sensor current values differ by more than 0.2 mA (> 0.2 mA) return isDistanceSafe = False (0)
Otherwise return isDistanceSafe = True (1)
R2.4: If any of voter A or B returns isDistanceSafe = False (0), Stage2Voter shall return enterSafeState = True(1), otherwise it shall return enterSafeState = False(0). 0 means the system stays operational, 1 means go to safe state
R2.5: The system shall have a single outlier filter, to smooth the output behavior




# Architecture

![image](https://github.com/Martfri/Programming-High-Integrity-Systems/assets/73395595/cdeac87b-b747-4ba5-9a53-47d73ca665c3)

