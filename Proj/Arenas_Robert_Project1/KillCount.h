/* 
 * File:   KillCount.h
 * Author: Robert Arenas ID:2255685
 *
 * Created on November 10, 2015, 12:20 PM
 */

#ifndef KILLCOUNT_H
#define	KILLCOUNT_H

//System Libraries
#include <map>
#include <string>
#include <iostream>

using namespace std;

class KillCount{
    
    public: 
        //default constructor
        KillCount(); 
        //increases the number each time a certain enemy is killed by player
        void incrementCount(string); 
        //displays the map of enemies with their kill count
        void printKillMap();
        
    private:
        //map holds enemy name and number of times defeated by user
        map<string, int> kMap; 
        //used to print and search the map
        map<string, int>::iterator it; 
};
//initialize map of enemies in constructor for class
KillCount::KillCount(){
    kMap.insert(make_pair("Dragon", 0));
    kMap.insert(make_pair("Zombie", 0));
    kMap.insert(make_pair("Goatman", 0));
    kMap.insert(make_pair("Gravekeeper", 0));
}
//increases the number each time a certain enemy is killed by player
void KillCount::incrementCount(string name){
    //loop to find name of enemy
    for(it = kMap.begin(); it != kMap.end(); it++){
        //if name found second value representing kill count in pair increased
        if(it->first == name){
            it->second++;
        }
    }
}
//displays the map of enemies with their kill count
void KillCount::printKillMap(){
    cout << endl;
    cout << "Monster" << " / " << " Times Killed" << endl;
    //loop to through map to print the map
    for(it = kMap.begin(); it != kMap.end(); it++){
        cout << it->first << " / " << it->second << endl;
    }
    cout << endl;
}
#endif	/* KILLCOUNT_H */

