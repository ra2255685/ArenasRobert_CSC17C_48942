/* 
 * File:   main.cpp
 * Author: Robert Arenas Id:255685
 *
 * Created on September 29, 2015, 6:54 PM
 */

#include <iostream>

#include "SimpleVector.h"

using namespace std;

int main(int argc, char** argv) {

    int values = 10;  //number of values to be added to list
    int position;    //user entered value to get value from position on list
    
    SimpleVector<int> list(0);
    
    cout << "appending values on to the list" << endl;
    for(int i = 1;i <= values; i++){
        list.append(i);
    } 
    cout << list.toString();
    cout << "The size of the list is: " << list.size() << endl;
    
    cout<<endl;
    
    cout << "Prepending values" << endl;
    list.prepend(27);
    list.prepend(56);
    cout << list.toString();
    cout << "The size of the list is: " << list.size() << endl;
    
    cout<<endl;
    
    cout << "Enter a number to find value in that position" << endl;
    cin >> position;
    cout << "the value at position " << position <<" is " << list.getElementAT(position) << endl;
    
    cout<<endl;
    
    SimpleVector<int> list2(list); //copy constructor to copy original list before 
                              //demonstrating extract function
    
    cout << "extracting values 2, 5, 8" << endl;
    list.extract(2);
    list.extract(5);
    list.extract(8);
    cout << "list after extraction" << endl;
    cout << list.toString();
    cout << "The size of the list is: " << list.size() << endl;
    
    cout<<endl;
    
    cout << "copy of list before extraction" << endl;
    cout << list2.toString();
    cout << "The size of the list is: " << list2.size() << endl;
    
    cout <<endl;
    
    cout << "inserting values after 1, 4, 10"<<endl;
    list.insertAfter(26,1);
    list.insertAfter(29,4);
    list.insertAfter(30,10);
    cout << list.toString();
    cout << "The size of the list is: " << list.size() << endl;
    
    cout<<endl;
    
    cout << "Inserting values before 4, 7, 10" << endl;
    list.insertBefore(15,4);
    list.insertBefore(16,7);
    list.insertBefore(17,10);
    cout << list.toString();
    cout << "The size of the list is: " << list.size() << endl;
    
    cout<<endl;
    
    cout << "first last function" << endl;
    cout << "The first value in the list is: " << list.first() << endl;
    cout << "The last value in the list is: " << list.last() << endl;
    return 0;
}

