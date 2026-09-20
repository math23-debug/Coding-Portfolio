#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <limits>

int Menu();

class Password
{
private:
    std::string storedPassword;

public:
    void setPassword()
    {
        std::cout << "Enter your new password: \n";
        std::cin >> storedPassword;
        system("cls");
    }
    void checkPassword()
    {
        std::string attempt;
        bool check = false;
        system("cls");
        while (!check)
        {
            std::cout << "Enter password to continue: \n";
            std::cin >> attempt;
            if (attempt != storedPassword)
            {
                system("cls");
                std::cout << "INCORRECT!\n";
            }
            else
            {
                check = true;
            }
        }
        system("cls");
    }
    bool strongPassword()
    {
        bool hasUpper = false, hasLower = false, hasDigit = false, hasSymbol = false;
        for (char c : storedPassword)
        {
            if (isupper(c)) hasUpper = true;
            if (islower(c)) hasLower = true;
            if (isdigit(c)) hasDigit = true;
            if (ispunct(c)) hasSymbol = true;

        }
        return hasUpper && hasLower && hasDigit && hasSymbol && storedPassword.length() >= 8;
    }
    void passwordRetry()
    {
        bool strenght = false;

        while (!strenght)
        {
            setPassword();
            strenght = strongPassword();
            if (!strenght) std::cout << "Password must include Uppercase, Lowercase, Number, Symbol and at least 8 characters \n";
        }
    }
};

class Banking
{
private:
    double balance = 0;
    Password myPassword;

public:

    Banking()
    {
        myPassword.passwordRetry();
    }
    void checkBalance()
    {
        while (true)
        {
            std::cout << balance << "\nHit ENTER to return\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            
            break;
        }
        system("cls");
    }

    void deposit()
    {
        myPassword.checkPassword();

        double depositAmount;

        while (true)
        {
            std::cout << "Enter deposit amount: \n";
            std::cin >> depositAmount;
            if (depositAmount > 0) break;
            system("cls");
            std::cout << "INVALID AMOUNT\n";
        }

        balance = balance + depositAmount;

        std::cout << "Deposit successful\nPress ENTER to return\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();

        system("cls");

    }

    void withdraw()
    {
        myPassword.checkPassword();

        double withdrawAmount;
        while (true)
        {
            std::cout << "Enter withdraw amount: \n";
            std::cin >> withdrawAmount;
            if (withdrawAmount <= balance && withdrawAmount > 0) break;
            system("cls");
            std::cout << "INVALID AMOUNT\n";
        }

        balance = balance - withdrawAmount;

        std::cout << "Withdrawal successful\nPress ENTER to return\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();

        system("cls");

    }
};

int main()
{
    Banking myBanking;

    while (true)
    {
        int menuChoice = Menu();
        if (menuChoice == 1) myBanking.checkBalance();
        if (menuChoice == 2) myBanking.withdraw();
        if (menuChoice == 3) myBanking.deposit();
    }

}

int Menu()
{
    int menuChoice = 0;
    while (menuChoice < 1 || menuChoice > 3)
    {
        std::cout << "Welcome to Matheo Banking\n(1)View balance\n(2)Withdraw\n(3)Diposit\n";
        std::cin >> menuChoice;
        if (menuChoice < 1 || menuChoice > 3)
        {
            system("cls");
            std::cout << "INVALID CHOICE\n";
        }
    }
    system("cls");
    return menuChoice;
}