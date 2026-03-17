#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
};

Node* createNode(int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->prev = nullptr;
    newNode->next = nullptr;
    return newNode;
}

void appendNodeRecursive(Node*& head, Node*& tail, int value) {
    if (head == nullptr) {
        head = tail = createNode(value);
        return;
    }

    if (head->next == nullptr) {
        Node* newNode = createNode(value);
        head->next = newNode;
        newNode->prev = head;
        tail = newNode;
        return;
    }

    appendNodeRecursive(head->next, tail, value);
}

void createListRecursive(Node*& head, Node*& tail, int count, int index = 1) {
    if (index > count) {
        return;
    }

    int value;
    cout << "Enter element " << index << ": ";
    cin >> value;

    appendNodeRecursive(head, tail, value);
    createListRecursive(head, tail, count, index + 1);
}

void printListForwardRecursive(Node* head) {
    if (head == nullptr) {
        return;
    }

    cout << head->data << " ";
    printListForwardRecursive(head->next);
}

void printListBackwardRecursive(Node* tail) {
    if (tail == nullptr) {
        return;
    }

    cout << tail->data << " ";
    printListBackwardRecursive(tail->prev);
}

void deleteNode(Node*& head, Node*& tail, Node* nodeToDelete) {
    if (nodeToDelete == nullptr) {
        return;
    }

    if (nodeToDelete == head) {
        head = nodeToDelete->next;
    }

    if (nodeToDelete == tail) {
        tail = nodeToDelete->prev;
    }

    if (nodeToDelete->prev != nullptr) {
        nodeToDelete->prev->next = nodeToDelete->next;
    }

    if (nodeToDelete->next != nullptr) {
        nodeToDelete->next->prev = nodeToDelete->prev;
    }

    delete nodeToDelete;
}

void removeElementsAfterValueRecursive(Node*& head, Node*& tail, Node* current, int targetValue) {
    if (current == nullptr || current->next == nullptr) {
        return;
    }

    if (current->data == targetValue) {
        Node* nodeToDelete = current->next;
        Node* nextAfterDeleted = nodeToDelete->next;

        deleteNode(head, tail, nodeToDelete);

        removeElementsAfterValueRecursive(head, tail, nextAfterDeleted, targetValue);
    }
    else {
        removeElementsAfterValueRecursive(head, tail, current->next, targetValue);
    }
}

void clearListRecursive(Node*& head, Node*& tail) {
    if (head == nullptr) {
        tail = nullptr;
        return;
    }

    Node* temp = head;
    head = head->next;
    delete temp;

    clearListRecursive(head, tail);
}

int main() {
    Node* head = nullptr;
    Node* tail = nullptr;

    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    createListRecursive(head, tail, n);

    cout << "\nOriginal list forward: ";
    if (head == nullptr) {
        cout << "List is empty.";
    }
    else {
        printListForwardRecursive(head);
    }

    cout << "\nOriginal list backward: ";
    if (tail == nullptr) {
        cout << "List is empty.";
    }
    else {
        printListBackwardRecursive(tail);
    }

    int targetValue;
    cout << "\n\nEnter target value: ";
    cin >> targetValue;

    removeElementsAfterValueRecursive(head, tail, head, targetValue);

    cout << "\nResult list forward: ";
    if (head == nullptr) {
        cout << "List is empty.";
    }
    else {
        printListForwardRecursive(head);
    }

    cout << "\nResult list backward: ";
    if (tail == nullptr) {
        cout << "List is empty.";
    }
    else {
        printListBackwardRecursive(tail);
    }

    cout << endl;

    clearListRecursive(head, tail);

    return 0;
}