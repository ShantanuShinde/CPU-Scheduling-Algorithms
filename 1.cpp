#include<iostream>
#include<fstream>
#include<string>
#include "queue.h"

using namespace std;

void getDataFromFile(int *&arrivalTimes,int *&burstTimes,int *totalBurstTime,int *no_processes)
{
    ifstream processFile("processes.txt");
    int n = 0,b=0;
    while(!processFile.eof()){
        string temp;
        getline(processFile,temp);
        n++;
    }
    *no_processes = n;
    processFile.clear();
    processFile.seekg(0,ios::beg);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
    arrivalTimes = new int[n];
    burstTimes = new int[n];

    for(int i=0;i<n;i++)
    {
        char temp;
        //cout<<temp<<endl;
        processFile>>temp;
        processFile>>temp;
        processFile>>temp;
        processFile>>arrivalTimes[i];
        processFile>>temp;
        processFile>>burstTimes[i];
        processFile>>temp;
        //processFile>>temp;cout<<temp<<endl;
        b+=burstTimes[i];
    }
    *totalBurstTime = b;
    //cout<<"file read complete"<<endl;
}

void FCFS()
{
    cout<<"FCFS: "<<endl;
    Queue *FIFO = new Queue();
    int no_processes,totalBurstTime;
    int *np = &no_processes,*tbt=&totalBurstTime,*burstTimes,*arrivalTimes;
    getDataFromFile(arrivalTimes,burstTimes,tbt,np);
    int *executing = new int[no_processes](),*turnaround = new int[no_processes](),*waitingTime = new int[no_processes];
    int time=0,topProcess,burstTimeLeft = totalBurstTime;
    bool idle=true;
    waitingTime[0] = 0;
    while(!FIFO->isEmpty()||idle||burstTimes[topProcess])
    {
        for(int i=0;i<no_processes;i++)
        {
            if(time==arrivalTimes[i]&&!executing[i])
            {
                FIFO->enqueue(i);
                executing[i]=1;
                
            }
        }
        if(idle&&!FIFO->isEmpty())
        {
            idle=false;
            topProcess=FIFO->dequeue();
        }
        time++;
        if(!idle)
        {
            cout<<"Process "<<topProcess<<" is executing from time "<<time-1<<" to "<<time<<endl;
            turnaround[topProcess]++;
            if(!--burstTimes[topProcess])
            {
                if(!FIFO->isEmpty())
                {
                    topProcess = FIFO->dequeue();
                    executing[topProcess]=0;
                }
                else
                {
                    idle=true;
                }
            }
            
            burstTimeLeft--;
        }
        else
        {
            cout<<"The cpu is idle for time "<<time<<endl;
        }
        if(!burstTimeLeft)
            idle=false;
    }
    for(int i=1;i<no_processes;i++)
    {
        waitingTime[i] = waitingTime[i-1] + turnaround[i-1];
    }
    for(int i=0;i<no_processes;i++)
    {
        cout<<"Process "<<i<<": Turnaround = "<<turnaround[i]<<" Waiting time = "<<waitingTime[i]<<endl;
    }
    cout<<"System throughput = "<<(float)no_processes/time<<endl;
}

void SJF_pre_emptive()
{
    cout<<"SJF Pre-Emptive: "<<endl;
    int no_processes,totalBurstTime;
    int *np = &no_processes,*tbt=&totalBurstTime,*burstTimes,*arrivalTimes;
    getDataFromFile(arrivalTimes,burstTimes,tbt,np);
    int *turnaround = new int[no_processes](),*waitingTime = new int[no_processes];
    int time=0,executing,burstTimeLeft=totalBurstTime;
    bool idle=true;
    while(burstTimeLeft)
    {
        int minBurst=10000;
        for(int i=0;i<no_processes;i++)
        {
            if(burstTimes[i]>0&&burstTimes[i]<minBurst&&arrivalTimes[i]<=time)
            {
                minBurst = burstTimes[i];
                executing=i;
                idle=false;
            }
        }
        if(minBurst==10000)
        {
            idle=true;
        }
        time++;
        if(!idle)
        {
            turnaround[executing]++;
            cout<<"Process "<<executing<<" is executing from time "<<time-1<<" to "<<time<<endl;
            if(!--burstTimes[executing])
            {
                waitingTime[executing] = time-turnaround[executing]-arrivalTimes[executing];
            }  
            burstTimeLeft--;   
        }
        else
        {
            cout<<"CPU is idle from time "<<time-1<<" to "<<time<<endl;
        }
        
    }
    for(int i=0;i<no_processes;i++)
    {
        cout<<"Process "<<i<<": Turnaroud time = "<<turnaround[i]<<" Waiting time = "<<waitingTime[i]<<endl;
    }
    cout<<"System throughput = "<<(float)no_processes/time<<endl;

}

