#Authors: Brandon Sabillon and Ryan Chen
#Date: 11/2/23
#Description: Working with abstract functions in teams of two

#-----------------------------------------------------------------
#Brandons code

file = open('2009-Obama.txt', 'r')
Obama = file.read()

#This function will cont the number of sentences in the file by counting up one 
# everytime it meets with a punctuation
def numberOfSentences(file_name):
  substring = [".","?","!"]
  countSentence = sum(Obama.count(sub) for sub in substring)
  return countSentence
  
  
  

#This function will count the number of words in the file by using a counter
def numberOfWords(file_name):
  countWords = len(Obama.split())
  

  return countWords

# This function will count the number of times one word shows up in 
# this speech
def numberOfWordVocab(file_name):
  countVocab = len(set(Obama.split()))
  return countVocab
  



