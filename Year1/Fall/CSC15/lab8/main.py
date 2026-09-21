#Brandon, Ryan, Manny
#Dates worked on 11/30/23 , 12/ 3 / 23... 12/ 7 / 23
#Description: Makes a table of the features of the presidential 
#speeches using the document class and also makes another table 
#of the amount of bi grams for each speech



from document import document 
import pandas as pd

file1 = open('1985-Reagan.txt', 'r')
Reagan = file1.read()
file2 = open('1993-Clinton.txt', 'r')
Clinton = file2.read()
file3 = open('2001-Bush.txt', 'r')
Bush = file3.read()


def removePuncAndNum(x):
  removable = [".", "!", "?",",",":",";","'","-","(",")","[","]","{","}","�"]
  cleantext = "".join([char for char in x if char not in removable])
  return cleantext
cleanReagan = removePuncAndNum(Reagan)
cleanClinton = removePuncAndNum(Clinton)
cleanBush = removePuncAndNum(Bush)
#This function returns all the bi grams in the three speeches
def bigram():
  token = cleanReagan.split()
  token2 = cleanClinton.split()
  token3 = cleanBush.split()
  reaganBi = []
  clintonBi = []
  bushBi = []
  countReagan = 0
  countClinton = 0
  countBush = 0
  for x in range(len(token)-1):
    word = token[x] + ' ' + token[x+1]
    countReagan +=1
    reaganBi.append(word)
  for x in range(len(token2)-1):
    word = token2[x] + ' ' + token2[x+1]
    countClinton +=1
    clintonBi.append(word)
  for x in range(len(token3)-1):
    word = token3[x] + ' ' + token3[x+1]
    countBush +=1
    bushBi.append(word)
  
  return reaganBi, clintonBi, bushBi
#This function returns the amount of bigrams in a speech (I know its not 
#effcient but it works) 
def bigram2():
  token = cleanReagan.split()
  token2 = cleanClinton.split()
  token3 = cleanBush.split()
  reaganBi = []
  clintonBi = []
  bushBi = []
  countReagan = 0
  countClinton = 0
  countBush = 0
  for x in range(len(token)-1):
    word = token[x] + ' ' + token[x+1]
    countReagan +=1
    reaganBi.append(word)
  for x in range(len(token2)-1):
    word = token2[x] + ' ' + token2[x+1]
    countClinton +=1
    clintonBi.append(word)
  for x in range(len(token3)-1):
    word = token3[x] + ' ' + token3[x+1]
    countBush +=1
    bushBi.append(word)

  return countReagan, countClinton,countBush


def main():
  #Instance of the document class that calls on its methods
  doc = document()
  countWords = doc.numberWords()
  uniqueWords = doc.uniqueWords()
  numbers = doc.numbers()
  sentences = doc.sentences()
  paragraph = doc.paragraph()
  #Using Pandas to make a table of the features from document class
  data = {
      'Speech': ['Reagan', 'Clinton', 'Bush'],
      'Number of Words': countWords,
      'Unique Words': uniqueWords,
      'Numbers': numbers,
      'Sentences': sentences,
      'Paragraphs': paragraph
  }
  dataTwo = {
      'Speech' : ['Reagan', 'Clinton', 'Bush'],
      'Word Pairs': bigram2()
  }
  dft = pd.DataFrame(dataTwo)
  df = pd.DataFrame(data)
  r = bigram()
  print(r)
  print(df)
  print(dft)
 

main()

