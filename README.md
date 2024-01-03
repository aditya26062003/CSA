# CSA
OVERVIEW
This program implements various CPU scheduling algorithms, allowing users to simulate and analyze the performance of different scheduling strategies. The supported scheduling algorithms include:

First-Come-First-Serve (FCFS)
Shortest Job First (SJF)
Round Robin (RR)
Shortest Remaining Time First (SRTF)
Priority Scheduling
The program takes user input for the number of processes, burst times, and priorities (if applicable) and provides details such as waiting time, turnaround time, and averages for each algorithm.

Compilation and Execution
Compilation:

Compile the program using a C compiler. 

User Input:

Follow the on-screen prompts to input the number of processes, burst times, priorities (if applicable), and time quantum (for Round Robin).

Results:

The program will display the results for each scheduling algorithm, including details for each process and average metrics.

Scheduling Algorithms
1. First-Come-First-Serve (FCFS)
This algorithm executes processes in the order they arrive, without considering burst times or priorities.

2. Shortest Job First (SJF)
Processes are scheduled based on their burst times, with the shortest job executed first.

3. Round Robin (RR)
Processes are executed in a circular manner with a fixed time quantum. Each process gets a turn to execute, and the algorithm cycles through the processes until all are completed.

4. Shortest Remaining Time First (SRTF)
Similar to SJF, but the algorithm dynamically selects the process with the shortest remaining burst time at each step.

5. Priority Scheduling
Processes are scheduled based on priority, with the highest priority process executed first. In case of a tie, FCFS is used.

Author
ADITYA SINGH

License
Unlicense
