#include "cs.h"
#include "pipe.h"
#include "file.h"
using namespace std;

ofstream logFile;

bool isInteger(string const& str) {
    istringstream iss(str);
    int num;
    return (iss >> num) && iss.eof();
}

void upload(int& i, int& j) {
    string input, line, name, pipeLength, pipeDiameter, pipeRepair, workSt, numInWork, eff;
    bool repair;

    cout << "Enter filename with extension:" << endl;
    getline(cin, input);
    logMessage(input);

    ifstream in(input);
    if (!in.is_open()) {
        cout << "Could not open file for reading." << endl;
        return;
    }

    while (getline(in, line)) {
        try {
            if (line == "=PIPE=") {
                if (!getline(in, name) || !getline(in, pipeLength) || !getline(in, pipeDiameter) || !getline(in, pipeRepair) || stoi(pipeLength) < 1 || stoi(pipeDiameter) < 1) {
                    throw invalid_argument("Error reading pipe data");
                }
                if (pipeRepair == "1") repair = true;
                else if (pipeRepair == "0") repair = false;
                else throw invalid_argument("Invalid repair status");

                Pipes[i] = pipe(name, stoi(pipeLength), stoi(pipeDiameter), repair);
                i++;
            }
            else if (line == "=CS=") {
                if (!getline(in, name) || !getline(in, workSt) || !getline(in, numInWork) || !getline(in, eff) || stoi(workSt) < 1 || stoi(numInWork) < 1) {
                    throw invalid_argument("Error reading cs data");
                }
                if (stoi(workSt) < stoi(numInWork)) {
                    throw invalid_argument("workshops in operation cannot exceed total workshops");
                }
                if (stoi(eff) <= 0 || stoi(eff) > 100) {
                    throw invalid_argument("Efficiency must be in range (0, 100]");
                }

                Css[j] = cs(name, stoi(workSt), stoi(numInWork), stoi(eff));
                j++;
            }
            else {
                cout << "Unknown section: " << line << endl;
            }
        }
        catch (const exception& e) {
            cout << "\nReading error: " << e.what() << endl << endl;
            break;
        }
    }
    in.close();

    showPipes();
    showCss();
}

void save()
{
    string fileName;
    cout << "Enter filename with extension:" << endl;
    getline(cin, fileName);
    logMessage(fileName);

    ofstream outFile(fileName);

    if (!outFile.is_open()) {
        cout << "Error: Could not open file for writing." << endl;
        return;
    }

    if (!Pipes.empty()) {
        cout << "Saving pipe data..." << endl;
        for (const auto& pair : Pipes) {
            const pipe& p = pair.second;
            outFile << "=PIPE=" << endl;
            outFile << p.getPipeName() << endl;
            outFile << p.getPipeLength() << endl;
            outFile << p.getPipeDiameter() << endl;
            outFile << (p.isRepairing() ? "1" : "0") << endl;
        }
    }
    else {
        cout << "No pipes to save." << endl;
    }

    if (!Css.empty()) {
        cout << "Saving compressor station data..." << endl;
        for (const auto& pair : Css) {
            const cs& c = pair.second;
            outFile << "=CS=" << endl;
            outFile << c.getName() << endl;
            outFile << c.getNumberOfWorkshops() << endl;
            outFile << c.getWorkshopsInOperation() << endl;
            outFile << c.getEfficiency() << endl;
        }
    }
    else {
        cout << "No compressor stations to save." << endl;
    }

    cout << "Data successfully saved to " << fileName << endl;
    outFile.close();
}

void initLog(const string& logFileName)
{
    logFile.open(logFileName, ios::app);
    if (!logFile.is_open()) {
        cerr << "[Error] Could not open log file: " << logFileName << endl;
    }
    logMessage("-------------------------");

    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);

    char buffer[100];
    ctime_s(buffer, sizeof(buffer), &now_time);
    logMessage(buffer);
}

void logMessage(const string& message)
{
    if (logFile.is_open()) {
        logFile << message << endl;
    }
}

void closeLog() {
    if (logFile.is_open()) {
        logFile.close();
    }
}
