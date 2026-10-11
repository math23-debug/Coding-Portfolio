#include <iostream>

class MyVector
{
private:
    int* data;
    int size;
    int capacity;

    void grow()
    {
        capacity *= 2;
        int* newData = new int[capacity];
        for (int i = 0; i < size; i++)
        {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        std::cout << "Data grew. \nCapacity = " << capacity << "\n";
    }
public:
    MyVector()
    {
        size = 0;
        capacity = 2;
        data = new int[capacity];
        std::cout << "MyVector created \n";
    }
    ~MyVector()
    {
        delete[] data;
        std::cout << "MyVector was desctructed \n";
    }
    MyVector(const MyVector& other)
    {
        size = other.size;
        capacity = other.capacity;
        for (int i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
    }
    MyVector& operator=(const MyVector& other)
    {
        if (this == &other) { return *this; }
        delete[] data;                      
        size = other.size;
        capacity = other.capacity;
        data = new int[capacity];
        for (int i = 0; i < size; i++)
            data[i] = other.data[i];

        return *this;
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
        MyVector b;
        std::cout << "Inside loop \n";
        v.push_back(9);
        v.push_back(6);
        v.print();
        v.push_back(8);
        v.print();
        std::cout << v.get(2) << "\n";
        std::cout << v.get(80) << "\n";
        v.pop_back();
        v.print();
        std::cout << "Size : " << v.getSize() << "\n";
        b = v;
        b.push_back(300);
        b.print();
        v.print();
    }
    std::cout << "Outside Loop \n";
}