#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include <climits>
#include <fstream>
#include <sstream>
#include "graph.h"
#define SIZE 100000

// constructor
graph:: graph(){
    mapping = new hashTable(SIZE);
    size = 0;
}

bool graph::contains(const std::string &id){
    return mapping->contains(id);
}

void graph::insert(const std::string &name, const std::string &dest, int cost){
    node *origin;
    node *dest_Node;

    origin = insertNode(name);
    dest_Node = insertNode(dest);

    edge medge;
    medge.weight = cost;
    medge.connected = dest_Node;

    origin->adjacency.push_back(medge);
}

graph::node* graph::insertNode(const std::string &name){
    node *mnode;
    if(mapping->contains(name)){
        // node already exist
        mnode = (node*)mapping->getPointer(name);
    }else{
        // create new node for new vertix appeared
        mnode = new node;
        mnode->id = name;
        mnodeList.push_back(mnode);
        mapping->insert(name,mnode);
        size++;
    }

    return mnode;
}

void graph::dijkstra(const std::string &id){

    heap mHeap(size);
    node *origin = (node*)mapping->getPointer(id);

    origin->d = 0;
    origin->path.push_back(id);
    
    // insert all other nodes into the heap
    for(std::list<node *>::const_iterator it = mnodeList.begin(); it != mnodeList.end(); it++){
         mHeap.insert((*it)->id, (*it)->d, *it);
	}

    for(int i = 0; i < size; i++){
        node *mnode;
        mHeap.deleteMin(nullptr,nullptr, &mnode);
        mnode->known = true;
        
        // addint INT_MAX might cause overflow problem and made the sum to be negative so it is checked in the condition
        for (std::list<edge>::const_iterator it = mnode->adjacency.begin(); it != mnode->adjacency.end() && mnode->d != INT_MAX; it++){
            if (it->connected->known==false && (it->weight+mnode->d) < it->connected->d){
                it->connected->path.clear();
                it->connected->path.insert(it->connected->path.begin(), mnode->path.begin(), mnode->path.end());
                it->connected->path.push_back(it->connected->id);
                it->connected->d = it->weight + mnode->d;
				mHeap.setKey(it->connected->id, it->connected->d);
		    }
		}

    }
}

void graph::exportShortPath(const std::string &outName){
    std::ofstream output;
    output.open(outName);

    for(std::list<node *>::const_iterator it = mnodeList.begin(); it != mnodeList.end(); it++){
        if ((*it)->d == INT_MAX){
			output << (*it)->id << ": NO PATH" << std::endl;
        }else{
			output << (*it)->id << ": " << (*it)->d << " [";
            for (std::list<std::string>::const_iterator iter = (*it)->path.begin(); iter != --(*it)->path.end(); iter++){
				output << *iter << ", ";
            }
            
			output << (*it)->path.back() << "]" << std::endl;
		} 
	}
	output.close();
}