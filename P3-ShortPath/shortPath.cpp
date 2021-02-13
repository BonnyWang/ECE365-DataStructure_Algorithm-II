#include "graph.h"
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>  
#include <list>
#include <iterator>

using namespace std;

void getInput(graph &mgraph);
string getOriginName(graph &mgraph);
void getOutput(graph &mgraph);

int main(){
    graph mgraph;
    ifstream input;
    string inName;
    string originName;
    clock_t start;
    clock_t end;
    
    getInput(mgraph);
    originName = getOriginName(mgraph);

    start = clock();
    mgraph.dijkstra(originName);
    end = clock();
    cout << "Total time (in seconds) to apply Dijkstra's algorithm:" << ((double)(end-start))/CLOCKS_PER_SEC <<endl;
    
    getOutput(mgraph);
}

void getInput(graph &mgraph){
    ifstream input;
    string inName;

    do{
        cout << "Enter a valid graph input file: ";
        cin >> inName;
        input.open(inName);
    }while (!input.is_open());

    string origin, dest;
    int cost;

    // Insert the information from the file to the graph
    while (input >> origin >> dest >> cost){
        mgraph.insert(origin,dest, cost);
    }

    input.close();
}

string getOriginName(graph &mgraph){
    string originName;
    do{
        cout << "Enter a valid vertex id for the starting vertex: ";
        cin >> originName;
    }while(!mgraph.contains(originName));

    return originName;
}

void getOutput(graph &mgraph){
    string outName;
    ofstream output;
	
    cout << "Enter name of output file: ";
    cin >> outName;

    mgraph.exportShortPath(outName);
}