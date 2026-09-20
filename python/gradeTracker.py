import os
os.system('cls') 

grades = []
def enterGrades():
    print ("Press enter to return")
    x = "x"
    while x != "":
        x = input("Enter a grade: ")
        if x.strip().isdigit() and int(x) <= 100: grades.append(int(x))
        elif (x != ""): print ("INVALID INPUT")
    os.system('cls') 

def printGrades():
    sort()
    for i in range(len(grades)):
        print (grades[i], end= " ")
    print ("\n")
    x = "x"
    while x != "": x = input("Enter to go back to menu ")
    os.system('cls') 

def average():
    print (round(sum(grades) / len(grades), 1))
    x = "x"
    while x != "": x = input("Enter to go back to menu ")
    os.system('cls') 

def extremes(): 
    print ("Highest = ", max(grades))
    print ("Lowest  = ", min(grades))
    x = "x"
    while x != "": x = input("Enter to go back to menu ")
    os.system('cls') 

def sort():
    while grades != sorted(grades):
        for i in range(len(grades) - 1):
            if grades[i] > grades[i + 1]:
                grades[i], grades[i+1] = grades[i+1], grades[i]


def isValidChoice (choice, high, low):
    try: 
        i = int(choice)
    except ValueError: 
        return False
    if (i < low or i > high):
        return False
    else: 
        return True

while True:
    choice = input("Enter grade (1) \nShow Grades (2) \nView class average(3) \nView highest and lowest(4) \n")
    while not isValidChoice(choice, 4, 1):
        print ("INVALID CHOICE \n Try again")       
        choice = input()
    os.system("cls")
    if choice == 1: enterGrades()
    if choice == 2: printGrades()
    if choice == 3: average()
    if choice == 4: extremes()