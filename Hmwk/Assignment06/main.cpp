/* 
 * File:   main.cpp
 * Author: Robert Arenas ID: 255685
 *
 * Created on September 29, 2015, 6:54 PM
 */

#include <iostream>
#include <ctime>

#include "SimpleVector.h" //doubly linked list
#include "StackList.h"    //stack list
#include "CirList.h"      //circularly linked list
#include "PrioList.h"     //priority linked list
#include "SortList.h"     //sorted link list
 
using namespace std;

int main(int argc, char** argv) {

    int values = 10;  //number of values to be added to list
    
    //Initialize random number generator
    srand(static_cast<unsigned int>(time(0)));
    
    StackList<int> list;          //initialize stack from linked list 
    SimpleVector<int> dubList(0); //initialize doubly linked list
    CirList<int> cirList(0);      //initialize circularly linked list
    PrioList<int> prioList(0);    //initialize priority linked list
    SortList<int> sorList(27);    //initialize sorted linked list
    
    cout << "///////////////////////////" << endl;
    cout << "    linked list Stack  " << endl;
    cout << "///////////////////////////" << endl;
    //add values to stack
    cout << "Adding values to stack" << endl;
    for(int i = 0; i <= values; i++){
        list.push(i);
        
    }

    cout << "The stack is" << endl;
    cout << list.toString();
    cout << "Size of list is " << list.size() << " elements" << endl;
    cout << "first value is: " << list.first() << endl; 
    cout << "last value is: " << list.last() << endl;
    cout << "Element at position 2 is " << list.getElementAT(2) <<endl;
 
    StackList<int> list2(list);
    
    cout << endl;
    list.pop();
    list.pop();
    
    cout << "The stack (after removing top 2 values) is" << endl;
    cout << list.toString();
    cout << "Size of list is " << list.size() << " elements" << endl;
    cout << "top value is: " << list.first() << endl; 
    cout << "last value is: " << list.last() << endl;
    cout << "Element at position 2 is " << list.getElementAT(2) <<endl;
    
    cout << "copy of original list using copy constructor" << endl;
    cout << list2.toString() << endl;
    
    cout << "///////////////////////////" << endl;
    cout << "    Doubly linked list   " << endl;
    cout << "///////////////////////////" << endl;
    //add items to list
    cout << "Adding values to stack" << endl;
    for(int i = 1; i <= values; i++){
        dubList.append(i);
    }
    
    cout << "The list original list is:" << endl;
    cout << dubList.toString();
    cout << "The size of list is: " << dubList.size() << endl;
    cout << "Element at position 5 is " << dubList.getElementAT(5) << endl; 
    cout << "First Value: " << dubList.first() << endl;
    cout << "Last Value: " << dubList.last() << endl << endl;
    
    SimpleVector<int> dubList2(dubList); //copy original list with copy constructor
    
    cout << "Adding a value after 4 and before 5" << endl;
    cout << "prepending and appending values" << endl;
    cout << "removing the values 3 and 8" << endl;
    dubList.insertAfter(27, 4);
    dubList.insertBefore(56, 5);
    dubList.prepend(29);
    dubList.append(15);
    dubList.extract(8);
    dubList.extract(3);
    cout << endl;
    
    cout << "Edited list is: " << endl;
    cout << dubList.toString();
    cout << "The size of list is: " << dubList.size() << endl;
    cout << "Element at position 5 is " << dubList.getElementAT(5) << endl; 
    cout << "First Value: " << dubList.first() << endl;
    cout << "Last Value: " << dubList.last() << endl << endl;
    
    
    //print list backwards
    cout <<"Printing list in reverse" << endl;
    cout << dubList.toStringBack() << endl;;
    
    cout << "Copy of original list with copy constructor" << endl;
    cout << dubList2.toString() << endl;
    
    cout << "///////////////////////////" << endl;
    cout << "   circular linked list   " << endl;
    cout << "///////////////////////////" << endl;
    //add items to list
    for(int i = 1; i <= values; i++){
        cirList.append(i);
    }
    
    cout << "The original list is:" << endl;
    cout << cirList.toString();
    cout << "The size of list is: " << cirList.size() << endl;
    cout << "Element at position 5 is " << cirList.getElementAT(5) << endl; 
    cout << "First Value: " << cirList.first() << endl;
    cout << "Last Value: " << cirList.last() << endl << endl;
    
    CirList<int> cirList2(cirList); //copy constructor copies orig list
    
    cout << "Adding a value after 6 and before 2" << endl;
    cout << "prepending and appending values" << endl;
    cout << "removing the values 5 and 10" << endl;
    cirList.insertAfter(15, 6);
    cirList.insertBefore(33, 2);
    cirList.prepend(27);
    cirList.append(15);
    cirList.extract(5);
    cirList.extract(10);
    cout << endl;
    
    cout << "The edited list is:" << endl;
    cout << cirList.toString();
    cout << "The size of list is: " << cirList.size() << endl;
    cout << "Element at position 5 is " << cirList.getElementAT(5) << endl; 
    cout << "First Value: " << cirList.first() << endl;
    cout << "Last Value: " << cirList.last() << endl << endl;
    
    cout << "printing list circularly" << endl;
    cirList.cirPrint(45);
    cout << endl;
    
    cout << "copy of original list with copy constructor" << endl;
    cout << cirList2.toString();
    cout << "The size of list is: " << cirList2.size() << endl;
    cout << "Element at position 5 is " << cirList2.getElementAT(5) << endl; 
    cout << "First Value: " << cirList2.first() << endl;
    cout << "Last Value: " << cirList2.last() << endl << endl;
    
    cout << "///////////////////////////" << endl;
    cout << "   priority linked list   " << endl;
    cout << "///////////////////////////" << endl;
    //add items to list
    for(int i = 1; i <= values; i++){
        prioList.push(i);
    }
    
    cout << "The original list is:" << endl;
    cout << prioList.toString();
    cout << "The size of list is: " << prioList.size() << endl;
    cout << "Element at position 5 is " << prioList.getElementAT(5) << endl; 
    cout << "Top Value: " << prioList.top() << endl << endl;
    
    PrioList<int> prioList2(prioList); // copy constructor
    
    cout << "adding values 33, 99, 5, 11" << endl;
    prioList.push(33);
    prioList.push(99);
    prioList.push(5);
    prioList.push(11);
    cout << endl;
    
    cout << "The edited list is:" << endl;
    cout << prioList.toString();
    cout << "The size of list is: " << prioList.size() << endl;
    cout << "Element at position 5 is " << prioList.getElementAT(5) << endl; 
    cout << "Top Value: " << prioList.top() << endl << endl;
    
    int listSize = prioList.size(); //user to pop tops of list
    
    cout << "Removing tops and showing new tops" << endl;
    for(int i = 1; i <= listSize; i++){
        cout << "Top of list is " << prioList.top() << endl;
        prioList.pop();
    }
    prioList.pop();
    cout << endl;
    
    cout << "copy of original list with copy constructor" << endl;
    cout << prioList2.toString();
    cout << "The size of list is: " << prioList2.size() << endl;
    cout << "Element at position 5 is " << prioList2.getElementAT(5) << endl; 
    cout << "Top Value: " << prioList2.top() << endl << endl;
    
    
    cout << "///////////////////////////" << endl;
    cout << "   Sorted linked list   " << endl;
    cout << "///////////////////////////" << endl;
    cout << "Adding random numbers between 1-100" << endl;
    for(int i = 1; i <= values; i++){
        //add random values to list between 1-100
        sorList.insert(rand()%(100-1)+1);
    }
    
    cout << "The original list is" << endl;
    cout << sorList.toString();
    cout << "The size of list is: " << sorList.size() << endl;
    cout << "Element at position 3 is " << sorList.getElementAT(3) << endl; 
    cout << "First Value: " << sorList.first() << endl;
    cout << "Last value: " << sorList.last() << endl << endl;
    
    SortList<int> sorList2(sorList); //copy of original list with copy constructor
    
    cout << "inserting values 88, 25, 29" << endl;
    cout << "Attempting to extract values 75, 33 if they exist in list" << endl;
    sorList.insert(88);
    sorList.insert(25);
    sorList.insert(29);
    sorList.extract(75);
    sorList.extract(33);
    cout << endl;
    
    cout << "The edited list is" << endl;
    cout << sorList.toString();
    cout << "The size of list is: " << sorList.size() << endl;
    cout << "Element at position 3 is " << sorList.getElementAT(3) << endl; 
    cout << "First Value: " << sorList.first() << endl;
    cout << "Last value: " << sorList.last() << endl << endl;
    
    cout << "Extracting previously added values 88, 25, 29 to show extract() works" << endl;
    sorList.extract(88);
    sorList.extract(25);
    sorList.extract(29);
    cout << "List after extraction" << endl;
    cout << sorList.toString();
    cout << "The size of list is: " << sorList.size() << endl;
    cout << "Element at position 3 is " << sorList.getElementAT(3) << endl; 
    cout << "First Value: " << sorList.first() << endl;
    cout << "Last value: " << sorList.last() << endl << endl;
    
    cout << "copy of original list with copy constructor" << endl;
    cout << sorList2.toString();
    cout << "The size of list is: " << sorList2.size() << endl;
    cout << "Element at position 3 is " << sorList2.getElementAT(3) << endl; 
    cout << "First Value: " << sorList2.first() << endl;
    cout << "Last value: " << sorList2.last() << endl;
   
}

