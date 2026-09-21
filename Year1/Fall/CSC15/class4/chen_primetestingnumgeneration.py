# Ryan Chen
# 10/9/2023
# Generate 20 random numbers and test if they're prime


import random
numlist = []

def randomnumber(n):
    for i in range(n):
        
        numlist.append(random.randint(0,99))

    print(numlist,"\n")    
    return numlist


def primetest():
    #run for loop through array
    primelist = []
    for nums in numlist:
        if nums >1:
            for i in range(2,int(nums/2)+1):
                if (nums%i)==0:
                    break
            else:
                primelist.append(nums)
    print(primelist)
    return primelist


    
def main():
    randomnumber(20)
    primetest()

main()
