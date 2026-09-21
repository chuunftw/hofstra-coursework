
from main import numberOfSentences
from main import numberOfWords
from main import numberOfWordVocab
Obama = '2009-Obama.txt'
file = open('2009-Obama.txt', 'r')
Obama = file.read()

numOfWords = numberOfWords(Obama)
numOfSentences = numberOfSentences(Obama)
numOfWordVocab = numberOfWordVocab(Obama)


#Ryan's code

def readinfile():
  file.read()

def removePuncAndNum(x):
  removable = [".", "!", "?",",",":",";","'","-","(",")","[","]","{","}","1","2","3","4"
     ,"5","6","7","8","9","0","�"]
  cleantext = "".join([char for char in x if char not in removable])
  return cleantext
clean = removePuncAndNum(Obama)


def prettyPrint():
  print('The number of words are: ', numOfWords)
  print('The number of sentences are: ', numOfSentences)
  print('The number of characters are: ', numOfWordVocab)
  print(clean)

  







prettyPrint()