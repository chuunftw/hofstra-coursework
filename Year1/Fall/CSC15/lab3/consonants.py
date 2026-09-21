#Author: 	Ryan Chen 
#Date: 		9/21/2023
#Description 	Lab 3 - Consonants 

#Resision History 		 
#Name		Date 		Desciption
#chen		9/21/2023	counting vowels 
#
#
#

vowels = ["a","e","i","o","u"]
word = input("Please enter a word: ")

count = 0
for x in range (len(word)):
	letter = word[x]
	if letter not in vowels:
		count = count+1
		print("consonants = ", letter, " count = ", count)
print("There are", count, "consonants in", word)
