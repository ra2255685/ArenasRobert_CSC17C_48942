/* 
 * File:   main.cpp
 * Author: Robert Arenas Id:  2255685
 *
 * Created on November 9, 2015, 2:05 PM
 */

//System Libraries
#include <cstdlib>
#include <iostream>
#include <string>
#include <stack>
#include <set>
#include <queue>

//user libraries
#include "KillCount.h"
#include "Hero.h"
#include "Enemy.h"

using namespace std;

//function prototypes

//menu for game
void menu();
//areas in the game
void area1(KillCount&, Hero<int>&, int&);
void area2(KillCount&, Hero<int>&, int&);
void area3(KillCount&, Hero<int>&, int&);
void area4(KillCount&, Hero<int>&, int&);
//introduction for the game explains objective
void intro(Hero<int>&, int);
//displays map with number of enemies killed
void displayKillMap(KillCount&);
//checks users gold
void checkGold(int);
//conducts battle  between enemy and user(hero)
void battle(KillCount&, Hero<int>&, Enemy<int>&, int&);

int main(int argc, char** argv) {
    
    srand(static_cast<unsigned int>(time(0))); //seed for rand 
    int userInput; //user input on which area to go to or exit game
    string userName; //name of player
    int gold = 3; //user starts with 3 pieces of gold
    KillCount kMap; //counts how many times enemies have been defeated
    
    //get name of player
    cout << "Enter your name to start" << endl;
    cin >> userName;
    
    Hero<int> hero(userName, 2700, 2000); //initialize player 
    
    intro(hero, gold); //display intro to game
    
    /* main loop of the game keeps going until player has lost all gold or 
      has gained enough gold to win */
    do{
        menu();
        cin >> userInput;
        
        switch(userInput){
          case 1:   area1(kMap, hero, gold);break;
          case 2:   area2(kMap, hero, gold);break;
          case 3:   area3(kMap, hero, gold);break;
          case 4:   area4(kMap, hero, gold);break;
          case 5:   displayKillMap(kMap);break;
          default:  cout << "Program Exited";}
        
        checkGold(gold); //check players gold for win and loss condition
    }while(userInput <= 5);

    return 0;
}
//menu of options while playing
void menu(){
    cout << "Where will you go?" << endl;
    cout << "1.) The caves"<<endl;
    cout << "2.) The Forest"<<endl;
    cout << "3.) The mountain"<<endl;
    cout << "4.) Mysterious cemetery"<<endl;
    cout << "5.) Display enemies killed"<<endl;
    cout<<"Type 5 to exit \n"<<endl;
}
//area 1 of the game
void area1(KillCount &kMap, Hero<int> &h, int &gold){
    cout << endl;
    cout << "The Caves" << endl;
    
    string eName = "Dragon"; //set enemy name
    //initialize enemy list
    Enemy<int> dragon(eName, dragon.genAttk(), dragon.genGold(), 1);
    int areaEnemies = 3; //number of enemies in area after first in constructor
    int enemySelect; //user input to select an enemy to battle
   
    //loop to create enemies
    for(int i = 1; i <= areaEnemies; i++){
        dragon.createEnemies(eName, dragon.genAttk(), dragon.genGold(), i+1);
    }
    
    dragon.showEnemies(dragon); //show the enemies created
    
    //user chooses an enemy to battle
    cout << "select enemy to battle" << endl;
    cin >> enemySelect;
    
    dragon.selectEnemy(enemySelect);//sets stats for enemy chosen
    
    battle(kMap, h, dragon, gold); //conduct battle between player and enemy
}
//area 2 of game 
void area2(KillCount &kMap, Hero<int> &h, int &gold){
    cout << endl;
    cout << "The Forest" << endl;
    
    string eName = "Zombie"; //set enemy name
    char showList; //user input to show list of enemies or not
    int areaEnemies = 9; //number of enemies in area after first in constructor
    int enemiesToFace = 3; //number of enemies that will be battled
    stack<int> enemyStack; //stack to hold ids of enemies to be battled
    set<int> id; //set to add random ids into also prevents multiples of same id 
    set<int>::iterator it; //iterator to move through the set
    //initialize enemy list
    Enemy<int> zombie(eName, zombie.genAttk(), zombie.genGold(), 0);
    
    //loop to create enemies
    for(int i = 1; i <= areaEnemies; i++){
        zombie.createEnemies(eName, zombie.genAttk(), zombie.genGold(), i);
    }
    
    //check if user would like to see list of enemies before facing select enemies
    cout << zombie.getEnemyCount() << " " << zombie.getName()<< " in area" << endl;
    cout << "Would you like to view them before " << enemiesToFace 
            << " are added to stack (Y/N)" << endl;
    cin >> showList;
    if (showList == 'y' || showList == 'Y'){
        zombie.showEnemies(zombie);
    }
   
    cout << "Adding enemies to stack" << endl;
    /* add enemies to a stack using a set to prevent multiple of random numbers
    add random values representing enemy id to set */
    while(id.size() < enemiesToFace){
       id.insert(rand()% (zombie.getEnemyCount() - 1));
    }
    //adding values in set to stack
    for(it = id.begin(); it != id.end(); it++){
        cout << "enemy " << *it << " added to stack" <<endl;
        enemyStack.push(*it);
    }
    
    cout << "battle beginning" << endl;
    //battle each enemy in stack(last in fist out) continues until stack is empty
    while(!enemyStack.empty()){
        //search and set stats for enemy to be faced from id stored in stack
        zombie.selectEnemy(enemyStack.top()); 
        battle(kMap, h, zombie, gold);
        enemyStack.pop(); //remove id already faced to move t next enemy in stack
    }
}
//area 3 of game
void area3(KillCount &kMap, Hero<int> &h, int &gold){
    cout << endl;
    cout << "The Mountain" << endl;
    
    string eName = "Goatman";//set enemy name
    char showList; //user input to show list of enemies or not
    int enemiesToFace = 3; //number of enemies that will be battled
    int areaEnemies = rand()%(30-10)+10; //random number of enemies in area
    set<int> id; //set to add random ids into also prevents multiples of same id 
    set<int>::iterator it; //iterator to move through the set
    queue<int> enemyQueue; //queue to hold ids of enemies to be battled
    
    //initialize enemies list
    Enemy<int> goatman(eName, goatman.genAttk(), goatman.genGold(), 0);

    //loop to create enemies
    for(int i = 1; i <= areaEnemies; i++){
        goatman.createEnemies(eName, goatman.genAttk(), goatman.genGold(), i);
    }
    
     //check if user would like to see list of enemies before facing select enemies
    cout << goatman.getEnemyCount() << " " << goatman.getName() << " in area" << endl;
    cout << "Would you like to view them before " << enemiesToFace
            << " are added to stack (Y/N)" << endl;
    cin >> showList;
    if (showList == 'y' || showList == 'Y'){
        goatman.showEnemies(goatman);
    }
    
    //add enemies to a queue using a set to prevent multiple of random numbers
    //add random values representing enemy id to set
    while(id.size() < enemiesToFace){
       id.insert(rand()% (goatman.getEnemyCount() - 1));
    }
    //adding values in set to queue(first in first out)
    for(it = id.begin(); it != id.end(); it++){
        cout << "enemy " << *it << " added to queue" <<endl;
        enemyQueue.push(*it);
    }
    
    cout << "battle beginning" << endl;
    //battle each enemy in stack
    while(!enemyQueue.empty()){
        //search and set stats for enemy to be faced from id stored in queue
        goatman.selectEnemy(enemyQueue.front());
        battle(kMap, h, goatman, gold);
        enemyQueue.pop(); //remove id already faced to move t next enemy in queue
    }
}
//area 4 of game
void area4(KillCount &kMap, Hero<int> &h, int &gold){
    cout << endl;
    cout << "Mysterious cemetery" << endl;
    
    string eName = "Gravekeeper"; //set enemy name
    char showList; //user input to show list of enemies or not
    int enemiesToFace = 3; //number of enemies that will be battled
    int areaEnemies = 10; //number of enemies n area
    vector<int> ids; //vector to store ids selected
    
    //initialize enemies list
    Enemy<int> gravekeeper(eName, gravekeeper.genAttkHigh(), gravekeeper.genGold(), 0);
    
    //loop to create enemies
    for(int i = 1; i <= areaEnemies; i++){
        gravekeeper.createEnemies(eName, gravekeeper.genAttkHigh(), 
                gravekeeper.genGold(), i);
    }
    
    //check if user would like to see list of enemies before sorted in descending order
    cout << gravekeeper.getEnemyCount() << " " << gravekeeper.getName() << "'s in area" << endl;
    cout << "Would you like to view the enemy list before it is " 
            << " sorted in descending order by attack (Y/N)" << endl;
    cin >> showList;
    if (showList == 'y' || showList == 'Y'){
        gravekeeper.showEnemies(gravekeeper);
    }
    
    gravekeeper.sort(); // sort in descending order according to attack stat
    
    //check if user would like to see list of enemies after sorted by attack
    cout << "Would you like to view the enemy list now that it has been sorted" 
            << " descending order by attack (Y/N)" << endl;
    cin >> showList;
    if (showList == 'y' || showList == 'Y'){
        gravekeeper.showEnemies(gravekeeper);
    }
    
    //get the ids of strongest enemies
    ids = gravekeeper.topIds(gravekeeper, enemiesToFace);
    
    //conduct battle continues until all enemies in vector have been faced
    cout << "Now battling the strongest " << enemiesToFace << " enemies" << endl;
    for(int i = 0; i < ids.size(); i++){
        //search and set stats for enemy to be faced from id stored in vector
        gravekeeper.selectEnemy(ids[i]);
        battle(kMap, h, gravekeeper, gold);
    }
}
//introduction for the game explains objective and game play
void intro(Hero<int> &h, int gold){
    cout <<"OK " << h.getName() << " your adventure begins here" << endl;
    cout << "Your interdimensional transport ship has run out of fuel(gold) in a \n" <<
            "mysterious dimension you must collect at least 35 gold pieces in order \n" <<
            "to make the trip home" << endl;
    cout << "Collect gold by defeating enemies in the various areas" << endl;
    cout << "winning gives you their gold losing removes gold equal to what the enemy "
            << "was carrying" << endl;
    cout << "your base attack is: " << h.getAttack() << endl;
    cout << "your base special attack is: " << h.getSpecial() << endl;
    cout << "you have " << gold << " to start collect at leat 35 to win" << endl;
    cout << "if no gold remaining you lose" << endl;
    cout << endl;
}
//display map that contains how many times player has killed an enemy 
void displayKillMap(KillCount &kObj){
    kObj.printKillMap();
}

