#include<iostream>
#include<string>
#include<fstream>
#include "queue.h"

using namespace std;

void getDataFromFile(int *&arrivalTimes,int *&burstTimes,int *&ioTime, int *& cpuToIO, int *totalBurstTime,int *no_processes)
{
    ifstream processFile("processes2.txt");
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
    ioTime = new int[n];
    cpuToIO = new int[n];


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
        processFile>>ioTime[i];
        processFile>>temp;
        processFile>>cpuToIO[i];
        processFile>>temp;
        //processFile>>temp;cout<<temp<<endl;
        b+=burstTimes[i];
        cout<<arrivalTimes[i]<<" "<<burstTimes[i]<<" "<<ioTime[i]<<" "<<cpuToIO[i]<<endl; 
    }
    *totalBurstTime = b;
    //cout<<"file read complete"<<endl;
}

void FCFS()
{
    cout<<"FCFS: "<<endl;
    Queue *FIFO = new Queue();
    List *IO = new List();
    int no_processes,totalBurstTime;
    int *np = &no_processes,*tbt=&totalBurstTime,*burstTimesLeft,*arrivalTimes,*cpuToIO,*ioTime;
    getDataFromFile(arrivalTimes,burstTimesLeft,ioTime,cpuToIO,tbt,np);
    int *burstTimes = new int[no_processes](),*waitingTime = new int[no_processes],*turnaround = new int[no_processes];
    int time=0,topProcess,currentCpuToIO,burstTimeLeft = totalBurstTime;
    bool idle=true;
    waitingTime[0] = 0;
    while(burstTimeLeft||IO->head)
    {
        if(IO->head!=NULL)
        {
            Node *io1 = IO->head;
            cout<<"Process "<<io1->processIndex<<" is executing in IO."<<endl;
            if(!--io1->data)
            {
                if(burstTimesLeft[io1->processIndex])
                {
                    //cout<<burstTimesLeft[io1->processIndex]<<endl;
                     FIFO->enqueue(io1->processIndex); 
                }
                else
                {
                    turnaround[io1->processIndex] = time-arrivalTimes[io1->processIndex];
                    waitingTime[io1->processIndex] = time-burstTimes[io1->processIndex]-arrivalTimes[io1->processIndex];
                }
                IO->Remove();
                
            }
        }
        for(int i=0;i<no_processes;i++)
        {
            if(time==arrivalTimes[i])
            {
                FIFO->enqueue(i);
            }
        }
        if(idle&&!FIFO->isEmpty())
        {
            idle=false;
            topProcess=FIFO->dequeue();
            currentCpuToIO = cpuToIO[topProcess];
        }
        time++;
        if(!idle)
        {
            cout<<"Process "<<topProcess<<" is executing from time "<<time-1<<" to "<<time<<endl;
            //cout<<"Burst Time left "<<burstTimesLeft[topProcess]<<" cpu to io "<<currentCpuToIO<<" topProcess "<<topProcess<<endl;

            burstTimes[topProcess]++;
            --burstTimesLeft[topProcess];
            if(!currentCpuToIO--)
            {
                //cout<<" here 3"<<burstTimesLeft[topProcess]<<endl;
                IO->InsertInTail(ioTime[topProcess],topProcess);
                if(!FIFO->isEmpty())
                {
                    topProcess = FIFO->dequeue();
                    currentCpuToIO = cpuToIO[topProcess];
                }
                else
                {
                    idle=true;
                }
            }

            else if(! burstTimesLeft[topProcess])
            {
                //cout<<"here4"<<endl;
                turnaround[topProcess] = time - arrivalTimes[topProcess];
                waitingTime[topProcess] = time - burstTimes[topProcess] - arrivalTimes[topProcess];
                if(!FIFO->isEmpty())
                {
                    topProcess = FIFO->dequeue();
                    currentCpuToIO = cpuToIO[topProcess];
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
    for(int i=0;i<no_processes;i++)
    {
        cout<<"Process "<<i<<": Turnaround = "<<turnaround[i]<<" Waiting time = "<<waitingTime[i]<<" Penalty ratio = "<<(float)turnaround[i]/burstTimes[i]<<endl;
    }
    cout<<"System throughput = "<<(float)no_processes/time<<endl;
}

void SJF_pre_emptive()
{
    cout<<"SJF Pre-Emptive: "<<endl;
    List *IO = new List();
    int no_processes,totalBurstTime;
    int *np = &no_processes,*tbt=&totalBurstTime,*burstTimesLeft,*arrivalTimes,*cpuToIO,*ioTime,*cpuToIOLeft;
    getDataFromFile(arrivalTimes,burstTimesLeft,ioTime,cpuToIO,tbt,np);
    int *burstTimes = new int[no_processes](),*waitingTime = new int[no_processes],*turnaround = new int[no_processes];
    cpuToIOLeft = new int[no_processes];
    int *executings = new int[no_processes]();
    for(int i=0;i<no_processes;i++)
    {
        cpuToIOLeft[i] = cpuToIO[i];
    }
    int time=0,executing=-1,currentCpuToIO,burstTimeLeft=totalBurstTime;
    bool idle=true;
    while(burstTimeLeft)
    {
        if(IO->head!=NULL)
        {
            Node *io1 = IO->head;
            cout<<"Process "<<io1->processIndex<<" is executing in IO."<<endl;
            if(!--io1->data)
            {
                if(burstTimesLeft[io1->processIndex])
                {
                    //cout<<burstTimesLeft[io1->processIndex]<<endl;
                    executings[io1->processIndex] = 0;
                }
                else
                {
                    turnaround[io1->processIndex] = time-arrivalTimes[io1->processIndex];
                    waitingTime[io1->processIndex] = time-burstTimes[io1->processIndex]-arrivalTimes[io1->processIndex];
                    cout<<arrivalTimes[io1->processIndex]<<endl;
                }
                IO->Remove();
                
            }
        }
        int minBurst=10000;
        for(int i=0;i<no_processes;i++)
        {
            if(burstTimesLeft[i]>0&&burstTimesLeft[i]<minBurst&&arrivalTimes[i]<=time&&!executings[i])
            {
                if(executing>=0)
                    executings[executing] = 0;

                minBurst = burstTimesLeft[i];
                
                executing=i;
                idle=false;
            }
        }
        if(minBurst==10000&&!burstTimesLeft[executing])
        {
            idle=true;
        }
        else
        {
            executings[executing]=1;
        }
        
        time++;
        if(!idle)
        {
            if(!cpuToIOLeft[executing]--)
            {
                IO->InsertInTail(ioTime[executing],executing);
                cpuToIOLeft[executing] = cpuToIO[executing];
                int minBurst=10000;
                for(int i=0;i<no_processes;i++)
                {
                    if(burstTimesLeft[i]>0&&burstTimesLeft[i]<minBurst&&arrivalTimes[i]<=time&&!executings[i])
                    {
                        minBurst = burstTimesLeft[i];
                        executing=i;
                    }
                }   
                if(minBurst==1000)
                {
                    idle=true;
                }
            }
            else
            {
                burstTimes[executing]++;
                --burstTimesLeft[executing];
                cout<<"Process "<<executing<<" is executing from time "<<time-1<<" to "<<time<<endl;
            
                if(!burstTimesLeft[executing])
                {
                    turnaround[executing] = time-arrivalTimes[executing];
                    waitingTime[executing] = time-burstTimes[executing]-arrivalTimes[executing];
                }  
                burstTimeLeft--;   
            }
        }
        else
        {
            cout<<"CPU is idle from time "<<time-1<<" to "<<time<<endl;
        }
        
    }
    for(int i=0;i<no_processes;i++)
    {
        cout<<"Process "<<i<<": Turnaround = "<<turnaround[i]<<" Waiting time = "<<waitingTime[i]<<" Penalty ratio = "<<(float)turnaround[i]/burstTimes[i]<<endl;
    }
    cout<<"System throughput = "<<(float)no_processes/time<<endl;

}

int main()
{
    //FCFS();
    SJF_pre_emptive();
}
