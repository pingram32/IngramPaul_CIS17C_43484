/* 
 * File:   main.cpp
 * Author: Paul Ingram
 * Created on April 29, 2021, 11:30 AM
 * Purpose:  Mancala 17C Version 4
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <time.h>
#include <algorithm>
#include <list>
#include <map>
#include <stack>
#include <queue>
#include "Board.h"
#include "SimGame.h"
using namespace std;

int main(int argc, char** argv) {
    srand(time(NULL));
    int gameMode;
    
    cout<<"Main Menu..."<<endl;
    cout<<"Enter 1) 1v1"<<endl;
    cout<<"Enter 2) 1vBot"<<endl;
    cin>>gameMode;
    
    if(gameMode==1){
        string player[2];
        int curPlr=rand()%2;
    
        cout<<"Enter Player 1 Name: "<<endl;
        cin>>player[0];
        cout<<"Enter Player 2 Name: "<<endl;
        cin>>player[1];
    
        Board board(player[0], player[1]);
    
        board.playGame();
    }
    else{
        string name;
        cout<<"Enter Player 1 Name: "<<endl;
        cin>>name;
        SimGame sim(name);
    }
    return 0;
}



