#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <chrono>
#include <ctime>
#pragma once
using namespace std;

void upload(int& i, int& j);
void save();
extern ofstream logFile;
void initLog(const string& logFileName);
void logMessage(const string& message);
void closeLog();
bool isInteger(string const& str);
