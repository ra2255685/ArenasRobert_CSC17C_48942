/* 
 * File:   SimpleVector.cpp
 * Author: Robert Arenas 
 * ID: 2255685
 * Created on September 24, 2015, 3:26 PM
 */

#include  <iostream>
#include  <cstdlib>
#include  <sstream>

#include "SimpleVector.h"

using namespace std;

//default constructor
SimpleVector::SimpleVector(int n) {
    Node *clink=new Node;
    clink->data=n;
    clink->next=NULL;
    head=clink;
}
//deconstructor borrowed from link list example
SimpleVector::~SimpleVector() {
    if(head){
        do{
            worker=head;
            head=head->next;
            delete worker;
        }while(head);
    }
}

//borrowed from linked list example prints list
string SimpleVector::toString(){
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

//push function same as append function borrowed from linkedlist example
void SimpleVector::push(int n){
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
//pull function to remove first value in list
void SimpleVector::pull(){
    
    if(head){
        Node *prev; //pointer to list
        prev = head->next;
        delete head;
        head = prev;
    }else{
        cout << "List is empty" << endl;
    }
}
//returns size of list
int SimpleVector::size(){
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
//return value at a given position
int SimpleVector::getElementAT(int position){
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
//copy constructor
SimpleVector::SimpleVector(const SimpleVector &obj){
    head = NULL;  // set the head to null in order to create new list
    //does nothing if node empty
    if(obj.head == NULL){
        return;
    }else{
        Node *temp = obj.head; //create temporary node to point to original list values
        while(temp != NULL){
            append(temp->data);
            temp = temp->next;
        }
    }
}
//add a value to start of list
void SimpleVector::prepend(int n){
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
void SimpleVector::append(int n){
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
//removes value from list
void SimpleVector::extract(int n){
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
void SimpleVector::insertAfter(int newValue, int preceadValue){
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
            cout <<"last item" << endl;
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
void SimpleVector::insertBefore(int newValue, int afterValue){
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
int SimpleVector::first(){
    Node *n = head;
    return n->data;
}
//return a reference to the last value in list
//could not figure out how to return the reference
//so just returns value of last node
int SimpleVector::last(){
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