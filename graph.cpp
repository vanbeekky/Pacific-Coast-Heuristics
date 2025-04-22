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

std::pair<double,int> Graph::dijkstra(int start, int goal) {
    const double INF = std::numeric_limits<double>::infinity();
    std::vector<double> dist(N, INF);
    std::vector<char> visited(N, 0);
    dist[start] = 0.0;
    using NodePair = std::pair<double,int>;
    std::priority_queue<NodePair, std::vector<NodePair>, std::greater<NodePair>> pq;
    pq.emplace(0.0, start);
    int explored = 0;
    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if(visited[u]) continue;
        visited[u] = 1;
        ++explored;
        if(u == goal) return {d, explored};
        for(const auto& e : adj[u]) {
            int v = e.first;
            double w = e.second;
            if(visited[v]) continue;
            double nd = d + w;
            if(nd < dist[v]) {
                dist[v] = nd;
                pq.emplace(nd, v);
            }
        }
    }
    return {INF, explored};
}

std::pair<double,int> Graph::astar(int start, int goal) {
    if(!hasCoords) return dijkstra(start, goal);
    const double INF = std::numeric_limits<double>::infinity();
    std::vector<double> dist(N, INF);
    std::vector<char> visited(N, 0);
    auto heuristic = [&](int u) {
        double dx = coords[u].first  - coords[goal].first;
        double dy = coords[u].second - coords[goal].second;
        return std::sqrt(dx*dx + dy*dy);
    };
    dist[start] = 0.0;
    using State = std::tuple<double,double,int>;
    struct Compare { bool operator()(State const& a, State const& b) const {
        return std::get<0>(a) > std::get<0>(b);
    }};
    std::priority_queue<State, std::vector<State>, Compare> pq;
    pq.emplace(heuristic(start), 0.0, start);
    int explored = 0;
    while(!pq.empty()) {
        auto [f, g, u] = pq.top(); pq.pop();
        if(visited[u]) continue;
        visited[u] = 1;
        ++explored;
        if(u == goal) return {g, explored};
        for(auto const& e : adj[u]) {
            int v = e.first;
            double w = e.second;
            if(visited[v]) continue;
            double ng = g + w;
            if(ng < dist[v]) {
                dist[v] = ng;
                pq.emplace(ng + heuristic(v), ng, v);
            }
        }
    }
    return {INF, explored};
}
