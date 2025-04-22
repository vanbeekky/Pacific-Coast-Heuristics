#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
#include <string>

class Graph {
public:
    // Graph data
    int N;
    bool hasCoords;
    std::vector<std::pair<double,double>> coords;
    std::vector<std::vector<std::pair<int,double>>> adj;

    Graph();
    bool loadFromFiles(const std::string& nodeFile, const std::string& edgeFile);
    std::pair<double,int> dijkstra(int start, int goal);
    std::pair<double,int> astar(int start, int goal);
};

#endif
