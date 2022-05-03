/* 
 * File:   Board.h
 * Author: Paul
 *
 * Created on April 29, 2022, 3:11 PM
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
#include <set>
using namespace std;

#ifndef BOARD_H
#define BOARD_H

class Board{
    private:
        map<string, int> plrScore;
        list<int> plr1pits;
        list<int> plr2pits;
        queue<int> gameHist;
        stack<int> curPlr;
        string player[2];
    public:
        Board(){
            for(int i=0;i<6;i++){
                plr1pits.push_back(4);
                plr2pits.push_back(4);
            }
        }
        Board(string p1, string p2){
            for(int i=0;i<6;i++){
                plr1pits.push_back(4);
                plr2pits.push_back(4);
            }
            plrScore[p1]=0;
            plrScore[p2]=0;
            player[0]=p1;
            player[1]=p2;
        }
        
        void setCurPlr(int plr){
            if(curPlr.empty()){
                curPlr.push(plr);
            }
            else{
                curPlr.pop();
                curPlr.push(plr);
            }
        }
        
        int returnCurPlr(){
            return curPlr.top();
        }
        
        void setPlayerName(string s, int plr){
            player[plr]=s;
            plrScore[s]=0;
        }
        
        void playGame(){
            setCurPlr(rand()%2);
            
            while(gameOver()){
                int choice;
        
                if(returnCurPlr()==0){
                    printBoard();
                    
                    cout<<getPlayerName(returnCurPlr())
                        <<"'s turn: Choose a cell 1-6 LR on top row";
                    cin>>choice;
            
                    updateGame(choice);
                    player1turn(choice);
            
                    setCurPlr(1);
                }
                else{
                    printBoard();
                    
                    cout<<getPlayerName(returnCurPlr())
                        <<"'s turn: Choose a cell 1-6 LR on bottom row";
                    cin>>choice;
            
                    updateGame(choice);
                    player2turn(choice);
            
                    setCurPlr(0);
                }
            }
            announceWin();
        }
        
        string getPlayerName(int plr){
            return player[plr];
        }
        
        void printBoard(){
            list<int>::iterator it;
            cout<<endl<<"|";
            for(it=plr1pits.begin();it!=plr1pits.end();it++){
                cout<<*it<<"|";
            }
            cout<<endl<<plrScore[player[0]]<<"==========="<<plrScore[player[1]] 
                    <<endl;
            cout<<"|";
            for(it=plr2pits.begin();it!=plr2pits.end();it++){
                cout<<*it<<"|";
            }   
            cout<<endl;
        }
        
        void updateGame(int cell){
            gameHist.push(cell);
        }
        
        void player1turn(int choice){
            int capCount=0;
            bool capture=false;
            
            list<int>::iterator it=plr1pits.begin();
            advance(it, choice-1);
            int marbles=*it;
            
            list<int>::reverse_iterator rit=plr1pits.rbegin();
            advance(rit, 6-choice);
            *rit=0;
            rit++;
            for(rit;rit!=plr1pits.rend();rit++){
                if(marbles>0){
                    marbles--;
                    *rit+=1;
                }
                if(marbles==0){
                    if(*rit==1){
                        *rit=0;
                        capture=true;
                    }
                    capCount++;
                }
            }
            
            bool goAgain=false;
            if(marbles>0){
                marbles--;
                if(marbles==0){
                    goAgain=true;
                }
                plrScore[player[curPlr.top()]]++;
            }
            
            while(goAgain){
                capCount=0;
                capture=false;
                
                printBoard();
                cout<<"You have earned another turn, go again"<<endl;
                cin>>choice;
                gameHist.push(choice);
                
                list<int>::reverse_iterator rit=plr1pits.rbegin();
                advance(rit, 6-choice);
                marbles=*rit;
                *rit=0;
                rit++;
                
                for(rit;rit!=plr1pits.rend();rit++){
                    if(marbles>0){
                        marbles--;
                        *rit+=1;
                    }
                    if(marbles==0){
                        if(*rit==1){
                            *rit=0;
                            capture=true;
                        }
                        capCount++;
                    }
                }
                
                goAgain=false;
                if(marbles>0){
                    marbles--;
                    if(marbles==0){
                        goAgain=true;
                    }
                    plrScore[player[curPlr.top()]]++;
                }
                
                int side=2;
                while(marbles>0){
                    if(side==2){
                        capCount=0;
                        capture=false;
                        list<int>::iterator it=plr2pits.begin();
                        for(it;it!=plr2pits.end();it++){
                            if(marbles>0){
                                marbles--;
                                *it+=1;
                            }
                        }
                        side=1;
                    }
                    else{
                        list<int>::reverse_iterator rit=plr1pits.rbegin();
                        for(rit;rit!=plr1pits.rend();rit++){
                            if(marbles>0){
                                marbles--;
                                *rit+=1;
                            }
                            if(marbles==0){
                                if(*rit==1){
                                    *rit=0;
                                    capture=true;
                                }
                                capCount++;
                            }
                        }
                        goAgain=false;
                        if(marbles>0){
                            marbles--;
                            if(marbles==0){
                                goAgain=true;
                            }
                            plrScore[player[curPlr.top()]]++;
                        }
                        side=2;
                    }
                }
            }
            
            int side=2;
            while(marbles>0){
                if(side==2){
                    list<int>::iterator it=plr2pits.begin();
                    for(it;it!=plr2pits.end();it++){
                        if(marbles>0 && marbles--){
                            *it+=1;
                        }
                    }
                    side=1;
                }
                else{
                    list<int>::reverse_iterator rit=plr1pits.rbegin();
                    for(rit;rit!=plr1pits.rend();rit++){
                        if(marbles>0){
                            marbles--;
                            *rit+=1;
                        }
                        if(marbles==0){
                            if(*rit==1){
                                *rit=0;
                                capture=true;
                            }
                            capCount++;
                        }
                    }
                    goAgain=false;
                    if(marbles>0){
                        marbles--;
                        if(marbles==0){
                            goAgain=true;
                        }
                        plrScore[player[curPlr.top()]]++;
                    }
                }
                while(goAgain){
                    capCount=0;
                    capture=false;
                    
                    printBoard();
                    cout<<"You have earned another turn, go again"<<endl;
                    cin>>choice;
                    gameHist.push(choice);
                    list<int>::reverse_iterator rit=plr1pits.rbegin();
                    advance(rit, 6-choice);
                    marbles=*rit;
                    *rit=0;
                    rit++;
                    for(rit;rit!=plr1pits.rend();rit++){
                        if(marbles>0){
                            marbles--;
                            *rit+=1;
                        }
                        if(marbles==0){
                            if(*rit==1){
                                *rit=0;
                                capture=true;
                            }
                            capCount++;
                        }
                    }
                    
                    goAgain=false;
                    if(marbles>0){
                        marbles--;
                        if(marbles==0){
                            goAgain=true;
                        }
                        plrScore[player[curPlr.top()]]++;
                    }
               
                    int side=2;
                    while(marbles>0){
                        if(side==2){
                            capture=false;
                            capCount=0;
                            
                            list<int>::iterator it=plr2pits.begin();
                            for(it;it!=plr2pits.end();it++){
                                if(marbles>0 && marbles--){
                                    *it+=1;
                                }
                            }
                            side=1;
                        }
                        else{
                            list<int>::reverse_iterator rit=plr1pits.rbegin();
                            for(rit;rit!=plr1pits.rend();rit++){
                                if(marbles>0){
                                    marbles--;
                                    *rit+=1;
                                }
                                if(marbles==0){
                                    if(*rit==1){
                                        *rit=0;
                                        capture=true;
                                    }
                                    capCount++;
                                }
                            }
                            goAgain=false;
                            if(marbles>0){
                                marbles--;
                                if(marbles==0){
                                    goAgain=true;
                                }
                                plrScore[player[curPlr.top()]]++;
                            }
                        }
                    }
                }
            }
            if(capture){
                player1capture(capCount);
            }
        }
        
        void player1capture(int capCount){
            cout<<"Capture!"<<endl;
            list<int>::iterator it=plr2pits.begin();
            advance(it, capCount-1);
            plrScore[player[0]]+=*it+1;
            *it=0;
        }
        
        void player2turn(int choice){
            int capCount=0;
            bool capture=false;
            
            list<int>::iterator it=plr2pits.begin();
            advance(it, choice-1);
            int marbles=*it;
            
            *it=0;
            it++;
            for(it;it!=plr2pits.end();it++){
                if(marbles>0){
                   marbles--;
                   *it+=1;
                }
                if(marbles==0){
                    if(*it==1){
                        *it=0;
                        capture=true;
                    }
                    capCount++;
                }
            }
            
            bool goAgain=false;
            if(marbles>0){
                marbles--;
                if(marbles==0){
                    goAgain=true;
                }
                plrScore[player[curPlr.top()]]++;
            }
            
            while(goAgain){
                capCount=0;
                capture=false;
                printBoard();
                cout<<"You have earned another turn, go again"<<endl;
                cin>>choice;
                gameHist.push(choice);
                list<int>::iterator it=plr2pits.begin();
                advance(it, choice-1);
                marbles=*it;
                *it=0;
                it++;
                for(it;it!=plr2pits.end();it++){
                    if(marbles>0){
                        marbles--;
                        *it+=1;
                    }
                    if(marbles==0){
                        if(*it==1){
                            *it=0;
                            capture=true;
                        }
                        capCount++;
                    }
                }
                
                goAgain=false;
                if(marbles>0){
                    marbles--;
                    if(marbles==0){
                        goAgain=true;
                    }
                    plrScore[player[curPlr.top()]]++;
                }
                
                int side=1;
                while(marbles>0){
                    if(side==1){
                        capCount=0;
                        capture=false;
                        list<int>::reverse_iterator rit=plr1pits.rbegin();
                        for(rit;rit!=plr1pits.rend();rit++){
                            if(marbles>0){
                                marbles--;
                                *rit+=1;
                            }
                        }
                        side=2;
                    }
                    else{
                        list<int>::iterator it=plr2pits.begin();
                        for(it;it!=plr2pits.end();it++){
                            if(marbles>0){
                                marbles--;
                                *it+=1;
                            }
                            if(marbles==0){
                                if(*it==1){
                                    *it=0;
                                    capture=true;
                                }
                                capCount++;
                            }
                        }
                        goAgain=false;
                        if(marbles>0){
                            marbles--;
                            if(marbles==0){
                                goAgain=true;
                            }
                            plrScore[player[curPlr.top()]]++;
                        }
                        side=1;
                    }
                }
            }
            
            int side=1;
            while(marbles>0){
                if(side==2){
                    list<int>::iterator it=plr2pits.begin();
                    for(it;it!=plr2pits.end();it++){
                        if(marbles>0){
                            marbles--;
                            *it+=1;
                        }
                        if(marbles==0){
                            if(*it==1){
                                *it=0;
                                capture=true;
                            }
                            capCount++;
                        }
                    }
                    goAgain=false;
                    if(marbles>0){
                        marbles--;
                        if(marbles==0){
                            goAgain=true;
                        }
                        plrScore[player[curPlr.top()]]++;
                    }
                    side=1;
                }
                else{
                    capCount=0;
                    capture=false;
                    list<int>::reverse_iterator rit=plr1pits.rbegin();
                    for(rit;rit!=plr1pits.rend();rit++){
                        if(marbles>0){
                            marbles--;
                            *rit+=1;
                        }
                    }
                    side=2;
                }
                while(goAgain){
                    capCount=0;
                    capture=false;
                    
                    printBoard();
                    cout<<"You have earned another turn, go again"<<endl;
                    cin>>choice;
                    gameHist.push(choice);
                    list<int>::iterator it=plr2pits.begin();
                    advance(it, choice-1);
                    marbles=*it;
                    *it=0;
                    it++;
                    for(it;it!=plr2pits.end();it++){
                        if(marbles>0){
                            marbles--;
                            *it+=1;
                        }
                        if(marbles==0){
                            if(*it==1){
                                *it=0;
                                capture=true;
                            }
                            capCount++;
                        }
                    }
                    
                    goAgain=false;
                    if(marbles>0){
                        marbles--;
                        if(marbles==0){
                            goAgain=true;
                        }
                        plrScore[player[curPlr.top()]]++;
                    }
               
                    int side=1;
                    while(marbles>0){
                        if(side==2){
                            list<int>::iterator it=plr2pits.begin();
                            for(it;it!=plr2pits.end();it++){
                                if(marbles>0){
                                    marbles--;
                                    *it+=1;
                                }
                                if(marbles==0){
                                    if(*it==1){
                                        *it=0;
                                        capture=true;
                                    }
                                    capCount++;
                                }
                            }
                            goAgain=false;
                            if(marbles>0){
                                marbles--;
                                if(marbles==0){
                                    goAgain=true;
                                }
                                plrScore[player[curPlr.top()]]++;
                            }
                            side=1;
                        }
                        else{
                            capCount=0;
                            capture=false;
                            list<int>::reverse_iterator rit=plr1pits.rbegin();
                            for(rit;rit!=plr1pits.rend();rit++){
                                if(marbles>0){
                                    marbles--;
                                    *rit+=1;
                                }
                            }
                            side=2;
                        }
                    }
                }
            }
            if(capture){
                player2capture(capCount);
            }
        }
        
        void player2capture(int capCount){
            cout<<"Capture!"<<endl;
            list<int>::reverse_iterator rit=plr1pits.rbegin();
            advance(rit, capCount-1);
            plrScore[player[1]]+=*rit+1;
            *rit=0;
        }
        void botPlay(int choice){
            list<int>::iterator it=plr2pits.begin();
            advance(it, choice-1);
            int marbles=*it;
            
            *it=0;
            it++;
            for(it;it!=plr2pits.end();it++){
                if(marbles>0){
                   marbles--;
                   *it+=1;
                }
            }
            
            bool goAgain=false;
            if(marbles>0){
                marbles--;
                if(marbles==0){
                    goAgain=true;
                }
                plrScore[player[curPlr.top()]]++;
            }
            
            while(goAgain){
                printBoard();
                cout<<"You have earned another turn, go again"<<endl;
                int choice=rand()%6+1;
                cout<<"Bot Selected: "<<choice<<endl;
                
                gameHist.push(choice);
                list<int>::iterator it=plr2pits.begin();
                advance(it, choice-1);
                marbles=*it;
                *it=0;
                it++;
                for(it;it!=plr2pits.end();it++){
                    if(marbles>0){
                        marbles--;
                        *it+=1;
                    }
                }
                
                goAgain=false;
                if(marbles>0){
                    marbles--;
                    if(marbles==0){
                        goAgain=true;
                    }
                    plrScore[player[curPlr.top()]]++;
                }
                
                int side=1;
                while(marbles>0){
                    if(side==1){
                        list<int>::reverse_iterator rit=plr1pits.rbegin();
                        for(rit;rit!=plr1pits.rend();rit++){
                            if(marbles>0){
                                marbles--;
                                *rit+=1;
                            }
                        }
                        side=2;
                    }
                    else{
                        list<int>::iterator it=plr2pits.begin();
                        for(it;it!=plr2pits.end();it++){
                            if(marbles>0){
                                marbles--;
                                *it+=1;
                            }
                        }
                        goAgain=false;
                        if(marbles>0){
                            marbles--;
                            if(marbles==0){
                                goAgain=true;
                            }
                            plrScore[player[curPlr.top()]]++;
                        }
                        side=1;
                    }
                }
            }
            
            int side=1;
            while(marbles>0){
                if(side==2){
                    list<int>::iterator it=plr2pits.begin();
                    for(it;it!=plr2pits.end();it++){
                        if(marbles>0){
                            marbles--;
                            *it+=1;
                        }
                    }
                    goAgain=false;
                    if(marbles>0 && marbles--){
                        if(marbles==0){
                            goAgain=true;
                        }
                        plrScore[player[curPlr.top()]]++;
                    }
                    side=1;
                }
                else{
                    list<int>::reverse_iterator rit=plr1pits.rbegin();
                    for(rit;rit!=plr1pits.rend();rit++){
                        if(marbles>0){
                            marbles--;
                            *rit+=1;
                        }
                    }
                    side=2;
                }
                while(goAgain){
                    printBoard();
                    cout<<"You have earned another turn, go again"<<endl;
                    int choice=rand()%6+1;
                    cout<<"Bot Selected: "<<choice<<endl;
                    gameHist.push(choice);
                    
                    list<int>::iterator it=plr2pits.begin();
                    advance(it, choice-1);
                    marbles=*it;
                    *it=0;
                    it++;
                    for(it;it!=plr2pits.end();it++){
                        if(marbles>0){
                            marbles--;
                            *it+=1;
                        }
                    }
                    
                    goAgain=false;
                    if(marbles>0){
                        marbles--;
                        if(marbles==0){
                            goAgain=true;
                        }
                        plrScore[player[curPlr.top()]]++;
                    }
               
                    int side=1;
                    while(marbles>0){
                        if(side==2){
                            list<int>::iterator it=plr2pits.begin();
                            for(it;it!=plr2pits.end();it++){
                                if(marbles>0 && marbles--){
                                    *it+=1;
                                }
                            }
                            goAgain=false;
                            if(marbles>0 && marbles--){
                                if(marbles==0){
                                    goAgain=true;
                                }
                                plrScore[player[curPlr.top()]]++;
                            }
                            side=1;
                        }
                        else{
                            list<int>::reverse_iterator rit=plr1pits.rbegin();
                            for(rit;rit!=plr1pits.rend();rit++){
                                if(marbles>0){
                                    marbles--;
                                    *rit+=1;
                                }
                            }
                            side=2;
                        }
                    }
                }
            }
        }
        
        bool gameOver(){
            list<int>::iterator it;
            int sum1=0;
            for(it=plr1pits.begin();it!=plr1pits.end();it++){
                sum1+=*it;
            }
            int sum2=0;
            for(it=plr2pits.begin();it!=plr2pits.end();it++){
                sum2+=*it;
            }
            return sum1 || sum2;
        }
        
        void announceWin(){
            list<int>::iterator it;
            for(it=plr1pits.begin();it!=plr1pits.end();it++){
                plrScore[player[0]]+=*it;
            }
            for(it=plr2pits.begin();it!=plr2pits.end();it++){
                plrScore[player[1]]+=*it;
            }
            int winScore=max(plrScore[player[0]], plrScore[player[1]]);
            if(winScore==plrScore[player[0]]){
                cout<<player[0]<<" wins with a score of "<<plrScore[player[0]];
            }
            else{
                cout<<player[1]<<" wins with a score of "<<plrScore[player[1]];
            }
        }
};

#endif /* BOARD_H */

