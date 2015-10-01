/* 
 * File:   SimpleVector.h
 * Author: Robert Arenas 
 * ID: 2255685
 * Created on September 24, 2015, 3:26 PM
 */

#ifndef SIMPLEVECTOR_H
#define	SIMPLEVECTOR_H

#include <string>

using namespace std;

class SimpleVector {
public:
    SimpleVector(int);       //default constructors
    virtual ~SimpleVector(); //destructor
    string toString();      //prints the linkedlist
    
    //functions from array implemetation made to work with linked lists
    void push(int);        //add element to back of vector list
    void pull();           //pull to remove first element in list 
    int getElementAT(int); // gets an element at specified position
    int size();            //returns the size of the linked list
    
    //assignment 5 functions
    SimpleVector(const SimpleVector &);  //copy constructor
    void prepend(int);                   //adds a value to front of list
    void append(int);                    //adds a value to end of list
    void extract(int);                   //removes a value from the list
    void insertAfter(int, int);          //insert value after a specified value
    void insertBefore(int, int);         //insert value before a specified value
    int first();                         //returns a reference first could not get to work properly
    int last();                         //returns a reference to last element could not get to work properly
    
private:
    struct Node{
         int data;
         Node *next;
    };
    Node *head;
    Node *worker;
};

#endif	/* SIMPLEVECTOR_H */

