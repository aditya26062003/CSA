#include <stdio.h>
#include <limits.h>

void fcfs(int processes[], int n, int bt[]);
void sjf(int processes[], int n, int bt[]);
void RR(int processes[], int n, int bt[]);
void srtf(int processes[], int n, int bt[]);
void p_y(int processes[], int n, int bt[], int priority[]);

int main() {
    int choice;
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n];
    int burst_time[n];
    int priority[n];

    printf("Enter Burst Time and Priority for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &burst_time[i]);

        printf("Enter priority for process P%d: ", i + 1);
        scanf("%d", &priority[i]);

        processes[i] = i + 1;
    }

   do{
    printf("\nChoose Scheduling Algorithm:\n");
    printf("1. FCFS\n");
    printf("2. SJF\n");
    printf("3. SRTF\n");
    printf("4. Priority\n");
    printf("5. RoundRobin\n");
    printf("6. EXIT\n");
    printf("Enter your choice (1-6): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            fcfs(processes, n, burst_time);
            break;
        case 2:
            sjf(processes, n, burst_time);
            break;
        case 3:
            srtf(processes, n, burst_time);
            break;
        case 4:
            p_y(processes, n, burst_time,priority);
            break;
        case 5:
            RR(processes,n,burst_time);
            break;
        case 6:
            printf("Exiting ...............!!!!!!!!!");
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }}while(choice!=6);

    return 0;
}




void fcfs(int processes[], int n, int bt[]) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;


    wt[0] = 0;
    for (int i = 1; i < n; i++)
        wt[i] = bt[i - 1] + wt[i - 1];


    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];


    printf("\nFCFS Scheduling:\n");
    printf("Processes\tBurst time\tWaiting time\tTurnaround time\n");


    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("P%d\t\t%d\t\t%d\t\t%d\n", processes[i], bt[i], wt[i], tat[i]);
    }


    float avg_wt = (float)total_wt / n;
    float avg_tat = (float)total_tat / n;
    printf("\nAverage waiting time = %f", avg_wt);
    printf("\nAverage turnaround time = %f\n", avg_tat);
}





void sjf(int processes[], int n, int bt[]) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;


    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (bt[j] > bt[j + 1]) {

                int temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;


                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }


    wt[0] = 0;
    for (int i = 1; i < n; i++)
        wt[i] = bt[i - 1] + wt[i - 1];


    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];


    printf("\nSJF Scheduling:\n");
    printf("Processes\tBurst time\tWaiting time\tTurnaround time\n");


    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("P%d\t\t%d\t\t%d\t\t%d\n", processes[i], bt[i], wt[i], tat[i]);
    }

    // Calculate and display average waiting time and average turnaround time
    float avg_wt = (float)total_wt / n;
    float avg_tat = (float)total_tat / n;
    printf("\nAverage waiting time = %f", avg_wt);
    printf("\nAverage turnaround time = %f\n", avg_tat);
}







void srtf(int processes[], int n, int bt[]) {
    int wt[n], tat[n], remaining_time[n];
    int time = 0;


    for (int i = 0; i < n; i++) {
        wt[i] = 0;
        tat[i] = 0;
        remaining_time[i] = bt[i];
    }

    int completed = 0;

    while (completed < n) {
        int shortest = INT_MAX;
        int shortest_process = -1;

        // Find the process with the shortest remaining time at the current time
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0 && remaining_time[i] < shortest && time >= wt[i]) {
                shortest = remaining_time[i];
                shortest_process = i;
            }
        }

        if (shortest_process == -1) {
            time++;
            continue;
        }


        remaining_time[shortest_process]--;
        time++;

        if (remaining_time[shortest_process] == 0) {
            completed++;
            tat[shortest_process] = time;
            wt[shortest_process] = tat[shortest_process] - bt[shortest_process];
        }
    }

    printf("\nSRTF Scheduling:\n");
    printf("Processes\tBurst time\tWaiting time\tTurnaround time\n");


    for (int i = 0; i < n; i++)
        printf("P%d\t\t%d\t\t%d\t\t%d\n", processes[i], bt[i], wt[i], tat[i]);


    float avg_wt = 0, avg_tat = 0;
    for (int i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tat += tat[i];
    }
    avg_wt /= n;
    avg_tat /= n;
    printf("\nAverage waiting time = %f", avg_wt);
    printf("\nAverage turnaround time = %f\n", avg_tat);
}

void p_y(int processes[], int n, int bt[], int priority[]) {
    int wt[n], tat[n], completed[n];
    int total_wt = 0, total_tat = 0;


    for (int i = 0; i < n; i++)
        completed[i] = 0;


    for (int time = 0; time < n; time++) {
        int highest_priority = -1;
        int selected_process = -1;


        for (int i = 0; i < n; i++) {
            if (!completed[i] && priority[i] > highest_priority) {
                highest_priority = priority[i];
                selected_process = i;
            }
        }

        if (selected_process == -1)
            break;


        completed[selected_process] = 1;


        wt[selected_process] = time;
        tat[selected_process] = wt[selected_process] + bt[selected_process];


        total_wt += wt[selected_process];
        total_tat += tat[selected_process];
    }

    printf("\nPriority Scheduling:\n");
    printf("Processes\tBurst time\tPriority\tWaiting time\tTurnaround time\n");


    for (int i = 0; i < n; i++)
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], bt[i], priority[i], wt[i], tat[i]);


    float avg_wt = (float)total_wt / n;
    float avg_tat = (float)total_tat / n;
    printf("\nAverage waiting time = %f", avg_wt);
    printf("\nAverage turnaround time = %f\n", avg_tat);
}

void RR(int processes[], int n, int bt[]) {
    int wt[n], tat[n], remaining_time[n];
    int quantum;


    printf("Enter the time quantum for Round Robin: ");
    scanf("%d", &quantum);


    for (int i = 0; i < n; i++) {
        wt[i] = 0;
        remaining_time[i] = bt[i];
    }

    int time = 0;
    int flag;


    while (1) {
        flag = 0;


        for (int i = 0; i < n; i++) {

            if (remaining_time[i] > 0) {
                flag = 1;
                if (remaining_time[i] > quantum) {
                    time += quantum;
                    remaining_time[i] -= quantum;
                } else {
                    time += remaining_time[i];
                    wt[i] = time - bt[i];
                    remaining_time[i] = 0;
                }
            }
        }


        if (flag == 0)
            break;
    }


    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];

    printf("\nRound Robin Scheduling:\n");
    printf("Processes\tBurst time\tWaiting time\tTurnaround time\n");


    for (int i = 0; i < n; i++)
        printf("P%d\t\t%d\t\t%d\t\t%d\n", processes[i], bt[i], wt[i], tat[i]);


    float avg_wt = 0, avg_tat = 0;
    for (int i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tat += tat[i];
    }
    avg_wt /= n;
    avg_tat /= n;
    printf("\nAverage waiting time = %f", avg_wt);
    printf("\nAverage turnaround time = %f\n", avg_tat);
}





