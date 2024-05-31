#include<bits/stdc++.h>
using namespace std;

struct Process {
    int id;
    int arrival_time;
    int burst_time;
};

void roundRobin(vector<Process>& processes, int quantum) {
    int n = processes.size();
    vector<int> completion_time(n, 0);
    vector<int> turnaround_time(n);
    vector<int> waiting_time(n, 0);
    queue<int> ready_queue;
    vector<int> response_time(n, -1);

    int current_time = 0;
    int remaining_processes = n;
    int current_process = 0;

    while (remaining_processes > 0) {
        while (current_process < n && processes[current_process].arrival_time <= current_time) {
            ready_queue.push(current_process);
            current_process++;
        }

        if (ready_queue.empty()) {
            current_time++;
            continue;
        }

        int current_process_id = ready_queue.front();
        ready_queue.pop();
         if (response_time[current_process_id] == -1) {
            response_time[current_process_id] = current_time - processes[current_process_id].arrival_time;
        }

        int execute_time = min(quantum, processes[current_process_id].burst_time);
        current_time += execute_time;
        processes[current_process_id].burst_time -= execute_time;

        if (processes[current_process_id].burst_time == 0) {
            completion_time[current_process_id] = current_time;
            turnaround_time[current_process_id] = current_time - processes[current_process_id].arrival_time;
            waiting_time[current_process_id] = turnaround_time[current_process_id] - processes[current_process_id].burst_time;
            remaining_processes--;
        } else {
            ready_queue.push(current_process_id);
        }
    }

    // Display the results
    int wt = 0,rt = 0 , tt = 0,ct = 0;
    cout << "Process"<<" "<<"Arrival Time"<<" "<<"Burst Time"<<" "<<"CompletionTime"<<" "<<"TurnaroundTime"<<" "<<" WaitingTime"<<" "<<"   ResponseTime\n";
    for (int i = 0; i < n; i++) {
         cout << processes[i].id << "\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t"
             << completion_time[i] << "\t\t" << turnaround_time[i] << "\t\t" << waiting_time[i] << "\t\t" << response_time[i] << endl;
             ct +=completion_time[i];
             tt += turnaround_time[i];
             wt += waiting_time[i];
             rt += response_time[i];
    }

cout <<"\n\n";

cout << "Average CompletionTime: "<<(ct/((float)n))<<endl;
cout << "Average ResponseTime: "<<(rt/((float)n))<<endl;
cout << "Average WaitingTime: "<<(wt/((float)n))<<endl;
cout << "Average turnAroundTime: "<<(tt/((float)n))<<endl;
}

int main() {

        int n,q;
        freopen("input.txt","r",stdin);
        cin >> n >> q;

        vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        cin >> processes[i].id >> processes[i].arrival_time>> processes[i].burst_time;
    }

    roundRobin(processes, q);

    return 0;
}

