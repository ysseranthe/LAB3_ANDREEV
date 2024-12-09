#pragma once
#include <map>
#include <vector>
#include <iostream>
#include "pipe.h"
#include "cs.h"
#include "file.h"
using namespace std;

class cs;
class pipe;
class GasNetwork {
private:
    map<int, vector<pair<int, int>>> adjList;

public:
    void addConnection(int startCS, int endCS, int pipeId);
    void showConnections();

    vector<int> topologicalSort();
    bool isPipeInUse(int pipeId) const;
    void removeConnections(int elementId, const string& type);
};

void connectStations(map<int, pipe>& Pipes, GasNetwork& network, map<int, cs>& Css, int& pipeId);
void performTopologicalSort(GasNetwork& network);