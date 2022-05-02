/* 
 * File:   main.cpp
 * Author: Paul Ingram
 * Created on April 29, 2021, 11:30 AM
 * Purpose:  Mancala 17C Version 3
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
using namespace std;

int main(int argc, char** argv) {
    srand(time(NULL));
    
    string player[2];
    int curPlr=rand()%2;
    
    cout<<"Enter Player 1 Name: "<<endl;
    cin>>player[0];
    cout<<"Enter Player 2 Name: "<<endl;
    cin>>player[1];
    
    Board board(player[0], player[1]);
    
    while(board.gameOver()){
        int choice;
        
        if(curPlr==0){
            board.setCurPlr(curPlr);
            board.printBoard();
            cout<<board.getPlayerName(curPlr)
                    <<"'s turn: Choose a cell 1-6 LR on top row";
            cin>>choice;
            
            board.updateGame(choice);
            board.player1turn(choice);
            
            curPlr=1;
            board.setCurPlr(curPlr);
        }
        else if(curPlr==1){
            board.setCurPlr(curPlr);
            board.printBoard();
            cout<<board.getPlayerName(curPlr)
                    <<"'s turn: Choose a cell 1-6 LR on bottom row";
            cin>>choice;
            
            board.updateGame(choice);
            board.player2turn(choice);
            
            curPlr=0;
            board.setCurPlr(curPlr);
        }
    }
    
    board.announceWin();
  
    return 0;
}



