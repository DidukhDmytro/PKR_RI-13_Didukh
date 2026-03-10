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
        return;

    cout << head->data << " ";
    printList(head->next);
}

int calculatePositiveSum(const Node* head)
{
    if (head == nullptr)
        return 0;

    int value = 0;

    if (head->data > 0)
        value = head->data;

    return value + calculatePositiveSum(head->next);
}

void destroyList(Node*& head)
{
    if (head == nullptr)
        return;

    Node* temp = head;
    head = head->next;

    destroyList(head);

    delete temp;
}

int main()
{
    Node* head = nullptr;
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    createList(head, n);

    cout << "List: ";
    printList(head);
    cout << endl;

    int sum = calculatePositiveSum(head);

    cout << "Sum of positive elements: " << sum << endl;

    destroyList(head);

    return 0;
}