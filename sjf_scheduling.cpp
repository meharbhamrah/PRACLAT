#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;        // Process ID
    int burstTime; // Burst Time
    int waitingTime;
    int turnAroundTime;
};

bool compareByBurstTime(Process a, Process b) {
    return a.burstTime < b.burstTime;
}

void findWaitingTime(vector<Process>& processes) {
    processes[0].waitingTime = 0;
    for (size_t i = 1; i < processes.size(); i++) {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
    }
}

void findTurnAroundTime(vector<Process>& processes) {
    for (size_t i = 0; i < processes.size(); i++) {
        processes[i].turnAroundTime = processes[i].waitingTime + processes[i].burstTime;
    }
}

void findAverageTimes(vector<Process>& processes) {
    findWaitingTime(processes);
    findTurnAroundTime(processes);

    int totalWT = 0, totalTAT = 0;
    cout << "Processes  Burst Time  Waiting Time  Turn-Around Time\n";

    for (const auto& process : processes) {
        totalWT += process.waitingTime;
        totalTAT += process.turnAroundTime;
        cout << " " << process.id << "\t\t" << process.burstTime << "\t\t" 
             << process.waitingTime << "\t\t" << process.turnAroundTime << "\n";
    }

    cout << "\nAverage Waiting Time = " << (float)totalWT / processes.size() << endl;
    cout << "Average Turn-Around Time = " << (float)totalTAT / processes.size() << endl;
}

int main() {
    vector<Process> processes = {
        {1, 6, 0, 0},
        {2, 8, 0, 0},
        {3, 7, 0, 0},
        {4, 3, 0, 0},
    };

    sort(processes.begin(), processes.end(), compareByBurstTime);

    cout << "Order of execution after sorting by burst time: ";
    for (const auto& process : processes) {
        cout << "P" << process.id << " ";
    }
    cout << endl;

    findAverageTimes(processes);

    return 0;
}

