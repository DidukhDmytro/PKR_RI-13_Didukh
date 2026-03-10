#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

struct Node
{
    int data;
    Node* next;
};

int calculatePositiveSum(const Node* head)
{
    if (head == nullptr)
        return 0;

    int value = 0;

    if (head->data > 0)
        value = head->data;

    return value + calculatePositiveSum(head->next);
}

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestPositiveSumRecursive)
        {
            Node* n1 = new Node{ -2, nullptr };
            Node* n2 = new Node{ 5, nullptr };
            Node* n3 = new Node{ 3, nullptr };

            n1->next = n2;
            n2->next = n3;

            int result = calculatePositiveSum(n1);

            Assert::AreEqual(8, result);

            delete n1;
            delete n2;
            delete n3;
        }
    };
}