/* 
 * File:   Enemy.h
 * Author: Robert Arenas Id:  2255685
 *
 * Created on December 12, 2015, 5:07 PM
 */

#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

template<class T>
class Enemy{
    public:
        //default constructor adds first enemy to list
        Enemy(string, T, int, int);
        //destructor
        virtual ~Enemy();
        //adds enemies to list
        void createEnemies(string, T, int, int);
        //displays all enemies in list
        void showEnemies(Enemy&);
        //generate attack stat range 2300 to 3500
        T genAttk();
        //generate attack stat range 3600 to 4700
        T genAttkHigh();
        //generate gold carried
        int genGold();
        //finds enemy that will be battled
        void selectEnemy(int);
        //access attack stat
        T getAttk();
        //access gold stat
        int getEgold();
        //access number of enemies in list (size of list)
        int getEnemyCount();
        //access id stat
        int getID();
        //access name stat
        string getName();
        //retrieve ids of a number enemies starting from start of list
        vector<int> topIds(Enemy&, int);
        /*used to call merge sort in main due to merge sort being node type 
        and since node is private must be in private section*/
        void sort();
        
    private:
        
      struct Node{
         string name;
         T attack;
         int gold;
         int id;
         Node *next;
    };
    Node *head;    //head of list
    Node *worker; //utility pointer used primarily for list traversal
    
    /*used to battle individual enemies et each time time selectEnemy(int) 
    function is called before combat*/
    //combat access stats
    T eattack;
    int egold;
    int enemyCount;
    int eId;
    string enemyName;
    
