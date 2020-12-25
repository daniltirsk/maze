#include <iostream>
#include <iomanip>  

#include "Node.h"

using namespace std;

Node::Node(char name, int weigh) {
	this->name = name;
	this->weight = weight;
}

Node::Node(char name) {
	this->name = name;
	this->weight = -1;
}

Node::Node() {
	this->name = 'e';
	this->weight = -1;
}
