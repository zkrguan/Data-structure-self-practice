#include <iostream>

//#define BLK1
//#define BLK2
//#define BLK3
//#define BLK4
#define BLK5
#define BLK6
#define BLK7
#define BLK8

/*
 
After study array and list. 
Time to practice. 
	How to implement a list in C++

*/

// simple list with one node starting from scratch // 
#ifdef BLK1
class Node {
public:
	// Data is stored //
	int data{};
	// Pointing at the next one//
	Node* next{};

};

int main() {
	// When the list is pointing at nothing, the list is empty // 
	Node* list{};
	Node* temp = new Node();
	temp->data = 4;
	// letting the list pointing at the first node// 
	list = temp;
	// You could have the temp pointed at null 
	// Cuz you let the list pointed at this, so you have two ptr pointed at the same resource. 
	temp = nullptr;
	std::cout << list->data << std::endl;
	// The first singly linked list created by us//
}

#endif // BLK1

//Basic operations on a list// 
#ifdef BLK2
class Node {
public:
	// Data is stored //
	int data{};
	// Pointing at the next one//
	Node* next{};
	Node(int src, Node* nxt) : data(src), next(nxt) {};
};



int main() {
	/* in this snippet, the list is working like stake LIFO*/
	/* head is always pointing at the first element*/
	Node* head{};
	int size,input{};
	std::cout << "how many numbers are we adding in?\n";
	std::cin >> size;

	for (int i = 0; i < size; i++){
		std::cout << "Enter the num you are adding\n";
		std::cin >> input;
		/*
			Now we need to think about how to add.
			and Node* head{};
		*/
		head = new Node(input, head);
		// display 
		// A very classic logic to tranverse through a list( singly )
		for (Node* p = head; p; p = p->next) {
			std::cout<<"current list contains: " << p->data << std::endl;
		}
	}
	
	// Remove first two elements
	// temp ptr pointing at head //
	Node* remove = head;
	// let head ptr pointing at next node//
	head = head->next;
	//delete remove's resource which is the head previously pointed at
	delete remove;
	// same process repeat one more time // 
	remove = head;
	head = head->next;
	delete remove;

	// remove the whole list// 
	// condition here is checking if the p is null
	while (Node* p = head){
		// you see the logic is acting like previous remove. 
		// always let the p pointed at the resource you would like to remove// 
		// let hte head move by one //
		// then delete the p // 
		head = head->next;
		delete p;
	}

	return 0;
}
#endif // BLK2


#ifdef BLK3
// implementation of the list // 

// stack, as we know, stack is LIFO. 
// Remove and add is from the head of the stack

class Data {
	int data{};
public:
	Data(int d = 0) :data(d) {};
	int out() const { return data; }
};

struct Node{
	Data data{};
	Node* next{};
	Node(const Data& d, Node* n) : data(d), next(n) {};
};

class Stack {
	Node* head{};
public:
	
	Stack() : head(nullptr) {};

	// A clean logic of the destructor like the previous code explained //
	~Stack() {
		while (Node* p = head){
			head = head->next;
			delete p;
		}
	}

	void push(int src) {
		head = new Node(src, head);
	}
	// returns Data after removed the Node //
	Data pop() {
		Data res{};
		// check if the head is not empty //
		if (head){
			Node* p = head;
			res = head->data;
			head = head->next;
			delete p;
		}
		return res;
	}

	bool empty() {
		return head == nullptr;
	}
};

int main() {
	Stack s;
	s.push(3);
	s.push(5);
	s.push(8);

	
	while (!s.empty()){
		std::cout << "Poppping the value --->" << s.pop().out() << " \n";
	}
	std::cout << "\n";
	return 0;
}
#endif // !BLK3



#ifdef BLK4
// Queue is another implementation of the ADT list
// adds from nodes from the tail and remove nodes from the head
// So it is FIFO
// Linked Lists - Queue


class Data {
	int data;
public:
	Data(int d = 0) : data(d) {}
	int out() const { return data; }
};

struct Node {
	Data data;
	Node* next;
	Node(const Data& d, Node* n) : data(d), next(n) {}
};

class Queue {
	Node* head;
	// Notice when we implement the queue, there is another variable called tail// 
	// This is mainly for pushing since queue add from the end///
	Node* tail;
public:
	Queue() : head(nullptr), tail(nullptr) {}
	~Queue() {

		while (Node* current = head) {
			head = head->next;
			delete current;
		}
	}
	void push(int d) {
		Node* p = new Node(d, 0);
		// if head is not empty//
		if (head)
			// old tail's next is this new node//
			tail->next = p;
		else
			// when first time running, the head is p, tail is also p //
			head = p;
		// now you let tail pointed at the new node!!!//
		// This is delicate// 
		tail = p;
	}

	// Same as the stack, nothing really fancy here//
	Data pop() {
		Data data;
		if (head) {
			Node* p = head;
			data = head->data;
			head = head->next;
			delete p;
			if (!head) tail = nullptr;
		}
		return data;
	}
	bool empty() { return head == nullptr; }
};

int main() {
	Queue q;

	// Push Data onto the Queue
	q.push(3);
	q.push(5);
	q.push(9);
	q.push(8);

	// Remove First Node
	q.pop();

	// Pop Data Off the Queue
	while (!q.empty())
		std::cout << q.pop().out() << ' ';
	std::cout << std::endl;
}


#endif // BLK4



#ifdef BLK5

