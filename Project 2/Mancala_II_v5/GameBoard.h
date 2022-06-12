/* 
 * File:   GameBoard.h
 * Author: Paul
 *
 * Created on June 7, 2022, 6:05 PM
 */

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include <array>
#include <string>
#include "Player.h"
using namespace std;

class GameBoard{
    private:
        vector<vector<int>> board;
        vector<int> cells;
        Player player;
        int side=1;
    public:
        GameBoard(){
            string name[2];
            cout<<"This is Mancala"<<endl;
            cout<<"Enter Player 1 Name: ";
            cin>>name[0];
            cout<<"Enter Player 2 Name: ";
            cin>>name[1];
            
            player.setPlayer(name[0], 1);
            player.setPlayer(name[1], 2);
            player.setUserID(player.getPlayer(1), 1);
            player.setUserID(player.getPlayer(2), 2);
            setCells();
            setBoard();
        }
        
        void showBoard(){
            cout<<"|"<<cells[5]<<"|"<<cells[4]<<"|"<<cells[3]<<"|"<<cells[2]<<"|"
                <<cells[1]<<"|"<<cells[0]<<"|"<<endl;
            cout<<cells[6]<<"==========="<<cells[13]<<endl;
            cout<<"|"<<cells[7]<<"|"<<cells[8]<<"|"<<cells[9]<<"|"<<cells[10]<<"|"
                <<cells[11]<<"|"<<cells[12]<<"|"<<endl;
        }
        
        int gameOver(){
            int top=0, bottom=0;
            for(int i=0;i<6;i++){
                top+=cells[i];
            }
            for(int i=7;i<13;i++){
                bottom+=cells[i];
            }
            return top || bottom;
        }
        
        void plr1Turn(){
            showBoard();
            int choice;
            int recMove=recMove1();
            cout<<player.getPlayer(1)
                    <<" select a cell on the top row 1-6 (L-R)"<<endl;
            cout<<"The recommended cell is "<<recMove<<endl;
            cin>>choice;
            
            while(choice<1 || choice>6){
                cout<<"Please select a cell between 1-6 (L-R)"<<endl;
                cin>>choice;
            }
            
            int marbles=cells[6-choice];
            int cell=board[6-choice][0];
            cells[6-choice]=0;
            cell=recUpdate1(marbles, cell);
            
            if(cell==6){
                cout<<"You have earned another turn, go again"<<endl;
                side=1;
            }
            else if(cell>=0 && cell<=5 && cells[cell]==1){
                cout<<"Capture!"<<endl;
                cells[6]+=cells[board[cell][1]]+1;
                cells[board[cell][1]]=0;
                cells[cell]=0;
                side=2;
            }
            else side=2;
        }
        
        int recUpdate1(int marbles, int cell){
            if(marbles==0){
                return cell-1;
            }
            if(cell==13){
                cell=0;
                cells[cell]++;
                cell=board[cell][0];
                marbles--;
                return recUpdate1(marbles, cell);
            }
            else{
                cells[cell]++;
                cell=board[cell][0];
                marbles--;
                return recUpdate1(marbles, cell);
            }
        }
        
        int recMove1(){
            vector<array<int,2>> v;
            for(int i=0;i<6;i++){
                v.push_back({i, cells[i]});
            }
            int recMove=0;
            for(int i=0;i<6;i++){
                if(v[i][1]==1 && v[i][0]==5){
                    recMove=1;
                }
                else if(!recMove && 6-v[i][0]==v[i][1]){
                    recMove=6-v[i][0];
                }
                else if(!recMove && v[i][1]==1 && cells[board[v[i][0]][0]]==0){
                    recMove=6-v[i][0];
                }
            }
            if(!recMove){
                recMove=1;
                while(!cells[6-recMove]){
                    recMove++;
                }
            }
            return recMove;
        }
        
        void bubbleSort(vector<array<int,2>> &v, int n){
            if(n==1){
                return;
            }
            for(int i=0;i<n-1;i++){
                if(v[i][1]>v[i+1][1]){
                    swap(v[i],v[i+1]);
                }
            }
            bubbleSort(v, n-1);
        }
        
        void plr2Turn(){
            showBoard();
            
            int choice;
            cout<<player.getPlayer(2)
                    <<" select a cell on the bottom row 1-6 (L-R)"<<endl;
            cin>>choice;
            
            while(choice<1 || choice>6){
                cout<<"Please select a cell between 1-6 (L-R)"<<endl;
                cin>>choice;
            }
            
            int marbles=cells[6+choice];
            int cell=board[6+choice][0];
            cells[6+choice]=0;
            cell=recUpdate2(marbles, cell);
            
            if(cell==13){
                cout<<"You have earned another turn, go again"<<endl;
                side=2;
            }
            else if(cell>=7 && cell<=12 && cells[cell]==1){
                cout<<"Capture!"<<endl;
                cells[13]+=cells[board[cell][1]]+1;
                cells[board[cell][1]]=0;
                cells[cell]=0;
                side=2;
            }
            else side=1;
        }
        
        int recUpdate2(int marbles, int cell){
            if(marbles==0){
                return cell-1;
            }
            if(cell==6){
                cell=7;
                cells[cell]++;
                cell=board[cell][0];
                marbles--;
                return recUpdate2(marbles, cell);
            }
            else{
                cells[cell]++;
                cell=board[cell][0];
                marbles--;
                return recUpdate2(marbles, cell);
            }
        }
        
        int getSide(){
            return side;
        }
        
        void setCells(){
            for(int i=0;i<14;i++){
                cells.push_back(0);
            }
        }
        
        void setBoard(){
            for(int i=0;i<14;i++){
                vector<int> v;
                board.push_back(v);
        
                if(i==6){
                    board[i].push_back(i+1);
                    board[i].push_back(i-1);
                    cells[i]=0;
                }
                else if(i==13){
                    board[i].push_back(0);
                    board[i].push_back(i-1);
                    cells[i]=0;
                }
                else if(i>=0 && i<=5){
                    board[i].push_back(i+1);
                    board[i].push_back(12-i);
                    cells[i]=6;
                }
                else if(i>=7 && i<=12){
                    board[i].push_back(i+1);
                    board[i].push_back(12-i);
                    cells[i]=6;
                }
            }
        }
};

#endif /* GAMEBOARD_H */

