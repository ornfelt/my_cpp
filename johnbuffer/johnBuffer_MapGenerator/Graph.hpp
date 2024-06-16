#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED

#include <list>
#include <map>
#include "Region.hpp"

struct Node
{
    bool   marked = false;
    double dist   = -1;
    Node*  last   = nullptr;

    Region* region;
    std::list<Node*> neighbors;

    Node(Region* arg_region) : region(arg_region) {}

    void addNeighbour(Node* node);
    double distToNode(Node* node);
};

class Graph
{
public:
    Graph();
    void addConnection(Region* region1, Region* region2);

    std::vector<Region*> getPath(Region* region1, Region* region2);

private:
    std::list<Node> _nodes;
    std::map<Node*, Region*> _pairs;
    std::map<Region*, Node*> _reversePairs;

    void checkRegionRegistration(Region* region);
};

#endif // GRAPH_HPP_INCLUDED
