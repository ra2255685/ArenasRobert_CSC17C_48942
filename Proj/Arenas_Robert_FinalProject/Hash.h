/* 
 * File:   Hash.h
 * Author: Robert Arenas Id:  2255685
 *
 * Created on December 15, 2015, 2:28 PM
 */

#ifndef HASH_H
#define HASH_H

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
    //adds enemy to table with their location
    void addItem(string , string);
    //prints the hash table
    void printTable();
    
private:
    //size of the hash table 
    static const int tableSize = 10;
    
    //node to store enemy name and location
    struct Node{
        string enemyName;
        string area;
        Node *next; //pointer to next node
    };
    
    Node *hashTable[tableSize]; //pointer to hash table
    Node *worker; //utility pointer for traversing hash table
    
    //creates the hash index an item will be stored at by name of area
    int hashing(string);
    //gets the number of items stored in a given index
    int itemsInIndex(int);
    //prints index containing multiple items
    void printBucket(int);
};
//constructors initializes the hash table with a generic node at each index
Hash::Hash(){  
    for(int i = 0; i < tableSize; i++){  
        hashTable[i] = new Node;
        hashTable[i]->enemyName = "empty";
        hashTable[i]->area = "empty";
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
//creates the hash index an item will be stored at by name of area
int Hash::hashing(string key){
    int hash = 0;//initial hash value
    int index; //index enemy will be stored at
    
    //hash  created by adding up ascii values each letter in name of area
    for(int i = 0; i < key.length(); i++){
        hash = hash + (int)key[i];
    }
    
    //index enemy will be stored at aquired by modding hash with table size 
    //and returning the remainder as index
    index = hash % tableSize;
    
    return index;
}
//add an item(enemy) to hash table
void Hash::addItem(string name, string area){
    //first aquire index from hash function based on area name
    int index = hashing(area);
    
    //check if index already ocupied by non generic node 
    //if generic node replace values with the new enemy
    //else create new node and add it after node already in hash table
    if(hashTable[index]->enemyName == "empty"){
        
       hashTable[index]->enemyName = name;
       hashTable[index]->area = area;
       
    }else{
       //pointer to loop to end of nodes in index
       worker = hashTable[index];
       //create new node
       Node *temp = new Node;
       temp->enemyName = name;
       temp->area = area;
       temp->next = NULL;
       
       //loop to end of index list
       while(worker->next != NULL){
           worker = worker->next;
       }
       //add new node at end
       worker->next = temp;
    }
}
//check how many item nodes are located in a specific index
int Hash::itemsInIndex(int index){
    int count = 0; //initialize counter
    //if node at index contains generic information no items in count
    //else loop through nodes incrementing count for each node at index
    if(hashTable[index]->enemyName == "empty"){
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
//prints the hash table
void Hash::printTable(){
    
    int n; // used to retrieve number of items in index
    
    for(int i = 0; i < tableSize; i++){
       //retrieve number of items in index for appropriate print instructions 
       n = itemsInIndex(i); 
       
       //if one item print it 
       //else if multiples at index use printBucket function to print all nodes in it
       //else the index contains no items
       if(n == 1){
           cout << "-------------------" << endl;
           cout << "Hash Table index " << i << " contains" << endl;
           cout << hashTable[i]->enemyName << " found in " << 
                   hashTable[i]->area << endl;
           cout << "-------------------" << endl;
       }else if(n >= 2 ){
           cout << "-------------------" << endl;
           cout << "Hash Table index " << i << " contains" << endl;
           printBucket(i);
           cout << "-------------------" << endl;
       }else{
           cout << "-------------------" << endl;
           cout << "Hash Table index " << i << " empty" << endl;
           cout << "-------------------" << endl;
       }
    }
    
}
//prints multiple nodes located at same index location
void Hash::printBucket(int index){
    
    worker = hashTable[index]; //pointer to traverse index
    
    //if node points to generic data it has no enemy items
    //else loop through index and print information of nodes
    if(worker->enemyName == "empty"){
        cout << "index = " << index << " is empty" << endl;
    }else{
        
        //loop till end of index list
        while(worker != NULL){
            ///print information
            cout << worker->enemyName << " found in " 
                    << worker->area << endl;
            //advance to next node
            worker = worker->next;
        }
     }
}

#endif /* HASH_H */

