/* 
 * File:   SimpleVector.h
 * Author: Robert Arenas ID: 2255685
 *
 * Created on September 29, 2015, 6:57 PM
 */

#ifndef SIMPLEVECTOR_H
#define	SIMPLEVECTOR_H

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

template<class T>
class SimpleVector{
    public:
    SimpleVector(T);                     //default constructors
    SimpleVector(const SimpleVector &);  //copy constructor
    virtual ~SimpleVector();             //destructor
    
    string toString();      //prints the linkedlist
    T getElementAT(int); // gets an element at specified position
    int size();            //returns the size of the linked list
    
    //assignment 5 functions modified for assignment 6
    //to work with doubly linked lists
    
    void prepend(T);                   //adds a value to front of list
    void append(T);                    //adds a value to end of list
    void extract(T);                   //removes a value from the list
    void insertAfter(T, T);            //insert value after a specified value
    void insertBefore(T, T);           //insert value before a specified value
    T first();                         //returns a reference first value could not get to work properly
    T last();                          //returns a reference last value could not get to work properly
    
    string toStringBack(); //prints the linkedlist backwards
    
    private:
      struct Node{
         T data;
         Node *next;
         Node *prevous; //point to previous node used in doubly linked list
    };
    Node *head;     //in assignment 6 used as pointer to top of stack
    Node *tail;     //point to last node in list
    Node *worker;  
};

