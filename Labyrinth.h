#pragma once

#ifndef _LABYRINTH_H
#define _LABYRINTH_H

#include <iostream>
#include <vector>
#include <istream>
#include <fstream>
#include <iterator>
#include <iomanip>
#include <set>
#include "Node.h"

using namespace std;

class LabyrinthException {};

class Labyrinth {
private:
	unsigned char* pixels;
	unsigned char header[54];

	Node* graph;
	int height;
	int width;

	int start = -1;
	int end = -1;
	vector<int>shortestPath;
public:
	Labyrinth(char* filename);

	int saveAsBMP(char* filename);

	vector<int> findShortersPath();
	vector<int> findNeighbours(int nodeNumber);

};

#endif