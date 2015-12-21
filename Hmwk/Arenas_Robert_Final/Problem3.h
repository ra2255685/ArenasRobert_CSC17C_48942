/* 
 * File:   Problem3.h
 * Author: Robert Arenas Id: 2255685
 *
 * Created on December 17, 2015, 1:10 PM
 */

#ifndef PROBLEM3_H
#define PROBLEM3_H

#include <cstdlib>
#include <iostream>

using namespace std;

class Bank{
public:
    Bank();
    void addCustomer(int time);
    void print();
    void removeCustomer(int index);
    float serviceTime();
    void removeAtTime(int time);
private:
    
    //size of the hash table 
    static const int tellers = 10;
    
    struct Node{
        bool person;
        int arrivalTime;
        float waitTime;
        Node* next; //pointer to next node customer
    };
    
    Node *lines[tellers]; //pointer to hash table
    Node *worker;
    
    float totalSec;
    
    int addToLine();
    int itemsInIndex(int index);
    float getWaitTime(int index);
};

Bank::Bank(){
    for(int i = 0; i < tellers; i++){
        
        lines[i] = new Node;
        lines[i]->person = false;
        lines[i]->arrivalTime = 0;
        lines[i]->waitTime = 0;
        lines[i]->next = NULL;
    }
    
    totalSec = 0;
}
void Bank::addCustomer(int time){
    
    int index = addToLine();
    
    if(lines[index]->person == false){
        
        lines[index]->arrivalTime = time;
        lines[index]->waitTime = getWaitTime(index);
        lines[index]->person = true;
        
    }else{
        worker = lines[index];
        Node *temp = new Node;
        
        temp->arrivalTime = time;
        lines[index]->waitTime = getWaitTime(index);
        temp->person = true;
        temp->next = NULL;
        
       while(worker->next != NULL){
           worker = worker->next;
       }
       
       worker->next = temp;
    }
}

int Bank::addToLine(){
    int number = 0;
    
    for(int i = 0; i < tellers; i++){
         number = itemsInIndex(i);
         if(number < 5){
             number = i;
             break;
         }
    }
    
    return number;
}

int Bank::itemsInIndex(int index){
    int count = 0;
    
    if(lines[index]->person == false){
        return count;
    }else{
        
        count ++;
    
        worker = lines[index];
        
        while(worker->next != NULL){
            count ++;
            worker = worker->next;
        }
    }
    
    return count;
}

void Bank::print(){
    int number;
    
    for(int i = 0; i < tellers; i++){
        number = itemsInIndex(i);
        cout << "-------------------" << endl;
        cout << "index = " << i << endl;
        cout << "#of items in bucket " << number << endl;
        cout << "-------------------" << endl;
    }
}

float Bank::getWaitTime(int index){
    float waittime;
    int number;
    
    if(index == 1){
        number = itemsInIndex(index);
        waittime = .30 * (float)number;
    }else if(index == 2){
        number = itemsInIndex(index);
        waittime = .45 * (float)number;
    }else{
        number = itemsInIndex(index);
        waittime = .60 * (float)number;
    }
    
    return waittime;
}

void Bank::removeCustomer(int index){
    
    //nothing to delete
    if(lines[index]->person == false && lines[index]->waitTime == 0){
        //cout << index << " empty not found" << endl;
        
        //only one in bucket
    }else if(lines[index]->person == true && lines[index]->next == NULL){
        
        totalSec = totalSec + lines[index]->waitTime;
        
        lines[index] = new Node;
        lines[index]->person = false;
        lines[index]->arrivalTime = 0;
        lines[index]->waitTime = 0;
        lines[index]->next = NULL;
        
      //fist item in bucket and more to follow  
    }else if(lines[index]->person == true){
        
        worker = lines[index];
        
        totalSec = totalSec + worker->waitTime;
        
        lines[index] = lines[index]->next;
        
        delete worker;     
    }
    
}

float Bank::serviceTime(){
    return totalSec;
}

void Bank::removeAtTime(int time){
    
    if(time % 10 == 0){
        removeCustomer(0);
        removeCustomer(3);
        removeCustomer(4);
        removeCustomer(5);
        removeCustomer(6);
        removeCustomer(7);
        removeCustomer(8);
        removeCustomer(9);
        
    }
        
    if(time % 2 == 0){
        removeCustomer(1);
    }
        
    if(time % 5 == 0){
        removeCustomer(2);
    }
}
#endif /* PROBLEM3_H */

