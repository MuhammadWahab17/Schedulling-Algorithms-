//
//  SJF.h
//  CPU Scheduling
//
//  Created by Ch Muhammad Wahab on 02/11/2021.
//  Copyright © 2021 Ch Muhammad Wahab. All rights reserved.
//

#ifndef SJF_h
#define SJF_h
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include"Process.h"

using namespace std;
struct node_sjf {
    process data;
    node_sjf*next;
    node_sjf(process d,node_sjf*n=NULL){
        data = d;
        next = n;
    }
};
class sjf {
    node_sjf*head,*tail;
    double avg_TAT,avg_WT;
public:
    sjf(){
        head = NULL;
        avg_WT = avg_TAT = 0;
    }
    ~sjf(){
        while(head !=NULL){
            node_sjf*temp=head;
            head = head->next;
            delete temp;
        }
    }
    
    void sort(node_sjf*h){
        node_sjf*cur=h;
        if(head==NULL)
            throw "NULL \n";
        while(cur!=NULL){
            node_sjf*hold=cur;
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
        node_sjf*temp = head->next;
        node_sjf*prev = head;
        avg_TAT = avg_WT = 0;
        while (temp!=NULL) {
            temp->data.termination = prev->data.termination + temp->data.BT;
            prev = temp;
            avg_TAT += (temp->data.termination- temp->data.AT);
            avg_WT += ((temp->data.termination - temp->data.AT)-temp->data.BT);
            temp=temp->next;
        }
    }
    void add_process(process d){
        node_sjf*input= new node_sjf(d);
        if(head ==NULL){
            d.termination = d.BT;
            input->data = d;
            head = tail = input;
        }
        else{
            if(d.AT<=head->data.AT){
                input->next = head;
                head=input;
                
                if(head->data.BT > head->next->data.BT){
                    process p = head->next->data;
                    head->next->data = head->data;
                    head->data = p;
                }
                head->data.termination = head->data.BT;
                head->next->data.termination = head->data.termination+head->next->data.BT;
            }
            else {
                node_sjf*temp = head;
                bool inserted = false;
                if(d.AT < tail->data.AT)
                    while(temp->next!=NULL){
                        if(d.AT <= temp->next->data.AT)
                        {
                            input->next = temp->next;
                            temp->next = input;
                            if(temp->next->data.BT > temp->next->next->data.BT){
                                process p = temp->next->data;
                                temp->next->data = temp->next->next->data;
                                temp->next->next->data = p;
                            }
                            inserted = true;
                            break;
                        }
                        temp = temp->next;
                    }
                temp = head;
                if(!inserted)
                    while(temp!=NULL){
                        if(d.AT <= temp->data.termination){
                            //                        sort(temp->next);
                            if(temp->next == NULL){
                                tail->next = new node_sjf(d,NULL);
                                tail = tail->next;
                            }
                            else if(d.BT < temp->next->data.BT){
                                node_sjf* input = new node_sjf(d,temp->next);
                                temp->next = input;
                            }
                            else if(d.BT > tail->data.BT){
                                tail->next = new node_sjf(d,NULL);
                                tail = tail->next;
                            }
                            else{
                                node_sjf*tempp = temp->next;
                                while(tempp->next!=NULL){
                                    if(d.BT<tempp->next->data.BT)
                                        break;
                                    tempp = tempp->next;
                                }
                                node_sjf* input = new node_sjf(d,tempp->next);
                                tempp->next = input;
                            }
                            inserted = true;
                            break;
                        }
                        temp=temp->next;
                    }
                if(!inserted){
                    tail->next = input;
                    tail = tail->next;
                }
                set_termination_time();
            }
        }
    }
    void tablular_form(){
        cout<<endl;
        cout<<setw(7)<<setfill(' ')<<"Process"<<setw(15)<<"Arrival Time"<<setw(15)<<"Bust Time"<<endl;
        node_sjf*temp = head;
        while(temp!=NULL){
            cout<<setw(7)<<setfill(' ')<<temp->data.name<<setw(15)<<temp->data.AT<<setw(15)<<temp->data.BT<<endl;
            temp = temp->next;
        }
        cout<<endl;
    }
    void gantt_chart(){
        node_sjf*temp = head;
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

#endif /* SJF_h */
