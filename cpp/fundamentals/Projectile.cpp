#include <iostream>
#include <cmath>
#include <cstdlib> 

const double PI = 3.1415926535;

double angleConversion(double angleDegree);
double calculateRange(double angleRadian, double magnitude);

int main()
{
	double magnitude, range, restart = 1, i;
	double angleDegree, angleRadian;

	while(restart == 1)
	{
		system("cls");
		std::cout << "Strenght (m/s): \n";
		std::cin >> magnitude;
		std::cout << "Launch angle (degrees): \n";
		std::cin >> angleDegree;

		angleRadian = angleConversion(angleDegree);

		range = calculateRange(angleRadian, magnitude);

		std::cout << "\nIt will go " << range << " meters\n";

		std::cout << "\nRestart? (1 YES  0 NO) \n";
		std::cin >> restart;
	}
}

double angleConversion(double angleDegree)
{

	double angleRadian = angleDegree * (PI / 180);
	return angleRadian;
}

double calculateRange(double angleRadian, double magnitude)
{
	double range = (magnitude * std::cos(angleRadian) * 2 * magnitude * std::sin(angleRadian)) / 9.81;

	return range;
}