/* 
 * File:   Problem1.h
 * Author: Robert Arenas Id: 2255685
 * 
 * Created on December 16, 2015, 11:03 AM
 */

#ifndef PROBLEM1_H
#define PROBLEM1_H

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

class Hash{
    
public:
    //constructor
    Hash();
    //destructor
    ~Hash();
    //adds initial to hash table no full name because no time to come up 
    //with 1000 full names
    void addItem(string initial);
    //prints collision stats
    void printStats();
    //searches for an initial
    void search(string initial);
    
private:
    //size of the hash table 
    static const int tableSize = 20;
    
    struct Node{
        string inital; //initial of individual 
        string name; //full name of individual 
        Node* next; //pointer to next node
    };
    
    Node *hashTable[tableSize]; //pointer to hash table
    Node *worker; //utility pointer for traversing hash table
    
    //get index for string passed in
    int hashing(string key);
    //gets the number of items stored in a given index
    int itemsInIndex(int index);
    //get number for letter number correspond to number value for letter on a
    //telephone key pad
    int letterValue(char letter);
};

//constructors initializes the hash table with a generic node at each index
Hash::Hash(){
    for(int i = 0; i < tableSize; i++){
        
        hashTable[i] = new Node;
        hashTable[i]->inital = "empty";
        hashTable[i]->name = "empty";
        hashTable[i]->next = NULL;
    }
}
//destructor
Hash::~Hash(){
    Node *temp; //temporary pointer for traversing nodes to be deleted
    //loop through each bucket and delete its contents
    for(int i = 0; i < tableSize; i++){
        worker = hashTable[i];
        while(worker != NULL){
            temp = worker->next;
            delete worker;
            worker = temp;
        }
       hashTable[i] = NULL; //set bucket to null
    }
}
//creates the hash index an item will be stored at by hash index of initial
//name set also t initial due to time restraints
void Hash::addItem(string initial){
    //first aquire index from hash function based on area name
    int index = hashing(initial);
    
    //check if index already occupied by non generic node 
    //if generic node replace values with the new person
    //else create new node and add it after node already in hash table
    if(hashTable[index]->inital == "empty"){
        
       hashTable[index]->inital = initial;
       hashTable[index]->name = initial;
       
    }else{
        //pointer to loop to end of nodes in index
       worker = hashTable[index];
       //create new node
       Node *temp = new Node;
       temp->inital = initial ;
       temp->name = initial;;
       temp->next = NULL;
       
       //loop to end of index list
       while(worker->next != NULL){
           worker = worker->next;
       }
       //add new node at end
       worker->next = temp;
    }
}
//check how many collisions have occured at each index 
//also gets total number of collisions and max number of collisions
void Hash::printStats(){
    int number; //number of items in index
    int colls; //collisions
    int maxColls = 0; //max number of collisions initialized to zero
    int totalColls = 0; //total number of collisions accross each index
    
    //loop to aquire information
    for(int i = 0; i < tableSize; i++){
       number = itemsInIndex(i); //number of items in index
       
       //if more than one item collisions is equal to one less than the total number
       //of items at index because first insertion does not count as collision
       if(number > 0){
           colls = number - 1; 
       }else{
           colls = number; //returns zero for no items in index
       }
       
       totalColls = totalColls + colls; //running total all collisions
       
       //check for max number of colisions
       if(colls > maxColls){
           maxColls = colls;
       }
       
       //display data for each index
       cout << "-------------------" << endl;
       cout << "index = " << i << endl;
       cout << "#of items in bucket " << number << endl;
       cout << "#of collisions at Index(bucket): " << colls<< endl;
       cout << "-------------------" << endl;
    }
    //display max collision number and total number of collisions
    cout << "Maximum number of collisions was: " << maxColls << endl;
    cout << "Total number of collisions was: " << totalColls << endl;
}
void Hash::search(string initial){
    //returns index value to be searched should be stored at
    int index = hashing(initial);
    bool foundName = false; // false if not found true if found
    string fName; //fulname to be printed
    
    worker = hashTable[index]; //pointer to hash table
    
    //loop to search 
    while(worker != NULL){
        
        //if found set found to true and break loop
        if(worker->inital == initial){
           foundName = true;
           fName = worker->name;
           break;
        }
        //advance to next node
        worker = worker->next;
    }
    //display found full name or message if it does not exist
    if(foundName == true){
        cout << "Full name is: " << fName << endl;
    }else{
        cout << initial << "'s info was not found!" << endl;
    }
}
//generate index for initial
int Hash::hashing(string key){
    int hash = 0;
    int index;
    
    //hash is sum of number value letter corresponds to on telephone keypad
    for(int i = 0; i < key.length(); i++){
        hash = hash + letterValue(key[i]);
    }
    
    //get index and return
    index = hash % tableSize; 
    return index;
}
//returns value for letter based on a telephone keypad
int Hash::letterValue(char letter){
    if(letter == 'A' || letter == 'B' || letter == 'C'){
        return 2;
    }else if(letter == 'D' || letter == 'E' || letter == 'F'){
        return 3;
    }else if(letter == 'G' || letter == 'H' || letter == 'I'){
        return 4;
    }else if(letter == 'J' || letter == 'K' || letter == 'L'){
        return 5;
    }else if(letter == 'M' || letter == 'N' || letter == 'O'){
        return 6;
    }else if(letter == 'P' || letter == 'Q' || letter == 'R' || letter == 'S'){
        return 7;
    }else if(letter == 'T' || letter == 'U' || letter == 'V'){
        return 8;
    }else if(letter == 'W' || letter == 'X' || letter == 'Y' || letter == 'Z'){
        return 9;
    }
}

int Hash::itemsInIndex(int index){
    int count = 0; //initialize counter
    
    //if node at index contains generic information no items in count
    //else loop through nodes incrementing count for each node at index
    if(hashTable[index]->inital == "empty"){
        return count;
    }else{
        count++; //increment for fist node
        
        worker = hashTable[index]; //pointer to loop through nodes
        
        //loop through nodes and increment count
        while(worker->next != NULL){
            //increment for each following node
            count ++;
            //advance to next node
            worker = worker->next;
        }
    }
    //return final count
    return count;
}


#endif /* PROBLEM1_H */

