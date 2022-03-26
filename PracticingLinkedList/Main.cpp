#include <stdlib.h>
#include <iostream>
#include "LinkedList.h"

int main() {

	//Create 3 nodes
	Node* first = new Node();
	Node* second = new Node();
	Node* third = new Node();

	//Set node values
	first->data = "first";
	second->data = "second";
	third->data = "third";

	LinkedList* list = new LinkedList();
	//list->head = first;
	//list->head->next = second;
	//list->head->next->next = third;

	list->append(first);
	list->append(second);
	list->append(third);

	list->traverse();

	//Test delete by value
	list->deleteByValue("first");

	list->traverse();


	//Clean up
	if (first) {
		delete first;
		first = nullptr;
	}
	if (second) {
		delete second;
		second = nullptr;
	}
	if (third) {
		delete third;
		third = nullptr;
	}
	if (list) {
		delete list;
		list = nullptr;
	}


	return 0;
}