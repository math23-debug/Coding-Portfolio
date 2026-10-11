#include <iostream>
#include <memory>
#include <string>

template <typename T>
class MyVector
{
private:
    std::unique_ptr<T[]> data;
    int size;
    int capacity;

    void grow()
    {
        capacity *= 2;
        std::unique_ptr<T[]> newData = std::make_unique<T[]>(capacity);
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
        data = std::make_unique<T[]>(capacity);
        std::cout << "MyVector created \n";
    }

    void push_back(T value)
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
        MyVector<int> i;
        i.push_back(2);
        i.print();
        MyVector<std::string> s;
        s.push_back("Hello");
        s.print();
        MyVector <double> d;
        d.push_back(3.14);
        d.print();
    }
    std::cout << "Outside Loop \n";
}
