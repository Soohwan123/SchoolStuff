#include "LinkedList.h"

LinkedList::LinkedList()
{
	this->head = nullptr;
}

LinkedList::~LinkedList()
{
	if (this->head) {
		delete this->head;
		this->head = nullptr;
	}
}


bool LinkedList::append(Node* node)
{
	if (this->head == nullptr) {
		this->head = node;
		return true;
	}

	Node* current = this->head;
	while (current->next != nullptr)
	{
		current = current->next;
	}
	//we have reached the tail
	current->next = node;

	return true;
}

bool LinkedList::deleteByValue(int data)
{
	if (this->head == nullptr)
	{
		return false;
	}

	if (this->head->data == data) {
		this->head = this->head->next;
		return true;
	}

	Node* current = this->head;
	while (current->next != nullptr)
	{
		if (current->next->data == data) {
			current->next = current->next->next;
			return true;
		}
		current = current->next;
	}


	return false;
}

void LinkedList::traverse()
{
	Node* current = this->head;
	while (current != nullptr)
	{
		std::cout << current->data << std::endl;
		current = current->next;
	}
	std::cout << std::endl;
}




void LinkedList::Ascending() {

	Node* previousHead = this->head;
	Node* nextHead = previousHead->next;

	while (previousHead != nullptr)
	{
		while (nextHead != nullptr)
		{
			if (previousHead->data > nextHead->data)
			{
				swap(&previousHead->data, &nextHead->data);
			}
			nextHead = nextHead->next;
		}
		previousHead = previousHead->next;
		if (previousHead != nullptr) {
			nextHead = previousHead->next;
		}
	}
	while (nextHead != nullptr)
	{
		std::cout << nextHead->data << std::endl;
		nextHead = nextHead->next;
	}
	std::cout << std::endl;
}

void LinkedList::Descending()
{
	Node* previousHead = this->head;
	Node* nextHead = previousHead->next;

	while (previousHead != nullptr)
	{
		while (nextHead != nullptr)
		{
			if (previousHead->data < nextHead->data)
			{
				swap(&previousHead->data, &nextHead->data);
			}
			nextHead = nextHead->next;
		}
		previousHead = previousHead->next;
		if (previousHead != nullptr) {
			nextHead = previousHead->next;
		}
	}
	while (nextHead != nullptr)
	{
		std::cout << nextHead->data << std::endl;
		nextHead = nextHead->next;
	}
	std::cout << std::endl;
};


void LinkedList::Odd_Even_Ascending() 
{
	Node* previousHead = this->head;
	Node* nextHead = previousHead->next;
	while (previousHead != nullptr)
	{
		while (nextHead != nullptr)
		{
			if ((previousHead->data % 2) == 1)
			{
				if ((nextHead->data % 2) == 1)
				{
					if (previousHead->data > nextHead->data)
					{
						swap(&previousHead->data, &nextHead->data);
					}
				}
			}
			else if ((previousHead->data % 2) == 0)
			{
				if ((nextHead->data % 2) == 1)
				{
					swap(&previousHead->data, &nextHead->data);
				}
				else if ((nextHead->data % 2) == 0)
				{
					if (previousHead->data > nextHead->data)
					{
						swap(&previousHead->data, &nextHead->data);
					}
				}
			}
			nextHead = nextHead->next;
		}
		previousHead = previousHead->next;
		if (previousHead != nullptr) {
			nextHead = previousHead->next;
		}
	}
	while (nextHead != nullptr)
	{
		std::cout << nextHead->data << std::endl;
		nextHead = nextHead->next;
	}
	std::cout << std::endl;
};


void LinkedList::Odd_Even_Descending() 
{
	Node* previousHead = this->head;
	Node* nextHead = previousHead->next;
	while (previousHead != nullptr)
	{
		while (nextHead != nullptr)
		{
			if ((previousHead->data % 2) == 1)
			{
				if ((nextHead->data % 2) == 1)
				{
					if (previousHead->data < nextHead->data)
					{
						swap(&previousHead->data, &nextHead->data);
					}
				}
			}
			else if ((previousHead->data % 2) == 0)
			{
				if ((nextHead->data % 2) == 1)
				{
					swap(&previousHead->data, &nextHead->data);
				}
				else if ((nextHead->data % 2) == 0)
				{
					if (previousHead->data < nextHead->data)
					{
						swap(&previousHead->data, &nextHead->data);
					}
				}
			}
			nextHead = nextHead->next;
		}
		previousHead = previousHead->next;
		if (previousHead != nullptr) {
			nextHead = previousHead->next;
		}
	}
	while (nextHead != nullptr)
	{
		std::cout << nextHead->data << std::endl;
		nextHead = nextHead->next;
	}
	std::cout << std::endl;
};

