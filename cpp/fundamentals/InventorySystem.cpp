#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <limits>
#include <vector>

int menu();
bool validAnswer(int input, int low, int high);
void RETURN();

class Item
{
public:
    std::string name;
    int quantity;
    double price;
};

class Inventory
{
private:
    std::vector<Item> items;
public:
    void addItem()
    {
        Item newItem;
        std::cout << "Item Name:\n";
        std::cin >> newItem.name;
        std::cout << "Item Price:\n";
        std::cin >> newItem.price;
        while (newItem.price < 0)
        {
            std::cout << "Price cannot be negative\n";
            std::cin >> newItem.price;
        }
        std::cout << "Item Quantity:\n";
        std::cin >> newItem.quantity;
        while (newItem.quantity < 0)
        {
            std::cout << "Quantity cannot be negative\n";
            std::cin >> newItem.quantity;
        }

        items.push_back(newItem);
        RETURN();
    }

    void showInventory()
    {
        for (Item i : items)
        {
            std::cout << i.name << " - $" << i.price << " x" << i.quantity << "\n";
        }
        RETURN();
    }

    void totalValue()
    {
        double totalValue = 0;
        for (Item i : items)
        {
            totalValue += i.price * i.quantity;
        }
        std::cout << "Total value: " << totalValue << "\n";
        RETURN();
        
    }

    void removeItem()
    {
        std::string search;
        std::cout << "Which item would you like to delete\n";
        std::cin >> search;
        
        for (int i = 0; i < items.size(); i++)
        {
            if (search == items[i].name)
            {
                items.erase(items.begin() + i);
                std::cout << "Item errased successfully\n";
                RETURN();
                return;
            }
        }
        std::cout << "Item not found\n";
        RETURN();
    }
};

int main()
{
    Inventory TheInventory;

    while (true)
    {

        int menuChoice = menu();

        if (menuChoice == 1) TheInventory.addItem();
        if (menuChoice == 2) TheInventory.showInventory();
        if (menuChoice == 3) TheInventory.totalValue();
        if (menuChoice == 4) TheInventory.removeItem();
    }


}

int menu()
{
    int menuChoice;
    bool valid = false;

    while (!valid)
    {
        std::cout << "Add Item (1)\nView Inventory(2)\nTotal Value (3)\nDelete Item (4)\n";
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


