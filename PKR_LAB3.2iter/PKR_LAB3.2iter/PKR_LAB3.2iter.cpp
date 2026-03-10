#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;
};

void appendNode(Node*& head, int value)
{
    Node* newNode = new Node{ value, nullptr };

    if (head == nullptr)
    {
        head = newNode;
        return;
    }

    Node* current = head;
    while (current->next != nullptr)
    {
        current = current->next;
    }
    current->next = newNode;
}

void createList(Node*& head, int n)
{
    head = nullptr;

    for (int i = 0; i < n; i++)
    {
        int value;
        cout << "Enter element " << i + 1 << ": ";
        cin >> value;
        appendNode(head, value);
    }
}

void printList(const Node* head)
{
    if (head == nullptr)
    {
        cout << "List is empty." << endl;
        return;
    }

    const Node* current = head;

    cout << "List elements: ";

    while (current != nullptr)
    {
        cout << current->data << " ";
        current = current->next;
    }

    cout << endl;
}

int calculatePositiveSum(const Node* head)
{
    int sum = 0;
    const Node* current = head;

    while (current != nullptr)
    {
        if (current->data > 0)
        {
            sum += current->data;
        }
        current = current->next;
    }

    return sum;
}

void destroyList(Node*& head)
{
    while (head != nullptr)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main()
{
    Node* head = nullptr;
    int n;

    cout << "Enter number of list elements: ";
    cin >> n;

    createList(head, n);

    printList(head);

    int positiveSum = calculatePositiveSum(head);

    cout << "Sum of positive elements: " << positiveSum << endl;

    destroyList(head);

    return 0;
}