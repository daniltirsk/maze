#include <iostream>
#include <vector>
#include <istream>
#include <fstream>
#include <iterator>
#include <iomanip>
#include <set>


using namespace std;

#include "Labyrinth.h"

int main() {
	char infilename[] = "C:\\Users\\ASUS\\Desktop\\lebedev\\Grafy\\�����\\maze.bmp";
	Labyrinth l(infilename);

	l.findShortersPath();

	char outfilename[] = "C:\\Users\\ASUS\\Desktop\\lebedev\\Grafy\\�����\\solvedMaze.bmp";
	l.saveAsBMP(outfilename);

	return 0;
}