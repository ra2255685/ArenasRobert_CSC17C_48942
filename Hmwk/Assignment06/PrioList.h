/* 
 * File:   PrioList.h
 * Author: Robert Arenas ID: 2255685
 *
 * Created on October 11, 2015, 6:23 PM
 */

#ifndef PRIOLIST_H
#define	PRIOLIST_H

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

template<class T>
class PrioList{
    public:
        PrioList(T);                //constructor
        PrioList(const PrioList &); //copy constructor
        virtual ~PrioList();        //destructor
        void push(T);               //add value to the list
        void pop();                 //remove top element
        T top();                    //return value at top of list
        T getElementAT(int);        // gets an element at specified position
        int size();                 //return size of list
        string toString();          //print the list
        
    private:
        struct Node{
         T data;
         Node *next;
        };
        Node *head;
        Node *worker;
        
        Node *front = NULL;
        Node *back = NULL;
        
        void prioritize(); // sort list putting higher value (priority value) at top 
                           // of list called when ever item is added to list is an 
                           //insertion swap
        
        void append(T); // used only for copy constructor 
};

//default constructor
template <class T>
PrioList<T>::PrioList(T n){
    Node *clink=new Node;
    clink->data=n;
    clink->next=NULL;
    head=clink;
}
//copy constructor
template <class T>
PrioList<T>::PrioList(const PrioList &obj){
    head = NULL;  // set the head to null in order to create new list
    //does nothing if node empty
    if(obj.head == NULL){
        return;
    }else{
        Node *temp = obj.head; //create temporary node to point to original list values
        while(temp != NULL){
            append(temp->data); //copy value into new list
            temp = temp->next;  //advance to next node in new list
        }
    }
}
//destructor
template <class T>
PrioList<T>::~PrioList(){
    if(head){
        do{
            worker=head;
            head=head->next;
            delete worker;
        }while(head);
    }
}
//adds value to list inserts at head
template <class T>
void PrioList<T>::push(T n){
    if(head){
        Node *prev = head;       //pointer to start of previous node
        Node *clink = new Node;
        clink->data = n;
        head = clink;            //change the head value to new value
        clink->next = prev;      //add previous node after new head
    }else{ //if node is empty create new node
        Node *clink=new Node;
        clink->data=n;
        clink->next=NULL;
        head=clink;
    }
    prioritize();
}
//remove top value from list
template <class T>
void PrioList<T>::pop(){
    if(head){
        Node *nodePtr; //pointer to list
        nodePtr = head->next;
        delete head;
        head = nodePtr;
    }else{
        cout << "List is empty" << endl;
    }
}
template <class T>
T PrioList<T>::getElementAT(int position){
    int listSize = size(); //size of the list
    Node *lstPtr = head;   //will alow list to be traversed
    int count = 1;         //functions as the position of the value of the list
    
    if(position < 0 || position > listSize){
        cout << "ERROR: position out of range" << endl;
        exit(EXIT_FAILURE);
    }
    while(lstPtr != NULL){
        if (count == position){
            return(lstPtr->data); //returns position value when position requested
                                  //is equal to the count as it cycles through each node
                                  // one by one
        }  
        count++;                //increment count to move to next value in list
        lstPtr = lstPtr->next; //move to next value in list   
    }
}
//return top value in list
template <class T>
T PrioList<T>::top(){
    return head->data;
}
//returns size of list
template <class T>
int PrioList<T>::size(){
    int count = 0; //used to keep track of size
    
    //cycles through each node and increments count to represent size
    if(head){
        worker = head;
        do{
            count++;
        }while(worker = worker->next);
        return count;
    }else{
        return 0;
    }
}
//print list
template <class T>
string PrioList<T>::toString(){
    string build="";
    if(head){
        worker=head;
        do{
             build+=("Data element in the list ->");
             stringstream ss;
             ss<<worker->data;
             string data;
             ss>>data;
             build+=data;
             build+="\n";
        }while(worker=worker->next);
    }else{
        build = "LIST IS EMPTY!";
    }
    return build;
}
//sorts array higher numbers moved to top of list because they have priority
template <class T>
void PrioList<T>::prioritize(){

    Node *current = head->next; //starts at value after head
    Node *insertionPtr = head;  //starts at head
 
    while(current != NULL){
        insertionPtr = head;
        
        while(insertionPtr != current){
            if(insertionPtr->data < current->data){
                T temp = current->data;  //temp value to hold value to be swaped
                //swap the values
                current->data = insertionPtr->data;
                insertionPtr->data = temp;
            }else{
                //advance  insertionPtr to next value 
                insertionPtr = insertionPtr->next;
            }
        }
            //advance current to next value
            current = current->next;
    }
}
//append value to end of list
//only used in copy constructor for Stack list
template <class T>
void PrioList<T>::append(T n){
    Node *prev;
    //copies node into prev pointer 
    if(head){
        worker = head;
        do{
            prev = worker;
        }while(worker = worker->next);
        Node *clink = new Node; //create new node to store new vale n
        clink->data = n;
        clink->next = NULL;
        prev->next = clink; //adds new value to end of the previous list
    }else{
       //if list is empty creates a new list
       Node *clink=new Node;
        clink->data=n;
        clink->next=NULL;
        head=clink; 
    }
}
#endif	/* PRIOLIST_H */

