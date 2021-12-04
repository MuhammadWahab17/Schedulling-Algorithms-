//
//  SRTF.h
//  CPU Scheduling
//
//  Created by Ch Muhammad Wahab on 08/11/2021.
//  Copyright © 2021 Ch Muhammad Wahab. All rights reserved.
//

#ifndef SRTF_h
#define SRTF_h

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include"Process.h"
using namespace std;
struct srtf_node {
    process data;
    srtf_node*next;
    srtf_node(process d,srtf_node*n=NULL){
        data = d;
        next = n;
    }
};
class srtf {
    srtf_node*head,*tail;
    double avg_TAT,avg_WT;
public:
    srtf(){
        head = NULL;
        avg_WT = avg_TAT = 0;
    }
    ~srtf(){
        while(head !=NULL){
            srtf_node*temp=head;
            head = head->next;
            delete temp;
        }
    }
    void schedule(){
        srtf lst;
        srtf_node*cur=head;
        srtf_node*temp;
        if(head==NULL || head->next==NULL)
        {
            cout<<"head null";
            return;
        }
        lst.insert(head->data);
        cur = cur->next;
        while(cur!=NULL){
            temp =lst.head;
            srtf_node*prev =lst.head;
            while(temp!=NULL){
                if(cur->data.AT < temp->data.termination){
                    int at;
                    if(prev != lst.head)
                        at = cur->data.AT-prev->data.termination;
                    else
                        at = cur->data.AT;
                    int bt = (temp->data.BT) - at;
                    if(cur->data.BT < bt){
                        process p;
                        p.BT = bt;
                        temp->data.BT = temp->data.BT - bt;
                        p.AT = temp->data.AT;
                        p.name = temp->data.name;
                        lst.insert(cur->data);
                        lst.insert(p);
                    }
                    else{
                        lst.insert(cur->data);
                    }
                    lst.sort(temp->next);
                    lst.set_termination_time();
                    break;
                }
                else{
                    lst.insert(cur->data);
                    lst.set_termination_time();
                    break;
                }
                prev = temp;
                temp = temp->next;
            }
            cur = cur->next;
        }
        lst.tablular_form();
        lst.gantt_chart();
        cur = head;
        avg_TAT = avg_WT = 0;
        while(cur!=NULL){
            temp = lst.head;
            while(temp!=NULL){
                if(cur->data.AT == temp->data.AT){
                    cur->data.termination = temp->data.termination;
                }
                temp=temp->next;
            }
            avg_TAT += (cur->data.termination- cur->data.AT);
            avg_WT += ((cur->data.termination - cur->data.AT)-cur->data.BT);
            cur = cur->next;
        }
        averages();
    }
    void insert(process p){
        srtf_node*input= new srtf_node(p);
        if(head == NULL){
            head = tail = input;
        }else{
            tail->next = input;
            tail=tail->next;
        }
    }
    void sort(srtf_node*c){
        srtf_node*cur=c;
        if(head==NULL)
        throw "NULL \n";
        while(cur!=NULL){
            srtf_node*hold=cur;
            while(cur->next!=NULL){
                if(hold->data.BT > cur->next->data.BT){
                    process s=hold->data;
                    hold->data=cur->next->data;
                    cur->next->data=s;
                }
                cur=cur->next;
            }
            cur=hold->next;
        }
    }
    void set_termination_time(){
        head->data.termination = head->data.BT;
        if(head->next == NULL)
            return;
        srtf_node*temp = head->next;
        srtf_node*prev = head;
        while (temp!=NULL) {
            temp->data.termination = prev->data.termination + temp->data.BT;
            prev = temp;
            temp=temp->next;
        }
    }
    void add_process(process d){
        srtf_node*input= new srtf_node(d);
        if(head ==NULL){
            input->data = d;
            head = tail = input;
        }
        else{
            srtf_node *temp=head;
            if(d.AT<head->data.AT){
                input->next=head;
                head=input;
            }
            else if(d.AT > tail->data.AT){
                tail->next = input;
                tail = tail->next;
            }
            else{
                while(temp->next!=NULL){
                    if(temp->next->data.AT > d.AT)
                    break;
                    temp=temp->next;
                }
                input->next=temp->next;
                temp->next=input;
            }
        }
        set_termination_time();
    }
    void tablular_form(){
        cout<<endl;
        cout<<setw(7)<<setfill(' ')<<"Process"<<setw(15)<<"Arrival Time"<<setw(15)<<"Bust Time"<<endl;
        srtf_node*temp = head;
        while(temp!=NULL){
            cout<<setw(7)<<setfill(' ')<<temp->data.name<<setw(15)<<temp->data.AT<<setw(15)<<temp->data.BT<<endl;
            temp = temp->next;
        }
        cout<<endl;
    }
    void gantt_chart(){
        srtf_node*temp = head;
        cout<<" ";
        while(temp!=NULL){
            cout<<setw(temp->data.BT+2)<<setfill(' ')<<temp->data.name;
            temp = temp->next;
        }
        cout<<endl;
        if(head!=NULL){
            cout<<head->data.AT;
            cout<<setw(head->data.BT+2)<<setfill('-');
            cout<<head->data.BT;
        }
        temp = head->next;
        while(temp!=NULL){
            cout<<setw(temp->data.BT+2)<<setfill('-');
            cout<<temp->data.termination;
            temp = temp->next;
        }
    }
    void averages(){
        
        cout<<"\n\nAverage Turn Around Time :"<<avg_TAT/numberOfProcesses<<endl;
        cout<<"Average Wait time :"<<avg_WT/numberOfProcesses<<endl;
    }
};
#endif /* SRTF_h */
