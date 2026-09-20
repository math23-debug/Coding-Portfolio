#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <limits>
#include <vector>

int menu();
bool validAnswer(int input, int low, int high);
void RETURN();

class gradeTracker
{
private:
    std::vector<int> grades;

public:
    void addGrade()
    {
        while (true)
        {
            int gradesInput = 101, backtomenu = 0;
            bool valid = false;

            while (!valid)
            {
                std::cout << "Enter a grade: \n";
                std::cin >> gradesInput;
                valid = validAnswer(gradesInput, 0, 100);
            }
            grades.push_back(gradesInput);
            
            valid = false;

            while (!valid)
            {
                std::cout << "Enter 1 to continue entering grades or enter 2 to exit\n";
                std::cin >> backtomenu;
                valid = validAnswer(backtomenu, 1, 2);
            }
            system("cls");
            if (backtomenu == 2) break;
        }
    }

    void showGrades()
    {
        for (int g : grades) std::cout << g << "\n";
        RETURN();
    }

    void calculateAverage()
    {
        double sum = 0, average;
        for (int g : grades)
        {
            sum += g;
        }
        average = sum / grades.size();
        std::cout << "The classes average is: " << average << "\n";
        RETURN();
    }

    void highestLowest()
    {
        int highest = 0, lowest = 100;
        if (grades.size() > 0)
        {
            for (int g : grades)
            {
                if (g > highest)
                {
                    highest = g;
                }
                if (g < lowest)
                {
                    lowest = g;
                }

            }
            std::cout << "Highest: " << highest << "\nLowest: " << lowest << "\n";
        }
        else std::cout << "No grades entered \n";
        RETURN();
    }

};

int main()
{
    gradeTracker classGrades;

    while (true)
    {

        int menuChoice = menu();

        if (menuChoice == 1) classGrades.addGrade();
        if (menuChoice == 2) classGrades.showGrades();
        if (menuChoice == 3) classGrades.calculateAverage();
        if (menuChoice == 4) classGrades.highestLowest();


    }

}

int menu()
{
    int menuChoice;
    bool valid = false;
    
    while (!valid)
    {
        std::cout << "Enter grade (1)\nView grades(2)\nCalculate average (3)\nView highest and lowest grade (4)\n";
        std::cin >> menuChoice;
        valid = validAnswer(menuChoice, 1, 4);
    }

    system("cls");
    return menuChoice;
}

bool validAnswer(int input, int low, int high)
{
    if (input < low || input > high)
    {
        system("cls");
        std::cout << "INVALID CHOICE\n";
        return false;
    }
    else return true;

}


void RETURN()
{
    std::cout << "Press ENTER to return\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    system("cls");
}
