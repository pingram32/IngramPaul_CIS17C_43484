/* 
 * File:   main.cpp
 * Author: Paul Ingram
 * Created on June 6, 2022, 7:51 PM
 * Purpose:  Mancala for project 2
 */

//System Libraries
#include <iostream>   //Input/Output Library
#include "GameBoard.h"
using namespace std;  //STD Name-space where Library is compiled

//User Libraries

//Global Constants not Variables
//Math/Physics/Science/Conversions/Dimensions

//Function Prototypes

//Code Begins Execution Here with function main
int main(int argc, char** argv) {
    //Set random number seed once here
    
    //Declare variables here
    GameBoard mancala;
    //Initialize variables here
   
    //Map inputs to outputs here, i.e. the process
    while(mancala.gameOver()){
        if(mancala.getSide()==1){
            mancala.plr1Turn();
        }
        else{
            mancala.plr2Turn();
        }
    }
    //Display the results
    
    return 0;
}