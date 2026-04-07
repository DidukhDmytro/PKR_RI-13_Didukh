#include <iostream>
#include <fstream> 
#include <string>

using namespace std;

struct Node {
    char data;
    Node* next;
};

struct Queue {
    Node* front;
    Node* rear;
};

void initQueue(Queue& q) {
    q.front = nullptr;
    q.rear = nullptr;
}

bool isEmpty(const Queue& q) {
    return q.front == nullptr;
}

void enqueue(Queue& q, char value) {
    Node* newNode = new Node{ value, nullptr };

    if (isEmpty(q)) {
        q.front = newNode;
        q.rear = newNode;
    }
    else {
        q.rear->next = newNode;
        q.rear = newNode;
    }
}

bool dequeue(Queue& q, char& value) {
    if (isEmpty(q)) {
        return false;
    }

    Node* temp = q.front;
    value = temp->data;
    q.front = q.front->next;

    if (q.front == nullptr) {
        q.rear = nullptr;
    }

    delete temp;
    return true;
}

bool readLineFromFile(const string& fileName, string& line) {
    ifstream fin(fileName);

    if (!fin.is_open()) {
        return false;
    }

    getline(fin, line);
    fin.close();
    return true;
}

void fillQueueFromString(Queue& q, const string& line) {
    for (char ch : line) {
        enqueue(q, ch);
    }
}

bool isEnglishLetter(char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

void splitQueue(const Queue& source, Queue& englishQueue, Queue& otherQueue) {
    Node* current = source.front;

    while (current != nullptr) {
        if (isEnglishLetter(current->data)) {
            enqueue(englishQueue, current->data);
        }
        else {
            enqueue(otherQueue, current->data);
        }
        current = current->next;
    }
}

void printQueue(const Queue& q, const string& title) {
    cout << title;

    if (isEmpty(q)) {
        cout << "(empty)" << endl;
        return;
    }

    Node* current = q.front;
    while (current != nullptr) {
        cout << current->data;
        current = current->next;
    }
    cout << endl;
}

void clearQueue(Queue& q) {
    char temp;
    while (dequeue(q, temp)) {
    }
}

int main() {

    Queue sourceQueue, englishQueue, otherQueue;
    initQueue(sourceQueue);
    initQueue(englishQueue);
    initQueue(otherQueue);

    string line;
    string fileName = "Text.txt";

    if (!readLineFromFile(fileName, line)) {
        cout << "error: cannot open a file " << fileName << endl;
        return 1;
    }

    fillQueueFromString(sourceQueue, line);
    splitQueue(sourceQueue, englishQueue, otherQueue);

    cout << "String from file: " << line << endl << endl;

    printQueue(sourceQueue, "Starting line: ");
    printQueue(englishQueue, "Eng symbols line: ");
    printQueue(otherQueue, "Other symbols line: ");

    clearQueue(sourceQueue);
    clearQueue(englishQueue);
    clearQueue(otherQueue);

    return 0;
} 