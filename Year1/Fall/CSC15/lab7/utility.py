#Team members: Brandon Sabillon, Ryan Chen, Dylan Alflen
# Description: Create a bag of words model from speeches
# Revision History:
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
# Name:            Date:          Comments:
# Brandon Sabillon         11/09/23       Imported parseUtility and all txt files
# Dylan Alflen             11/24/23.      Imported string
# Ryan Chen                11/24/23.      Completed getTokens, getTF and prettyPrint
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

import string


def getFileNames():
  file1 = open('1981-Reagan.txt', 'r')
  filer1 = file1.read()

  file2 = open('1993-Clinton.txt', 'r')
  filer2 = file2.read()

  file3 = open('2001-Bush.txt', 'r')
  filer3 = file3.read()

  file4 = open('2009-Obama.txt', 'r')
  filer4 = file4.read()

  file5 = open('2017-Trump.txt', 'r')
  filer5 = file5.read()

  return filer1,filer2,filer3,filer4,filer5

def removePunc(txt):
  txt_clean = txt.translate\
              (str.maketrans('', '', string.punctuation))
  txt_clean = txt_clean.lower()
  return txt_clean



def getTokens(txt):

  unique_list = []
  tokens = txt.split()
  for word in tokens:
    if len(unique_list) == 0:
      unique_list.append(word)

    if len(unique_list) > 0 and word not in unique_list:
      unique_list.append(word)


  return unique_list



#term frequency / dictionary
def getTF(unique_list,txt_clean):
  dict_tokens = {}
  c = 0
  txt_cleaner = txt_clean.split()

  for unique in unique_list:
    c = txt_cleaner.count(unique)
    dict_tokens[unique] = c

  return dict_tokens




def prettyPrint(dict_tokens):
  # Print the names of the columns.
  print("{:<10} {:<10}".format('WORD', 'FREQUENCY'))

  # print each data item.
  for key, value in dict_tokens.items():
      word, frequency = key, value
      print("{:<10} {:<10}".format(word, frequency))







