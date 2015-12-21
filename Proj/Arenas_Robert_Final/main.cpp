/* 
 * File:   main.cpp
 * Author: Robert Arenas Id: 2255685
 *
 * Created on December 16, 2015, 10:33 AM
 */

//System Libraries
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cmath>
#include <stack>
#include <queue>

////User Libraries
#include "Problem1.h" //contains functions for Problem 1 - Hashing
#include "Problem2.h" //contains functions for Problem 2 - Stacks
#include "Problem3.h" //contains functions for Problem 3 - Queues
#include "Problem4.h" //contains functions for Problem 4 - Sorting
#include "Problem5.h" //contains functions for Problem 5 - Binary Trees
#include "Problem6.h" //contains functions for Problem 6 - Weighted Graph

using namespace std;

//Function Prototypes
void Menu();
int getN();
void def(int);
void problem1(); //Problem 1 - Hashing
void problem2(); //Problem 2 - Stacks
void problem3(); //Problem 3 - Queues
void problem4(); //Problem 4 - Sorting
void problem5(); //Problem 5 - Binary Trees
void problem6(); //Problem 6 - Weighted Graph

int main(int argc, char** argv) {

    int inN;
        do{
            //menu of problems
            Menu();
            inN = getN();
            switch(inN){
                case 1:    problem1();break;
                case 2:    problem2();break;
                case 3:    problem3();break;
                case 4:    problem4();break;
                case 5:    problem5();break;
                case 6:    problem6();break;
                default:   cout << "Program Exited" << endl;
            }
        }while(inN <= 6);   
	
    return 0;
}
//menu for problens
void Menu(){
    cout << "Enter number corresponding to problem to view it" << endl;
    cout << "1.) Problem 1 - Hashing"<<endl;
    cout << "2.) Problem 2 - Stacks"<<endl;
    cout << "3.) Problem 3 - Queues"<<endl;
    cout << "4.) Problem 4 - Sorting"<<endl;
    cout << "5.) Problem 5 - Binary Trees"<<endl;
    cout << "6.) Problem 6 - Weighted Graph"<<endl;
    cout<<"Type 7 to exit"<<endl;
}
//hets user input
int getN(){
    int inN;
    cin>>inN;
    return inN;
}

void problem1(){
    cout << endl;
    cout << "Problem 1 - Hashing"<<endl;
    
    Hash hash; //access hash class in Problem1.h
    string initial; //used to read in initials from file
    ifstream inputFile; // used to open close txt file containing initials
    float secs; //calculate search function time
    clock_t start; // start of timer 
    clock_t end; // end of timer
    
    
    //open file and add initials to hash table then close file
    //NOTE full name was also set to initials because had no time to come up with 
    //1000 full names
    inputFile.open("initials.txt");
    while(inputFile >> initial){
        hash.addItem(initial);
    }
    inputFile.close();
   
    cout << "Searching for initials from file to calculates search time" << endl;
    
    //open file and search for each initial then close file
    //also start time when file opened and stop timer then file closed
    start = clock(); //set clock start time
    inputFile.open("initials.txt");
    while(inputFile >> initial){
        hash.search(initial);
    }
    inputFile.close();
    end = clock(); // get end clock time
 
    //display table stats
    hash.printStats();
    
    //calculate and display average search time
    secs  = (float(end - start) / CLOCKS_PER_SEC);
    cout << "Average search time is " <<  secs / 1000 
            << " seconds" << endl;
 
    cout << endl;
}

void problem2(){
    cout << endl;
    cout << "Problem 2 - Stacks"<<endl;
    
    //stack to hold either letter c for cosine 
    //or s for sine
    stack<char> calls; 
    Hyperbolic hy; //access Hyperbolic class in Problem2.h
    
    float angDeg=45;
    float angRad=angDeg*atan(1)/45;
    cout<<"Angle = "<<angDeg<<" sinh = "<<sinh(angRad)<<
            " our h = "<<hy.h(angRad, calls)<<endl;
    cout<<"Angle = "<<angDeg<<" cosh = "<<cosh(angRad)<<
            " our g = "<<hy.g(angRad, calls)<<endl;
    
  
    //display number of calls
    cout << endl;
    hy.calculateCalls(calls);
    
    cout << endl;
}

