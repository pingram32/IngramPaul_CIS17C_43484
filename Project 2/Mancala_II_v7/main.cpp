/* 
 * File:   main.cpp
 * Author: Paul Ingram
 * Created on June 9, 2022, 9:05 PM
 * Purpose:  Mancala for project 2
 */

//System Libraries
#include <iostream>   //Input/Output Library
#include "Simulate.h"
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
    cout<<"2) Simulate for statistics"<<endl;
    cin>>choice;
    
    if(choice==1){
        GameBoard mancala;
        while(mancala.gameOver()){
            if(mancala.getSide()==1){
                mancala.plr1Turn();
            }
            else{
                mancala.plr2Turn();
            }
        }
    }
    else{
        Simulate sim;
        while(sim.gameOver()){
            if(sim.getSide()==1){
                sim.plr1Turn();
            }
            else{
                sim.plr2Turn();
            }
        }
        sim.printStats();
    }
    //Display the results
    
    return 0;
}