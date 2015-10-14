/* 
 * File:   CirList.h
 * Author: Robert Arenas ID: 2255685
 *
 * Created on October 9, 2015, 3:54 PM
 */

#ifndef CIRLIST_H
#define	CIRLIST_H

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

template<class T>
class CirList{
    
    public:
        CirList(T);                // default constructor
        CirList(const CirList &);  //copy constructor
        virtual ~CirList();        //destructor
        string toString();         //prints the linkedlist
        void prepend(T);           //add value to start of list
        void append(T);            //add value to end of list 
        void extract(T);           //remove value from list
        void insertAfter(T, T);    //insert value after a specified value
        void insertBefore(T, T);   //insert value before a specified value
        T first();                 //returns a reference first value could not get to work properly
        T last();                  //returns a reference last value could not get to work properly
        int size();                //returns the size of the linked list
        T getElementAT(int);       // gets an element at specified position
        void cirPrint(int);        //print list to prove it is circular
        
    private:
        struct Node{
         T data;
         Node *next;
        };
        Node *head;
        Node *tail;
        Node *worker;                 
};

//default constructor
template <class T>
CirList<T>::CirList(T n){
    head = NULL;
    Node *clink=new Node;
    clink->data=n;
    head = clink;
    tail = clink;
    tail->next = head; 
}
//copy constructor
template <class T>
CirList<T>::CirList(const CirList &obj){
    head = NULL;  // set the head and tail to null in order to create new list
    tail = NULL;
    //does nothing if node empty
    if(obj.head == NULL){
        return;
    }else{
       Node *temp = obj.head;
       Node *cpyTail = obj.tail; //used to add tail to copy of list because loop 
                                 //breaks before copying tail
        while(temp->next != obj.head){
        append(temp->data);
        temp = temp->next; 
        }
       append(cpyTail->data); //add tail to list copy after breaking loop
    }
}
//destructor
template <class T>
CirList<T>::~CirList(){
    if(head){
        //cycle through list until tail is reached 
        do{
            worker=head;
            head=head->next;
            delete worker;
        }while(head->next != tail);  
        delete tail; // delete tail after breaking loop
    }
}
//print list
template <class T>
string CirList<T>::toString(){
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
             worker=worker->next;
        }while(worker != head);
    }else{
        cout << "List is empty" << endl;
    }
    return build;
}
//add value to start of list
template <class T>
void CirList<T>::prepend(T n){
    if(head){
        Node *prev = head;
        Node *temp = new Node;
        temp->data = n;           //add new value to temp node
        temp->next = prev;        //add previous list to new head
        head = temp;              // set head as the prepended value 
        tail->next = head;        //connect tail to new head
    }else{ 
       //if list is empty creates a new list
        head = NULL;
        Node *clink=new Node;
        clink->data=n;
        head = clink;
        tail = clink;
        tail->next = head;
    }
}
//add value to end of list
template <class T>
void CirList<T>::append(T n){
    Node *prev;
    //copies node into prev pointer 
    if(head){
        worker = head;
        do{
            prev = worker;
            worker = worker->next;
        }while(worker != head);
        
        Node *clink = new Node; //create new node to store new vale n
        clink->data = n;
        tail->next = clink;   //adds new value after previous last value
        tail = clink;         //sets tail pointer back to end value 
        tail->next = head;    //sets value after tail to null
        
    }else{
       //if list is empty creates a new list
        head = NULL;
        Node *clink=new Node;
        clink->data=n;
        head = clink;
        tail = clink;
        tail->next = head; 
    }
}
//remove value fro list
template <class T>
void CirList<T>::extract(T n){
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
        //remove head
        head = nodePtr;       //set head equal to previously second list item
        tail->next = head;
    }else{
        
        nodePtr = head;  //pointer set to start of list
        
        //skip nodes whose values are not equal to n
        while(nodePtr->next != head && nodePtr->data != n){
            prev = nodePtr;
            nodePtr = nodePtr->next;
        }
       
        if(tail->data == n){
            //deletes tail if it is chosen
            nodePtr = prev;
            delete tail;
            nodePtr->next = head;
            tail = nodePtr;
        }else if(nodePtr->next == head){
            //message if chosen value not in list
            cout << "EXTRACTION FAILED: The Value "  << n 
                    << " does not exist in the list" << endl;
        }else{
            temp = nodePtr;         //set pointer to node to be deleted
            nodePtr = temp->next;   //move nodePtr to value after value to be deleted
            //connect values before and after deleted value
            prev->next = nodePtr;
            delete temp; //delete node with value chosen
        }
    }
}
//insert a value after a designated value
//preceadValue refers to value the newValue will come after
template <class T>
void CirList<T>::insertAfter(T newValue, T preceadValue){
    Node *newNode;  //new node
    Node *nodePtr; // allows list to be traversed
    Node *prev ;   //point to previous list before changing
    
    //create new node and store newValue
    newNode = new Node;
    newNode->data = newValue;
    
    if(!head){
        //if list is empty creates a new list
        head = NULL;
        Node *clink=new Node;
        clink->data=newValue;
        head = clink;
        tail = clink;
        tail->next = head;
    }else if(head->data == preceadValue){
        //add value after head
        nodePtr = head->next;
        head->next = newNode;
        newNode->next = nodePtr;
    }else if(tail->data == preceadValue){
        //if value is to  be added after tail it is appended
        append(newValue);
    }else{
        nodePtr = head; //point to start of list
        
        //skip nodes whose values are not equal to preceadValue
        while(nodePtr->next != head && nodePtr->data != preceadValue){
            prev = nodePtr;
            nodePtr = nodePtr->next;
        }
        
        if(nodePtr->next == head){
            //if value to insert after not found message displayed
            cout << "INSERTION FAILED: The Value "  << preceadValue 
                    << " does not exist in the list" << endl;
        }else{
            
            //move pointers to proper location 
            nodePtr = nodePtr->next;  //will come after newValue
            prev = prev->next;        //will come before newValue
            
            //add newValue to list
            prev->next = newNode;
            newNode->next = nodePtr;
        }
    }
}
//insert a value before a designated value
//afterValue refers to value the newValue will come before
template <class T>
void CirList<T>::insertBefore(T newValue, T afterValue){
    Node *newNode;  //new node
    Node *nodePtr; // allows list to be traversed
    Node *prev ;   //point to previous list before changing
    
    //create new node and store newValue
    newNode = new Node;
    newNode->data = newValue;
    
    if(!head){
        //if list is empty creates a new list
        head = NULL;
        Node *clink=new Node;
        clink->data=newValue;
        head = clink;
        tail = clink;
        tail->next = head;
    }else if(head->data == afterValue){
        prepend(newValue);
    }else{
        nodePtr = head; //point to start of list
        
        //skip nodes whose values are not equal to n
        while(nodePtr->next != head && nodePtr->data != afterValue){
            prev = nodePtr;
            nodePtr = nodePtr->next;
        }
        
        if(tail->data == afterValue){
            //add the value before tail had to add condition to check if adding before
            //tail because insertion error would trigger when trying to add before tail
            prev->next = newNode;
            newNode->next = nodePtr;
        }else if(nodePtr->next == head){
            //if value to insert before not found message displayed
            cout << "INSERTION FAILED: The Value "  << afterValue 
                    << " does not exist in the list" << endl;
        }else{
            //insert newValue before afterValue
            prev->next = newNode;
            newNode->next = nodePtr;
        }
    }
}
//return first value in list
template <class T>
T CirList<T>::first(){
    return head->data;
}
//return last value in list
template <class T>
T CirList<T>::last(){
    return tail->data;
}
//return size of list
template <class T>
int CirList<T>::size(){
    int count = 0; //used to keep track of size
    
    //cycles through each node and increments count to represent size
    if(head){
        worker = head;
        do{
            count++;
            worker = worker->next;
        }while(worker != head);
        return count;
    }else{
        return 0;
    }
}
//
template <class T>
T CirList<T>::getElementAT(int position){
    int listSize = size(); //size of the list
    Node *lstPtr = head;   //will alow list to be traversed
    int count = 1;         //functions as the position of the value of the list
    
    if(position < 0 || position > listSize){
        cout << "ERROR: position out of range. program exited" << endl;
        exit(EXIT_FAILURE);
    }
    
    if(position == listSize){
        //if position is size of list return last value
        return tail->data;
    }else{
        while(lstPtr != tail){
            if (count == position){
                return(lstPtr->data); //returns position value when position requested
                                      //is equal to the count as it cycles through each node
                                      // one by one
            }  
            count++;                //increment count to move to next value in list
            lstPtr = lstPtr->next; //move to next value in list   
        }
    }
}
//print list circularly
template <class T>
void CirList<T>::cirPrint(int n){
    Node *nodePtr = head;
    
    for(int i = 1; i < n ; i++){
        
        cout << nodePtr->data << " ";
        nodePtr = nodePtr->next; //advance to next item       
    }
    cout << endl;
}
#endif	/* CIRLIST_H */

