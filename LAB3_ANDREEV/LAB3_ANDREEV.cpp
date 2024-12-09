#include <iostream>
#include <fstream>
#include "pipe.h"
#include "cs.h"
#include "file.h"
#include "gasnetwork.h"
using namespace std;

int main() {
    GasNetwork network;
    int pipeId = 0, csId = 0;
    string input;
    initLog("log.txt");
    while (true) {
        cout << "1. Add a pipe\n2. Add CS\n3. View all objects\n4. Find a pipe\n5. Find a CS\n6. Edit a pipe\n7. Edit a CS\n8. Save\n9. Upload\n10. Connect Stations\n11. Show Gas Network Connections\n12. Perform topological sort\n 0. Exit\n" << endl;
        getline(cin, input);
        logMessage(input);
        if (isInteger(input)) {
            int choose;
            choose = stoi(input);
            switch (choose) {
            case 0: {
                closeLog();
                return 0;
            }
            case 1: {
                addNewPipe(pipeId);
                break;
            }
            case 2: {
                addNewCs(csId);
                break;
            }
            case 3: {
                showPipes();
                showCss();
                break;
            }
            case 4: {
                filterPipe(network);
                break;
            }
            case 5: {
                filterCs();
                break;
            }
            case 6: {
                editPipe(network);
                break;
            }
            case 7: {
                editCs(network);
                break;
            }
            case 8: {
                save();
                break;
            }
            case 9: {
                upload(pipeId, csId);
                break;
            }
            case 10: {
                connectStations(Pipes, network, Css, pipeId);
                break;
            }
            case 11: {
                network.showConnections();
                break;
            }
            case 12: {
                performTopologicalSort(network);
                break;
            }
            default: {
                cout << "Enter number from 0 to 9." << endl;
                break;
            }
            }
        }
        else {
            cout << "Enter number from 0 to 12." << endl;
        }
        cout << endl;
    }
}
