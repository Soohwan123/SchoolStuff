#pragma once
#include <string>
//DECLARE CLASS Node
//DECLARE STRING data
//DECLARE Node pointer next
//DECLARE constructor
//DECLARE virtual destructor
//ENDDECLARE

class Node
{
public:
	Node();
	virtual ~Node();
	std::string data;
	Node* next;
};