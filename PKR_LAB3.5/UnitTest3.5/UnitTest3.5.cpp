#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StackUnitTest
{
    struct Node
    {
        int data;
        Node* next;
    };

    void Push(Node*& top, int value)
    {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = top;
        top = newNode;
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

    void ClearStack(Node*& top)
    {
        while (top != nullptr)
        {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    TEST_CLASS(StackUnitTest)
    {
    public:

        TEST_METHOD(Test_GetStackLength)
        {
            Node* top = nullptr;

            Push(top, 10);
            Push(top, 20);
            Push(top, 30);

            int actual = GetStackLength(top);
            int expected = 3;

            Assert::AreEqual(expected, actual);

            ClearStack(top);
        }

    };
}