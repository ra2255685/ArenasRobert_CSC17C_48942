/* 
 * File:   Hero.h
 * Author: Robert Arenas Id:  2255685
 *
 * Created on December 12, 2015, 5:08 PM
 */

#ifndef HERO_H
#define HERO_H

#include <string>

using namespace std;

template <class T>
class Hero{
    public:
        //default constructor
        Hero(string, T, T);
        //access player attack stat
        T getAttack();   
        //access player special attack stat
        T getSpecial();
        //access player name stat
        string getName();                 
        //returns value based od on power up chosen by user
        T boost();
    
    private:
        string name; //player name stat
        T attack; //player attack stat
        T specialAttack; //player special attack stat
};
//default constructor
template <class T>
Hero<T>::Hero(string n,T a, T sa){
    //set player stats in constructor
    name = n; 
    attack = a; 
    specialAttack = sa; 
}
//access player attack stat
template <class T>
T Hero<T>::getAttack(){
    return attack;
}
//access player special attack stat
template <class T>
T Hero<T>::getSpecial(){
    return specialAttack;
}
//access player name stat
template <class T>
string Hero<T>::getName(){
    return name;
}
//returns value based od on power up chosen by user
template <class T>
T Hero<T>::boost(){
        int  pick;  //allows user to pick power up 
        
        do{
            cout << "Which weapon will you use"<<endl;
            //power up choices
            cout << "1) Sword (+1000 attack)" <<endl;
            cout << "2) Shuriken (+200 attack)" << endl;
            cout << "3) Attack special attack combo + (" << getSpecial() <<")" <<endl;
            cout << "4) None" <<endl;
     
            //get choice 
            cin>>pick;
        }while(pick < 1 || pick > 4); 
        //return value based on what player has chosen
        switch(pick){
          case 1:   return 1000;break;
          case 2:   return 200;break;
          case 3:   return specialAttack;break;
          case 4:   return 0;break;
          default:  return 0;
        }
}


#endif /* HERO_H */

