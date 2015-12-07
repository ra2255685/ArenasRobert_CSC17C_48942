/* 
 * File:   Tree.h
 * Author: Robert Arenas ID: 2255685
 *
 * Created on December 1, 2015, 12:08 PM
 */

#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <stdlib.h>

using namespace std;

template <class T>
class Tree{
    public:
    //default constructor
    Tree();
    //destructor
    ~Tree();
    //access private insert function
    void insert(T n);
    //delete value from tree
    void deleteVal(T n);
    //access private printInOrder
    void printInOrder();
    //access private printPreorder
    void printPreOrder();
    //access private printPostOrder
    void printPostOrder();
    //access private isBalanced
    bool isBalanced();
    
    private:
        
    struct Node{
        T data;
        Node *left;
        Node *right;
        int height;
    };
    Node *root; //points to root value
    Node *worker; //utility pointer
    
    //inserts a value into tree
    typename Tree<T>::Node *insert(Node *, T);
    //deletes a value from tree
    typename Tree<T>::Node *deleteVal(Node *, T);
    //balances tree
    typename Tree<T>::Node *balance(Node *);
    //left rotate
    typename Tree<T>::Node *rotateL(Node *);
    //right rotate
    typename Tree<T>::Node *rotateR(Node *);
    //left left rotate
    typename Tree<T>::Node *rotateLL(Node *);
    //right right rotate
    typename Tree<T>::Node *rotateRR(Node *);
   
    
    ///////utility functions///////
    //finds node with max value used to find replacement or a deleted node
    typename Tree<T>::Node *maxVal(Node *);
    //finds max value between 2 values used for node height
    int max(int, int);
    //returns the height of node
    int height(Node *);
    //prints tree in order traversal
    void printInOrder(Node *);
    //prints tree in pre-order traversal
    void printPreOrder(Node *);
    //prints tree in post-order traversal
    void printPostOrder(Node *);
    //deletes tree
    void deleteTree(Node *);
    //sets height of node
    void setHeight(Node *);
    //gets balance factor of node
    int getBalance(Node*);
    //checks if tree is balanced
    //function borrowed from http://www.geeksforgeeks.org/how-to-determine-if-a-binary-tree-is-balanced/
    //in order to check if rotations were working right
    bool isBalanced(Node *);
    
};

//default constructor
template <class T>
Tree<T>::Tree(){
    root = NULL;
    worker = NULL;
}
//destructor
template <class T>
Tree<T>::~Tree(){
    deleteTree(root);
}
//access private insert function
template <class T>
void Tree<T>::insert(T n){
    root = insert(root, n);
}
//adds value to tree
template <class T>
typename Tree<T>::Node *Tree<T>::insert(Node *nodePtr, T n){
    
    //base case creates new node when node pointing to null appears
    //if n is less than root its is added to left side
    //if n is greater than or equal to root value it is added to right side 
    if(nodePtr == NULL){
        nodePtr = new Node;
        nodePtr->data = n;
        nodePtr->left = NULL;
        nodePtr->right = NULL; 
        nodePtr->height = 1;
        
    }else if(n < nodePtr->data){
        //recursive call to insert keeps going until null detected and node added
        nodePtr->left = insert(nodePtr->left, n);
        
        //balance function called to balance tree if it has become unbalanced
        nodePtr = balance(nodePtr);
    
    }else if(n >= nodePtr->data){
        //recursive call to insert keeps going until null detected and node added
        nodePtr->right = insert(nodePtr->right, n);
        
        //balance function called to balance tree if it has become unbalanced
        nodePtr = balance(nodePtr);
    }
    //sets height of node
    setHeight(nodePtr);
    
    //return nodePtr at this point should be pointing at node that is the root
    return nodePtr;
}
//access private deleteVal
template <class T>
void Tree<T>::deleteVal(T n){
    root = deleteVal(root, n);
    
}
//removes value from tree
template <class T>
typename Tree<T>::Node *Tree<T>::deleteVal(Node* nodePtr, T n){
    
    //return node if it is null
    if(nodePtr == NULL){
       return nodePtr; 
    }
    
    //if value to be deleted is less than a nodes value it is on the left
    //else if value to be deleted is greater than a nodes value it is on the right
    if(n < nodePtr->data){
        nodePtr->left = deleteVal(nodePtr->left, n);
    }else if(n > nodePtr->data){
        nodePtr->right = deleteVal(nodePtr->right, n);
    }else{
        //value deleted here
        
        //case if only one or no child node
        if(nodePtr->left == NULL || nodePtr->right == NULL){
            
            //assign temp pointer to child of node with data to be deleted
            if(nodePtr->left){
                worker = nodePtr->left;
            }else{
                worker = nodePtr->right;
            }
            
            //case if no child
            if(worker == NULL){
                worker = nodePtr;
                nodePtr = NULL;
            }else{
                //if one child copy non empty child
                *nodePtr = *worker;
            }
            
            delete(worker); //delete node
        }else{
            //case id two child nodes
            
            //get the replacement for node to be deleted which in this case would
            //be the largest value on left side
            worker = maxVal(nodePtr->left);
            
            //copy replacements data into node with value chosen for removal
            nodePtr->data = worker->data;
            
            //delete replacements original node
            nodePtr->left = deleteVal(nodePtr->left, worker->data);
            
        }
    }
    
    //return in case of only one node 
    if(nodePtr == NULL){
        return nodePtr;
    }
    
    //adjust height
    setHeight(nodePtr);
    //re-balance the tree then return it
    nodePtr = balance(nodePtr);
    return nodePtr;
}
//balances tree
template <class T>
typename Tree<T>::Node *Tree<T>::balance(Node *nodePtr){
    //get balance factor
    int bal = getBalance(nodePtr);
    
    //if factor greater than 1 tree is right-heavy 
    //else if factor less than -1 tree is left-heavy 
    if(bal > 1){
        //if factor of left node greater than 0 only one rotation needed
        //else double left rotation needed
        if(getBalance(nodePtr->left) > 0){
            nodePtr = rotateL(nodePtr);
        }else{
            nodePtr = rotateLL(nodePtr);
        }
    }else if(bal < -1){
        //if factor of left node greater than 0 only one rotation needed
        //else double right rotation needed
        if(getBalance(nodePtr->right) > 0){
            nodePtr = rotateRR(nodePtr);
        }else{
            nodePtr = rotateR(nodePtr);
        }
    
    }
    //adjust height and return the node
    setHeight(nodePtr);
    return nodePtr;
}
//left rotate
template <class T>
typename Tree<T>::Node *Tree<T>::rotateL(Node *nodePtr){
    
    //rotate
    worker = nodePtr->left;
    nodePtr->left = worker->right;
    worker->right = nodePtr;
    
    //adjust heights
    setHeight(worker);
    setHeight(nodePtr);
    
    return worker; //return rotated node
}
//right  rotate
template <class T>
typename Tree<T>::Node *Tree<T>::rotateR(Node *nodePtr){
    
    //rotate
    worker = nodePtr->right;
    nodePtr->right = worker->left;
    worker->left = nodePtr;
    
    //adjust heights
    setHeight(worker);
    setHeight(nodePtr);
    
    return worker; //return rotated node
}
//left left rotate
template <class T>
typename Tree<T>::Node *Tree<T>::rotateLL(Node *nodePtr){
    //rotate left side right
    nodePtr->left = rotateR(nodePtr->left);
    //rotate node left and return
    return rotateL(nodePtr);
}
//right rotate
template <class T>
typename Tree<T>::Node *Tree<T>::rotateRR(Node *nodePtr){
    //rotate right side left
    nodePtr->right = rotateL(nodePtr->right);
    //rotate node right and return
    return rotateR(nodePtr);
}
//finds max value on right side of node used to find replacement node when 
//deleting a node
template <class T>
typename Tree<T>::Node *Tree<T>::maxVal(Node *nodePtr){
    worker = nodePtr;
    
    //loop to find the leaf furthest right in tree which would contain largest 
    //value
    while(worker->right != NULL){
        worker = worker->right;    
    }
    //return largest value
    return worker;
}
//deletes tree
template <class T>
void Tree<T>::deleteTree(Node *nodePtr){
    if(nodePtr != NULL){
        deleteTree(nodePtr->left);
        deleteTree(nodePtr->right);
        delete nodePtr;
    }
}

