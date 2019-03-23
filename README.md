# CPU-Scheduling-Algorithms
This is a C++ program to demonstrate the CPU scheduling algorithms of First Come First Serve(FCFS), Shortest Job First(SJF), and Round Robin.<br/>
There are two programs, one with IO execution (advanced_cpu_scheduling.cpp) and one without (cpu_scheduling.cpp).<br/>
cpu_scheduling.cpp requires to have a .txt file in the same folder with name "processes1.txt". It should contain the information of the processes in the format:<br/>
P0;\<arrival time>\;\<cpu burst time>\;<br/> 
P1;\<arrival time>\;\<cpu burst time>\;<br/>
P2;\<arrival time>\;\<cpu burst time>\;<br/>
and so on.<br/>
The prorgram prints the sequence in which the processes will be executed for each algorithm, turnaround time and waiting time for each process, and the throughput of the system.<br/>
<br/>

advanced_cpu_scheduling.cpp requires to have a .txt file in the same folder with name "processes2.txt". It should contain the information of the processes in the format:<br/>
P0;\<arrival time>\;\<cpu burst time>\;\<IO time>\;\<CPU to IO time>\;<br/> 
P1;\<arrival time>\;\<cpu burst time>\;\<IO time>\;\<CPU to IO time>\;<br/>
P2;\<arrival time>\;\<cpu burst time>\;\<IO time>\;\<CPU to IO time>\;<br/>
and so on.<br/>
This was made as a class assignment.

