#pragma once
#include "Node.h"
#include <iostream>
//DECLARE CLASS LinkedList
//DECLARE Node pointer head
//DECLARE constructor
//DECLARE virtual destructor
//DECLARE bool append(Node pointer node) method
//DECLARE bool prePend(Node pointer node) method
//DECLARE bool deleteByValue(STRING data) method
//DECLARE void traverse method
//ENDDECLARE

class LinkedList
{
public:
	LinkedList();
	virtual ~LinkedList();
	Node* head;
	bool append(Node* node);
	bool deleteByValue(std::string data);
	void traverse();
};