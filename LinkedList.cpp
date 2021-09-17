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


//DECLARE current Node pointer variable
//set current = head
//
//IF current pointer to node is null then
//list is empty
//set head to INPUT node pointer
//RETURN true
//ENDIF
//
//while current next pointer is not null
//SET current to current next pointer
//endwhile
//
//SET current next pointer = INPUT node
//RETURN true

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

//IF heat pointer is null then
//return false
//ENDIF
//
//#special case what if head is the node we want to delete
//IF head pointer data = INPUT data then
//set head pointer to head next pointer
//RETURN true
//ENDIF
//
//DECLARE current Node pointer variable
//set current = head
//
//while current next pointer is not null
//IF current next pointer data == INPUT data
//#cut out the node that has to be removed
//SET current pointer next = current pointer next next
//RETURN true
//ENDIF
//endwhile
//
//RETURN false

bool LinkedList::deleteByValue(std::string data)
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

//DECLARE current Node pointer variable
//set current = head
//
//while current pointer is not null
//DISPLAY current pointer data
//SET current pointer to current pointer next
//endwhile
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