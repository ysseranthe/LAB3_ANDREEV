#pragma once
#include <sstream>
#include <map>
#include <iostream>
#include <string>
#include "gasnetwork.h"
using namespace std;

class GasNetwork;
class pipe
{
private:
    string name;
    int length;
    int diameter;
    bool repair;

public:
    pipe();
    pipe(string n, int l, int d, bool r);

    int getPipeLength() const;
    int getPipeDiameter() const;
    bool isRepairing() const;
    string getPipeName() const;

    void setName(string input);
    void setLength(int input);
    void setDiameter(int input);
    void setIsRepairing(bool t);
    friend ostream& operator<<(ostream& os, const pipe& p);
};

extern map<int, pipe> Pipes;

void pipeInfo(int id, const pipe p);
void showPipes();
void editPipe(GasNetwork& network);
void addNewPipe(int& i);
void filterPipe(GasNetwork& network);
string filterByName(string input);
string filterByRepair(string input);
void deletePipes(map<int, pipe>& Pipes, GasNetwork& network);