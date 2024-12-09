#include "cs.h"
#include "file.h"

map<int, cs> Css;

cs::cs()
{
	name = "Name";
	numberOfWorkshops = 1;
	workshopsInOperation = 1;
	efficiency = 52;
}

cs::cs(string n, int nw, int w, int e)
{
	name = n;
	numberOfWorkshops = nw;
	workshopsInOperation = w;
	efficiency = e;
}

void cs::changeOperatingWorkshops(int n)
{
	workshopsInOperation = n;
}

string cs::getName() const
{
	return name;
}

int cs::getNumberOfWorkshops() const
{
	return numberOfWorkshops;
}

int cs::getWorkshopsInOperation() const
{
	return workshopsInOperation;
}

int cs::getEfficiency() const
{
	return efficiency;
}

void showCss()
{
    if (Css.empty()) {
        cout << "There are no cs." << endl;
    }
    for (const auto& item : Css) {
        int id = item.first;
        const cs c = item.second;
        csInfo(id, c);
    }
}

void addNewCs(int& i)
{
    int numberOfWorkshops, workshopsInOperation, efficiency;
    string inputName, input;

    cout << "Enter the name of the compressor station:" << endl;
    getline(cin, inputName);
    logMessage(inputName);

    cout << "Enter the number of workshops:" << endl;
    while (true) {
        getline(cin, input);
        logMessage(input);

        if (isInteger(input) && stoi(input) > 0) {
            numberOfWorkshops = stoi(input);
            break;
        }
        else {
            cout << "Enter a positive number greater than 0" << endl;
        }
    }

    cout << "Enter the number of workshops in operation:" << endl;
    while (true) {
        getline(cin, input);
        logMessage(input);

        if (isInteger(input) && stoi(input) >= 0 && numberOfWorkshops >= stoi(input)) {
            workshopsInOperation = stoi(input);
            break;
        }
        else {
            cout << "Enter a positive number <= than number of workshops" << endl;
        }
    }

    cout << "Enter the efficiency:" << endl;
    while (true) {
        getline(cin, input);
        logMessage(input);
    
        if (isInteger(input) && stoi(input) > 0 && stoi(input) < 101) {
            efficiency = stoi(input);
            break;
        }
        else {
            cout << "Enter a number from 0 to 100" << endl;
        }
    }
    Css[i] = cs(inputName, numberOfWorkshops, workshopsInOperation, efficiency);
    i++;
}

void csInfo(int id, const cs c) {
    cout << "Cs ID: " << id << endl;
    cout << "Name: " << c.getName() << endl;
    cout << "The number of workshops: " << c.getNumberOfWorkshops() << endl;
    cout << "The number of workshops in operation: " << c.getWorkshopsInOperation() << endl;
    cout << "The efficiency: " << c.getEfficiency() << endl;
    cout << "-------------------------" << endl;
}

void filterByCsName(string input)
{
    for (const auto& item : Css) {
        int id = item.first;
        const cs c = item.second;

        if (Css[id].getName().find(input) != string::npos) {
            csInfo(id, c);
        }
    }
}

void filterByPercent(int input)
{
    for (const auto& item : Css) {
        int id = item.first;
        const cs c = item.second;

        if ((double)(Css[id].getWorkshopsInOperation() * 100 / (double)Css[id].getNumberOfWorkshops()) <= input) {
            csInfo(id, c);
        }
    }
}

void editCs(GasNetwork& network) {
    string input, id;
    if (Css.empty()) {
        cout << "There are no cs's." << endl;
    }
    else {
        while(true) {
            cout << "1. Change number of working workshops\n2. Delete a cs\n" << endl;
            getline(cin, input);
            logMessage(input);

            if (isInteger(input) && (stoi(input) == 1 || stoi(input) == 2)) {
                if (stoi(input) == 1) {
                    cout << "Enter cs id:" << endl;
                    getline(cin, id);
                    logMessage(id);

                    if (isInteger(id) && Css.find(stoi(id)) != Css.end()) {
                        while (true) {
                            cout << "Enter a number of working workshops to change (- if you reduce it): " << endl;
                            getline(cin, input);
                            logMessage(input);

                            if (isInteger(input) && stoi(input) >= -Css[stoi(id)].getWorkshopsInOperation() && stoi(input) + Css[stoi(id)].getWorkshopsInOperation() <= Css[stoi(id)].getNumberOfWorkshops()) {
                                Css[stoi(id)].changeOperatingWorkshops(stoi(input));
                                break;
                            }
                            else {
                                cout << "Try another number" << endl;
                            }
                        }
                    }
                    else {
                        cout << "There is no cs with id \"" << id << "\"" << endl;
                        break;
                    }
                }
                else {
                    deleteCs(Css, network);
                }
                break;
            }
            else {
                cout << "(1/2)" << endl;
            }
        }
    }
}

void deleteCs(map<int, cs>& Css, GasNetwork& network) {
    string id;
    cout << "Enter cs id:" << endl;
    getline(cin, id);
    logMessage(id);

    if (isInteger(id) && Css.find(stoi(id)) != Css.end()) {
        int csId = stoi(id);

        Css.erase(csId);

        network.removeConnections(csId, "cs");
        cout << "Compressor station with ID " << csId << " deleted successfully.\n";
    }
    else {
        cout << "There is no cs with id \"" << id << "\"" << endl;
    }
}


void filterCs()
{
    string choose, input;
    if (Css.empty()) {
        cout << "There are no cs's." << endl;
    }
    else {
        while (true) {
            cout << "1. Filtration by name\n2. Filtration by percentage of unused workshops\n" << endl;
            getline(cin, choose);
            logMessage(choose);

            if (isInteger(choose) && (stoi(choose) == 1 || stoi(choose) == 2)) {
                if (isInteger(choose) && (stoi(choose) == 1 || stoi(choose) == 2)) {
                    if (stoi(choose) == 1) {
                        cout << "Enter the text:" << endl;
                        getline(cin, input);
                        logMessage(input);

                        filterByCsName(input);
                    }
                    else {
                        while (true) {
                            cout << "Enter the percentage of unused workshops:" << endl;
                            getline(cin, input);
                            logMessage(input);

                            if (isInteger(input) && 0 <= stoi(input) && stoi(input) <= 100) {
                                filterByPercent(stoi(input));
                                break;
                            }
                            else {
                                cout << "Enter a number from 0 to 100." << endl;
                            }
                        }
                    }
                    break;
                }
                else {
                    cout << "Enter 1 or 2." << endl;
                }
            }
        }
    }
}