/* 
 * File:   main.cpp
 * Author: Paul Ingram
 * Created on June 11, 2022, 5:30 PM
 * Purpose:  Mancala for project 2
 */

//System Libraries
#include <iostream>   //Input/Output Library
#include "BotGame.h"
using namespace std;  //STD Name-space where Library is compiled

//User Libraries

//Global Constants not Variables
//Math/Physics/Science/Conversions/Dimensions

//Function Prototypes

//Code Begins Execution Here with function main
int main(int argc, char** argv) {
    //Set random number seed once here
    srand(time(0));
    //Declare variables here
    
    //Initialize variables here
    int choice;
    //Map inputs to outputs here, i.e. the process
    cout<<"Main Menu..."<<endl;
    cout<<"1) 1v1"<<endl;
    cout<<"2) 1vBot"<<endl;
    cout<<"3) Simulate for statistics"<<endl;
    cin>>choice;
    
    if(choice==1){
        GameBoard mancala;
    }
    else if(choice==2){
        BotGame game;
    }
    else{
        cout<<"Mancala Statistics Version"<<endl;
        int n=1000;
        int plr1Win=0;
        int plr2Win=0;
        int tie=0;
        vector<int> cellPlays1(7);
        vector<int> cellPlays2(7);
        for(int i=0;i<n;i++){
            Simulate sim;
            map<int, int> plays1=sim.Plr1Hist();
            map<int, int> plays2=sim.Plr2Hist();
            if(sim.returnWin()==1){
                plr1Win++;
            }
            else if(sim.returnWin()==2){
                plr2Win++;
            }
            else{
                tie++;
            }
            
            for(int i=1;i<=6;i++){
                cellPlays1[i]+=plays1[i];
            }
            for(int i=1;i<=6;i++){
                cellPlays2[i]+=plays2[i];
            }
        }
        
        cout<<"Player One Total Plays: "<<endl;
        for(int i=1;i<=6;i++){
            cout<<"Cell "<<i<<" Plays: "<<cellPlays1[i]<<endl;
        }
        cout<<"Player Two Total Plays: "<<endl;
        for(int i=1;i<=6;i++){
            cout<<"Cell "<<i<<" Plays: "<<cellPlays2[i]<<endl;
        }
        cout<<"Player 1    Wins: "<<plr1Win<<endl;
        cout<<"Player 2    Wins: "<<plr2Win<<endl;
        cout<<"Ties            : "<<tie<<endl;
    }
    //Display the results
    
    return 0;
}