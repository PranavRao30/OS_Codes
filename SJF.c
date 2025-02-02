#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10

struct Process {
    int id;
    int at;
    int bt;
    int wt;
    int tat;
    int st;
    int et;
    int rt;
    int vi;
};

int main() {
    struct Process processes[MAX_PROCESSES];
    int n;
    int total_wt = 0;
    int total_tat = 0;
    int total_rt = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", processes[i].id);
        scanf("%d %d", &processes[i].at, &processes[i].bt);
        processes[i].vi = 0;
    }

    int curr_time = 0;
    for (int j = 0; j < n; j++) {
        int min_bt = INT_MAX;
        int ind = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].vi == 0 && processes[i].at <= curr_time && processes[i].bt < min_bt) {
                min_bt = processes[i].bt;
                ind = i;
            }
        }
        if (ind == -1) {
            curr_time = processes[j].at;
            continue;
        }
        struct Process process = processes[ind];
        process.st = curr_time;
        process.et = curr_time + process.bt;
        curr_time = process.et;
        process.tat = process.et - process.at;
        process.wt = process.tat - process.bt;
        process.rt = process.st - process.at;
        total_wt += process.wt;
        total_tat += process.tat;
        total_rt += process.rt;
        processes[ind] = process;
        processes[ind].vi = 1;
        struct Process temp = processes[ind];
        processes[ind] = processes[j];
        processes[j] = temp;
    }

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tResponse Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].at, processes[i].bt, processes[i].wt, processes[i].tat, processes[i].rt);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
    printf("Throughput: %.2f\n", (float)curr_time / n);
    printf("Average Response Time: %.2f\n", (float)total_rt / n);

    return 0;
}
