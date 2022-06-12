/* 
 * File:   Player.h
 * Author: Paul
 *
 * Created on June 8, 2022, 8:33 PM
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
using namespace std;

class Player{
    private:
        string player[2];
        int userID[2];
    public:
        void setPlayer(string s, int n){
            player[n-1]=s;
        }
        
        string getPlayer(int n){
            return player[n-1];
        }
        
        void setUserID(string s,int plrnum){
            int p=31;
            int m=1e9+7;
            int hash=0;
            int n=s.length();
            long pow=1;
            
            for(int i=0;i<n;i++){
                hash=(hash+(s[i]-'a'+1)*pow)%m;
                pow=(pow*p)%m;
            }
            
            userID[plrnum-1]=hash;
        }
        
        int getUserID(int n){
            return userID[n-1];
        }
};

#endif /* PLAYER_H */