void problem3(){
    cout << endl;
    cout << "Problem 3 - Queues"<<endl;
    
    Bank b;
    int min = 180;
    int custnum = 1;
    
    for(int i = 0; i < 15; i++){
        b.addCustomer(custnum);
        custnum++;
    }
    
    for(int i = 0; i < min; i++){
        
        
        if(i % 3 == 0){
            
            b.addCustomer(custnum);
            
            custnum++;
           
            b.addCustomer(custnum);
            
            custnum++;
            
        }
        
        
        //remove customer if at proper service time
        b.removeAtTime(i);
        
    }
   
    
    cout << "tellers at end" << endl;
    b.print();
    
    cout << "Number of customers serviced " << custnum << endl;
    cout << "Total time serviced " << b.serviceTime() << " mins" << endl;
    cout << "Average wait time " << b.serviceTime() / (float)custnum 
            << " mins" << endl;
    cout << endl;
}

void problem4(){
    cout << endl;
    cout << "Problem 4 - Sorting"<<endl;
    
    srand(static_cast<unsigned int>(time(0)));
    
    Sorts s; //allow access Sorts class in Problem4.h
    int SIZE = 100000; //100000
    int test[SIZE]; //array to hold all 100000 values
    int beg; //timer beginning
    int end; //timer end
    int *tops = NULL; //pointer to tops array
    int topElements; //number of top elements user wants
    int sortChoice; //sort user chooses to use
    
    //fill the array
    for(int i = 0; i < SIZE; i++){
        test[i] = rand();
    }
    
    s.sortOptions();
    cin >> sortChoice;
    cout << endl;
    
    //get number of top elements user wants
    do{
        cout << "Enter the number of top Elements you would like" << endl;
        cin >> topElements;
    }while(topElements < 0 || topElements > SIZE);
    
    cout << "Sorting : " << endl;
    //s.print(test, N);
    
    //testing was conducted buy setting a timer beg and end, and by placing the sort 
    //and get tops function in between to calculate time take in seconds
    //average time in a coment above each
    
    if(sortChoice == 1){
        //quicksort took less than 1 sec on average
        cout << "Quick sort" << endl;
        beg = time(0);
        s.quickSort(test, 0, SIZE - 1);
        tops = s.topElements(test, topElements);
        end = time(0);
    }else if(sortChoice == 2){
        //merge sort took less than 1 sec on average
        cout << "Merge sort" << endl;
        beg = time(0);
        s.merge_sort(test, 0, SIZE - 1);
        tops = s.topElements(test, topElements);
        end = time(0);
    }else if(sortChoice == 3){
        //heap sort took less than 1 sec on average
        cout << "Heap sort" << endl;
        beg = time(0);
        s.heapsort(test, SIZE);
        tops = s.topElements(test, topElements);
        end = time(0);
    }else if(sortChoice == 4){
        //bubble time: 50(secs) to sort on average
        cout << "Bubble sort" << endl;
        beg = time(0);
        s.bubble(test, SIZE - 1);
        tops = s.topElements(test, topElements);
        end = time(0);
    }else if(sortChoice == 5){
        //selection sort took 12 sec to sort on average
        cout << "Selection sort" << endl;
        beg = time(0);
        s.selection(test, SIZE-1);
        tops = s.topElements(test, topElements);
        end = time(0);
    }else if(sortChoice == 6){
        //insertion sort took 13 sec to sort on average
        cout << "Insertion sort" << endl;
        beg = time(0);
        s.insertion(test, SIZE);
        tops = s.topElements(test, topElements);
        end = time(0);
    }else{
        cout << "No sort selected" << endl;
    }
    
    //print information if a sort was selected
    if(tops != NULL){
        cout << "The top " << topElements << " are:" << endl;
        //print tops requested
        for(int i = 0; i < topElements; i++){
            cout << tops[i] << " ";
        }
        cout << endl;
    
        //display time taken
        cout<<"The array of size "<< SIZE <<" took "<<end-beg<<"(secs) to sort" << endl;
    
        delete tops; //delete tops array
    }
    cout << endl;
    //answer question of which routines could be configured to have shortest time
    cout << "Answer to: What routines could be configured to have the shortest \n" 
            << "sort time and why." <<endl;
    s.findings();
    cout << endl;
}

