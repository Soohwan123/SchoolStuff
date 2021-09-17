#include "Node.h"

Node::Node()
{
	this->data = "";
	this->next = nullptr;
}

Node::~Node()
{
	if (this->next) {
		delete this->next;
		this->next = nullptr;
	}
}