void SFJ_non_pre_emptive()
{
    cout<<"SJF Non Pre-Emptive:"<<endl;
    int no_processes,totalBurstTime;
    int *np = &no_processes,*tbt=&totalBurstTime,*burstTimes,*arrivalTimes;
    getDataFromFile(arrivalTimes,burstTimes,tbt,np);
    int *turnaround = new int[no_processes](),*waitingTime = new int[no_processes];
    int time=0,executing=-1,burstTimeLeft=totalBurstTime;
    bool idle=true;
    while(burstTimeLeft)
    {
        if(executing==-1||!burstTimes[executing])
        {
            int minBurst=10000;
            for(int i=0;i<no_processes;i++)
            {
            if(burstTimes[i]>0&&burstTimes[i]<minBurst&&arrivalTimes[i]<=time)
            {
                minBurst = burstTimes[i];
                executing=i;
                idle=false;
            }
            }
            if(minBurst==10000)
            {
                idle=true;
            }
        }
        time++;
        if(!idle)
        {
            turnaround[executing]++;
            cout<<"Process "<<executing<<" is executing from time "<<time-1<<" to "<<time<<endl;
            if(!--burstTimes[executing])
            {
                waitingTime[executing] = time-turnaround[executing]-arrivalTimes[executing];
            }  
            
            burstTimeLeft--;   
        }
        else
        {
            cout<<"CPU is idle from time "<<time-1<<" to "<<time<<endl;
        }
        
    }
    for(int i=0;i<no_processes;i++)
    {
        cout<<"Process "<<i<<": Turnaroud time = "<<turnaround[i]<<" Waiting time = "<<waitingTime[i]<<endl;
    }
    cout<<"System throughput = "<<(float)no_processes/time<<endl;


}

void RoundRobin()
{
    cout<<"Round Robin:"<<endl;
    Queue *FIFO = new Queue();
    int no_processes,totalBurstTime;
    int *np = &no_processes,*tbt=&totalBurstTime,*burstTimes,*arrivalTimes;
    getDataFromFile(arrivalTimes,burstTimes,tbt,np);
    int *turnaround = new int[no_processes](),*waitingTime = new int[no_processes];
    int time=0,timeInQuantum=0,timeQuantum=5,topProcess=-1,burstTimeLeft = totalBurstTime;
    bool idle=true;
    while(burstTimeLeft)
    {
        for(int i=0;i<no_processes;i++)
        {
            if(time == arrivalTimes[i])
            {
                idle=false;
                FIFO->enqueue(i);
                if(topProcess==-1)
                    topProcess = FIFO->dequeue();
            }
        }
        if(timeInQuantum == timeQuantum)
        {
            timeInQuantum=0;
            if(FIFO->isEmpty())
            {
                if(!burstTimes[topProcess])
                {
                    topProcess=-1;
                    idle=true;
                }
            }
            else
            {
                FIFO->enqueue(topProcess);
                topProcess = FIFO->dequeue();
            }
        }
        time++,timeInQuantum++;
        if(idle)
        {
            cout<<"CPU is idle from time "<<time-1<<" to "<<time<<endl;
        }
        else
        {
            turnaround[topProcess]++;
            cout<<"Process "<<topProcess<<" executing from time "<<time-1<<" to "<<time<<endl;
            if(!--burstTimes[topProcess])
            {
                waitingTime[topProcess] = time - turnaround[topProcess]-arrivalTimes[topProcess];
                timeInQuantum=0;
                if(!FIFO->isEmpty())
                    topProcess = FIFO->dequeue();
                else
                {
                    topProcess=-1;
                    idle=true;
                }
            }
            burstTimeLeft--;
        }
    }
    for(int i=0;i<no_processes;i++)
    {
        cout<<"Process "<<i<<": Turnaround time = "<<turnaround[i ]<<" Waiting time = "<<waitingTime[i]<<endl;
    }
    cout<<"System Throughput = "<<(float)no_processes/time<<endl;
    
}
int main()
{
    FCFS();
    SJF_pre_emptive();
    SFJ_non_pre_emptive();
    RoundRobin();
    
    return 0;
}
