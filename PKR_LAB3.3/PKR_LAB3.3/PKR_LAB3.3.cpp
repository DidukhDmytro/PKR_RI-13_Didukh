#include <iostream>
#include <vector>

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

void appendNode(Node*& head, Node*& tail, int value) {
    Node* newNode = createNode(value);

    if (head == nullptr) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void createList(Node*& head, Node*& tail, int count) {
    for (int i = 0; i < count; i++) {
        int value;
        cout << "Enter element " << i + 1 << ": ";
        cin >> value;
        appendNode(head, tail, value);
    }
}

void printListForward(Node* head) {
    if (head == nullptr) {
        cout << "List is empty." << endl;
        return;
    }

    cout << "List: ";
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void printListBackward(Node* tail) {
    if (tail == nullptr) {
        cout << "List is empty." << endl;
        return;
    }

    cout << "Reverse list: ";
    Node* current = tail;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->prev;
    }
    cout << endl;
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

void removeElementsAfterValue(Node*& head, Node*& tail, int targetValue) {
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    vector<Node*> nodesToDelete;

    Node* current = head;
    while (current != nullptr && current->next != nullptr) {
        if (current->data == targetValue) {
            nodesToDelete.push_back(current->next);
        }
        current = current->next;
    }

    for (Node* node : nodesToDelete) {
        deleteNode(head, tail, node);
    }
}

void clearList(Node*& head, Node*& tail) {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    tail = nullptr;
}

int main() {
    Node* head = nullptr;
    Node* tail = nullptr;

    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    createList(head, tail, n);

    cout << "\nOriginal list:" << endl;
    printListForward(head);
    printListBackward(tail);

    int target;
    cout << "\nEnter target value: ";
    cin >> target;

    removeElementsAfterValue(head, tail, target);

    cout << "\nResult list after deletion:" << endl;
    printListForward(head);
    printListBackward(tail);

    clearList(head, tail);

    return 0;
}