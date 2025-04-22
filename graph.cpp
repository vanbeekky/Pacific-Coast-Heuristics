#include "Graph.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <limits>
#include <iostream>
#include <queue>
#include <tuple>

Graph::Graph(): N(0), hasCoords(false) {}

bool Graph::loadFromFiles(const std::string& nodeFile, const std::string& edgeFile) {
    N = 0;
    hasCoords = false;
    coords.clear();
    adj.clear();
    if(!nodeFile.empty()) {
        std::ifstream nf(nodeFile);
        int id; double lon, lat;
        while(nf >> id >> lon >> lat) {
            if(id >= N) {
                N = id + 1;
                coords.resize(N);
            }
            coords[id] = {lon, lat};
        }
        nf.close();
        hasCoords = true;
        adj.resize(N);
    }
    std::ifstream ef(edgeFile);
    std::string line;
    while(std::getline(ef, line)) {
        if(line.empty() || line[0]=='#') continue;
        std::istringstream iss(line);
        int u, v;
        if(!(iss >> u >> v)) continue;
        if(u >= N || v >= N) {
            int newN = std::max(u, v) + 1;
            coords.resize(newN);
            adj.resize(newN);
            N = newN;
        }
        double w = 1.0;
        if(hasCoords) {
            double dx = coords[u].first  - coords[v].first;
            double dy = coords[u].second - coords[v].second;
            w = std::sqrt(dx*dx + dy*dy);
        }
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    ef.close();
    return true;
}
