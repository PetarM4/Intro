#include <fstream>
#include <sstream>
#include "Node.h"
using namespace std;

class LinkedList {
private:
	
public:
	Node* head;
	Node* tail;
	LinkedList();
	LinkedList* copy() const;
	void append(Node* newNode);
	void split();
	void average();
	void subdivide();
	void insert(double x, double y);
	void display() const;
	void readFromFile(const string& filename);
	void saveToFile(const string& filename) const;
};
