#pragma once
#include <iostream>
#include <stack>
#include <vector>
#include <string>

struct Node
{
	std::string data;
	Node* next = 0;
	Node* down = 0;
	int deep;

	Node(std::string data = "", int deep = 0)
	{
		this->data = data;
		this->deep = deep;
		next = nullptr;
		down = nullptr;
	}

	void print()
	{
		std::cout << deep << ". " << data << "\n";
		if (down != 0)
		{
			Node* tempDown = down;
			tempDown->print();
		}
		if (next != 0)
		{
			Node* tempNext = next;
			tempNext->print();
		}
	}

	friend std::ostream& operator<<(std::ostream& out, const Node node)
	{
		out << node.deep << ". " << node.data << "\n";
		return out;
	}

	~Node()
	{
		next = nullptr;
		down = nullptr;
	}
};

struct MyIterator
{
	Node* it = nullptr;

	std::pair<int, std::string> operator*()
	{
		return std::pair<int, std::string>(it->deep, it->data);
	}

	std::pair<int, std::string> operator->() 
	{
		return std::pair<int, std::string>(it->next->deep, it->next->data);
	}

	MyIterator next()
	{
		if (it->next == nullptr)
			throw "Cannot be reached";
		it = it->next;
		return *this;
	}

	MyIterator endNext()
	{
		if (it != nullptr)
			while (it->next != nullptr)
				next();
		return *this;
	}

	MyIterator nextLevel()
	{
		if (it->down == nullptr)
			throw "Cannot be reached";
		it = it->down;
		return *this;
	}

	MyIterator endNextLevel()
	{
		if (it != nullptr)
			while (it->down != nullptr)
				nextLevel();
		return *this;
	}

	void insertNext(std::string data)
	{
		if (it == nullptr)
			it = new Node(data);
		else
		{
			int lev = it->deep;
			it->next = new Node(data, lev);
		}
	}	
	void insertDown(std::string data)
	{
		if (it == nullptr)
			it = new Node(data);
		int lev = it->deep;
		it->down = new Node(data, lev + 1);
	}

	bool operator==(const MyIterator& iterator)
	{
		return (this->it->data == iterator.it->data && this->it->deep == iterator.it->deep);
	}
	bool operator!=(const MyIterator& iterator)
	{
		return (this->it->data != iterator.it->data || this->it->deep != iterator.it->deep);
	}
};

class MyList
{
	Node* begin = nullptr;
	Node* end = nullptr;
public:
	~MyList()
	{
		if (begin == nullptr)
			return;

		std::stack<Node*> stack;
		stack.push(begin);

		Node* lastElement = getEnd().it;
		while (lastElement->next != nullptr || lastElement->down != nullptr)
		{
			if (lastElement->next != nullptr)
				lastElement = lastElement->next;
			else
				lastElement = lastElement->down;
		}


		while (lastElement->next != nullptr || lastElement->down != nullptr)
		{
			Node* temp = stack.top();
			stack.pop();
			if (temp->next != nullptr)
				stack.push(temp->next);
			if (temp->down != nullptr)
				stack.push(temp->down);
			delete temp;
			temp = nullptr;
		}
	}
	
	std::pair<int, std::string> pop()
	{
		std::pair<int, std::string> p(end->deep, end->data);
		Node* temp = begin;
		while (temp->next != end)
		{
			temp = temp->next;
		}
		delete temp->next;
		temp->next = nullptr;
		end = temp;
		return p;
	}

	MyIterator getBegin()
	{
		MyIterator temp;
		temp.it = begin;
		return temp;
	}

	MyIterator getEnd()
	{
		MyIterator temp;
		temp.it = begin;
		temp.endNext();
		return temp;
	}

	void push_back_current_level(std::string data)
	{
		MyIterator temp;
		temp = getBegin();
		temp.endNext();
		temp.insertNext(data);

		begin = temp.it;
		end = getEnd().it;
	}

	void push_back_next_level(std::string data)
	{
		MyIterator temp;
		temp = getBegin();
		temp.endNextLevel();
		temp.insertDown(data);

		begin = temp.it;
		end = getEnd().it;
	}

	void print()
	{
		begin->print();
	}
};