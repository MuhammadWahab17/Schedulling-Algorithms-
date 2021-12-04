//
//  main.cpp
//  CPU Scheduling
//
//  Created by Ch Muhammad Wahab on 31/10/2021.
//  Copyright © 2021 Ch Muhammad Wahab. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include"Process.h"
#include"ready_queue.h"
#include"FCFS.h"
#include"SJF.h"
#include"SRTF.h"
#include"RR.h"
using namespace std;



int main(int argc, const char * argv[]) {
    
    cout<<"Enter number of processes:";
    cin>>numberOfProcesses;
    
    sorted_queue fcfs;
    ready_queue rq;
    sjf SJF;
    srtf SRTF;
    RR r(numberOfProcesses);
    
    for (int i=0; i<numberOfProcesses; i++) {
        process p;
        cin>>p;
        if(!rq.check_queue(p)){
            rq.add_process(p);
            fcfs.add_process(p);
            SJF.add_process(p);
            SRTF.add_process(p);
            r.add_process(p);
        }
        else{
            cout<<"Process is already in Ready Queue\nEnter Again\n";
            i--;
        }
    }
    
    cout<<"\n**************First Come First Serve**************\n";
    //--------First Come Fist Serve-----------//
    fcfs.tablular_form();
    fcfs.gantt_chart();
    fcfs.averages();
    //--------First Come Fist Serve-----------//
    
    cout<<"\n\n**************Shortest Job First**************\n";
    //--------Shortest Job First-----------//
    SJF.tablular_form();
    SJF.gantt_chart();
    SJF.averages();
    //--------Shortest Job First-----------//
    
    cout<<"\n\n**************Shortest remainimg time First**************\n";
    //--------Shortest Job First-----------//
    SRTF.schedule();
    //--------Shortest Job First-----------//
    
    cout<<"\n\n**************Round Robin**************\n";
    //--------Round Robin-----------//
    cout<<"Enter time quantum: ";
    int q;
    cin>>q;
    r.RunRR(q);
    //--------Round Robin-----------//
    
    return 0;
}
