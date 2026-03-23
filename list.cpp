#include <iostream>

template <typename T>
struct Node {

	Node(T&& val) : data(val) {}

	Node(T&& val, Node* next, Node* prev) : data(val), prev(next), next(prev) {}

	T data;
	Node* prev;
	Node* next;
};

template <typename T>
struct MyList {
	struct FakeNode
	{
		Node<T>* begin = nullptr;
		Node<T>* end = nullptr;
	};

	MyList() = default;

	using nodeType = Node<T>;

	void push_back(T&& val) {
		if (size_ == 0) {
			nodeType* temp = new nodeType(std::forward<T>(val));
			beginEnd.begin = temp;
			beginEnd.end = temp;
			temp->next = nullptr;
			temp->prev = beginEnd.begin;
		}
		else {
			nodeType* temp = new nodeType(std::forward<T>(val));
			nodeType* last = beginEnd.end;
			last->next = temp;
			temp->prev = last;
			beginEnd.end = temp;
			temp->next = nullptr;
		}
		size_++;
	}

	void push_front(T&& val) {
		if (size_ == 0) {
			nodeType* temp = new nodeType(val);
			beginEnd.begin = temp;
			beginEnd.end = temp;
			temp->next = nullptr;
			temp->prev = beginEnd.begin;
		}
		else {
			nodeType* temp = new nodeType(val);
			nodeType* first = beginEnd.begin;
			first->prev = temp;
			temp->next = first;
			beginEnd.begin = temp;
			temp->prev = nullptr;
		}
		size_++;
	}

	void print() {
		nodeType* curr_node = beginEnd.begin;
		while (curr_node->next != nullptr) {
			std::cout << curr_node->data << " -> ";
			curr_node = curr_node->next;
		}
		std::cout << curr_node->data << "\n";
	}

	size_t size() {
		return size_;
	}

	~MyList() {
		if (size_ != 0) {
			nodeType* curr_node = beginEnd.begin;
			while (curr_node->next != nullptr) {
				curr_node = curr_node->next;
				delete curr_node->prev;
			}
			delete curr_node;
		}
	}

	FakeNode beginEnd;
	size_t size_ = 0;
};

int main() {
	MyList<int> myList;
	myList.push_back(5);
	myList.push_back(6);
	myList.push_back(7);
	myList.push_back(8);
	myList.push_back(9);
	myList.print();
}
