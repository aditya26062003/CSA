#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <gtk/gtk.h>

// Define global variables for process information
int n;
int *AT, *BT, *WT, *TT, quantum;

// Function prototypes
void sjf();
void fcfs();
void srtf();
void roundRobin();

// Callback function for "Run Scheduling" button
void run_scheduling(GtkWidget *widget, gpointer data) {
    // Get the number of processes from the spin button
    n = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(data));

    // Call scheduling algorithms with updated values
    sjf();
    fcfs();
    srtf();
    roundRobin();
}

int main(int argc, char *argv[]) {
    GtkWidget *window, *vbox, *label, *spin_button, *button;

    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Scheduling Algorithms");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box layout
    vbox = gtk_vbox_new(TRUE, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create a label
    label = gtk_label_new("Enter the number of processes:");
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);

    // Create a spin button for entering the number of processes
    spin_button = gtk_spin_button_new_with_range(1, 10, 1);
    gtk_box_pack_start(GTK_BOX(vbox), spin_button, TRUE, TRUE, 0);

    // Create a button to run scheduling algorithms
    button = gtk_button_new_with_label("Run Scheduling");
    g_signal_connect(button, "clicked", G_CALLBACK(run_scheduling), spin_button);
    gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

    // Show all widgets
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();

    // Free the allocated memory
    free(AT);
    free(BT);
    free(WT);
    free(TT);

    return 0;
}

// Implement your scheduling algorithms (sjf, fcfs, srtf, roundRobin) here
// You can use the global variables (n, AT, BT, WT, TT, quantum) to get the user input.

void fcfs() {
    // Implementation of FCFS scheduling algorithm
    {
    int burst=0,cmpl_T;
    float Avg_WT,Avg_TT,Total=0;
    printf("Enter number of the process\n");
    scanf("%d",&n);
    printf("Enter Arrival time and Burst time of the process\n");
    printf("AT\tBT\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d%d",&AT[i],&BT[i]);
    }

    // Logic for calculating Waiting time
    for(int i=0;i<n;i++)
    {
        if(i==0)
            WT[i]=AT[i];
        else
            WT[i]=burst-AT[i];
        burst+=BT[i];
        Total+=WT[i];
    }
    Avg_WT=Total/n;

    // Logic for calculating Turn around time
    cmpl_T=0;
    Total=0;
    for(int i=0;i<n;i++)
    {
        cmpl_T+=BT[i];
        TT[i]=cmpl_T-AT[i];
        Total+=TT[i];
    }
    Avg_TT=Total/n;

    // printing of outputs

    printf("Process ,Waiting_time ,TurnA_time\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t\t%d\t\t%d\n",i+1,WT[i],TT[i]);
    }
    printf("Average waiting time is : %f\n",Avg_WT);
    printf("Average turn around time is : %f\n",Avg_TT);
}

void sjf() {
    // Implementation of SJF scheduling algorithm
    int burst = 0, completionTime, minBTIndex;
    float Avg_WT, Avg_TT, Total = 0;

    // Initialize arrays
    for (int i = 0; i < n; i++) {
        WT[i] = 0;
        TT[i] = 0;
    }

    // Logic for SJF
    for (int i = 0; i < n; i++) {
        minBTIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (BT[j] < BT[minBTIndex]) {
                minBTIndex = j;
            }
        }

        // Swap the processes to order them by burst time
        int temp = BT[i];
        BT[i] = BT[minBTIndex];
        BT[minBTIndex] = temp;

        temp = AT[i];
        AT[i] = AT[minBTIndex];
        AT[minBTIndex] = temp;
    }

    // Logic for calculating Waiting time and Turnaround time
    for (int i = 0; i < n; i++) {
        WT[i] = burst;
        burst += BT[i];
        TT[i] = burst - AT[i];
        Total += WT[i];
    }
    Avg_WT = Total / n;
    Avg_TT = Total / n;

    // Printing of outputs
    printf("Process\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\n", i + 1, WT[i], TT[i]);
    }
    printf("Average Waiting Time: %f\n", Avg_WT);
    printf("Average Turnaround Time: %f\n", Avg_TT);
}

void srtf() {
    // Implementation of SRTF scheduling algorithm
        int remainingBT[10], completionTime, time = 0, minBTIndex;
    float Avg_WT, Avg_TT, Total_WT = 0, Total_TT = 0;

    // Initialize arrays
    for (int i = 0; i < n; i++) {
        remainingBT[i] = BT[i];
        WT[i] = 0;
        TT[i] = 0;
    }

    int processesCompleted = 0;

    while (processesCompleted < n) {
        minBTIndex = -1;
        int minBT = INT_MAX;

        // Find the process with the shortest remaining burst time
        for (int i = 0; i < n; i++) {
            if (AT[i] <= time && remainingBT[i] < minBT && remainingBT[i] > 0) {
                minBT = remainingBT[i];
                minBTIndex = i;
            }
        }

        if (minBTIndex == -1) {
            // No process is ready, move time forward
            time++;
        } else {
            // Process with the shortest remaining burst time is found
            remainingBT[minBTIndex]--;
            time++;

            if (remainingBT[minBTIndex] == 0) {
                // Process has completed
                processesCompleted++;

                // Calculate waiting time and turnaround time
                WT[minBTIndex] = time - AT[minBTIndex] - BT[minBTIndex];
                TT[minBTIndex] = time - AT[minBTIndex];

                // Update totals
                Total_WT += WT[minBTIndex];
                Total_TT += TT[minBTIndex];
            }
        }
    }

    // Calculate averages
    Avg_WT = Total_WT / n;
    Avg_TT = Total_TT / n;

    // Printing of outputs
    printf("Process\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\n", i + 1, WT[i], TT[i]);
    }
    printf("Average Waiting Time: %f\n", Avg_WT);
    printf("Average Turnaround Time: %f\n", Avg_TT);
}

void roundRobin() {
    // Implementation of Round Robin scheduling algorithm
    int remainingBT[10], time = 0, completionTime = 0;
    float Avg_WT = 0, Avg_TT = 0, Total_WT = 0, Total_TT = 0;

    // Initialize arrays
    for (int i = 0; i < n; i++) {
        remainingBT[i] = BT[i];
        WT[i] = 0;
        TT[i] = 0;
    }

    int processesCompleted = 0;

    // Round Robin scheduling
    while (processesCompleted < n) {
        for (int i = 0; i < n; i++) {
            if (remainingBT[i] > 0) {
                if (remainingBT[i] <= quantum) {
                    time += remainingBT[i];
                    completionTime = time;
                    remainingBT[i] = 0;
                    processesCompleted++;

                    // Calculate waiting time and turnaround time
                    WT[i] = completionTime - AT[i] - BT[i];
                    TT[i] = completionTime - AT[i];

                    // Update totals
                    Total_WT += WT[i];
                    Total_TT += TT[i];
                } else {
                    time += quantum;
                    remainingBT[i] -= quantum;
                }
            }
        }
    }

    // Calculate averages
    Avg_WT = Total_WT / n;
    Avg_TT = Total_TT / n;

    // Printing of outputs
    printf("Process\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\n", i + 1, WT[i], TT[i]);
    }
    printf("Average Waiting Time: %f\n", Avg_WT);
    printf("Average Turnaround Time: %f\n", Avg_TT);
}



