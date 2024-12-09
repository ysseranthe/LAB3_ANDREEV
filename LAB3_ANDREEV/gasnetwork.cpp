#include "gasnetwork.h"
#include <queue>
#include <iostream>
#include <stdexcept>
#include <utility>

using namespace std;

void GasNetwork::addConnection(int startCS, int endCS, int pipeId) {
    adjList[startCS].push_back({ endCS, pipeId });
    cout << "Connected CS " << startCS << " -> CS " << endCS << " by Pipe ID " << pipeId << endl;
}

void GasNetwork::showConnections() {
    for (const auto& pair : adjList) {
        int cs = pair.first;
        const auto& neighbors = pair.second;

        cout << "CS " << cs << " connects to:" << endl;
        for (const auto& connection : neighbors) {
            int neighbor = connection.first;
            int pipeId = connection.second;
            cout << "  --- CS " << neighbor << " by Pipe ID " << pipeId << endl;
        }
        cout << "-------------------------" << endl;
    }
}

vector<int> GasNetwork::topologicalSort() {
    map<int, int> inDegree; 
    for (const auto& pair : adjList) {
        int cs = pair.first;
        const auto& neighbors = pair.second;

        if (inDegree.find(cs) == inDegree.end()) {
            inDegree[cs] = 0; 
        }
        for (const auto& connection : neighbors) {
            int neighbor = connection.first;
            inDegree[neighbor]++;
        }
    }

    queue<int> zeroDegree;
    for (const auto& pair : inDegree) {
        int cs = pair.first;
        int degree = pair.second;

        if (degree == 0) {
            zeroDegree.push(cs);
        }
    }

    vector<int> result;
    while (!zeroDegree.empty()) {
        int current = zeroDegree.front();
        zeroDegree.pop();
        result.push_back(current);

        for (const auto& connection : adjList[current]) {
            int neighbor = connection.first;
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                zeroDegree.push(neighbor);
            }
        }
    }

    if (result.size() != adjList.size()) {
        throw runtime_error("Cycle detected! Topological sorting not possible.");
    }

    return result;
}

bool isValidCS(const map<int, cs>& Css, int id) {
    return Css.find(id) != Css.end();
}

void connectStations(map<int, pipe>& Pipes, GasNetwork& network, map<int, cs>& Css, int& pipeId) {
    string startCS, endCS, diameter;

    cout << "Enter start CS ID: ";
    getline(cin, startCS);
    if (!isInteger(startCS) || !isValidCS(Css, stoi(startCS))) {
        cout << "Invalid start CS ID. Please enter a valid ID.\n";
        return;
    }

    cout << "Enter end CS ID: ";
    getline(cin, endCS);
    if (!isInteger(endCS) || !isValidCS(Css, stoi(endCS))) {
        cout << "Invalid end CS ID. Please enter a valid ID.\n";
        return;
    }

    cout << "Enter pipe diameter: ";
    getline(cin, diameter);
    if (!isInteger(diameter) || stoi(diameter) <= 0) {
        cout << "Invalid pipe diameter. Please enter a valid positive number.\n";
        return;
    }

    bool foundPipe = false;

    for (const auto& pair : Pipes) {
        int id = pair.first;
        const pipe& p = pair.second;

        if (network.isPipeInUse(id)) {
            cout << "Pipe ID " << id << " is already in use. Skipping this pipe.\n";
            continue;
        }

        if (p.getPipeDiameter() == stoi(diameter)) {
            if (!p.isRepairing()) {
                network.addConnection(stoi(startCS), stoi(endCS), id);
                cout << "Connected using existing pipe ID " << id << ".\n";
                foundPipe = true;
                return;
            }
            else {
                cout << "Pipe ID " << id << " with diameter " << diameter << " is currently under repair. Skipping this pipe.\n";
            }
        }
    }

    if (!foundPipe) {
        cout << "No suitable pipe found with the specified diameter. Creating a new one.\n";
        Pipes[pipeId] = pipe("Auto Created Pipe", 100, stoi(diameter), false);
        network.addConnection(stoi(startCS), stoi(endCS), pipeId);
        cout << "Connected using new pipe ID " << pipeId << ".\n";
        pipeId++;
    }
}

bool GasNetwork::isPipeInUse(int pipeId) const {
    for (const auto& pair : adjList) {
        const auto& neighbors = pair.second;
        for (const auto& connection : neighbors) {
            if (connection.second == pipeId) {
                return true;
            }
        }
    }
    return false;
}

void performTopologicalSort(GasNetwork& network) {
    try {
        vector<int> order = network.topologicalSort();
        cout << "Topological Sort Order: ";
        for (int cs : order) { 
            cout << cs << " ";
        }
        cout << endl;
    }
    catch (const exception& e) { 
        cout << e.what() << endl;
    }
}

void GasNetwork::removeConnections(int elementId, const string& type) {
    if (type == "cs") {
        adjList.erase(elementId);

        for (auto& pair : adjList) {
            vector<std::pair<int, int>>& neighbors = pair.second;
            neighbors.erase(
                remove_if(neighbors.begin(), neighbors.end(),
                    [elementId](const std::pair<int, int>& connection) {
                        return connection.first == elementId;
                    }),
                neighbors.end());
        }
        cout << "Compressor station " << elementId << " and its connections were removed from the network.\n";
    }
    else if (type == "pipe") {
        for (auto& pair : adjList) {
            vector<std::pair<int, int>>& neighbors = pair.second;
            neighbors.erase(
                remove_if(neighbors.begin(), neighbors.end(),
                    [elementId](const std::pair<int, int>& connection) {
                        return connection.second == elementId;
                    }),
                neighbors.end());
        }
        cout << "Pipe " << elementId << " and its connections were removed from the network.\n";
    }
    else {
        cout << "Invalid type specified for removal.\n";
    }
}
