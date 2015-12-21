/* 
 * File:   Problem2.h
 * Author: Robert Arenas Id: 2255685
 *
 * Created on December 17, 2015, 10:57 AM
 */

#ifndef PROBLEM2_H
#define PROBLEM2_H

#include <iostream>
#include <stack>

using namespace std;

class Hyperbolic{
    
public:
    //constructor
    Hyperbolic();
    //sine function
    float h(float, stack<char>&); 
    //cosine function
    float g(float, stack<char>&); 
    //calculate the number of times each function called
    void calculateCalls(stack<char>&);
};

//constructor
Hyperbolic::Hyperbolic(){
    
}
//functions for hyperbolic sin/cos recursive function in problem 2
float Hyperbolic::h(float angR, stack<char> &calls){
    
    calls.push('s'); //add s to represent calls to sine
    
    float tol=1e-6;
    
    if(angR>-tol&&angR<tol){
        return angR+angR*angR*angR/6;
    }
    return 2*h(angR/2, calls)*g(angR/2, calls);
}
float Hyperbolic::g(float angR, stack<char> &calls){
    calls.push('c'); //add c to represent calls to cosine
    
    float tol=1e-6;
    
    if(angR>-tol&&angR<tol){
        return 1+angR*angR/2;
    }
    
    float b=h(angR/2, calls);
    return 1+2*b*b;
}
//calculate the number of times each function called
void Hyperbolic::calculateCalls(stack<char> &calls){
    int s = 0; //counter for sine calls
    int c = 0; //counter for cosine calls
    
    //loop through stack and count the letters count for each will
    // be equal to number of calls for each function
    while(!calls.empty()){
        //increment for sine
        if (calls.top() == 's'){
            s++;
        }
        //increment for cosine
        if(calls.top() == 'c'){
            c++;
        }
        //remove top value to move to next value in stack
        //continue until stack empty
        calls.pop();
    }
    
    ///display results
    cout << "# of calls to sine(h() function): " << s << endl;
    cout << "# of calls to cosine(g() function: " << c << endl;
}
#endif /* PROBLEM2_H */

