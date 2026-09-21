#Author: 	Ryan Chen 
#Date: 		9/21/2023
#Description 	Lab 3 - Vowels 

#Resision History 		 
#Name		Date 		Desciption
#chen		9/21/2023	counting vowels 
#
#
#


word = input("Please enter a word: ")
vowels = ["a","e","i","o","u"]

count = 0
for x in range (len(word)):
	letter = word[x]
	if letter in vowels:
		count = count+1
		print("vowel = ", letter, " count = ", count)
