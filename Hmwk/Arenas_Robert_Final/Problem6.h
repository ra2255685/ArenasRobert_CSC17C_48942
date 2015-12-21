/* 
 * File:   Problem6.h
 * Author: Robert Arenas Id: 2255685
 *
 * Created on December 19, 2015, 11:34 AM
 */

#ifndef PROBLEM6_H
#define PROBLEM6_H

#include <iostream>
#include <list>
#include <queue>

using namespace std;

class Edge{
public:
    //edge constructor takes a vertex v  and w weight of edge
    Edge(int v, int w);
    int getVer(); //gets vertex conected to 
    int getWeight(); //gets cost
private:
    int ver; //number of vertex connected to edge
    int weight; //cost of edge between vertices
};

class Graph{
public:
    //constructor creates list of vertices
    Graph(int v);
    //destructor
    ~Graph();
    //Add edge to graph
    void addEdge(int u, int v, int w);
    //breadth first traversal
    void BFT(int s);
    //depth first traversal
    void DFT(int s);
    //finds shortest path from inputed verticies
    queue<int> dijkstra(int s, int d);
    //print spanning tree of graph using prim's algorithm
    void prims();
    //translate numbers to airports
    string translateNums(int);
    void test();
    
private:
    int verticies; //number of verticies
    //pointer to array of lists with vertexes and their adjacent vertexes
    list<Edge> *adjList; 
    //private recursive function for depth first traversal
    void DFTRec(int, bool[]);
};

