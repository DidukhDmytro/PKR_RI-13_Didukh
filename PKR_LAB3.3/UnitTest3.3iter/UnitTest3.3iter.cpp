#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ListTests
{
	struct Node {
		int data;
		Node* prev;
		Node* next;
	};

	Node* createNode(int value) {
		Node* n = new Node;
		n->data = value;
		n->prev = nullptr;
		n->next = nullptr;
		return n;
	}

	void appendNode(Node*& head, Node*& tail, int value) {
		Node* n = createNode(value);
		if (!head) {
			head = tail = n;
		}
		else {
			tail->next = n;
			n->prev = tail;
			tail = n;
		}
	}

	void deleteNode(Node*& head, Node*& tail, Node* node) {
		if (!node) return;

		if (node == head) head = node->next;
		if (node == tail) tail = node->prev;

		if (node->prev)
			node->prev->next = node->next;

		if (node->next)
			node->next->prev = node->prev;

		delete node;
	}

	void removeElementsAfterValue(Node*& head, Node*& tail, int target) {
		Node* current = head;

		while (current && current->next) {
			if (current->data == target) {
				Node* toDelete = current->next;
				current = toDelete->next; // рухаємося далі
				deleteNode(head, tail, toDelete);
			}
			else {
				current = current->next;
			}
		}
	}

	void clearList(Node*& head, Node*& tail) {
		Node* cur = head;
		while (cur) {
			Node* next = cur->next;
			delete cur;
			cur = next;
		}
		head = tail = nullptr;
	}

	TEST_CLASS(ListTests)
	{
	public:

		TEST_METHOD(RemoveAfterValue_Test)
		{
			Node* head = nullptr;
			Node* tail = nullptr;

			appendNode(head, tail, 1);
			appendNode(head, tail, 5);
			appendNode(head, tail, 7);
			appendNode(head, tail, 5);
			appendNode(head, tail, 9);

			removeElementsAfterValue(head, tail, 5);

			int expected[] = { 1, 5, 5 };

			Node* cur = head;
			for (int i = 0; i < 3; i++) {
				Assert::IsNotNull(cur);
				Assert::AreEqual(expected[i], cur->data);
				cur = cur->next;
			}

			Assert::IsNull(cur);

			clearList(head, tail);
		}
	};
}