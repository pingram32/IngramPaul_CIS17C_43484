/* 
 * File:   main.cpp
 * Author: Paul Ingram
 * Created on April 28, 2021, 9:15 PM
 * Purpose:  Mancala 17C Version 1
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
using namespace std;

int sumSide(list<int>);
void printBoard(list<int>, list<int>, map<string, int>, string[]);

int main(int argc, char** argv) {
    srand(time(NULL));
    
    string player[2];
    map<string, int> plrScore;
    stack<int> currentPlr;
    list<int> plr1pits;
    list<int> plr2pits;
    queue<int> gameHist;
    
    for(int i=0;i<6;i++){
        plr1pits.push_back(4);
        plr2pits.push_back(4);
    }
    
    cout<<"Enter Player 1 Name: "<<endl;
    cin>>player[0];
    cout<<"Enter Player 2 Name: "<<endl;
    cin>>player[1];
    
    plrScore[player[0]]=0;
    plrScore[player[1]]=0;
    
    currentPlr.push(rand()%2);
    //sumSide(plr1pits) || sumSide(plr2pits)
    int x=1;
    while(x--){
        int choice,
            curPlr=0;
        
        printBoard(plr1pits, plr2pits, plrScore, player);
        cout<<player[curPlr]<<"'s turn: Choose a cell 1-6 LR";

        if(curPlr==0){
            cout<<" on top row"<<endl;
            cin>>choice;
            gameHist.push(choice);
            list<int>::iterator it=plr1pits.begin();
            advance(it, plr1pits.size()-(7-choice));
            int marbles=*it;
            
            list<int>::reverse_iterator rit=plr1pits.rbegin();
            advance(rit, 6-choice);
            *rit=0;
            rit++;
            for(rit;rit!=plr1pits.rend();rit++){
                 if(marbles--) *rit+=1;
            }
            plrScore[player[curPlr]]++;
            printBoard(plr1pits, plr2pits, plrScore, player);
            
            if(marbles){
                if(marbles-(plr1pits.size()-(7-choice))>=0){

                }
            }
            

        }
        
    }
  
    return 0;
}

int sumSide(list<int> side){
    list<int>::iterator it;
    int sum=0;
    for(it=side.begin();it!=side.end();it++){
        sum+=*it;
    }
    return sum;
}

void printBoard(list<int> plr1pits, list<int> plr2pits,
        map<string, int> plrScore, string player[]){
    list<int>::iterator it;
    cout<<endl<<"|";
    for(it=plr1pits.begin();it!=plr1pits.end();it++){
        cout<<*it<<"|";
    }
    cout<<endl<<plrScore[player[0]]<<"==========="<<plrScore[player[1]]<<endl;
    cout<<"|";
    for(it=plr2pits.begin();it!=plr2pits.end();it++){
        cout<<*it<<"|";
    }
    cout<<endl;
}

