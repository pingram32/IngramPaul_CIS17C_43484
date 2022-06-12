/* 
 * File:   BotGame.h
 * Author: Paul
 *
 * Created on June 11, 2022, 4:55 PM
 */

#ifndef BOTGAME_H
#define BOTGAME_H
#include "Simulate.h"
class BotGame{
    private:
        vector<int> plr1Hist;
        vector<int> plr2Hist;
        vector<vector<int>> board;
        vector<int> cells;
        Player player;
        int side=1;
    public:
        BotGame(){
            string temp="AAA";
            cout<<"Enter Player 1 Name: ";
            cin>>temp;
            player.setPlayer(temp, 1);
            player.setUserID(temp, 1);
            
            temp="AAA";
            for(int i=0;i<3;i++){
                temp[i]+=rand()%26;
            }
            player.setPlayer(temp, 2);
            player.setUserID(temp, 2);
            
            setCells();
            setBoard();
            
            while(gameOver()){
                if(getSide()==1){
                    plr1Turn();
                }
                else{
                    plr2Turn();
                }
            }
            
            for(int i=0;i<6;i++){
                cells[6]+=cells[i];
            }
            for(int i=7;i<13;i++){
                cells[13]+=cells[i];
            }
            
            if(cells[6]>cells[13]){
                cout<<"Player 1 Wins!"<<endl;
            }
            else if(cells[6]<cells[13]){
                cout<<"Player 2 Wins!"<<endl;
            }
            else{
                cout<<"It's a Tie!"<<endl;
            }
        }
        
        int returnWin(){
            if(cells[6]>cells[13]){
                return 1;
            }
            else if(cells[13]>cells[6]){
                return 2;
            }
            else 
                return 3;
        }
        
        void showBoard(){
            cout<<"|"<<cells[5]<<"|"<<cells[4]<<"|"<<cells[3]<<"|"<<cells[2]<<"|"
                <<cells[1]<<"|"<<cells[0]<<"|"<<endl;
            cout<<cells[6]<<"==========="<<cells[13]<<endl;
            cout<<"|"<<cells[7]<<"|"<<cells[8]<<"|"<<cells[9]<<"|"<<cells[10]<<"|"
                <<cells[11]<<"|"<<cells[12]<<"|"<<endl;
        }
        
        void plr1Turn(){
            showBoard();
            int choice;
            cout<<"The Recommended Cell: "<<recMove1()<<endl<<endl;
            cin>>choice;
            plr1Hist.push_back(choice);
            
            int marbles=cells[6-choice];
            int cell=board[6-choice][0];
            cells[6-choice]=0;
            cell=recUpdate1(marbles, cell);
            
            if(cell==6){
                cout<<"You Have Earned Another Turn"<<endl;
                side=1;
            }
            else if(cell>=0 && cell<=5 && cells[cell]==1 
                    && cells[board[cells[cell]][1]]){
                cout<<"Capture!"<<endl;
                cells[6]+=cells[board[cell][1]]+1;
                cells[board[cell][1]]=0;
                cells[cell]=0;
                side=2;
            }
            else side=2;
        }
        
        int minIndex(vector<array<int,2>> &v, int i, int j){
            if(i==j){
                return i;
            }
            int k=minIndex(v, i+1, j);
            return(v[i][1]<v[k][1])? i:k;
        }
        
        void selectionSort(vector<array<int,2>> &v, int n, int index=0){
            if(index==n){
                return;
            }
            int k=minIndex(v, index, n-1);
            if(k!=index){
                swap(v[k], v[index]);
            }
            selectionSort(v, n, index+1);
        }
        
        int recMove1(){
            vector<array<int,2>> v;
            for(int i=0;i<6;i++){
                v.push_back({i, cells[i]});
            }
            selectionSort(v, v.size());
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
        
        void plr2Turn(){
            showBoard();
            int choice=rand()%6+1;
            int marbles=cells[6+choice];
            int cell=board[6+choice][0];
            while(!cells[cell]){
                choice=rand()%6+1;
            }
            cout<<"Bot Selected Cell "<<choice<<endl<<endl;
            cell=board[6+choice][0];
            marbles=cells[6+choice];
            cells[6+choice]=0;
            cell=recUpdate2(marbles, cell);
            if(cell==-1){
                cout<<"You Have Earned Another Turn"<<endl;
                side=2;
            }
            else if(cell>=7 && cell<=12 && cells[cell]==1 
                    && cells[board[cells[cell]][1]]){
                cout<<"Capture!"<<endl;
                cells[13]+=cells[board[cell][1]]+1;
                cells[board[cell][1]]=0;
                cells[cell]=0;
                side=1;
            }
            else side=1;
        }
        
        int recMove2(){
            vector<array<int,2>> v;
            for(int i=7;i<13;i++){
                v.push_back({i, cells[i]});
            }
            selectionSort(v, v.size());
            int recMove=0;
            for(int i=0;i<6;i++){
                if(v[i][1]==1 && v[i][0]==12){
                    recMove=6;
                }
                else if(!recMove && 13-v[i][0]==v[i][1]){
                    recMove=v[i][0]-6;
                }
                else if(!recMove && v[i][1]==1 && cells[board[v[i][0]][0]]==0
                        && cells[board[v[i][0]][1]]){
                    recMove=v[i][0]-6;
                }
            }
            if(!recMove){
                recMove=6;
                while(!cells[6+recMove]){
                    recMove--;
                }
            }
            return recMove;
        }
        
        void MergeSort(vector<int> &v, int s, int e){
            if(s<e){
                int m=(s+e)/2;
                MergeSort(v, s, m);
                MergeSort(v, m+1, e);
                MergeSortedIntervals(v, s, m, e);
            }
        }
        
        void MergeSortedIntervals(vector<int> &v, int s, int m, int e){
            vector<int> temp;
            int i, j;
            i=s;
            j=m+1;
            
            while(i<=m && j<=e){
                if(v[i]<=v[j]){
                    temp.push_back(v[i]);
                    i++;
                }
                else{
                    temp.push_back(v[j]);
                    j++;
                }
            }
            
            while(i<=m){
                temp.push_back(v[i]);
                i++;
            }
            
            while(j<=e){
                temp.push_back(v[j]);
                j++;
            }
            
            for(int i=s;i<=e;i++){
                v[i]=temp[i-s];
            }
        }
        
        int totalPlays(){
            return plr1Hist.size()+plr2Hist.size();
        }
        
        map<int, int> Plr1Hist(){
            map<int, int> plr1Freq;
            MergeSort(plr1Hist, 0, plr1Hist.size()-1);
            
            for(int i=0;i<plr1Hist.size();i++){
                plr1Freq[plr1Hist[i]]++;
            }
            
            return plr1Freq;
        }
        
        map<int, int> Plr2Hist(){
            map<int, int> plr2Freq;
            MergeSort(plr2Hist, 0, plr2Hist.size()-1);
            
            for(int i=0;i<plr2Hist.size();i++){
                plr2Freq[plr2Hist[i]]++;
            }
            
            return plr2Freq;
        }
        
        bool gameOver(){
            int top=0, bottom=0;
            for(int i=0;i<6;i++){
                top+=cells[i];
            }
            for(int i=7;i<13;i++){
                bottom+=cells[i];
            }
            if( top==0 || bottom==0){
                return false;
            }
            else{
                return true;
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

#endif /* BOTGAME_H */

