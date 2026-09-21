#Author: Ryan Chen 
#Date: 9/14/2023
#Desciption: Binary to Decimal

import numpy as np
import pandas as pd 
import seaborn as sns

MAX =255

def main(n):

	print("The dcimal number:" ,n)

	b = convertToBinary(n)
	n = convertToDecimal(b)

	print("This is binary	:",b)

def convertToDecimal(binary):
  number = (input("Enter a binary number: "))
  x = int(number,2)
  
  print('The binary is equal to ',x)


