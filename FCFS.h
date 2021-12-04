//
//  FCFS.h
//  CPU Scheduling
//
//  Created by Ch Muhammad Wahab on 31/10/2021.
//  Copyright © 2021 Ch Muhammad Wahab. All rights reserved.
//

#ifndef FCFS_h
#define FCFS_h
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include"Process.h"
using namespace std;

struct node {
    process data;
    node*next;
    node(process d,node*n=NULL){
        data = d;
        next = n;
    }
};

class sorted_queue{
    node*first,*last;
    double avg_TAT,avg_WT;
public:
    sorted_queue(){
        first = last = NULL;
        avg_TAT=0;avg_WT=0;
    }
    ~sorted_queue(){
        while(first !=NULL){
            node*temp=first;
            first = first->next;
            delete temp;
        }
    }
    bool check_queue(process p){
        node*temp = first;
        while(temp!=NULL){
            if(strcmp(temp->data.name.c_str(),p.name.c_str())==0){
                return true;
            }temp = temp->next;
        }
        return false;
    }
    void add_process(process d){
        if(first == NULL){
            first = last = new node(d,NULL);
        }
        else{
            if(d.AT < first->data.AT){
                node* input = new node(d,first);
                first = input;
            }
            else if(d.AT >= last->data.AT){
                last->next = new node(d,NULL);
                last = last->next;
            }
            else{
                node*temp = first;
                while(temp->next!=NULL){
                    if(d.AT<temp->next->data.AT)
                        break;
                    temp = temp->next;
                }
                node* input = new node(d,temp->next);
                temp->next = input;
            }
        }
    }
    void tablular_form(){
        cout<<endl;
        cout<<setw(7)<<"Process"<<setw(15)<<"Arrival Time"<<setw(15)<<"Bust Time"<<endl;
        node*temp = first;
        while(temp!=NULL){
            cout<<setw(7)<<temp->data.name<<setw(15)<<temp->data.AT<<setw(15)<<temp->data.BT<<endl;
            temp = temp->next;
        }
        cout<<endl;
    }
    void gantt_chart(){
        node*temp = first;
        cout<<" ";
        while(temp!=NULL){
            cout<<setw(temp->data.BT+2)<<setfill(' ')<<temp->data.name;
            temp = temp->next;
        }
        cout<<endl;
        int termination_time=0;
        if(first!=NULL){
            cout<<first->data.AT;
            cout<<setw(first->data.BT+2)<<setfill('-');
            termination_time = first->data.BT;
            avg_TAT += termination_time-first->data.AT;
            avg_WT += (termination_time-first->data.AT) - first->data.BT;
            cout<<first->data.BT;
        }
        temp = first->next;
        while(temp!=NULL){
            cout<<setw(temp->data.BT+2)<<setfill('-');
            termination_time += temp->data.BT;
            cout<<termination_time;
            avg_TAT += termination_time-temp->data.AT;
            avg_WT += (termination_time-temp->data.AT) - temp->data.BT;
            temp = temp->next;
        }
        avg_WT /= numberOfProcesses;
        avg_TAT /= numberOfProcesses;
    }
    void averages(){
        cout<<"\n\nAverage Turn Around Time :"<<avg_TAT<<endl;
        cout<<"Average Wait time :"<<avg_WT<<endl;
    }
    
};

#endif /* FCFS_h */
