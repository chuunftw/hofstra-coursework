def getInput():
  key = int(input("Please enter a number 1-9 (This will be your encryption key) : "))
  encrypted = input("Please enter the message you'd like to encrypt : ")
  while len(encrypted.replace(" ","")) < 56:
    encrypted = input("Message must be at least 56 characters long, try again: ")

    

  return key, encrypted

def encryptInput(key,encrypted):
  enc_message = ''
  for letter in encrypted:
    ord_value = ord(letter)
    enc_value = ord_value + key
    enc_message = enc_message + chr(enc_value)

  return enc_message

def forcefulDecrypt(enc_message):
  
  for x in range(26):
    og_message = ''
    for letter in enc_message:
      ord_value = ord(letter)
      enc_value = ord_value - x
      og_message += chr(enc_value)
    print(og_message)


def prettyPrint(enc_message):
  print("Your encrypted message is :", enc_message)
  
  print("The program will now attempt to decrypt your message through a brute force approach... ")

  forcefulDecrypt(enc_message)
  

def main():
  key, encrypted = getInput()
  enc_message = encryptInput(key,encrypted.replace(" ", ""))
  prettyPrint(enc_message)
main()
