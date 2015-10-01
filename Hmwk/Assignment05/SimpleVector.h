/* 
 * File:   SimpleVector.h
 * Author: Robert Arenas
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
       SimpleVector(T);       //default constructors
    virtual ~SimpleVector(); //destructor
    string toString();      //prints the linkedlist
    
    //functions from array implemetation made to work with linked lists
    void pull();           //pull to remove first element in list 
    T getElementAT(int); // gets an element at specified position
    int size();            //returns the size of the linked list
    
    //assignment 5 functions
    SimpleVector(const SimpleVector &);  //copy constructor
    void prepend(T);                   //adds a value to front of list
    void append(T);                    //adds a value to end of list
    void extract(T);                   //removes a value from the list
    void insertAfter(T, T);          //insert value after a specified value
    void insertBefore(T, T);         //insert value before a specified value
    T first();                         //returns a reference first could not get to work properly
    T last();       
    
    private:
      struct Node{
         T data;
         Node *next;
    };
    Node *head;
    Node *worker;  
};

//default constructor
template <class T>
SimpleVector<T>::SimpleVector(T n){
    Node *clink=new Node;
    clink->data=n;
    clink->next=NULL;
    head=clink;
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
//pull function to remove first value in list
template <class T>
void SimpleVector<T>::pull(){
        if(head){
        Node *prev; //pointer to list
        prev = head->next;
        delete head;
        head = prev;
    }else{
        cout << "List is empty" << endl;
    }
}
//return value at a given position
template <class T>
T SimpleVector<T>::getElementAT(int position){
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
//copy Constructor
template <class T>
SimpleVector<T>::SimpleVector(const SimpleVector &obj){
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
template <class T>
//add a value to the start of the list
void SimpleVector<T>::prepend(T n){
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
//removes value fro list
template <class T>
void SimpleVector<T>::extract(T n){
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
        head = newNode;
        newNode->next = NULL;
    }else if(head->data == preceadValue){
        nodePtr =head->next;   //points to values after the first value
        head->next = newNode;  //add new value after head
        prev = head->next;     //pont to  newValue
        prev->next = nodePtr;  //add rest of previous values after newValue  
    }else{
        nodePtr = head; //point to start of list
        
        //skip nodes whose values are not equal to n
        while(nodePtr != NULL && nodePtr->data != preceadValue){
            prev = nodePtr;
            nodePtr = nodePtr->next;
        }
        
        //if being added after last value append function is called
        //else newValue inserted after designated value
        if(nodePtr->next == NULL){
            append(newValue);
        }else{
            Node *temp; //points to values after position where newValue Will be inserted
            
            temp = nodePtr->next;     //values after position where newValue Will be inserted
            nodePtr->next = newNode;  //add the newValue
            newNode->next = temp;     //add values after new value
            prev->next = nodePtr;     //add newValue and succeeding values after preceding values
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
        head = newNode;
        newNode->next = NULL;
    }else if(head->data == afterValue){
        prepend(newValue);
    }else{
        nodePtr = head; //point to start of list
        
        //skip nodes whose values are not equal to n
        while(nodePtr != NULL && nodePtr->data != afterValue){
            prev = nodePtr;
            nodePtr = nodePtr->next;
        }
        
        //inserts the new value before the user chosen value
        prev->next = newNode;
        newNode->next = nodePtr;
    }
}
//return a reference to the first value in list
//could not figure out how to return the reference
//so just returns value of first node
template <class T>
T SimpleVector<T>::first(){
    Node *n = head;
    return n->data;
}
//return a reference to the last value in list
//could not figure out how to return the reference
//so just returns value of last node
template <class T>
T SimpleVector<T>::last(){
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
#endif	/* SIMPLEVECTOR_H */

