#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

class Node {
public:

    double x;
    double y;
    Node* next;

    Node(double x, double y) {
        this->x = x;
        this->y = y;
        this->next = nullptr;
    }
};
#endif