template<typename Obj>
class List {


// Preparation before the list class //
private:
// Node class is declared inside the private part of the list class.
// struct members are all public, but inside the private part of list. 
// So all the members are visiable to the list class, but invisiable once it is out of the List class
	struct Node {
		Obj data{};
		Node* prev{};
		Node* next{};
		// default constructor and three args constructor //
		Node(const Obj& d = Obj{}, Node* p = nullptr, node* n = nullptr) :data{ d }, prev{ p }, next{ n }{};
		// move constructor//
		Node(const Obj&& d = Obj{}, Node* p = nullptr, node* n = nullptr) :data{ std::move(d) }, prev{ p }, next{ n }{};
	};

public:
	class const_iterator {
	// why is this protected?
	// Because you would like the iterator class inherit the members
	// But the other class can not reach it..

	protected:
		Node* current{};
		Obj& retrieve() const {
			return current-> data
		}
		// Also, you do not want all classes to see this constructor. 
		// Iterators should not be visiably constructed from pointers variables. 
		// So it can't be public. 
		// But List does not have the access to it too..
		const_iterator(Node* p):current{p}{}
		// That's why we use friend to let the List class have the access too. //
		// declaring the ownership//
		friend class List<Obj>;

	public:
		// Except the default constructor, all the other methods are overloading//
		const_iterator() :current{ nullptr } {

		}

		const Obj& operator* () const {
			return retrieve();
		}

		// here you can see prefix is faster //
		// Because you don't need to copy and return the old.// 
		const_iterator& operator ++() {
			current = current->next;
			return *this;
		}

		const_iterator operator++ (int) {
			const_iterator old = *this;
			++(*this);
			return old;
		}

		bool operator == (const const_iterator& rhs)const {
			return current == rhs.current;
		}

		bool operator!=(const const_iterator& rhs)const {
			return !(*this == rhs);
		}
	};

	// Here the iterator is inherited from const_iterator.
	// Why?
	// It makes sure the iterator class has the same functionality as const_iterator
	// In this class we are not adding more attributes. 
	// Also we are not change the behavior of an existing method. 
	// 
	class iterator : public const_iterator {
	protected:
		iterator(Node* p):const_iterator{p}{}
		friend class List<Obj>;
	public:
		// we do not have to implement the operator overloads
		// Because there is no more data added, the const_iterator methods can be used as well. 
		iterator() {}
		
		// These two are implemented explicitly 
		// Otherwise the original implemntationis hidden by the new version ( like 362 will override the 
		// the one from the inherited class
		Obj& operator*{
			return const_iterator::retrieve();
		}
		
		const Obj& operator* () const {
			return const_iterator::operator*();
		}

		iterator& operator++() {
			this->current = this->current->next;
			return *this;
		}

		iterator operator++(int) {
			iterator old = *this;
			++(*this);
			return old;
		}
	};

// Main body of the list
// Constructor and init and rule of 5
// Container structure //

private:
// The size is used for constant time of accessing if we keep track of the num of the elements. 
	int theSize;
// We create extra nodes at the front and the end to represent the begining and end marker
// sentinel nodes ( line 397 )
// Why? Without it , removing the first node would be the special case to handle//
// the removing algorithm in general needs to access the node before the node being removed. 

	Node* head;
	Node* tail;

public:
	List() {
		// This is to connect to the init() 
		init();
	}
	List(const List& rhs) {
		init();
		for (auto& x : rhs)
			push_back(x);
	}
	// deallocate the head and tail after clearing the list.//
	~List() {
		clear();
		delete head;
		delete tail;
	}
	// 
	List& operation(const List& rhs) {
		List copy = rhs;
		std::swap(*this, copy);
		return *this;
	}
	List(List&& rhs) :theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }{
		rhs.theSize = 0;
		rhs.head = nullptr;
		rhs.tail = nullptr;
	}

	List& operator = (const List& rhs) {
		List copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	List & operator = (List && rhs) {
		std::swap(theSize, rhs.theSize);
		std::swap(head, rhs.head);
		std::swap(tail, rhs.tail);
		return *this;
	}

	
	// Create a empty linked list//
	void init() {
		// We create extra nodes at the front and the end to represent the begining and end marker
		// sentinel nodes
		theSize = 0;
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->prev = head;
	}

	// Some common functions//
	iterator begin(){ return { head->next }; }
	const_iterator begin() const{ return { head->next }; }
	iterator end(){ return { tail }; }
	const_iterator end() const{ return { tail }; }
	int size() const { return theSize; }
	bool empty() const{ return size() == 0; }
	void clear(){
		while (!empty())
			pop_front();
	}

	Obj & front(){ return *begin(); }
	const Obj & front() const{ return *begin(); }
	Obj & back(){ return *--end(); }
	const Obj & back() const{ return *--end(); }
	void push_front(const Obj & x){ insert(begin(), x); }
	void push_front(Obj && x){ insert(begin(), std::move(x)); }
	void push_back(const Obj & x){ insert(end(), x); }
	void push_back(Obj && x){ insert(end(), std::move(x)); }
	void pop_front(){ erase(begin()); }
	void pop_back(){ erase(--end()); }
// insert logic
	//1. Inserting before itr:
	iterator insert(iterator itr, const Obj& x) {
		Node* p = itr.current;
		theSize++;
		return { p->prev = p->prev->next = new Node{x,p->prev,p} };
	}
	iterator insert(iterator itr, Obj&& x) {
		Node* p = itr.current;
		theSize++;
		return { p->prev = p->prev->next = new Node{std::move(x),p->prev,p} };
	}

	//2. Erase at itr
	iterator erase(iterator itr) {
		Node* p = itr.current;
		iterator retVal{ p->next };
		p->next->next = p->next;
		p->next->prev = p->prev;
		delete p;
		theSize--;
		return retVal;
	}

	iterator earse(iterator from, iterator to) {
		for (iterator itr = from; itr != to; itr = earse(itr););
		return to;
	}

};

#endif // BLK5
