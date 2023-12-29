# Multi-Algorithm-Operating-System-Scheduler-Implementation-in-C-
This C++ code implements several process scheduling algorithms commonly studied in operating system courses. The code includes implementations for the First Come First Serve (FCFS), Shortest Job Next (SJN) both preemptive and non-preemptive, Priority Scheduling (both preemptive and non-preemptive), Round Robin, and Banker's Algorithm. Each algorithm is encapsulated in a modular structure for easy understanding and modification.

The First Come First Serve algorithm schedules processes based on their arrival time, while the Shortest Job Next algorithm, both preemptive and non-preemptive, prioritizes processes with the shortest burst time. The Priority Scheduling algorithm assigns priority levels to processes, determining their order of execution. The Round Robin algorithm uses a time quantum to share the CPU among processes in a circular manner. Lastly, the Banker's Algorithm is implemented to avoid deadlock in a system by managing resource allocation.

The code provides detailed output, including turnaround time, response time, and wait time for each process, along with averages for better analysis. The modular structure of the code allows for easy extension or modification to accommodate additional algorithms or features.

Note: The code utilizes C++ features such as structures, functions, and standard template library (STL) containers.
