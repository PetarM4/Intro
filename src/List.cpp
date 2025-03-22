#include "List.h"
#include "Node.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
LinkedList::LinkedList() {
	head = nullptr;
	tail = nullptr;
}

LinkedList* LinkedList::copy() const {
	LinkedList* newList = new LinkedList();
	Node* current = head;
	while (current != nullptr) {
		newList->append(new Node(current->x, current->y));
		current = current->next;
	}
	return newList;
}

void LinkedList::append(Node* newNode) {
	if (head == nullptr) {
		head = newNode;
		tail = newNode;
	}
	else {
		tail->next = newNode;
		tail = newNode;
	}
}

void LinkedList::split() {
	Node* current = head;
	while (current != nullptr && current->next != nullptr) {
		double midX = (current->x + current->next->x) / 2;
		double midY = (current->y + current->next->y) / 2;

		Node* newNode = new Node(midX, midY);
		newNode->next = current->next;
		current->next = newNode;

		current = newNode->next;
	}
}

void LinkedList::average() {
	Node* current = head;
	while (current != nullptr && current->next != nullptr) {
		current->x = (current->x + current->next->x) / 2;
		current->y = (current->y + current->next->y) / 2;

		Node* toDelete = current->next;
		current->next = current->next->next;
		delete toDelete;

		current = current->next;
	}
}

void LinkedList::subdivide() {
	split();
	average();
}

void LinkedList::insert(double x, double y) {
	Node* newNode = new Node(x, y);
	if (!head) { 
		head = newNode;
		tail = newNode;
	}
	else if (tail) { 
		tail->next = newNode;
		tail = newNode;
	}
}

void LinkedList::display() const {
	Node* temp = head;
	while (temp) {
		cout << "(" << temp->x << ", " << temp->y << ")\n";
		temp = temp->next;
	}
}

void LinkedList::readFromFile(const string& filename) {
	ifstream file(filename);
	if (!file) {
		cout << "Error opening file!" << endl;
		return;
	}
	string line;
	while (getline(file, line)) {
		stringstream ss(line);
		double x, y;
		char comma;
		if (ss >> x >> y) {
			Node* newNode = new Node(x, y);
			append(newNode);
		}
	}
	file.close();
}

void LinkedList::saveToFile(const string& filename) const {
	ofstream file(filename);
	Node* temp = head;
	while (temp) {
		file << temp->x << "," << temp->y << "\n";
		temp = temp->next;
	}
	file.close();
}