void checkGold(int gold){
    cout << endl;
    cout << "You have " << gold << " gold" << endl; //display player gold
    //if player has no gold left the lose, losing message displayed
    if(gold <= 0){
        cout << "No gold remaining you have died of peasantry!" << endl;
        cout << "GAME OVER!" << endl;
        exit(0);
    }
    //if player has at leat 35 gold the have won, winning message displayed
    if(gold >= 35){
        cout<<"You have collected enough gold to power your interdimensional "
              << "transport ship and in your way home" <<endl;
        exit(0);
    }
}
//conducts the battle between player and enemy also increments or decrements gold
void battle(KillCount& kMap, Hero<int> &hero, Enemy<int> &e, int &gold){
    cout << endl;
    //show enemy stats and players stats before player chooses weapon
    cout << "Now battling " << e.getName() << " " << e.getID() << " carrying " 
            << e.getEgold() << " gold" << endl;
    cout << "Enemy has " << e.getAttk() << " attack" << endl;
    cout << hero.getName() << " has " << hero.getAttack() << endl;
    
    //player attack after the have chosen a weapon
    int heroBattleAttk = hero.getAttack() + hero.boost(); 
    
    //show player attack after they have chosen a weapon
    cout << hero.getName() << " Attack become " << heroBattleAttk << endl;
            
    if(e.getAttk() > heroBattleAttk){
        //if enemy has more attack player loses gold equal to amount carried by enemy
        cout << "You have lost battle " << e.getEgold() << " gold lost" << endl;
        gold -= e.getEgold();
        cout << "Gold count now: " << gold << endl;
    }else if(e.getAttk() < heroBattleAttk){
        //if player has more attack than enemy player gains gold gold carried by enemy
        cout << "You have won battle " << e.getEgold() << " gold gained" << endl;
        gold += e.getEgold();
        kMap.incrementCount(e.getName());
        cout << "Gold count now: " << gold << endl;
    }else{
        //if tie no gold won or lost
        cout << "Battle is a tie no gold gained or lost" << endl;
        gold +=0;
        cout << "Gold count now: " << gold << endl;
    }
}