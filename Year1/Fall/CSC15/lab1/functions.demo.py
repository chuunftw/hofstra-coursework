# Author: Ryan Chen 
# Date: 9/7/2023
# Desciption: Simple Functions in Python 
#

def computeSum(data):
	quiz_total=0
	for num in data:
		quiz_total= quiz_total + num
    
	return quiz_total

def main(): 
	quiz = [98, 78, 79, 83, 87]

	# calculate the sum of the quiz
	computeSum(quiz)
	s = computeSum(quiz)

	#print the sum
	print('The sum is ' , s)

# - - run main - - 
main()