void problem5(){
    cout << endl;
    cout << "Problem 5 - Binary Trees" << endl;
    
    Tree<string> t; //allow access Tree class in Problem5.h
    string initial; //used to read in initials from file
    ifstream inputFile; // used to open close txt file containing initials
    float secs; //calculate search function time
    clock_t start; // start of timer 
    clock_t end; // end of timer
    
    //open file and add initials to tree then close file
    inputFile.open("initials.txt");
    while(inputFile >> initial){
        t.insert(initial);
    }
    inputFile.close();
    
    //check if tree is balanced after insertion
    if(t.isBalanced()){
        cout << "Tree is balanced" << endl;
    }else{
            cout << "Tree not balanced" << endl;
    }
    
    //open file and search for each initial then close file
    //also start time when file opened and stop timer then file closed
    start = clock(); //set clock start time
    inputFile.open("initials.txt");
    while(inputFile >> initial){
        t.search(initial);
    }
    inputFile.close();
    end = clock(); // get end clock time
    
    //calculate and display average search time
    //search times seem ti indicate the tree seach is more consistant and better 
    //than the hash search
    //laptop specs lenovo g510s intel i5 2.50 GHz processor 6gb of ram
    //hash table seach takes either 1.5e-05 seconds or 3.1e-05 seconds
    //tree search takes either 0 seconds or 1.6e-05 seconds 
    secs  = (float(end - start) / CLOCKS_PER_SEC);
    cout << "Average search time is " <<  secs / 1000 
            << " seconds" << endl;
    
    cout << endl;  
}

void problem6(){
    cout << endl;
    cout << "Problem 6 - Weighted Graph"<<endl;
    
    //0 = bos, 1 = ord, 2 = jfk, 3 = mia, 4 = dfw, 5 = lax, 6 = sfo
    Graph g(7); //allow access Graph class in Problem6.h
    g.addEdge(6,0, 2704);  
    g.addEdge(6,1, 1846);
    g.addEdge(1,0, 867);
    g.addEdge(1,2, 740);
    g.addEdge(2,0, 187);
    g.addEdge(6,4, 1464);
    g.addEdge(4, 1, 802);
    g.addEdge(4, 3, 1121);
    g.addEdge(3, 2, 1090);
    g.addEdge(3, 0, 1258);
    g.addEdge(6, 5, 337);
    g.addEdge(5, 4, 1235);
    g.addEdge(5, 3, 2342);
    
    int s = 0; //vertex where functions start
    
    cout << "Breadth first traversal from vertex " << s << endl;
    g.BFT(s);
    cout << endl;
    
    cout << "Depth first traversal from vertex " << s << endl;
    g.DFT(s);
    cout << endl;
    
    
    cout << "Shortest path(Dijkstra) from vertex " << s << endl;
    //get shortest path
    queue<int> path = g.dijkstra(0, 5);
    //print airports using queue and translate function to turn numers into 
    // the correct string
    while(!path.empty()){
        cout << g.translateNums(path.front()) << " ";
        path.pop();
                
    }
    cout << endl << endl;
    
    cout << "Minimum spanning tree(Prim) of graph from vertex 0" << endl;
    g.prims();
    
    //g.test(); functions used for testing how to get smallest  edge in list
    cout << endl;
}