//default constructor
template <class T>
SimpleVector<T>::SimpleVector(T n){
    Node *clink=new Node;
    clink->data=n;
    clink->prevous = NULL;
    head = clink;
    tail = clink;
    tail->next = NULL;
}
//copy Constructor
template <class T>
SimpleVector<T>::SimpleVector(const SimpleVector &obj){
    head = NULL;  // set the head and tail to null in order to create new list
    tail = NULL;
    //does nothing if node empty
    if(obj.head == NULL){
        return;
    }else{
       Node *temp = obj.head;
       
        while(temp != NULL){
        append(temp->data);
        temp = temp->next; 
        }
    }
}
//deconstructor borrowed from link list example
template <class T>
SimpleVector<T>::~SimpleVector(){
    if(head){
        do{
            worker=head;
            head=head->next;
            delete worker;
        }while(head);
    }
}
//borrowed from linked list class example prints list
template <class T>
string SimpleVector<T>::toString(){
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
    }
    return build;
}
//return value at a given position
template <class T>
T SimpleVector<T>::getElementAT(int position){
    int listSize = size(); //size of the list
    Node *lstPtr = head;   //will alow list to be traversed
    int count = 1;         //functions as the position of the value of the list
    
    if(position < 0 || position > listSize){
        cout << "ERROR: position out of range. program exited" << endl;
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
//returns size of list
template <class T>
int SimpleVector<T>::size(){
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
//add a value to the start of the list
template <class T>
void SimpleVector<T>::prepend(T n){
    if(head){
        Node *prev = head;
        Node *temp = new Node;
        temp->data = n;           //add new value to temp node
        temp ->prevous = NULL;    //make value before new node NULL
        temp->next = prev;        //add previous list to new head
        head->prevous = temp;     //add the temp node before previous head
        head = temp;              // set head as the prepended value 
    }else{ //if node is empty create new node
        Node *clink=new Node;
        clink->data=n;
        clink->prevous = NULL;
        head = clink;
        tail = clink;
        tail->next = NULL;
    }
}
//append value to end of list
template <class T>
void SimpleVector<T>::append(T n){
    Node *prev;
    //copies node into prev pointer 
    if(head){
        worker = head;
        do{
            prev = worker;
        }while(worker = worker->next);
        Node *clink = new Node; //create new node to store new vale n
        clink->data = n;
        clink->prevous = tail;
        tail->next = clink;   //adds new value after previous last value
        tail = clink;         //sets tail pointer back to end value 
        tail->next = NULL;    //sets value after tail to null
    }else{
       //if list is empty creates a new list
       Node *clink=new Node;
       clink->data=n;
       clink->prevous = NULL;
       head = clink;
       tail = clink;
       tail->next = NULL;
    }
}
//removes value from list
template <class T>
void SimpleVector<T>::extract(T n){
    Node *nodePtr; //allows list to be traversed
    Node *prev;     //point to previous node
    Node *temp;    //used to allow item in between head and tail to be deleted 
    
    //does nothing if node empty
    if(!head){
        return;
    }
    
    //deletes first node if it is chosen
    if(head->data == n){
        nodePtr = head->next; //pointer set equal to value after head
        delete head; 
        nodePtr->prevous = NULL;
        //remove head
        head = nodePtr;       //set head equal to previously second list item
    }else if(tail->data == n){ //delete last value if chosen
        nodePtr = tail->prevous;
        delete tail;
        nodePtr->next = NULL;
        tail = nodePtr;
    }else{
        
        nodePtr = head;  //pointer set to start of list
        
        //skip nodes whose values are not equal to n
        while(nodePtr != NULL && nodePtr->data != n){
            prev = nodePtr;
            nodePtr = nodePtr->next;
        }
        
        if(nodePtr){
            temp = nodePtr;         //set pointer to node to be deleted
            nodePtr = temp->next;   //move nodePtr to value after value to be deleted
            //connect values before and after deleted value
            prev->next = nodePtr;
            nodePtr->prevous = prev;
         
            delete temp; //delete node with value chosen
        }else{
            cout << "EXTRACTION FAILED: The Value "  << n 
                    << " does not exist in the list" << endl;
        }
    }
}
//insert a value after a designated value
//preceadValue refers to value the newValue will come after
template <class T>
void SimpleVector<T>::insertAfter(T newValue, T preceadValue){
    Node *newNode;  //new node
    Node *nodePtr; // allows list to be traversed
    Node *prev ;   //point to previous list before changing
    
    //create new node and store newValue
    newNode = new Node;
    newNode->data = newValue;
    
    //if list is empty create new list
    if(!head){
        newNode->prevous = NULL;
        head = newNode;
        tail = newNode;
        tail->next = NULL;
    }else if(head->data == preceadValue){
        //add value after head
        nodePtr = head->next;
        head->next = newNode;
        newNode->prevous = head;
        newNode->next = nodePtr;
        nodePtr->prevous = newNode;
    }else if(tail->data == preceadValue){
        //if value is to  be added after tail it is appended
        append(newValue);
    }else{
        nodePtr = head; //point to start of list
        
        //skip nodes whose values are not equal to preceadValue
        while(nodePtr != NULL && nodePtr->data != preceadValue){
            prev = nodePtr;
            nodePtr = nodePtr->next;
        }
        
        if(nodePtr){
            //move pointers to proper location 
            nodePtr = nodePtr->next;  //will come after newValue
            prev = prev->next;        //will come before newValue
            
            //connect newNode to values before it
            prev->next = newNode;
            newNode->prevous = prev;
            //connect newNode to Values after it
            newNode->next = nodePtr;
            nodePtr->prevous = newNode;
          
        }else{
            cout << "INSERTION FAILED: The Value "  << preceadValue 
                    << " does not exist in the list" << endl;
        }
    }
}
//insert a value before a designated value
//afterValue refers to value the newValue will come before
template <class T>
void SimpleVector<T>::insertBefore(T newValue, T afterValue){
    Node *newNode;  //new node
    Node *nodePtr; // allows list to be traversed
    Node *prev ;   //point to previous list before changing
    
    //create new node and store newValue
    newNode = new Node;
    newNode->data = newValue;
    
    if(!head){
        newNode->prevous = NULL;
        head = newNode;
        tail = newNode;
        tail->next = NULL;
    }else if(head->data == afterValue){
        prepend(newValue);
    }else{
        nodePtr = head; //point to start of list
        
        //skip nodes whose values are not equal to n
        while(nodePtr != NULL && nodePtr->data != afterValue){
            prev = nodePtr;
            nodePtr = nodePtr->next;
        }
        
        if(nodePtr){
            //connect newNode to values before it
            prev->next = newNode;
            newNode->prevous = prev;
            //connect newNode to Values after it
            newNode->next = nodePtr;
            nodePtr->prevous = newNode;
        }else{
            cout << "INSERTION FAILED: The Value "  << afterValue 
                    << " does not exist in the list" << endl;
        }
    }
}
//return a reference to the first value in list
//could not figure out how to return the reference
//so just returns value of first node
template <class T>
T SimpleVector<T>::first(){
    return head->data;
}
//return a reference to the last value in list
//could not figure out how to return the reference
//so just returns value of last node
template <class T>
T SimpleVector<T>::last(){
    if(head->next == NULL){
        return head->data; //return head if only value in list
    }else{
        return tail->data; //else return tail
    }
}
//modified version of toString prints the list in reverse
template <class T>
string SimpleVector<T>::toStringBack(){
    Node* temp = tail;
    
    string build="";
    if(tail){
        worker=tail;
        do{
             build+=("Data element in the list ->");
             stringstream ss;
             ss<<worker->data;
             string data;
             ss>>data;
             build+=data;
             build+="\n";
        }while(worker=worker->prevous);
    }
    return build;
}
#endif	/* SIMPLEVECTOR_H */

