#include <iostream>
#include <vector>
#include <istream>
#include <fstream>
#include <iterator>
#include <iomanip>
#include <set>


using namespace std;

vector<int> findNeighbours(int node, char* graph, int width, int height) {
    vector<int> neighbours;
    if (node < width * height && node > -1)
    {
        if (node % width + 1 < width) {
            if (graph[node+1] != 'b')
            {
                neighbours.push_back(node + 1);
            }
        }
        if (node % width - 1 > -1) {
            if (graph[node - 1] != 'b')
            {
                neighbours.push_back(node - 1);
            }
        }
        if (node + width < height * width) {
            if (graph[node + width] != 'b')
            {
                neighbours.push_back(node + width);
            }
        }
        if (node - width > -1) {
            if (graph[node - width] != 'b')
            {
                neighbours.push_back(node - width);
            }
        }
    }
    return neighbours;
}

int LiAlg(int node,int end, char* graph, int* graphWeights, vector<int> &visited,int width,int height) {
    set<int> queue;
    queue.insert(node);
    while (queue.size()>0 && graphWeights[end] < 0)
    {
        node = *queue.begin();
        queue.erase(queue.begin());
        visited.push_back(node);
        vector<int> neighbours = findNeighbours(node, graph, width, height);
        for (size_t i = 0; i < neighbours.size(); i++)
        {
            if (graphWeights[neighbours[i]] == -1)
            {
                graphWeights[neighbours[i]] = graphWeights[node] + 1;
            }
        }

        for (size_t i = 0; i < neighbours.size(); i++)
        {
            bool checked=false;
            for (size_t j = 0; j < visited.size(); j++)
            {
                if (visited[j]==neighbours[i])
                {
                    checked = true;
                }
            }
            if (!checked) queue.insert(neighbours[i]);
        }
    }

    return 0;

}

vector<int> shortestPath(int start, int end, char* graph, int* graphWeights, vector<int> &visited,int width,int height) {
    graphWeights[start] = 0;
    LiAlg(start, end, graph, graphWeights, visited, width, height);

    vector<int> path;
    int curNode = end;
    path.push_back(curNode);

    while (curNode!=start)
    {
        vector<int> neighbours = findNeighbours(curNode, graph, width, height);
        int min=INT_MAX;
        for (size_t i = 0; i < neighbours.size(); i++)
        {
            if (graphWeights[neighbours[i]] < min && graphWeights[neighbours[i]]>-1)
            {
                min = graphWeights[neighbours[i]];
                curNode = neighbours[i];
            }
        }
        path.push_back(curNode);
    }

    return path;
}

std::vector<char> readBMP(char* filename)
{
    cout << filename << endl;
    ifstream in(filename, ios::binary);
    unsigned char header[54];
    in.read((char*)&header, sizeof(header));
    unsigned int width = *(int*)&header[18];
    unsigned int height = *(int*)&header[22];

    cout << height << "  " << width << endl;

    unsigned char* pixels = new unsigned char[3*height*width];
    in.read((char*)pixels, 3*height*width);

    
    char* graph = new char[height * width];
    int* graphWeights = new int[height * width];
    int* pathGraph = new int[height * width];

    for (size_t i = 0; i < height*width; i++)
    {
        graphWeights[i] = -1;
    }

    int start;
    int end;

    for (int i = 0; i < height * width * 3; i += 3)
    {
        if ((int)pixels[i] == 255 && (int)pixels[i + 1] == 255 && (int)pixels[i + 2] == 255) {
            graph[i / 3] = 'w';
        }
        else if ((int)pixels[i + 2] > (int)pixels[i + 1] && (int)pixels[i + 2] > (int)pixels[i]) {
            graph[i / 3] = 'r';
            start = i / 3;
        }
        else if ((int)pixels[i + 1] > (int)pixels[i] && (int)pixels[i + 1] > (int)pixels[i+2]) {
            graph[i / 3] = 'g';
            end = i / 3;
        }
        else {
            graph[i / 3] = 'b';
        }
    }

    vector<int> visited;
    vector<int> path;
    cout << start << " " << end;

    path = shortestPath(start, end, graph, graphWeights, visited, width, height);

    for (size_t i = 0; i < path.size(); i+=1)
    {
        pixels[3*path[i]] = (char)255;
        pixels[3*path[i]+1] = (char)0;
        pixels[3*path[i]+2] = (char)0;
    }

    ofstream out("C:\\Users\\ASUS\\Desktop\\lebedev\\Grafy\\Графы\\new.bmp", ios::binary);
    out.write((char*)&header, sizeof(header));  
    out.write((char*)pixels, 3 * height * width);       
    out.close();

    vector<char> map;
    return map;
}


int main()
{
    char array[] = "C:\\Users\\ASUS\\Desktop\\lebedev\\Grafy\\Графы\\maze.bmp";
    vector <char> map;
    map = readBMP(array);
    return 0;
}