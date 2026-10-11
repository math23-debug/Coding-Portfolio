#include <iostream>

struct Node
{
    int value;
    Node* next;
};

class LinkedList
{
private:
    Node* head;
    int size = 0;
public:
    LinkedList() { head = nullptr; }
    ~LinkedList()
    {
        Node* current = head;
        Node* next;
        while (current != nullptr)
        {
            next = current->next;
            std::cout << current->value << " deleted \n";
            delete current;
            current = next;
        }
    }
        
    void push_front(int value)
    {
        Node* newNode = new Node;
        newNode->value = value;
        newNode->next = head;
        head = newNode;
        size++;
    }
    void print()
    {
        Node* current = head;
        int i = 1;
        while (current != nullptr)
        {
            std::cout << "Item " << i << " = " << current->value << "\n";
            current = current->next;
            i++;
        }
    }
    void pop_front()
    {
        if (head == nullptr)
        {
            std::cout << "EMPTY LIST \n";
            return;
        }
        Node* oldHead = head;
        head = head->next;
        delete oldHead;
        size--;
    }
    int get(int index)
    {
        Node* current = head;
        for (int i = 0; i < index; i++)
        {
            if (current == nullptr)
            {
                std::cout << "INDEX OUT OF RANGE\n";
                return -1;
            }
            current = current->next;
        }
        if (current == nullptr)
        {
            std::cout << "INDEX OUT OF RANGE\n";
            return -1;
        }
        return current->value;
    }
    int get_size()
    {
        return size;
    }
    void insert(int index, int value)
    {
        if (index == 0)
        {
            push_front(value);
        }
        Node* current = head;
        for (int i = 0; i < index - 1; i++)
        {
            if (current == nullptr)
            {
                std::cout << "INDEX OUT OF RANGE\n";
                return;
            }
            current = current->next;
        }
        if (current == nullptr)
        {
            std::cout << "INDEX OUT OF RANGE\n";
            return;
        }

        Node* newNode = new Node;
        newNode->value = value;
        newNode->next = current->next;
        current->next = newNode;
        size++;
    }
    void remove(int index)
    {
        if (index == 0)
        {
            pop_front();
            return;
        }
        Node* current = head;
        for (int i = 0; i < index - 1; i++)
        {
            if (current == nullptr)
            {
                std::cout << "INDEX OUT OF RANGE\n";
                return;
            }
            current = current->next;
        }
        if (current == nullptr)
        {
            std::cout << "INDEX OUT OF RANGE\n";
            return;
        }
        if (current->next == nullptr)
        {
            std::cout << "INDEX OUT OF RANGE\n";
            return;
        }
        Node* badNode = current->next;
        current->next = badNode->next;
        delete badNode;
        size--;
    }
};

int main()
{
    LinkedList list;

    list.pop_front();
    list.push_front(30);
    list.push_front(40);
    list.push_front(50);
    list.push_front(60);
    list.push_front(70);
    list.push_front(80);
    list.print();
    std::cout << list.get(1) << "\n";
    std::cout << list.get(5) << "\n";
    list.pop_front();
    list.print();
    list.insert(3, 1000000);
    list.print();
    std::cout << list.get_size() << "\n";
    list.remove(3);
    list.remove(4);
    list.print();
}