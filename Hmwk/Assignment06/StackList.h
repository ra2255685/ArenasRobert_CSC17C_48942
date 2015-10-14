/* 
 * File:   StackList.h
 * Author: Robert Arenas ID: 2255685
 *
 * Created on October 8, 2015, 5:14 PM
 */

#ifndef STACKLIST_H
#define	STACKLIST_H
template<class T>
class StackList{
    public:
    StackList();                     //default constructors
    StackList(const StackList &);    //copy constructor
    virtual ~StackList();            //destructor
    
    void push(T);                    //add items in stack form always from top
    void pop();                      //remove first element in list 
    string toString();               //prints the linkedlist
    T getElementAT(int);             // gets an element at specified position
    int size();                      //returns the size of the linked list
    T first();                       //returns a reference first could not get to work properly
    T last();                        //returns a reference last could not get to work properly
    
    
    private:
      struct Node{
         T data;
         Node *next;
    };
    Node *head;
    Node *worker;  
    
    void append(T); // used only for copy constructor in stack list
};

//default constructor for stack 
template <class T>
StackList<T>::StackList(){
    head = NULL;
}
//copy constructor
template <class T>
StackList<T>::StackList(const StackList &obj){
    head = NULL;  // set the head to null in order to create new list
    //does nothing if node empty
    if(obj.head == NULL){
        return;
    }else{
        Node *temp = obj.head; //create temporary node to point to original list values
        while(temp != NULL){
            append(temp->data); //copy value into new list
            temp = temp->next;  //advance to next node in new list
        }
    }
}
//deconstructor borrowed from link list example
template <class T>
StackList<T>::~StackList(){
    if(head){
        do{
            worker=head;
            head=head->next;
            delete worker;
        }while(head);
    }
}
// add elements to stack always to top
template <class T>
void StackList<T>::push(T newVal){
    Node *temp;
    
    //store newVal in temp node
    temp = new Node;
    temp->data = newVal;
    
    //if no items in list item becomes the first node
    //otherwise items inserted before head value
    if(!head){
        head = temp;
        temp->next = NULL;
    }else{
        temp->next = head;
        head = temp;
    }
};
//pull function to remove first value in list
template <class T>
void StackList<T>::pop(){
        if(head){
        Node *prev; //pointer to list
        prev = head->next;
        delete head;
        head = prev;
    }else{
        cout << "List is empty" << endl;
    }
}
//borrowed from linked list class example prints list
template <class T>
string StackList<T>::toString(){
    string build="";
    if(head){
        worker=head;
        do{
             build+=("Data element in the list ->");
             stringstream ss;
             ss<<worker->data;
             string data;
             ss>>data;
             build+=data;
             build+="\n";
        }while(worker=worker->next);
    }
    return build;
}
//return value at a given position
template <class T>
T StackList<T>::getElementAT(int position){
    int listSize = size(); //size of the list
    Node *lstPtr = head;   //will alow list to be traversed
    int count = 1;         //functions as the position of the value of the list
    
    if(position < 0 || position > listSize){
        cout << "ERROR: position out of range" << endl;
        exit(EXIT_FAILURE);
    }
    while(lstPtr != NULL){
        if (count == position){
            return(lstPtr->data); //returns position value when position requested
                                  //is equal to the count as it cycles through each node
                                  // one by one
        }  
        count++;                //increment count to move to next value in list
        lstPtr = lstPtr->next; //move to next value in list   
    }
}
//returns size of list
template <class T>
int StackList<T>::size(){
    int count = 0; //used to keep track of size
    
    //cycles through each node and increments count to represent size
    if(head){
        worker = head;
        do{
            count++;
        }while(worker = worker->next);
        return count;
    }else{
        return 0;
    }
}
//return a reference to the first value in list
//could not figure out how to return the reference
//so just returns value of first node
template <class T>
T StackList<T>::first(){
    Node *n = head;
    return n->data;
}
//return a reference to the last value in list
//could not figure out how to return the reference
//so just returns value of last node
template <class T>
T StackList<T>::last(){
    Node *nodePtr; // allows list to be traversed
    Node *end ;    //used to check for null at endo list
    Node *lastVal; //used to get last value
    
    if(head->next == NULL){
        return head->data;
    }else{
        Node *nodePtr = head;
        Node *end = head->next;
        while(end->next != NULL){
            nodePtr = end;
            end = end->next;
        }
        lastVal = nodePtr->next;
        return lastVal->data;
    }
}
//append value to end of list
//only used in copy constructor for Stack list
template <class T>
void StackList<T>::append(T n){
    Node *prev;
    //copies node into prev pointer 
    if(head){
        worker = head;
        do{
            prev = worker;
        }while(worker = worker->next);
        //"pushes" new value on to the end of the list
        Node *clink = new Node; //create new node to store new vale n
        clink->data = n;
        clink->next = NULL;
        prev->next = clink; //adds new value to end of the previous list
    }else{
       //if list is empty creates a new list
       Node *clink=new Node;
        clink->data=n;
        clink->next=NULL;
        head=clink; 
    }
}
#endif	/* STACKLIST_H */

