#include <iostream>
#include <iomanip>  

#include "Labyrinth.h"

Labyrinth::Labyrinth(char* filename) {
    ifstream in(filename, ios::binary);
    if (!in)
    {
        cout << "Couldn't open the file!" << endl;
        throw LabyrinthException();
    }

    in.read((char*)&this->header, sizeof(this->header));

    this->width = *(int*)&this->header[18];
    this->height = *(int*)&this->header[22];

    this->graph = new Node[this->width * this->height];

    this->pixels = new unsigned char[3 * height * width];
    in.read((char*)this->pixels, 3 * this->height * this->width);

    for (int i = 0; i < this->height * this->width * 3; i += 3)
    {
        if ((int)pixels[i] == 255 && (int)pixels[i + 1] == 255 && (int)pixels[i + 2] == 255) {
            this->graph[i / 3] = Node('w');
        }
        else if ((int)pixels[i + 2] > (int)pixels[i + 1] && (int)pixels[i + 2] > (int)pixels[i]) {
            this->graph[i / 3] = Node('r');
            this->start = i / 3;
        }
        else if ((int)pixels[i + 1] > (int)pixels[i] && (int)pixels[i + 1] > (int)pixels[i + 2]) {
            this->graph[i / 3] = Node('g');
            this->end = i / 3;
        }
        else {
            this->graph[i / 3] = Node('b');
        }
    }
}

vector<int> Labyrinth::findNeighbours(int nodeNumber) {
    vector<int> neighbours;

    if (nodeNumber < this->width * this->height && nodeNumber > -1)
    {
        if (nodeNumber % this->width + 1 < this->width) {
            if (graph[nodeNumber + 1].name != 'b')
            {
                neighbours.push_back(nodeNumber + 1);
            }
        }
        if (nodeNumber % width - 1 > -1) {
            if (graph[nodeNumber - 1].name != 'b')
            {
                neighbours.push_back(nodeNumber - 1);
            }
        }
        if (nodeNumber + width < height * width) {
            if (graph[nodeNumber + width].name != 'b')
            {
                neighbours.push_back(nodeNumber + width);
            }
        }
        if (nodeNumber - width > -1) {
            if (graph[nodeNumber - width].name != 'b')
            {
                neighbours.push_back(nodeNumber - width);
            }
        }
    }
    return neighbours;
}

vector<int> Labyrinth::findShortersPath() {
    this->graph[this->start].weight = 0;
    
    set<int> queue;
    queue.insert(this->start);

    Node node;
    int nodeNumber;
    vector<int> visited;
    vector<int> neighbours;

    while (queue.size() > 0 && this->graph[this->end].weight < 0)
    {
        nodeNumber = *queue.begin();
        node = this->graph[*queue.begin()];
        queue.erase(nodeNumber);
        visited.push_back(nodeNumber);
        neighbours = this->findNeighbours(nodeNumber);

        for (size_t i = 0; i < neighbours.size(); i++)
        {
            if (this->graph[neighbours[i]].weight == -1)
            {
                this->graph[neighbours[i]].weight = this->graph[nodeNumber].weight + 1;
            }
        }

        for (size_t i = 0; i < neighbours.size(); i++)
        {
            bool checked = false;
            for (size_t j = 0; j < visited.size(); j++)
            {
                if (visited[j] == neighbours[i])
                {
                    checked = true;
                }
            }
            if (!checked) queue.insert(neighbours[i]);
        }
    }

    vector<int> path;
    int curNode = this->end;
    path.push_back(curNode);

    while (curNode != start)
    {
        neighbours = this->findNeighbours(curNode);
        int min = INT_MAX;
        for (size_t i = 0; i < neighbours.size(); i++)
        {
            if (this->graph[neighbours[i]].weight < min && this->graph[neighbours[i]].weight>-1)
            {
                min = this->graph[neighbours[i]].weight;
                curNode = neighbours[i];
            }
        }
        path.push_back(curNode);
    }
    this->shortestPath = path;
    return path;
}

int Labyrinth::saveAsBMP(char* filename) {

    ofstream out(filename, ios::binary);
    if (!out)
    {
        cout << "Couldn't open the file!" << endl;
        throw LabyrinthException();
    }

    for (size_t i = 0; i < shortestPath.size(); i += 1)
    {
        pixels[3 * this->shortestPath[i]] = (char)255;
        pixels[3 * this->shortestPath[i] + 1] = (char)0;
        pixels[3 * this->shortestPath[i] + 2] = (char)0;
    }

    out.write((char*)&this->header, sizeof(this->header));
    out.write((char*)this->pixels, 3 * this->height * this->width);
    out.close();

    return 0;
}