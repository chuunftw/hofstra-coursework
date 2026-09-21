#Document class
file1 = open('1985-Reagan.txt', 'r')
Reagan = file1.read()
file2 = open('1993-Clinton.txt', 'r')
Clinton = file2.read()
file3 = open('2001-Bush.txt', 'r')
Bush = file3.read()

class document:
    def __init__(self):
      pass

    def numberWords(self):
      countRWords = len(Reagan.split())
      countCWords = len(Clinton.split())
      countBWords = len(Bush.split())

      return countRWords, countCWords, countBWords

    def uniqueWords(self):
      countVocab1 = len(set(Reagan.split()))
      countVocab2 = len(set(Clinton.split()))
      countVocab3 = len(set(Bush.split()))
    
      return countVocab1, countVocab2, countVocab3


    def numbers(self):
      substring = ["0","1","2","3","4","5","6","7","8","9"]
      countRNumbers = sum(Reagan.count(sub) for sub in substring)  
      countCNumbers = sum(Clinton.count(sub) for sub in substring)
      countBNumbers = sum(Bush.count(sub) for sub in substring)
      return countRNumbers, countCNumbers, countBNumbers
    def sentences(self):
      substring = [".","?","!"]
      countSentence1 = sum(Reagan.count(sub) for sub in substring)
      countSentence2 = sum(Clinton.count(sub) for sub in substring)
      countSentence3 = sum(Bush.count(sub) for sub in substring)
      return countSentence1, countSentence2, countSentence3

    def paragraph(self):
      substring = ["\n\n"]
      countsentencesPerParagraph1 = sum(Reagan.count(sub) for sub in           substring)
      countsentencesPerParagraph2 = sum(Clinton.count(sub) for sub in substring)
      countsentencesPerParagraph3 = sum(Bush.count(sub) for sub in substring)
      return countsentencesPerParagraph1, countsentencesPerParagraph2, countsentencesPerParagraph3
    
  #def speechText(self):

