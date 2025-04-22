// main.cpp
#include <iostream>
#include <chrono>
#include <iomanip>
#include "Graph.h"

int main(int argc, char* argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string edgeFile, nodeFile;
    if(argc < 2) {
        std::cout << "Edge list file: ";
        std::cin  >> edgeFile;
        std::cout << "Node file or 'none': ";
        std::cin  >> nodeFile;
        if(nodeFile == "none") nodeFile.clear();
    } else {
        edgeFile = argv[1];
        if(argc >= 3 && std::string(argv[2]) != "none")
            nodeFile = argv[2];
    }

    Graph G;
    if(!G.loadFromFiles(nodeFile, edgeFile)) return 1;
    std::cout << "Nodes: " << G.N << "\n";

    while(true) {
        std::cout << "Start, goal (-1 -1 to quit): ";
        int start, goal;
        if(!(std::cin >> start >> goal) || start<0 || goal<0) break;
        if(start >= G.N || goal >= G.N) {
            std::cout << "Invalid IDs\n";
            continue;
        }
        auto t1 = std::chrono::high_resolution_clock::now();
        auto [dD, nD] = G.dijkstra(start, goal);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto [dA, nA] = G.astar(start, goal);
        auto t3 = std::chrono::high_resolution_clock::now();

        double timeD = std::chrono::duration<double, std::milli>(t2 - t1).count();
        double timeA = std::chrono::duration<double, std::milli>(t3 - t2).count();

        std::cout << std::fixed << std::setprecision(6)
                  << "Distance: " << dD << "\n"
                  << "Dijkstra: " << nD << " nodes, " << timeD << " ms\n"
                  << "A*:       " << nA << " nodes, " << timeA << " ms\n";
    }
    return 0;
}
