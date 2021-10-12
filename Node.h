#pragma once
//DECLARE CLASS Node
//DECLARE Node pointer next
//DECLARE constructor
//DECLARE virtual destructor
//ENDDECLARE

class Node
{
public:
	Node();
	virtual ~Node();
	int data;
	Node* next;
};