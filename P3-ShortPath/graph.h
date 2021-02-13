#ifndef graph_h
#define graph_h

#include <string>
#include <list>
#include <fstream>
#include "heap.h"

class graph{
    int size;

    class node;
    class edge;

    std::list<node *> mnodeList;
    hashTable *mapping;

    class edge{
    public:
        int weight;
        node *connected;
    };

    // Represent Vertices
    class node{
    public:
        std::string id;
        bool known = false;
        int d = INT_MAX;
        std::list<edge> adjacency;
        std::list<std::string> path;
    };

    //Useful functions for internal operation
    node* insertNode(const std::string &name);

public:
    graph();

    bool contains(const std::string &id);
    void insert(const std::string &src, const std::string &dest, int cost);
    void dijkstra(const std::string &id);
    void exportShortPath(const std::string &outName);
};

#endif