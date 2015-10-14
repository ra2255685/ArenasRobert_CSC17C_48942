/* 
 * File:   SortList.h
 * Author: Robert Arenas ID: 2255685
 *
 * Created on October 13, 2015, 9:47 AM
 */

#ifndef SORTLIST_H
#define	SORTLIST_H

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

template<class T>
class SortList{
    
    public:
        SortList(T); //default constructor
        SortList(const SortList &); //copy constructor
        virtual ~SortList(); //destructor
        void insert(T);    //add value to list in ascending order
        void extract(T);                   //removes a value from the list
        T getElementAT(int); // gets an element at specified position
        int size();            //returns the size of the linked list
        T first();                         //returns a reference first value 
        T last();                          //returns a reference last value
        string toString();          //print the list
        
        
    private:
         struct Node{
         T data;
         Node *next;
        };
        Node *head;
        Node *worker;   
        
        void append(T); // used only for copy constructor 
};

//default constructor
template <class T>
SortList<T>::SortList(T n){
    Node *clink=new Node;
    clink->data=n;
    clink->next=NULL;
    head=clink;
}
//copy constructor
template <class T>
SortList<T>::SortList(const SortList &obj){
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
SortList<T>::~SortList(){
    if(head){
        do{
            worker=head;
            head=head->next;
            delete worker;
        }while(head);
    }
}
//add values to list in ascending order
template <class T>
void SortList<T>::insert(T newValue){
   
    Node *newNode;  //new node
    Node *nodePtr; // allows list to be traversed
    Node *prev ;   //point to previous list before changing
    
    //create new node and store newValue
    newNode = new Node;
    newNode->data = newValue;
    
    //if list empty create new one
    if(!head){
        Node *clink=new Node;
        clink->data=newValue;
        clink->next=NULL;
        head=clink;
    }else if(head->data >= newValue){
        //place newValue before head if its is less than current head
        newNode->next = head;
        head = newNode;
    }else{
        
        nodePtr = head; //point to start of list
        
        //skip nodes whose values are less than newValue
        while(nodePtr != NULL && nodePtr->data < newValue){
            prev = nodePtr;
            nodePtr = nodePtr->next;
        }
        //add newValue in proper place
        newNode->next = nodePtr;
        prev->next = newNode;
    }
}
//remove value from list
template <class T>
void SortList<T>::extract(T n){
    Node *nodePtr; //allows list to be traversed
    Node *prev;     //point to previous node
    
    //does nothing if node empty
    if(!head){
        return;
    }
    
    //deletes first node if it is chosen
    if(head->data == n){
        nodePtr = head->next; //pointer set equal to value after head
        delete head;          //remove head
        head = nodePtr;       //set head equal to previously second list item
    }else{
        
        nodePtr = head;  //pointer set to start of list
        
        //skip nodes whose values are not equal to n
        while(nodePtr != NULL && nodePtr->data != n){
            prev = nodePtr;
            nodePtr = nodePtr->next;
        }
        
        //links previous node and node after vale to be deleted then deletes 
        //value
        if(nodePtr){
            prev->next = nodePtr->next;
            delete nodePtr;
        }else{
            cout << "EXTRACTION FAILED: The Value "  << n 
                    << " does not exist in the list" << endl;
        }
    }
}
//get element at specified position
template <class T>
T SortList<T>::getElementAT(int position){
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
//return size of list
template <class T>
int SortList<T>::size(){
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
//return value in head
template <class T>
T SortList<T>::first(){
    return head->data;
}
//return value at end of list
template <class T>
T SortList<T>::last(){
    Node *nodePtr; // allows list to be traversed
    Node *end ;    //used to check for null at endo list
    Node *lastVal; //used to get last value
    
    if(head->next == NULL){
        return head->data;
    }else{
        Node *nodePtr = head;
        Node *end = head->next;
        while(end->next != NULL){
            nodePtr = end;
            end = end->next;
        }
        lastVal = nodePtr->next;
        return lastVal->data;
    }
}
//print the list
template <class T>
string SortList<T>::toString(){
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
//used to make copy in copy constructor
template <class T>
void SortList<T>::append(T n){
    Node *prev;
    //copies node into prev pointer 
    if(head){
        worker = head;
        do{
            prev = worker;
        }while(worker = worker->next);
        //"pushes" new value on to the end of the list
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
#endif	/* SORTLIST_H */

