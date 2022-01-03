import decimal
import random

def RandNum():
   num1 = float(decimal.Decimal(random.randrange(400, 2000)/100 if(random.choice([1,2]) == 1) else random.choice([0,2])))
   num2 = float(decimal.Decimal(random.randrange(400, 2000)/100 if(random.choice([1,2]) == 1) else random.choice([0,2])))
   num3 = float(decimal.Decimal(random.randrange(400, 2000)/100 if(random.choice([1,2]) == 1) else random.choice([0,2])))
   return [num1, num2, num3]