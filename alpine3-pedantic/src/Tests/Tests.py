import TestCase
import unittest
import RandomNumberGenerator
import pytest
import main



class Tests(unittest.TestCase):
    def test_voters(self):
        while True:
            SensorValues = RandomNumberGenerator.RandNum()
            GoldenModel = main(SensorValues)
            Implementation = MainC(SensorValues)
            self.assertEqual(GoldenModel, Implementation)  
         
    

