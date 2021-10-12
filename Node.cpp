#include "Node.h"

Node::Node()
{
	this->data = 0;
	this->next = nullptr;
}

Node::~Node()
{
	if (this->next) {
		delete this->next;
		this->next = nullptr;
	}
}