    //locates center of linked list
    typename Enemy<T>::Node *FindMid(Node*);
    //merges the sorted halfs of linked list
    typename Enemy<T>::Node *mergeSortedList(Node*,Node*);
    //sorts linked list
    typename Enemy<T>::Node *mergeSort(Node*);
    //reverses the order of the linked list 
    void reverseList();        
};
//default constructor
template <class T>
Enemy<T>::Enemy(string n, T attk, int g, int i){
    
    //initialize combat access stats
    eattack = 0;
    egold = 0;
    enemyCount = 0; //initialize size of list
    enemyName = "Enemy";
    
    //create first enemy in list
    Node *clink=new Node;
    clink->name = n;
    clink->attack = attk;
    clink->gold = g;
    clink->id = i;
    clink->next=NULL;
    head=clink;
    
    enemyCount ++; //increase size of list
}
//destructor
template <class T>
Enemy<T>::~Enemy(){
   if(head){
        do{
            worker=head;
            head=head->next;
            delete worker;
            enemyCount --;
        }while(head);
    } 
}
//adds enemies to list
template <class T>
void Enemy<T>::createEnemies(string n, T attk, int g, int i){
    Node *prev;
    //if list empty create new one
    if(!head){
        head = NULL;
        Node *clink=new Node;
        clink->name = n;
        clink->attack = attk;
        clink->gold = g;
        clink->id = i;
        clink->next=NULL;
        head=clink;
        
        enemyCount ++; //increase size of list
    }else{
        worker = head;
        do{
            prev = worker;
        }while(worker = worker->next);
        //adds new enemies on to the end of the list
        Node *clink = new Node; //create new node to store new vale n
        clink->name = n;
        clink->attack = attk;
        clink->gold = g;
        clink->id= i;
        clink->next = NULL;
        prev->next = clink; //adds new value to end of the previous list
        
        enemyCount ++; //increase size of list
    }
}
//displays enemies in list
template <class T>
void Enemy<T>::showEnemies(Enemy &obj){
     
    worker = obj.head; //set pointer to object head
    
    if(!worker){
        //message if list empty
        cout << "Empty List" << endl;
    }else{
        //while list is not null print list
        while(worker){
           cout << worker->name << " " << worker->id << " has " << worker->attack 
                   << " attack and is carrying " << worker->gold << " gold" <<endl;
           worker = worker->next; //move pointer to next node
        }
    }
    cout << endl;
}
//generates attack in range of 2300 to 3500
template <class T>
T Enemy<T>::genAttk(){
   int attk = 0;
   //attack strength ranges from 2300 to 3500
   attk = rand()%(3500-2300)+2300;
   return attk;
}
//generates attack in range of 3600 to 4700
template <class T>
T Enemy<T>::genAttkHigh(){
   int attk = 0;
   //attack strength ranges from 3600 to 4700
   attk = rand()%(4700-3600)+3600;
   return attk; 
}
//generates gold in range of 1 to 5
template <class T>
int Enemy<T>::genGold(){
    int g = 0;
   //gold amount ranges from 1 to 5
   g = rand()%4 + 1;
   return g;
}
//select enemy to allow access to its stats
template <class T>
void Enemy<T>::selectEnemy(int n){
    //if id it is at head and set combat stats
    if(head->id == n){
            eattack = head->attack;
            egold = head->gold;
            enemyName = head->name;
            eId = head->id;
    }else{
        
        worker = head; //pointer to traverse list
        
        //skip nodes whose values are not equal to n
        while(worker != NULL && worker->id != n){
            worker = worker->next;
        }
        
        if(worker){
            //set combat access stats for battle calculations
            eattack = worker->attack;
            egold = worker->gold;
            enemyName = worker->name;
            eId = worker->id;
        }else{
            //if enemy does not exist
            cout << "Enemy does not exist" << endl;
            eattack = 0;
            egold = 0;
            enemyName = "Enemy";
            eId = 999;
        }
    } 
}
//access gold stat
template <class T>
int Enemy<T>::getEgold(){
    return egold;
}
//access attack stat
template <class T>
T Enemy<T>::getAttk(){
    return eattack;
}
//access enemy count stat
template <class T>
int Enemy<T>::getEnemyCount(){
    return enemyCount;
}
//access enemy id stat
template <class T>
int Enemy<T>::getID(){
    return eId;
}
//access name stat
template <class T>
string Enemy<T>::getName(){
    return enemyName;
}
//call merge sort and reverse list
template <class T>
void Enemy<T>::sort(){
   worker = head; //pointer to head
   head = NULL; //set head to null in order to place it as head of sorted list
   head = mergeSort(worker); // returns list in ascending order
   
   reverseList(); //reverse list to be placed in descending order
   
}
//returns the ids from the top n values in list in a vector
template <class T>
vector<int> Enemy<T>::topIds(Enemy &e, int n){
    
    worker = e.head; //set pointer to object head
    
    vector<int> idVec; //vector to be returned with ids
    
    for(int i = 0; i < n; i++){
        //add values to vector
        idVec.push_back((worker->id));
        //move to next node
        worker = worker->next;
    }
    return idVec; //return vector
}
//find the center of the list
template <class T>
typename Enemy<T>::Node *Enemy<T>::FindMid(Node *ref){
    Node *p=ref;
    Node *q=ref;
    
    if(p&&p->next){
        p=p->next->next;
        q=q->next;
    }
    return q;
}
//merges the sorted half of the list
template <class T>
typename Enemy<T>::Node *Enemy<T>::mergeSortedList(Node *a, Node *b){
    //base cases
    if(a == NULL){
        return b;
    }
    if(b == NULL){
        return a;
    }
    
    Node *result=NULL; // used to return sorted list
    //merging procedure
    if(a->attack <= b->attack){
        result=a;
        result->next=mergeSortedList(a->next,b);
    }else{
        result=b;
        result->next=mergeSortedList(a,b->next);
    }
    return result; //return merged list
}
//primary function in merge sort process
template <class T>
typename Enemy<T>::Node *Enemy<T>::mergeSort(Node *headRef){
    
    //retun null if head is null
    if(!headRef){
        return NULL;
    }
    
    //base cases
    if(headRef->next==NULL){
        return headRef;
    }else if(headRef->next->next==NULL){
        Node *p=headRef;
        if(p->attack>p->next->attack){
            headRef=headRef->next;
            p->next=NULL;
            headRef->next=p;
            return headRef;
        }else {
            return headRef;
        }
    }else{
        //splits list, sorts both halfs, and merges the 2 halfs
        Node *mid=FindMid(headRef);
        Node *SHalf=mid->next;
        mid->next=NULL;
        Node *head1=mergeSort(headRef);
        Node *head2=mergeSort(SHalf);

        return mergeSortedList(head1,head2);
    }
}
//reverses the order of the list
template <class T>
void Enemy<T>::reverseList(){
    
    Node *prev = NULL;    //represents node before current
    Node *current = NULL; 
    Node *nxt = NULL;    //represents node after current
    
    //do nothing if list is empty
    if(!head){
        return;
    }
    
    current = head; //start at beginning of list
    //loop rearranges list
    while(current != NULL){
        nxt = current->next;
        current->next = prev;
        prev = current;
        current = nxt;
    }
    //reset head pointer
    head = prev;
}


#endif /* ENEMY_H */

