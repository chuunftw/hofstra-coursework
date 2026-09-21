key=2 
enc_message = " "
message = (input("Please enter a message: "))

for letter in message: 
	ord_value = ord(letter)
	enc_value = ord_value +key 
	enc_messsage = enc_message + chr(enc_value)

print("The encrytped message is" +enc_message)
dmessage = " " 
for letter in enc_message: 
	chr_value = ord(letter)
	dvalue=chr_value -key 
	dmessage = dmessage + chr(dvalue)

print("The decrypted message is" +dmessage)
