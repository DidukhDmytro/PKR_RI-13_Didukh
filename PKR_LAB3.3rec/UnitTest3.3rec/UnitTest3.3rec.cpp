#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RecursiveListTests
{
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

	TEST_CLASS(RecursiveListTests)
	{
	public:

		TEST_METHOD(RemoveElementsAfterValueRecursive_Test)
		{
			Node* head = nullptr;
			Node* tail = nullptr;

			appendNodeRecursive(head, tail, 1);
			appendNodeRecursive(head, tail, 5);
			appendNodeRecursive(head, tail, 7);
			appendNodeRecursive(head, tail, 5);
			appendNodeRecursive(head, tail, 9);

			removeElementsAfterValueRecursive(head, tail, head, 5);

			int expected[] = { 1, 5, 5 };

			Node* current = head;
			for (int i = 0; i < 3; i++) {
				Assert::IsNotNull(current);
				Assert::AreEqual(expected[i], current->data);
				current = current->next;
			}

			Assert::IsNull(current);
			Assert::IsNotNull(tail);
			Assert::AreEqual(5, tail->data);

			clearListRecursive(head, tail);
		}
	};
}