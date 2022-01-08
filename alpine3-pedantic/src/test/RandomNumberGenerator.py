import decimal
import random

def RandNum():
   num1 = int(decimal.Decimal(random.gauss(120, 60))) % 255
   num2 = int(decimal.Decimal(random.gauss(120, 60))) % 255
   num3 = int(decimal.Decimal(random.gauss(120, 60))) % 255
   return [num1, num2, num3]
