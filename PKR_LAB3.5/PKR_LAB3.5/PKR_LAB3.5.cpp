#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Node
{
    int data;
    Node* next;
};

void InitStack(Node*& top)
{
    top = nullptr;
}

bool IsEmpty(const Node* top)
{
    return top == nullptr;
}

void Push(Node*& top, int value)
{
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = top;
    top = newNode;
}

bool Pop(Node*& top, int& value)
{
    if (IsEmpty(top))
    {
        return false;
    }

    Node* temp = top;
    value = top->data;
    top = top->next;
    delete temp;
    return true;
}

void ClearStack(Node*& top)
{
    int value;
    while (Pop(top, value))
    {
    }
}

int GetStackLength(const Node* top)
{
    int count = 0;
    const Node* current = top;

    while (current != nullptr)
    {
        count++;
        current = current->next;
    }

    return count;
}

void PrintStack(const Node* top, const string& stackName)
{
    cout << stackName << " (top -> bottom): ";

    if (top == nullptr)
    {
        cout << "empty" << endl;
        return;
    }

    const Node* current = top;
    while (current != nullptr)
    {
        cout << current->data;
        if (current->next != nullptr)
        {
            cout << " ";
        }
        current = current->next;
    }

    cout << endl;
}

vector<int> ReadValuesFromKeyboard()
{
    vector<int> values;
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter " << n << " integers:" << endl;
    for (int i = 0; i < n; i++)
    {
        int value;
        cin >> value;
        values.push_back(value);
    }

    return values;
}

vector<int> ReadValuesFromFile(const string& fileName)
{
    vector<int> values;
    ifstream fin(fileName);

    if (!fin.is_open())
    {
        cout << "Cannot open file: " << fileName << endl;
        return values;
    }

    int value;
    while (fin >> value)
    {
        values.push_back(value);
    }

    fin.close();
    return values;
}

void FillStackFromVector(Node*& top, const vector<int>& values)
{
    ClearStack(top);

    for (int i = 0; i < static_cast<int>(values.size()); i++)
    {
        Push(top, values[i]);
    }
}

void InputStackFromKeyboard(Node*& top)
{
    vector<int> values = ReadValuesFromKeyboard();
    FillStackFromVector(top, values);
}

void InputStackFromFile(Node*& top, const string& fileName)
{
    vector<int> values = ReadValuesFromFile(fileName);
    FillStackFromVector(top, values);
}

vector<int> StackToVector(const Node* top)
{
    vector<int> values;
    const Node* current = top;

    while (current != nullptr)
    {
        values.push_back(current->data);
        current = current->next;
    }

    return values;
}

Node* CreateStackFromTopToBottomSequence(const vector<int>& values)
{
    Node* newTop = nullptr;

    for (int i = static_cast<int>(values.size()) - 1; i >= 0; i--)
    {
        Push(newTop, values[i]);
    }

    return newTop;
}

Node* ConcatenateStacks(const Node* top1, const Node* top2)
{
    vector<int> values1 = StackToVector(top1);
    vector<int> values2 = StackToVector(top2);

    vector<int> combined;

    for (int i = 0; i < static_cast<int>(values1.size()); i++)
    {
        combined.push_back(values1[i]);
    }

    for (int i = 0; i < static_cast<int>(values2.size()); i++)
    {
        combined.push_back(values2[i]);
    }

    return CreateStackFromTopToBottomSequence(combined);
}

int ChooseInputMethod()
{
    int choice;
    cout << "Choose input method:" << endl;
    cout << "1 - keyboard" << endl;
    cout << "2 - file" << endl;
    cout << "Your choice: ";
    cin >> choice;
    return choice;
}

void InputStack(Node*& top, const string& stackName)
{
    cout << endl;
    cout << "Input for " << stackName << endl;

    int choice = ChooseInputMethod();

    if (choice == 1)
    {
        InputStackFromKeyboard(top);
    }
    else if (choice == 2)
    {
        string fileName;
        cout << "Enter file name: ";
        cin >> fileName;
        InputStackFromFile(top, fileName);
    }
    else
    {
        cout << "Invalid choice. Stack will be empty." << endl;
        ClearStack(top);
    }
}

int main()
{
    Node* stack1;
    Node* stack2;
    Node* stack3;

    InitStack(stack1);
    InitStack(stack2);
    InitStack(stack3);

    InputStack(stack1, "Stack 1");
    InputStack(stack2, "Stack 2");

    cout << endl;
    PrintStack(stack1, "Stack 1");
    PrintStack(stack2, "Stack 2");

    cout << "Length of Stack 1: " << GetStackLength(stack1) << endl;
    cout << "Length of Stack 2: " << GetStackLength(stack2) << endl;

    stack3 = ConcatenateStacks(stack1, stack2);

    cout << endl;
    PrintStack(stack3, "Concatenated Stack");

    cout << "Length of Concatenated Stack: " << GetStackLength(stack3) << endl;

    cout << endl;
    cout << "All stacks:" << endl;
    PrintStack(stack1, "Stack 1");
    PrintStack(stack2, "Stack 2");
    PrintStack(stack3, "Concatenated Stack");

    ClearStack(stack1);
    ClearStack(stack2);
    ClearStack(stack3);

    return 0;
}