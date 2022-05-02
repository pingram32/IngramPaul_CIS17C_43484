/* 
 * File:   SimGame.h
 * Author: Paul
 *
 * Created on May 1, 2022, 10:04 PM
 */
#include "Board.h"

#ifndef SIMGAME_H
#define SIMGAME_H

class SimGame{
    private:
        Board board;
    public:
        SimGame(string s){
            list<int> botPlays(6);
            set<int> cells;
            
            for(int i=0;i<6;i++){
                cells.insert(i+1);
            }
            
            board.setPlayerName(s, 0);
            board.setPlayerName("Bot", 1);
            
            int curPlr=0;
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
                            <<"'s turn: Choose a cell 1-6 LR on bottom row"<<endl;
                    
                    copy(cells.begin(), cells.end(), botPlays.begin());
                    
                    list<int>::iterator it;
                    it=find(botPlays.begin(), botPlays.end(), rand()%6+1);
                    choice=*it;
                    
                    cout<<"Bot Selected: "<<choice<<endl;
                  
                    board.updateGame(choice);
                    board.botPlay(choice);
            
                    curPlr=0;
                    board.setCurPlr(curPlr);
                }
            }
            
            board.announceWin();
        }    
        
};


#endif /* SIMGAME_H */

