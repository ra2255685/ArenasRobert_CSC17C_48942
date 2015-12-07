/* 
 * File:   main.cpp
 * Author: Robert Arenas ID: 2255685
 *
 * Created on December 1, 2015, 12:07 PM
 */

#include <cstdlib>
#include <iostream>
#include <ctime>

#include "Tree.h"

using namespace std;

int main(int argc, char** argv) {

    srand(static_cast<unsigned int>(time(0))); //seed for rand
    
    Tree<int> t;
    
    int nums; //number of values in tree
    int val;  //value to be deleted
    char y;   //used to ask if user wants to delete another value
    
    do{
        cout << "How many random numbers in tree?" << endl;
        cin >> nums;
    }while(nums < 0);
    
    for(int i = 0; i < nums; i++){
        t.insert(rand()% 100);
    }
    
    cout <<"The numbers in the tree are" << endl;
    cout << "In order print" << endl;
    t.printInOrder();
    cout << "Pre-order print" << endl;
    t.printPreOrder();
    cout << "Post-order print" << endl;
    t.printPostOrder();
    //check if tree is balanced
        if(t.isBalanced()){
        cout << "Tree is balanced" << endl;
        }else{
            cout << "Tree not balanced" << endl;
        }
    cout << endl;
    
    do{
        
        cout << "Select value to be deleted" << endl;
        cin >> val;
    
        t.deleteVal(val);
        
        cout << "Tree traversals after deleting " << val << endl;
         cout << "In order print" << endl;
        t.printInOrder();
        cout << "Pre-order print" << endl;
        t.printPreOrder();
        cout << "Post-order print" << endl;
        t.printPostOrder();
        
        //check if tree still balanced
        if(t.isBalanced()){
        cout << "Tree is balanced" << endl;
        }else{
            cout << "Tree not balanced" << endl;
        }
    
        cout << "would you like to delete another number (Y/N)?" << endl;
        cin >> y;
        cout << endl;
    }while(y == 'y' || y == 'Y');
    
   
    return 0;
}

