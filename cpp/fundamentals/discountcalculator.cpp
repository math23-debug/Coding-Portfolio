#include <iostream>

double calculate(double normal, double percent);

int main()
{
    double normal,percent, discounted;
    std::cout << "Normal price? \n";
    std::cin >> normal;
    std::cout << "Discount % \n";
    std::cin >> percent;

    discounted = calculate(normal,percent);

    std::cout << discounted << "$";
}


double calculate(double normal, double percent)
{
    double discounted = normal - (normal * (percent / 100));
    return discounted;
}


