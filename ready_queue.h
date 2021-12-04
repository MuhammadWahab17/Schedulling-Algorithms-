//
//  ready_queue.h
//  CPU Scheduling
//
//  Created by Ch Muhammad Wahab on 31/10/2021.
//  Copyright © 2021 Ch Muhammad Wahab. All rights reserved.
//

#ifndef ready_queue_h
#define ready_queue_h
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include"Process.h"
using namespace std;

struct ready_node {
    process data;
    ready_node*next;
    ready_node(process d,ready_node*n=NULL){
        data = d;
        next = n;
    }
};

class ready_queue{
    ready_node*first,*last;
    double avg_TAT,avg_WT;
public:
    ready_queue(){
        first = last = NULL;
        avg_TAT=0;avg_WT=0;
    }
    ~ready_queue(){
        while(first !=NULL){
            ready_node*temp=first;
            first = first->next;
            delete temp;
        }
    }
    bool check_queue(process p){
        ready_node*temp = first;
        while(temp!=NULL){
            if(strcmp(temp->data.name.c_str(),p.name.c_str())==0){
                return true;
            }temp = temp->next;
        }
        return false;
    }
    void add_process(process d){
        if(first == NULL){
            first = last = new ready_node(d,NULL);
        }
        else{
            if(d.AT < first->data.AT){
                ready_node* input = new ready_node(d,first);
                first = input;
            }
            else if(d.AT >= last->data.AT){
                last->next = new ready_node(d,NULL);
                last = last->next;
            }
            else{
                ready_node*temp = first;
                while(temp->next!=NULL){
                    if(d.AT<temp->next->data.AT)
                        break;
                    temp = temp->next;
                }
                ready_node* input = new ready_node(d,temp->next);
                temp->next = input;
            }
        }
    }
    
};
#endif /* ready_queue_h */
