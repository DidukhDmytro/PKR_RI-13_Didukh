#include "pch.h"
#include "CppUnitTest.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace QueueLabTests
{
    TEST_CLASS(QueueTests)
    {
    public:

        struct Node
        {
            char data;
            Node* next;
        };

        struct Queue
        {
            Node* front;
            Node* rear;
        };

        void initQueue(Queue& q)
        {
            q.front = nullptr;
            q.rear = nullptr;
        }

        bool isEmpty(const Queue& q)
        {
            return q.front == nullptr;
        }

        void enqueue(Queue& q, char value)
        {
            Node* newNode = new Node{ value, nullptr };

            if (isEmpty(q))
            {
                q.front = newNode;
                q.rear = newNode;
            }
            else
            {
                q.rear->next = newNode;
                q.rear = newNode;
            }
        }

        bool dequeue(Queue& q, char& value)
        {
            if (isEmpty(q))
            {
                return false;
            }

            Node* temp = q.front;
            value = temp->data;
            q.front = q.front->next;

            if (q.front == nullptr)
            {
                q.rear = nullptr;
            }

            delete temp;
            return true;
        }

        void fillQueueFromString(Queue& q, const string& line)
        {
            for (char ch : line)
            {
                enqueue(q, ch);
            }
        }

        bool isEnglishLetter(char ch)
        {
            return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
        }

        void splitQueue(const Queue& source, Queue& englishQueue, Queue& otherQueue)
        {
            Node* current = source.front;

            while (current != nullptr)
            {
                if (isEnglishLetter(current->data))
                {
                    enqueue(englishQueue, current->data);
                }
                else
                {
                    enqueue(otherQueue, current->data);
                }

                current = current->next;
            }
        }

        string queueToString(const Queue& q)
        {
            string result = "";
            Node* current = q.front;

            while (current != nullptr)
            {
                result += current->data;
                current = current->next;
            }

            return result;
        }

        void clearQueue(Queue& q)
        {
            char temp;
            while (dequeue(q, temp))
            {
            }
        }

        TEST_METHOD(TestQueueInitiallyEmpty)
        {
            Queue q;
            initQueue(q);

            Assert::IsTrue(isEmpty(q));
            Assert::IsTrue(q.front == nullptr);
            Assert::IsTrue(q.rear == nullptr);
        }

        TEST_METHOD(TestEnqueueOneElement)
        {
            Queue q;
            initQueue(q);

            enqueue(q, 'A');

            Assert::IsFalse(isEmpty(q));
            Assert::AreEqual('A', q.front->data);
            Assert::AreEqual('A', q.rear->data);
        }

        TEST_METHOD(TestEnqueueSeveralElements)
        {
            Queue q;
            initQueue(q);

            enqueue(q, 'A');
            enqueue(q, 'b');
            enqueue(q, '1');

            string actual = queueToString(q);
            Assert::AreEqual(string("Ab1"), actual);

            clearQueue(q);
        }

        TEST_METHOD(TestDequeueWorksCorrectly)
        {
            Queue q;
            initQueue(q);

            enqueue(q, 'X');
            enqueue(q, 'Y');

            char value;
            bool result = dequeue(q, value);

            Assert::IsTrue(result);
            Assert::AreEqual('X', value);

            string actual = queueToString(q);
            Assert::AreEqual(string("Y"), actual);

            clearQueue(q);
        }

        TEST_METHOD(TestDequeueFromEmptyQueue)
        {
            Queue q;
            initQueue(q);

            char value = '0';
            bool result = dequeue(q, value);

            Assert::IsFalse(result);
            Assert::AreEqual('0', value);
        }

        TEST_METHOD(TestIsEnglishLetter)
        {
            Assert::IsTrue(isEnglishLetter('A'));
            Assert::IsTrue(isEnglishLetter('z'));
            Assert::IsFalse(isEnglishLetter('5'));
            Assert::IsFalse(isEnglishLetter('!'));
            Assert::IsFalse(isEnglishLetter('Я'));
        }

        TEST_METHOD(TestFillQueueFromString)
        {
            Queue q;
            initQueue(q);

            fillQueueFromString(q, "Hello!");

            string actual = queueToString(q);
            Assert::AreEqual(string("Hello!"), actual);

            clearQueue(q);
        }

        TEST_METHOD(TestSplitQueue)
        {
            Queue source;
            Queue englishQueue;
            Queue otherQueue;

            initQueue(source);
            initQueue(englishQueue);
            initQueue(otherQueue);

            fillQueueFromString(source, "Ab1!Я");

            splitQueue(source, englishQueue, otherQueue);

            string english = queueToString(englishQueue);
            string other = queueToString(otherQueue);
            string sourceText = queueToString(source);

            Assert::AreEqual(string("Ab"), english);
            Assert::AreEqual(string("1!Я"), other);
            Assert::AreEqual(string("Ab1!Я"), sourceText);

            clearQueue(source);
            clearQueue(englishQueue);
            clearQueue(otherQueue);
        }

        TEST_METHOD(TestOrderIsPreserved)
        {
            Queue source;
            Queue englishQueue;
            Queue otherQueue;

            initQueue(source);
            initQueue(englishQueue);
            initQueue(otherQueue);

            fillQueueFromString(source, "C@b#A1");

            splitQueue(source, englishQueue, otherQueue);

            Assert::AreEqual(string("CbA"), queueToString(englishQueue));
            Assert::AreEqual(string("@#1"), queueToString(otherQueue));

            clearQueue(source);
            clearQueue(englishQueue);
            clearQueue(otherQueue);
        }
    };
} 