//return max between to int's
template <class T>
int Tree<T>::max(int a, int b){
    if(a > b){
        return a;
    }else{
        return b;
    }   
}
//returns height of a node
template <class T>
int Tree<T>::height(Node *nodePtr){
    //if node is not NULL returns height else returns -1
    if(nodePtr != NULL){
        return nodePtr->height;
    }else{
        return -1;
    }
}
//access private printInOrder
template <class T>
void Tree<T>::printInOrder(){
    printInOrder(root);
    cout << endl;
}
//print tree in order traversal
template <class T>
void Tree<T>::printInOrder(Node *nodePtr){
    //base case
    if(nodePtr == NULL){
        return;
    }
    
    printInOrder(nodePtr->left);
    cout << nodePtr->data << " ";
    printInOrder(nodePtr->right);
}
//access private printPreOrder
template <class T>
void Tree<T>::printPreOrder(){
    printPreOrder(root);
    cout << endl;
}
//print tree in pre-order traversal
template <class T>
void Tree<T>::printPreOrder(Node *nodePtr){
    //base case
    if(nodePtr == NULL){
        return;
    }
    
    cout << nodePtr->data << " - " << nodePtr->height << " ";
    printPreOrder(nodePtr->left);
    printPreOrder(nodePtr->right);
}
//access private printPostOrder
template <class T>
void Tree<T>::printPostOrder(){
    printPostOrder(root);
    cout << endl;
}
//print in post order traversal
template <class T>
void Tree<T>::printPostOrder(Node *nodePtr){
    //base case
    if(nodePtr == NULL){
        return;
    }
    
    printPostOrder(nodePtr->left);
    printPostOrder(nodePtr->right);
    cout << nodePtr->data << " ";
}
//access private is balanced
template <class T>
bool Tree<T>::isBalanced(){
    return isBalanced(root);
}
//checks if tree is balanced
//function borrowed from http://www.geeksforgeeks.org/how-to-determine-if-a-binary-tree-is-balanced/
//in order to check if rotations were working right
template <class T>
bool Tree<T>::isBalanced(Node *n){
    int lh, rh;
    
    if(n == NULL){
        return 1;
    }
    
    lh = height(n->left);
    rh = height(n->right);
    
    if(abs(lh-rh) <= 1 && isBalanced(n->left) && isBalanced(n->right)){
        return 1;
    }
    //if this return reached tree is not balanced
    return 0;
}
//sets the height of a node
template <class T>
void Tree<T>::setHeight(Node *n){
    if(n != NULL){
        n->height = max(height(n->left), height(n->right)) + 1;
    }else{
        n->height = 0;
    }
    
}
//retrieves balance factor of a node
template <class T>
int Tree<T>::getBalance(Node *n){
    
    return height(n->left) - height(n->right);
}
#endif /* TREE_H */

