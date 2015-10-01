/* 
 * File:   main.cpp
 * Author: Robert Arenas 
 * ID: 2255685
 * Created on September 24, 2015, 3:25 PM
 */

#include <cstdlib>
#include <iostream>

#include "SimpleVector.h"

using namespace std;

int main(int argc, char** argv) {

    int values = 10;  //number of values to be added to list
    int position;    //user entered value to get value from position on list
    
    //create the linked list
    SimpleVector list(0);    //initializes list with a first value of 0
    
    cout << "pushing values on to the list" << endl;
    for(int i = 1;i <= values; i++){
        list.push(i);
    }
    //print the list
    cout << list.toString();
    cout<<"Size = " << list.size() << endl;
    
    cout<<endl;
    cout<<"pulling value(s) from the list" << endl;
    list.pull();
    cout << list.toString();
    cout<<"Size = " << list.size() << endl;
    
    cout<<endl;
    cout << "Enter a number to find value in that position" << endl;
    cin >> position;
    
    cout << "the value at position " << position <<" is " << list.getElementAT(position) << endl;
    
    cout<<endl;
    cout << "Prepending value" << endl;
    list.prepend(60);
    cout << list.toString();
    
    cout<<endl;
    cout << "appending value" << endl;
    list.append(33);
    cout << list.toString();
   
    cout<<endl;
    cout << "insert after" << endl;
    list.insertAfter(27,60);
    cout << list.toString();
    
    cout<<endl;
    cout << "insert before" << endl;
    list.insertBefore(56,60);
    cout << list.toString();
    
    cout<<endl;
    cout << "extract" << endl;
    list.extract(33);
    cout << list.toString();
    
   cout<<endl;
   cout << list.last() << endl;
   
   SimpleVector list2(list);
   list2.extract(10);
   cout << list2.toString() << endl;
   
   cout << "list1"<<endl;
   cout << list.toString();
    return 0;
}

