#include <iostream>
#include <cstdlib>
#include <string>
#include <cctype>

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
	bool checkPassword(std::string attempt)
	{
		return attempt == storedPassword;
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
};

int main()
{
	Password myPassword;
	bool strenght = false;
	while (!strenght)
	{
		myPassword.setPassword();
		strenght = myPassword.strongPassword();
		if (!strenght) std::cout << "Password must include Uppercase, Lowercase, Number, Symbol and at least 8 characters \n";
	}

	std::string passwordGuess;
	bool check = false;

	while (!check)
	{
		std::cout << "Enter password to continue: \n";
		std::cin >> passwordGuess;
		check = myPassword.checkPassword(passwordGuess);
		if (!check)
		{
			system("cls");
			std::cout << "INCORRECT!\n";
		}
	}
	system("cls");
	std::cout << "CORRECT!\nProceed";

}