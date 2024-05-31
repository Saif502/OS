#include <stdio.h>
#include <stdlib.h>

struct process {
    int process_id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turn_around_time;
};

int main() {
    FILE *fp;
    fp = fopen("input.txt", "r");
    int n, i, j;
    int bt = 0, tat = 0, sum = 0, min;
    fscanf(fp, "%d", &n);
    struct process proc[n], temp;

    for (i = 0; i < n; i++) {
        proc[i].arrival_time = 0;
        fscanf(fp, "%d", &proc[i].burst_time);
        proc[i].process_id = i + 1;
    }

    for (i = 0; i < n; i++) {
        min = proc[i].burst_time;
        int k = i;

        for (j = i; j < n; j++) {
            if (bt >= proc[j].arrival_time && proc[j].burst_time < min) {
                min = proc[j].burst_time;
                k = j;
            }
        }
        temp = proc[i];
        proc[i] = proc[k];
        proc[k] = temp;

        bt += proc[i].burst_time;
    }

    proc[0].waiting_time = 0;
    int wait_time_total = 0;
    int turn_around_time_total = 0;

    for (i = 0; i < n; i++) {
        tat += proc[i].burst_time;
        proc[i].turn_around_time = tat - proc[i].arrival_time;
        turn_around_time_total += proc[i].turn_around_time;
    }

    for (i = 1; i < n; i++) {
        sum += proc[i - 1].burst_time;
        proc[i].waiting_time = sum - proc[i].arrival_time;
        wait_time_total += proc[i].waiting_time;
    }

    printf("Process\tBurst Time\tWaiting Time\tTurn-Around Time\n");

    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", proc[i].process_id, proc[i].burst_time, proc[i].waiting_time, proc[i].turn_around_time);
    }

    printf("Average waiting time: %f\n", (float)wait_time_total / n);
    printf("Average turn around time: %f\n", (float)turn_around_time_total / n);

    fclose(fp);

    return 0;
}
