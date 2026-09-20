import os
os.system('cls') 

def load_tasks():
    tasks = []
    if os.path.exists("Tasks.txt"):
        with open("Tasks.txt", "r") as file:
            tasks = file.read().splitlines()
    return tasks

def save_tasks(tasks):
    with open("Tasks.txt", "w") as file:
        for task in tasks:
            file.write(task + "\n")

def add_task(tasks):
    print("What task would you like to add?")
    new_task = input()
    tasks.append(new_task)
    save_tasks(tasks)

def print_tasks(tasks):
    os.system('cls') 
    print("TO-DO")
    for index, task in enumerate(tasks, start=1):
        print(f"{index}: {task}")
    print("ENTER TO RETURN")
    enter = input()

def remove_task(tasks):
    os.system('cls')
    index = -1
    valid = False
    while not valid:
        raw = input("Which task # would you like to remove? \n")
        print(f"DEBUG: len(tasks) = {len(tasks)}, tasks = {tasks}")
        try:
            index = int(raw)
            valid = 1 <= index <= len(tasks)
        except ValueError:
            valid = False
        if not valid:
            print("Invalid task #")

    tasks.pop(index - 1)
    save_tasks(tasks)


def menu():
    print("1. View tasks \n2. Add tasks \n3. Remove tasks")
    return int(input())

while True:
    os.system('cls') 
    tasks = load_tasks()
    choice = menu()
    if choice == 1:
        print_tasks(tasks)
    if choice == 2:
       add_task(tasks)
    if choice == 3:
        remove_task(tasks)
