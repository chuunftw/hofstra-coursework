#Author: Ryan Chen 
#Date: 9/14/2023
#Desciption: Binary to Decimal


MAX =255

def convertToBinary(integer):
  if integer < 0 or integer > MAX:
    raise ValueError("Enter an integer between 0 and 255")
  if integer == 0:
    return [0]
  digits = []
  while integer > 0:
    digits.append(integer % 2)
    integer //= 2
  digits.reverse()
  return digits

def main(n):

	print("The dcimal number:" ,n)

	b = convertToBinary(n)
	n = convertToDecimal(b)

	print("This is binary	:",b)

def convertToDecimal(binary):
  number = ''.join(str(digit) for digit in binary)
  x = int(number,2)
  
  print('The binary is equal to ',x)
  return x

