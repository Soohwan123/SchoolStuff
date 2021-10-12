#include <stdlib.h>
#include <iostream>
#include "LinkedList.h"

int main() {

	//Create nodes
	Node* first = new Node();
	Node* second = new Node();
	Node* third = new Node();
	Node* fourth = new Node();
	Node* fifth = new Node();
	Node* sixth = new Node();
	Node* seventh = new Node();
	Node* eighth = new Node();

	//Set node values
	first->data = 1;
	second->data = 2;
	third->data = 3;
	fourth->data = 4;
	fifth->data = 5;
	sixth->data = 6;
	seventh->data = 7;
	eighth->data = 8;

	LinkedList* list = new LinkedList();

	list->append(first);
	list->append(second);
	list->append(third);
	list->append(fourth);
	list->append(fifth);
	list->append(sixth);
	list->append(seventh);
	list->append(eighth);

	//Ascending
	list->Ascending();
	list->traverse();

	std::cout << "\n";
	std::cout << "\n";
	//Descending
	list->Descending();
	list->traverse();


	std::cout << "\n";
	std::cout << "\n";
	//Odd_Even_Ascending
	list->Odd_Even_Ascending();
	list->traverse();


	std::cout << "\n";
	std::cout << "\n";
	//Odd_Even_Descending
	list->Odd_Even_Descending();
	list->traverse();




	return 0;
}