//
//  Process.h
//  CPU Scheduling
//
//  Created by Ch Muhammad Wahab on 31/10/2021.
//  Copyright © 2021 Ch Muhammad Wahab. All rights reserved.
//

#ifndef Process_h
#define Process_h

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
using namespace std;

int numberOfProcesses;
struct process{
    string name;
    int AT;
    int BT;
    int termination;
    friend istream& operator>>(istream& in,process &p){
        cout<<"Enter process Name :";
        in>>p.name;
        cout<<"Enter Arrival Time :";
        in>>p.AT;
        cout<<"Enter Burst Time :";
        in>>p.BT;
        return in;
    }
    
};

#endif /* Process_h */
