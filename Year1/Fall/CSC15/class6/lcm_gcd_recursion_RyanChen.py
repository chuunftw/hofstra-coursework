import random
num1 = random.randint(1, 999)
num2 = random.randint(1, 999)
def sum(x):
    if x ==0:
        return 0
    else: 
        #print(x, end=", ")
        return x + sum(x - 1)

def factorial(x):
    if x ==1:
        return x
    else: 
        #print(x, end=", ")
        return x * factorial(x - 1)

def gcd(x, y):
    if y == 0:
        return x
    else:
        return gcd(y, x % y)

def main():
    n = random.randint(1,999)
    r = factorial(n)
    print("Factorial is: ", r, "\n")
    s = sum(n)
    print("Sum of Num is: ", s, "\n")
    g = gcd(num1,num2)
    print("The GCD of two random numbers is: ",g, "\n")
    

main()
