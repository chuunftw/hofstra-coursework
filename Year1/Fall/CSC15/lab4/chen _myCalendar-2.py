#Ryan Chen and Brandon Sabillon 
#10/12/23
#CSC15


monthList = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"]
daysList = ["SUN", "MON","TUE","WED","THU","FRI","SAT"]

def printMonth(year,month):
    print()
    printMonthTitle(year,month)
    printMonthBody(year, month)
    
def printMonthTitle(year, month):
    if month <= 12:
        month = month - 1
    print("       ",monthList[month], year, "  ")
    print('-----------------------------')
    print(" Sun Mon Tue Wed Thu Fri Sat ")
    
def printMonthBody(year,month):
    startDay = getStartDay(year, month)
    numberOfDaysInMonth = getNumberOfDaysInMonth(year, month)
    i = 0
    for i in range(startDay):
        print("    ", end = "")
    for i in range(1,numberOfDaysInMonth + 1):
        print(format(i, '4d'), end= '')
        if (i + startDay) % 7 == 0:
            print()

def getStartDay(year,month):
    START_DAY_FOR_JAN_1_1800 = 3
    totalNumberOfDays = getTotalNumberofDays(year, month)
    day = (totalNumberOfDays + START_DAY_FOR_JAN_1_1800) % 7
    return day

def getTotalNumberofDays(year,month):
    total = 0
    for i in range(1800, year):
        if isLeapYear(i):
            total = total + 366
        else:
            total = total + 365
    for i in range(1, month):
        total = total + getNumberOfDaysInMonth(year, i)
    return total

def getNumberOfDaysInMonth(year,month):
    day31months = [1, 3, 5, 7, 8, 10, 12]
    day30months = [4, 6, 9, 11]
    day28months = [2]
    if month in day31months:
        return 31
    if month in day30months:
        return 30
    if month in day28months:
        return 29 if isLeapYear(year) else 28
    return 0

def isLeapYear(year):
    return year % 400 == 0 or (year % 4 == 0 and year % 100 != 0)

def readInput():
    year = int(input("Enter full year (e.g., 2001): "))
    month = int(input("Enter month as number between 1 and 12: "))
    if year < 1800 or not 1 <= month <= 12:
        raise ValueError("Enter a year of at least 1800 and a month from 1 to 12")
    return year, month

def main():
    year, month = readInput()
    printMonth(year, month)
 

if __name__ == "__main__":
    main()
