#include <iostream>
#include <vector>
#include <climits> // Added for INT_MAX
using namespace std;

int selectWorst(int p, vector<int>& blocks) {
    int maxIndex = -1, maxSize = -1;

    for (size_t i = 0; i < blocks.size(); ++i) {
        if (p <= blocks[i] && blocks[i] > maxSize) {
            maxSize = blocks[i];
            maxIndex = i;
        }
    }
    return maxIndex;
}

int selectBest(int p, vector<int>& blocks) {
    int minIndex = -1, minSize = INT_MAX;

    for (size_t i = 0; i < blocks.size(); ++i) {
        if (p <= blocks[i] && blocks[i] < minSize) {
            minSize = blocks[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void firstFit(vector<int>& processes, vector<int>& blocks) {
    for (size_t i = 0; i < processes.size(); ++i) {
        for (size_t j = 0; j < blocks.size(); ++j) {
            if (processes[i] <= blocks[j]) {
                cout << "Process " << i + 1 << " allocated to Block " << j + 1 << endl;
                blocks[j] -= processes[i];
                processes[i] = 0;
                break;
            }
        }
    }
}

void bestFit(vector<int>& processes, vector<int>& blocks) {
    for (size_t i = 0; i < processes.size(); ++i) {
        int index = selectBest(processes[i], blocks);
        if (index != -1) {
            cout << "Process " << i + 1 << " allocated to Block " << index + 1 << endl;
            blocks[index] -= processes[i];
            processes[i] = 0;
        }
    }
}

void worstFit(vector<int>& processes, vector<int>& blocks) {
    for (size_t i = 0; i < processes.size(); ++i) {
        int index = selectWorst(processes[i], blocks);
        if (index != -1) {
            cout << "Process " << i + 1 << " allocated to Block " << index + 1 << endl;
            blocks[index] -= processes[i];
            processes[i] = 0;
        }
    }
}

void printUnallocated(const vector<int>& processes) {
    for (size_t i = 0; i < processes.size(); ++i) {
        if (processes[i] != 0) {
            cout << "Process " << i + 1 << " could not be allocated to any block." << endl;
        }
    }
}

int main() {
    int blockCount, processCount, choice;
    cout << "Enter the number of blocks: ";
    cin >> blockCount;

    vector<int> blocks(blockCount);
    cout << "Enter the sizes of the blocks: ";
    for (int& block : blocks) cin >> block;

    cout << "Enter the number of processes: ";
    cin >> processCount;

    vector<int> processes(processCount);
    cout << "Enter the sizes of the processes: ";
    for (int& process : processes) cin >> process;

    do {
        cout << "\nMENU (Choose the Algorithm):\n";
        cout << "1. First Fit\n";
        cout << "2. Best Fit\n";
        cout << "3. Worst Fit\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        vector<int> tempProcesses = processes;
        vector<int> tempBlocks = blocks;

        switch (choice) {
            case 1:
                cout << "\nFirst Fit Allocation:\n";
                firstFit(tempProcesses, tempBlocks);
                break;
            case 2:
                cout << "\nBest Fit Allocation:\n";
                bestFit(tempProcesses, tempBlocks);
                break;
            case 3:
                cout << "\nWorst Fit Allocation:\n";
                worstFit(tempProcesses, tempBlocks);
                break;
            case 4:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

        printUnallocated(tempProcesses);
    } while (choice != 4);

    return 0;
}

