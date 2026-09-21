#Author: 	Ryan Chen 
#Date: 		9/21/2023
#Description 	Lab 3 - Words 

#Resision History 		 
#Name		Date 		Desciption
#chen		9/21/2023	Words in Sentence
#
#
#

sentence = input("Enter a sentence: ") 

c = 1

for letter in sentence:
	if ord(letter) == 32:
		c+=1
print("There are", c, "words in this sentence")
	
