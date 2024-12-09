#pragma once
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include "gasnetwork.h"

using namespace std;

class GasNetwork;
class cs
{
	private:
		string name;
		int numberOfWorkshops;
		int workshopsInOperation;
		int efficiency;

	public:
		int getNumberOfWorkshops() const;
		int getWorkshopsInOperation() const;
		int getEfficiency() const;
		string getName() const;
		cs();
		cs(string N, int nw, int w, int e);
		void changeOperatingWorkshops(int n);
};

extern map<int, cs> Css;
void filterCs();
void showCss();
void addNewCs(int& i);
void csInfo(int id, const cs c);
void filterByCsName(string input);
void filterByPercent(int input);
void editCs(GasNetwork& network);
void deleteCs(map<int, cs>& Css, GasNetwork& network);
