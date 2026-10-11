#include <iostream>
#include <memory>

class MyVector
{
private:
    std::unique_ptr<int[]> data;
    int size;
    int capacity;

    void grow()
    {
        capacity *= 2;
        std::unique_ptr<int[]> newData = std::make_unique<int[]>(capacity);
        for (int i = 0; i < size; i++)
        {
            newData[i] = data[i];
        }
        data = std::move(newData);
        std::cout << "Data grew. \nCapacity = " << capacity << "\n";
    }
public:
    MyVector()
    {
        size = 0;
        capacity = 2;
        data = std::make_unique<int[]>(capacity);
        std::cout << "MyVector created \n";
    }

    void push_back(int value)
    {
        if (size == capacity)
        {
            std::cout << "FULL \n";
            grow();
        }
        data[size] = value;
        size += 1;
    }
    void print()
    {
        for (int i = 0; i < size; i++)
        {
            std::cout << "Item " << i + 1 << " : " << data[i] << "\n";
        }
        std::cout << "Size: " << size << "\nCapacity: " << capacity << "\n";
    }
    int get(int index)
    {
        if (index >= 0 && index < size)
        {
            return data[index];
        }
        else
        {
            std::cout << "INVALID INDEX \n";
            return -1;
        }
    }
    int getSize()
    {
        return size;
    }
    void pop_back()
    {
        if (size == 0)
        {
            std::cout << "Vector empty. \n";
        }
        size -= 1;
    }
};

int main()
{
    std::cout << "Start \n";
    {
        MyVector v;
        v.push_back(2);
        v.push_back(3); 
        v.push_back(4);
        v.print();
        v.pop_back();
        v.print();
    }
    std::cout << "Outside Loop \n";
}
