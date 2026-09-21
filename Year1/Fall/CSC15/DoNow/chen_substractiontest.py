"""import time
import turtle as tr 
count = 0.5s

for h in range(0,13,1):
    for m in range(0,60,1):
        print("\n",h, ":" ,m)
        clock = str(h) + ":" + str(m)
        time.sleep(count)
        tr.write(clock,font=('arial',50,'bold'))
        tr.hideturtle()
        time.sleep(count)
        tr.clear()"""

"""for n in range(1,13,1):
    for i in range(1,13,1):
        print(n*i,end="\t")
    print()"""
#Author: Ryan Chen
#Date: 9/27/2023
#Description: Subtracting Integers

import random

num1 = random.randint(0,9)
num2 = random.randint(0,9)

if num1<num2:
    num1,num2=num2,num1

answ = (num1-num2)

print("What is ", num1, "-", num2, "?")
ans = eval(input("Enter your answer "))
print("You got it!")

while ans != answ:
    if ans == answ:
        print("The answer is correct")
    else:
        print("That is incorrect, try again")
        ans = eval(input("Enter an answer "))
        print("The answer is correct")



        

        
        
