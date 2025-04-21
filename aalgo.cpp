#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cmath>
using namespace std;


//need f,g,h and coordinates and previous for each cell
//have open set and vector of cells (each with f, g, h and coordinates and previous)
//check all neighbors adding them to open set if tentative g_score is less than g score
//also update g_score and f_score
//pick node in set with the lowest f_score!!
//go until current = result

struct Node
{
    int x, y;
    double f, g, h;
};

//custom comparator to sort the list based on minimal f_score
//structure found through Google search
struct f_score_comp
{
    bool operator() (const Node& a, const Node& b)
    {
        return a.f < b.f;
    }
};

double hEuclid(Node& test, Node& target)
{
    return sqrt(pow((test.x-target.x),2)+pow(test.y-target.y,2));
}

double aStar(Node source, Node target, map<Node, vector<pair<Node, double>>> edges)
{
    //the x,y of the source node and target node will have been pre-filled appropriately
    //x, y, f, g, and h must be pre-filled appropriately upon graph construction (h = hEuclid for all,
    //f and g = 0.0 for source and INFINITY elsewhere).

    set<Node, f_score_comp> open;
    //set<Node> closed;

    open.insert(source);

    while (!open.empty())
    {
        Node current = *open.begin();
        open.erase(open.begin());

        if (current.x == target.x && current.y == target.y)
        {
            return current.g;
        }

        vector<pair<Node, double>> neighbors = edges[current];
        for (pair<Node, double> edge : neighbors)
        {
            Node& test = edge.first;
            double new_g = current.g + edge.second;
            if (new_g < test.g)
            {
                //if test in closed{continue} else{
                open.insert(test);
                //} not sure how this helps but this would be the closed set implementation to improve efficiency
                test.g = new_g;
                test.f = new_g + test.h;
            }
        }
    }

    return -1;
}