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
    Node* tail;
    int size = 0;
public:
    LinkedList() 
    {
        head = nullptr; 
        tail = nullptr;
    }
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
    void enqueue(int value)
    {
        Node* newNode = new Node;
        newNode->value = value;
        newNode->next = nullptr;

        if (tail == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }
    void dequeue()
    {
        if (head == nullptr)
        {
            std::cout << "EMPTY LIST \n";
            return;
        }
        else
        {
            Node* oldHead = head;
            head = oldHead->next;
            if (head == nullptr)
            {
                tail = nullptr;
            }
            delete oldHead;
            size--;
        }
    }
    int front()
    {
        if (size == 0)
        {
            std::cout << "EMPTY LIST \n";
            return -1;
        }
        return head->value;
    }
    int get_size() { return size; }
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
};
int main()
{
    LinkedList list;

    list.enqueue(90);
    list.enqueue(70);
    list.enqueue(60);
    list.enqueue(50);
    list.print();
    list.dequeue();
    list.dequeue();
    list.print();
    std::cout << list.get_size() << "\n";
}

