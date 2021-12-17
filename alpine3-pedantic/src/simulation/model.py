import random
import socket
import numpy as np

class Model:
    def __init__(self):
        self._distance = 0
        self._tolerance = 0.1
        self.sensor_auto = [True, True, True]
        self.sensor_error = [False, False, False]
        self._sensor_distance = [10, 10, 10]
        self._sensor_current = [0, 0, 0]
        pass

    def distance():
        doc = "The distance property."
        def fget(self):
            return self._distance
        def fset(self, value):
            if value > 30:
                self._distance = 30
            elif value < 0:
                self._distance = 0
            else:
                self._distance = value
        def fdel(self):
            del self._distance
        return locals()
    distance = property(**distance())

    def tolerance():
        doc = "The tolerance property."
        def fget(self):
            return self._tolerance
        def fset(self, value):
            if value > 10:
                self._tolerance = 10
            elif value < 0:
                self._tolerance = 0
            else:
                self._tolerance = value
        def fdel(self):
            del self._tolerance
        return locals()
    tolerance = property(**tolerance())


    def sensor_distance():
        doc = "The sensor_distance property."
        def fget(self):
            return self._sensor_distance
        def fset(self, value):
            for i in range(len(value)):
                if value[i] > 30:
                    self._sensor_distance[i] = 30
                elif value[i] < 0:
                    self._sensor_distance[i] = 0
                else:
                    self._sensor_distance[i] = value[i]
        def fdel(self):
            del self._sensor_distance
        return locals()
    sensor_distance = property(**sensor_distance())

    def sensor_current():
        doc = "The sensor_current property."
        def fget(self):
            return self._sensor_current
        def fdel(self):
            del self._sensor_current
        return locals()
    sensor_current = property(**sensor_current())

    def calculate_sensor_value(self, sensor_number):
        '''
        Calculate the current of one sensor
        Args:
            sensor_number (int): 1, 2 or 3 depending on wich sensor gets evaluated
        '''
        if self.sensor_auto[sensor_number-1]:
            self._sensor_distance[sensor_number-1] = 2*self._tolerance*random.random() + self._distance - self._tolerance
            if self._sensor_distance[sensor_number-1] > 20:
                self._sensor_distance[sensor_number-1] = 20
            elif self._sensor_distance[sensor_number-1] < 0:
                self._sensor_distance[sensor_number-1] = 0
        if self.sensor_error[sensor_number-1]:
            self._sensor_current[sensor_number-1] = random.choice([0, 2])
        else:
            self._sensor_current[sensor_number-1] = round(10 * (20 - 16/20*self._sensor_distance[sensor_number-1]))
        pass

    def calculate_all_sensor_values(self):
        '''
        Calculate the current of all sensors
        '''
        self.calculate_sensor_value(1)
        self.calculate_sensor_value(2)
        self.calculate_sensor_value(3)
        pass

    def write_sensor_currents(self):
        '''
        Write the currents of all sensors into a file. The values are given in mA and angle_reset
        seperated by a newline character
        '''
        data = np.array([self._sensor_current[0], self._sensor_current[1], self._sensor_current[2]], dtype = np.uint8).flatten()

        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
            addr = ("172.27.245.27", 8080)
            s.sendto(data, addr)
        pass