//edge functions
Edge::Edge(int v, int w){
    ver = v;//destination
    weight = w;
}
//gets destination vertex of edge
Edge::getVer(){
    return ver;
}
//gets weight of edge
Edge::getWeight(){
    return weight;
}
//graph functions
Graph::Graph(int v){
    verticies = v; //set number of vertices
    //create adjacency list to store the vertices
    adjList = new list<Edge>[v];
}
//destructor
Graph::~Graph(){
    //delete [] adjList;
} 
//add and edge to the graph
void Graph::addEdge(int u, int v, int w){
    Edge node(v, w); // create edge node with destination vertex and weight of edge
    Edge node2(u, w);
    //add edge to vertex it will be adjacent to 
    adjList[u].push_back(node);
    adjList[v].push_back(node2);
}
//breadth first traversal of graph
void Graph::BFT(int s){
    
    //mark vertices as not visited (false)
    bool *visited = new bool[verticies];
    for(int i = 0; i < verticies; i++){
        visited[i] = false;
    }
    
    list<int> l; //list to store visited vertex to be printed
    
    //mark first vertex as visited and add to print list
    visited[s] = true;
    l.push_back(s);
    
    list<Edge>::iterator it; //iterator to visit adjacent vertices
    
    while(!l.empty()){
        
        //print vertices as graph being traversed then remove from print list
        s = l.front();
        cout << translateNums(s) << " ";
        l.pop_front();
    
        //traverse to adjacent vertices
        for(it = adjList[s].begin(); it != adjList[s].end(); it++){
            Edge node = *it; //node to access edge destination 
            //if vertex has not been visited mark as visited and add to print list
            if(!visited[node.getVer()]){
                visited[node.getVer()] = true;
                l.push_back(node.getVer());
            }
        }
    }
    cout << endl;
}
//Depth first traversal of graph
void Graph::DFT(int s){
    //array to check if vertex has been visited
    bool *visited = new bool[verticies]; 
  
    //mark vertices as not visited
    for(int i = 0; i < verticies; i++){
        visited[i] = false;
    }
    //call recursive function to print vertices
    DFTRec(s, visited);
    cout << endl;
}
//private recursive function for depth first traversal
void Graph::DFTRec(int s, bool visited[]){
    //print vertex as it is passed in and mark as visited
    visited[s] = true;
    cout << translateNums(s) << " ";
    list<Edge>::iterator it; //iterator to move through list of edges
    
    //recusively visit adjacent nodes to vertices
    for(it = adjList[s].begin(); it != adjList[s].end(); it++){
        Edge node = *it; //node to access edge destination 
        if(!visited[node.getVer()]){
            DFTRec(node.getVer(), visited);     
        }
    }
}
//returns queue containing numbers representing airpot=rts
queue<int> Graph::dijkstra(int s, int d){
   
    queue<int> path; //queue contains path 
    list<int> l; // list for vertexes
    int *dist = new int[verticies]; //hold weights of edges 
    bool *visited = new bool[verticies]; // check if vertect visited
    list<Edge>::iterator it; // move through list
    
    int min;
    int tempv;
    int vp;
    int tempw;
    
    //initialize  visited and didtsance array
    for(int i = 0; i < verticies; i++){
        visited[i] = false;
        dist[i] = 999999;
    }
    
    //set sourc as distance 0 and visited, also ass to list and path queue
    dist[s] = 0;
    visited[s] = true;
    l.push_back(s);
    path.push(s);

    while(!l.empty()){
        
        //get vertex from list then remove it
        s = l.front();
        l.pop_front();
        
        //cout <<"sdjc " << s << endl;
        //beak out of loop one destination is reached
        if(s == d){
            break;
            return path;
            
        }
        
        //traverse to adjacent vertices
        for(it = adjList[s].begin(); it != adjList[s].end(); it++){
            
            //tempv = it->getWeight();
            
            
            //supossed to find smalest conected edge
            //could not figure out what was wrong
            if(visited[it->getVer()] == false){ 
                min = 999999;
                tempv = it->getWeight();
                //cout << it->getVer() << " " << it->getWeight() << endl;
                
                if(tempv < min){
                    min = tempv;
                    vp = it->getVer();
                    tempw = it->getWeight();
                
                }
                
            }
            
            
        }
        
        //cout << "vp in " << vp  << " " << tempw<< endl;
        
        if(!visited[vp]){
            if(dist[vp] < dist[vp]+ tempw){
                dist[vp] = dist[vp] + tempw;
                path.push(vp);
                l.push_back(vp);
            }
        }
        
        visited[vp] = true;
        //cout <<"next in stack " << vp << endl;
        
        
    }
    //cout <<"vp= " << vp << "-" << tempw << endl;
    //free memory taken by arrays
    delete []visited;
    delete []dist;
    
    //return path 
    return path;
}
//print spanning tree of graph using prim's algorithm
void Graph::prims(){
    int x = 0; //represents one vertex of edge
    int y = 0; //represents second vertex of edge
    int w = 0; //hold weight of an edge
    int totalWeight = 0; //counter for total weight 
    int *dist = new int[verticies]; //array to hold weights of edges
    bool *visited = new bool[verticies];//array to check if vertex has been visited
    list<Edge>::iterator it; //iterator to move through list of edges
    
    //mark vertices as not visited and weight to 9999
    for(int i = 0; i < verticies; i++){
        visited[i] = false;
        dist[i] = 9999;
    }
    
    //initialize first vertex has weight of zero and mark as visited
    dist[0] = 0;
    visited[0] = true;
    
    //header for print section 
    cout << "Edges, weight" << endl;
    
    //loop that prints spanning tree 
    for(int i = 0; i < verticies - 1; i++){
        //mark vertex as visited
        visited[i] = true;
        //iterate to adjecent vertexes
        for(it = adjList[i].begin(); it != adjList[i].end(); it++){
            Edge node = *it; //node to access edge destination and weight of current vertex
            
            //if vertex has not been visited check if it is next value in tree
            if(!visited[node.getVer()]){
                //visited[i] = true;
                if(dist[node.getVer()] > dist[i] +  node.getWeight()){
                    //change weight of edge in dist[] to new smaller value]
                    dist[node.getVer()] = dist[i] + node.getWeight();
                    //set edge values so they can be printed
                    x = i; 
                    y = node.getVer();
                    w = node.getWeight();
                    
                }
                
            }
        }
        
        //running total fro weight of tree
        totalWeight = totalWeight + w;
        //print edge with weight
        cout << translateNums(x) << " - " << translateNums(y) << ", " << w << endl;
    }
    //print total weight of tree
    cout << "Total weight of spanning tree: " << totalWeight << endl;
    
    //free memory taken by arrays
    delete []visited;
    delete []dist;
}
//translate numbers int airport names
string Graph::translateNums(int n){
    
    if(n == 0){
        return "BOS";
    }else if(n == 1){
        return "ORD";
    }else if(n == 2){
        return "JFK";
    }else if(n == 3){
        return "MIA";
    }else if(n == 4){
        return "DFW";
    }else if(n == 5){
        return "LAX";
    }else if(n == 6){
        return "SFO";
    }else{
        return "undefined";
    }
}

void Graph::test(){
    int i = 2;
    list<Edge>::iterator it; //iterator to move through list of edges
    
    int min = 999999;
    int tempv;
    int vp = 0;
    int tempw = 0;
    for(it = adjList[i].begin(); it != adjList[i].end(); it++){
        
        tempv = it->getWeight();
        
        if(tempv < min){
            min = tempv;
            vp = it->getVer();
            tempw = it->getWeight();
        }
        cout << it->getVer() << " - " << it->getWeight() << " ";
        
        
    }
    cout << endl;
    cout <<"vp= " << vp << "-" << tempw << endl;
}

#endif /* PROBLEM6_H */

