/* 
 * File:   main.cpp
 * Author: Robert Arenas
 *
 * Created on September 17, 2015, 10:59 AM
 */

#include <cstdlib>
#include <iostream>

#include "SimpleVector.h"

using namespace std;

int main(int argc, char** argv) {
    
    int size = 5;   // initial size of array
    
    //declare a vector of ints
    SimpleVector<int> intArray(size);
    
    //adds values to the vector
    for(int i = 0; i < size; i++){
        intArray[i] = (i + 1);
    }

    cout << "Original SimpleVector" << endl;
    intArray.print();
    
   //pushing values
    cout << "ADDING VALUES TO END" << endl;
    intArray.push(56);
    intArray.print();
    
    intArray.push(27);
    intArray.print();
    
    intArray.push(5);
    intArray.print();
    
    //pulling values
    cout <<"PULLING VALUES FROM TOP" << endl;
    intArray.pull();
    intArray.print();
    
    intArray.pull();
    intArray.print();
    
    intArray.pull();
    intArray.print();
    
    return 0;
}

