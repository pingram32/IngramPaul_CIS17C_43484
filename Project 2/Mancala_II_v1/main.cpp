/* 
 * File:   main.cpp
 * Author: Paul Ingram
 * Created on June 6, 2022, 7:51 PM
 * Purpose:  Mancala for project 2
 */

//System Libraries
#include <iostream>   //Input/Output Library
#include <vector>
#include <array>
#include <string>
using namespace std;  //STD Name-space where Library is compiled

//User Libraries

//Global Constants not Variables
//Math/Physics/Science/Conversions/Dimensions

//Function Prototypes
void fillBoard(vector<vector<int>> &, vector<int> &);
void showBoard(vector<int>);
int gameOver(vector<int>);
//Code Begins Execution Here with function main
int main(int argc, char** argv) {
    //Set random number seed once here
    
    //Declare variables here
    vector<vector<int>> board;
    vector<int> cells(14);
    string player[2];
    //Initialize variables here
    fillBoard(board, cells);
    //Map inputs to outputs here, i.e. the process
    cout<<"This is Mancala"<<endl;
    cout<<"Enter Player 1 Name: ";
    cin>>player[0];
    cout<<"Enter Player 2 Name: ";
    cin>>player[1];
    
    int side=1;
    while(gameOver(cells)){
        if(side==1){
            showBoard(cells);
            
            int choice;
            cout<<player[0]<<" select a cell on the top row 1-6 (L-R)"<<endl;
            cin>>choice;
            
            while(choice<1 || choice>6){
                cout<<"Please select a cell between 1-6 (L-R)"<<endl;
                cin>>choice;
            }
            
            int marbles=cells[6-choice];
            int cell=board[6-choice][0];
            cells[6-choice]=0;
            while(marbles){
                if(cell==13){
                    cell=0;
                    cells[cell]++;
                    cell=board[cell][0];
                    marbles--;
                }
                else{
                    cells[cell]++;
                    cell=board[cell][0];
                    marbles--;
                }
            }
            cell--;
            
            if(cell>=0 && cell<=5 && cells[cell]==1){
                cout<<"Capture!"<<endl;
                cells[6]+=cells[board[cell][1]]+1;
                cells[board[cell][1]]=0;
                cells[cell]=0;
                showBoard(cells);
            }
        }
    }
    //Display the results
    
    return 0;
}

void fillBoard(vector<vector<int>> &board, vector<int> &cells){
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

void showBoard(vector<int> cells){
    cout<<"|"<<cells[5]<<"|"<<cells[4]<<"|"<<cells[3]<<"|"<<cells[2]<<"|"
            <<cells[1]<<"|"<<cells[0]<<"|"<<endl;
    cout<<cells[6]<<"==========="<<cells[13]<<endl;
    cout<<"|"<<cells[7]<<"|"<<cells[8]<<"|"<<cells[9]<<"|"<<cells[10]<<"|"
            <<cells[11]<<"|"<<cells[12]<<"|"<<endl;
}

int gameOver(vector<int> cells){
    int top=0, bottom=0;
    for(int i=0;i<6;i++){
        top+=cells[i];
    }
    for(int i=7;i<13;i++){
        bottom+=cells[i];
    }
    return top || bottom;
}
