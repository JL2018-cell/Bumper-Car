#include <clocale>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include "car.h"
#include "screen.h"
#include <math.h>
#include <fstream>

using namespace std;

//input the number of round, difficulty level and progress array, no output
//to update the number of round, difficulty level and porgress, i.e. to log the saved game
void loggame(int &round, string & diff,int * progress){
    ifstream fin;
    fin.open("Temp.txt");
    if(!fin.fail()){
        string rec_round;
        getline(fin,rec_round);//the first line of "Temp.txt" records the progress of the game saved, 1 denotes WIN, 0 denotes LOSE         
        round = rec_round.length();
        for(int i=0;i<round;i++){
            progress[i]=stoi(rec_round[i]); // update the progress array
        }

        string diffi;        
        fin>>diffi;// the second line of "Temp.txt" records the difficulty level of the saved game;
        diff=diffi; 
        fin.close();               

    }

}

int main(){
    car p, t;
    screen bscreen;
    double direction;// starting direction of the p 
    double v0;// primary speed of the p
    double v1;// the speed of p before the moment of collision
    double v2,v3;// v2 denotes the speed of p after collision, v3 denotes the speed of t after collision
    string diff;// the difficulty level
    int * progress = new int[5];// record the progress of each round of game, 1 denotes WIN, 0 denotes LOSE
    int round;// the number of rounds that have been played

    char c=1; //the pointer whether the game session will restart(c=1) or not(c=0)
    while(c){
    int line =16;      
    ifstream fin;
    fin.open("Temp.txt");
    string command1;
    if(!fin.fail()){
        string rec_round;
        getline(fin,rec_round);
        if(rec_round.empty()){ //"Temp.txt" is empty means there is no saved game
            bscreen.gotoxy(83,line++);
            cout<<"Enter \"New\" to start a new game: ";           
            fflush(stdout);
            cin>>command1;
        }
        else{
            bscreen.gotoxy(83,line++);
            cout<<"Enter \"Log\" to log the saved game or enter \"New\" to start a new game: ";
            fflush(stdout);
            cin>>command1;
        }
        fin.close();        
    }

    while(command1 != "Log" && command1 != "New"){ //if the player input neither "Log" nor "New", the player needs to input again
        bscreen.gotoxy(83,line++);
        cout<<"Invalid input, please input again: ";
        fflush(stdout);
        cin>>command1;
    }

    if(commmand1=="Log"){  
        loggame(round,diff,& progress);
        p.primary_position();
        t.primary_position();
        p.samepos(t);
    }
    else if(command1=="New"){
        p.primary_position();
        t.primary_position();
        p.samepos(t);
        round = 0;
        bscreen.gotoxy(83,line++);
        cout<<"Enter the difficulty level: \"Easy\"/\"Medium\"/\"Hard\": ";
        fflush(stdout);
        cin>>diff;
        while(diff!="Easy" && diff!="Medium" && diff!="Hard"){
            bscreen.gotoxy(83,line++);
            cout<<"Invalid input, please input again: ";
            fflush(stdout);
            cin>>diff;
        }             

    }
    
    

    p.getdiff(diff);
    p.getu();   

    
    for(;round<5;round++){ //5 rounds at most
        bscreen.showrule();
        bscreen.arena();
        bscreen.showcar_p(p);
        bscreen.showcar_t(t);
        
        bscreen.gotoxy(83,line++);
        cout<<"Enter the direction: ";
        fflush(stdout);        
        cin>>direction;
        while(direction == -0 || direction <=-180 || direction >180){
            bscreen.gotoxy(83,line++);
            cout<<"Invaild input, please input again: ";
            fflush(stdout);
            cin>>direction;
        }
        
        bscreen.gotoxy(83,line++);
        cout<<"Enter the primary speed: ";
        fflush(stdout);
        cin>>v0;
        while(v0 < 1 || v0 > 15){
            bscreen.gotoxy(83,line++);
            cout<<"Invaild input, please input again: ";
            fflush(stdout);
            cin>>v0;
        }

        p.getdirec(direction); //update the diretion
        p.getv0(v0); //update the primary speed
        p.distance(t); //update d1
        p.dist_boundary(t); //update d2


        if(diff=="Easy"){
            if(p.checkdirec(t)){ // if the direction is right, wins this round for "Easy" mode              
                bscreen.gotoxy(83,line++);
                cout<<"Great collision, you WIN this round!";
                fflush(stdout);
                progress[round]=1; //update the progress array
            }
            else{                
                bscreen.gotoxy(83,line++);
                cout<<"Sorry, you LOSE this round";
                fflush(stdout);
                progress[round]=0;
            }
        }


        if(diff=="Medium"){            
            if(p.checkdirec(t)){
                v1=p.p_speed_beforecol();
                v3=p.t_speed_aftercol();
                if(v1>0 && p.check_t_out()){                
                    bscreen.gotoxy(83,line++);
                    cout<<"Great collision, you WIN this round!";
                    fflush(stdout);
                    progress[round]=1; 
                }
                else{ // if v1==0 or p.check_t_out() == false              
                    bscreen.gotoxy(83,line++);
                    cout<<"Sorry, you LOSE this round";
                    fflush(stdout);
                    progress[round]=0;
                }
            }

            else{ //if the direction is not right                
                bscreen.gotoxy(83,line++);
                cout<<"Sorry, you LOSE this round";
                fflush(stdout);
                progress[round]=0;
            }
        }


        if(diff=="Hard"){
            if(p.checkdirec(t)){
                v1=p.p_speed_beforecol();
                v2=p.p_speed_aftercol();
                v3=p.t_speed_aftercol();
                if(v1>0 && p.check_t_out() && p.check_p_remain()){                    
                    bscreen.gotoxy(83,line++);
                    cout<<"Great collision, you WIN this round!";
                    fflush(stdout);
                    progress[round]=1; 
                }
                else{                   
                    bscreen.gotoxy(83,line++);
                    cout<<"Sorry, you LOSE this round";
                    fflush(stdout);
                    progress[round]=0;
                }

            }
            else{                
                bscreen.gotoxy(83,line++);
                cout<<"Sorry, you LOSE this round";
                fflush(stdout);
                progress[round]=0;
            }
        }


        string command2;        
        bscreen.gotoxy(83,line++);
        cout<<"Do you want to check the progress? Enter \"Y\" or \"N\": ";
        fflush(stdout);
        cin>>command2;
        while(command2 != "Y" && command2 != "N"){
            bscreen.gotoxy(83,line++);
            cout<<"Invalid input, please input again: ";
            fflush(stdout);
            cin>>command2;
        }


        if(command2=="Y"){ //print out of the progress
            for(int i=0;i<=r;i++){                
                bscreen.gotoxy(83,line++);
                cout<<"Round "<<i+1<<" : "<<progress[i];
                fflush(stdout);
            }            
        }


        int n_wins=0, n_loses=0; // denote the number of wins and loses so far, respectively
        for(int i=0;i<=r;i++){
            if(progress[i]==0) n_loses++;
            if(progress[i]==1) n_wins++;
        }

        if(n_wins>=3){ // have wins 3 times or more will be regareded as success;            
            bscreen.gotoxy(83,line++);
            cout<<"You have SUCCEEDED for this session, congratulations!";
            fflush(stdout);
            delete [] progress; //free the dynamic array pointed to by progress
            bscreen.clrscr(); // clear the screen before this session of game terminates
            ofstream fout;
            fout.open("Temp.txt", ios::out | ios::trunc);
            fout.close(); // clear the content of "Temp.txt" if applicable
            break; // stop the loop this to terminate this game session
        }

        if(n_loses>=3){ // have lost 3 times or more will be regarded as failure;            
            bscreen.gotoxy(83,line++);
            cout<<"You have FAILED for this session, try again!";
            fflush(stdout);
            delete [] progress;
            bscreen.clrscr(); 
            ofstream fout;
            fout.open("Temp.txt", ios::out | ios::trunc);
            fout.close();
            break;
        }

        if(round!=4){
            string command3;            
            bscreen.gotoxy(83,line++);
            cout<<"Enter \"S\" to save the progress and leave or enter \"N\" to start a new round: ";
            fflush(stdout);
            cin>>command3;
            while(command3!="S" || command3 != "N"){
                bscreen.gotoxy(83,line++);
                cout<<"Invalid input, please input again: ";
                fflush(stdout);
                cin>>command3;
            }

            if(command3=="S"){
                ofstream fout;
                fout.open("Temp.txt")
                for(int i=0; i<=r;i++){
                    fout<<progress[i]; //save the progress in the 1st line of "Temp.txt"                   
                }
                fout<<endl;
                fout<<diff<<endl; // save the difficulty level at the 2nd line of "Temp.txt"
                fout.close() 
                delete [] progress;
                bscreen.clrscr(); 
                break; //terminates the session     
            }

            if(command3=="N"){
                bscreen.clrscr(); // clear the screen before the next round of game starts
                p.primary_position(); // to generate the random position of p and t again;
                t.primary_position();                             

            }
        }     
  

    }
    string command4;    
    bscreen.gotoxy(83,line++);
    cout<<"Start a new game session? Enter \"Y\" or \"N\": ";    
    fflush(stdout);
    cin>>command4;
    while(command4!="Y" && command4!="N"){
        bscreen.gotoxy(83,line++);
        cout<<"Invalid input, please input again: ";
        fflush(stdout);
        cin>>command4;
    }
    if(command4=="Y") c=1;
    else if(command4=="N") c=0;
    
    }
    return 0;
}

// have not include the plot function yet 
