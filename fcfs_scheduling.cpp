#include <iostream>
#include <vector>
using namespace std;

void findWaitingTime(vector<int> processes, int n, vector<int> bt, vector<int>& wt) {
    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];
    }
}

void findTurnAroundTime(vector<int> processes, int n, vector<int> bt, vector<int> wt, vector<int>& tat) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

void findavgTime(vector<int> processes, int n, vector<int> bt) {
    vector<int> wt(n, 0), tat(n, 0);
    int total_wt = 0, total_tat = 0;
    findWaitingTime(processes, n, bt, wt);
    findTurnAroundTime(processes, n, bt, wt, tat);
    cout << "Processes    Burst Time     Waiting Time      Turn-Around Time\n";
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        cout << " " << processes[i] << "\t\t" << bt[i] << "\t\t" << wt[i] << "\t\t" << tat[i] << endl;
    }
    cout << "\nAverage waiting time = " << (float)total_wt / n << endl;
    cout << "Average turn around time = " << (float)total_tat / n << endl;
}

int main() {
    vector<int> processes = {1, 2, 3};
    int n = processes.size();
    vector<int> burst_time = {10, 5, 8};
    findavgTime(processes, n, burst_time);
    return 0;
}

