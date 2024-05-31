#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Process {
    int id;            // Process ID
    int arrival_time;  // Arrival time
    int burst_time;    // Burst time
    int remaining_time; // Remaining burst time
};

// Function to implement SJF scheduling algorithm with preemption
void sjf_preemptive(vector<Process>& processes) {
    int n = processes.size();
    vector<int> completion_time(n, 0);
    vector<int> turnaround_time(n, 0);
    vector<int> waiting_time(n, 0);
    vector<int> response_time(n, -1); // Initialize response times to -1
    int current_time = 0;
    int completed_processes = 0;

    // Create a min-heap to store processes based on remaining burst time
    auto compare = [](const Process& a, const Process& b) {
        return a.remaining_time > b.remaining_time;
    };
    priority_queue<Process, vector<Process>, decltype(compare)> min_heap(compare);

    while (completed_processes < n) {
        // Add arrived processes to the min-heap
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                if (response_time[i] == -1) {
                    response_time[i] = current_time - processes[i].arrival_time;
                }
                min_heap.push(processes[i]);
            }
        }

        if (!min_heap.empty()) {
            // Get the process with the shortest remaining burst time
            Process shortest_job = min_heap.top();
            min_heap.pop();

            int exec_time = min(shortest_job.remaining_time, 1); // Execute for 1 time unit
            current_time += exec_time;
            shortest_job.remaining_time -= exec_time;

            if (shortest_job.remaining_time == 0) {
                // Process has completed
                completed_processes++;
                completion_time[shortest_job.id - 1] = current_time;
                turnaround_time[shortest_job.id - 1] = current_time - shortest_job.arrival_time;
                waiting_time[shortest_job.id - 1] = turnaround_time[shortest_job.id - 1] - shortest_job.burst_time;
            } else {
                // Process is not completed, put it back in the min-heap
                min_heap.push(shortest_job);
            }
        } else {
            // No process is available, increment current time
            current_time++;
        }
    }

    // Display the results including response time
   cout << "Process"<<" "<<"Arrival Time"<<" "<<"Burst Time"<<" "<<"CompletionTime"<<" "<<"TurnaroundTime"<<" "<<" WaitingTime"<<" "<<"   ResponseTime\n";
    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t"
             << completion_time[i] << "\t\t" << turnaround_time[i] << "\t\t" << waiting_time[i] << "\t\t" << response_time[i] << endl;
    }

    // Calculate average turnaround time, average waiting time, and average response time
    double avg_turnaround_time = 0.0, avg_waiting_time = 0.0, avg_response_time = 0.0;
    for (int i = 0; i < n; i++) {
        avg_turnaround_time += turnaround_time[i];
        avg_waiting_time += waiting_time[i];
        avg_response_time += response_time[i];
    }
    avg_turnaround_time /= n;
    avg_waiting_time /= n;
    avg_response_time /= n;

    cout << "\nAverage Turnaround Time: " << avg_turnaround_time << endl;
    cout << "Average Waiting Time: " << avg_waiting_time << endl;
    cout << "Average Response Time: " << avg_response_time << endl;
}

int main() {
    int n;
    freopen("input.txt","r",stdin);
    cin >> n;
    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        cin >> processes[i].id;
        cin >> processes[i].arrival_time;
        cin >> processes[i].burst_time;
        processes[i].remaining_time = processes[i].burst_time;
    }

    sjf_preemptive(processes);

    return 0;
}
