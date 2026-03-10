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
    int sum = 0;

    while (head != nullptr)
    {
        if (head->data > 0)
        {
            sum += head->data;
        }
        head = head->next;
    }

    return sum;
}

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestPositiveSum)
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