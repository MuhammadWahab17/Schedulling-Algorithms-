//
//  RR.h
//  CPU Scheduling
//
//  Created by Ch Muhammad Wahab on 08/11/2021.
//  Copyright © 2021 Ch Muhammad Wahab. All rights reserved.
//

#ifndef RR_h
#define RR_h
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include"Process.h"
using namespace std;

struct process_strcuture
{
    string p;
    int art,but,wtt,tat,rnt;
};

class RR{
    struct process_strcuture *processes  = NULL;
    int entries ;
public:
    RR(int n){
        entries = 0;
        processes = new process_strcuture[n];
    }
    ~RR(){
        if(processes!=NULL)
            delete [] processes;
    }
    void RightSelectionSort(struct process_strcuture a[],int size){
        for (int i=0 ; i<size-1 ; i++) {
            int min=i;
            for (int j=i+1; j<size ; j++) {
                if(a[j].art<a[min].art){
                    min=j;
                }
            }
            if(min!=i){
                struct process_strcuture temp = a[i];
                a[i] = a[min];
                a[min] = temp;
            }
        }
    }
    void add_process(process p){
        processes[entries].art = p.AT;
        processes[entries].p = p.name;
        processes[entries].but = p.BT;
        processes[entries].rnt = processes[entries].but;
        entries++;
    }
    
    void RunRR(int qua)
    {
        int remain,flag=0;
        float avgwt=0,avgtt=0;
        remain=numberOfProcesses;
        RightSelectionSort(processes, numberOfProcesses);
        
        cout<<"\n\n";
        cout<<"Gantt Chart\n";
        cout<<"0";

        for(int time=0, i=0;remain!=0;)
        {
            if(processes[i].rnt<=qua && processes[i].rnt>0)
            {
                time = time + processes[i].rnt;
                cout<<" --- "<<processes[i].p<<"--- "<<time;
                processes[i].rnt=0;
                flag=1;
            }
            else if(processes[i].rnt > 0)
            {
                processes[i].rnt = processes[i].rnt - qua;
                time = time + qua;
                cout<<" --- "<<processes[i].p<<"--- "<<time;
            }
            if(processes[i].rnt==0 && flag==1)
            {
                remain--;
                processes[i].tat = time-processes[i].art;
                processes[i].wtt = time-processes[i].art-processes[i].but;
                avgwt = avgwt + time-processes[i].art-processes[i].but;
                avgtt = avgtt + time-processes[i].art;
                flag=0;
            }
            if(i==numberOfProcesses-1)
                i=0;
            else if(processes[i+1].art <= time)
                i++;
            else
                i=0;
        }
        cout<<"\n\n";
        cout<<setw(10)<<setfill(' ')<<"Process_No"<<'\t'<<setw(13)<<"Arrival_Time"<<'\t'<<setw(11)<<"Brust_Time"<<'\t'<<setw(18)<<"Turnaround_Time"<<'\t'
        <<setw(10)<<"Wait_Time\n";
        for(int i=0;i<numberOfProcesses;i++){
            cout<<setw(10)<<processes[i].p<<"\t"<<setw(13)<<processes[i].art<<"\t"<<setw(11)<<processes[i].but<<"\t"
            <<setw(18)<<processes[i].tat<<"\t"<<setw(10)<<processes[i].wtt<<"\t""\n";
        }
        avgwt = avgwt/numberOfProcesses;
        avgtt = avgtt/numberOfProcesses;
        cout<<endl;
        cout<<"Average Turnaround Time:"<<avgtt;
        cout<<endl;
        cout<<"Average Waiting Time:"<<avgwt;
        cout<<endl;
    }
    
};
#endif /* RR_h */
