#pragma once

#ifndef _NODE_H
#define _NODE_H

#include <iostream>
#include <vector>
#include <istream>
#include <fstream>
#include <iterator>
#include <iomanip>
#include <set>

using namespace std;

class NodeException {};

class Node {
public:
	char name;
	int weight;
	Node();
	Node(char name);
	Node(char name, int weight);
};

#endif