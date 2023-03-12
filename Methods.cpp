#include <iostream> 
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <cstdio>
#include "Board.h"
#include "MyClasses.h"

using namespace std;



Entity :: Entity () {
        //cout << "Created Team\n";
}
Entity :: Entity (int xx,int yy,int height,int width ): x(xx), y(yy) , h(height) , w(width) {
        //cout << "Class Entity constructor : OK\n";
}


void  Entity ::  return_coordinates () {
    cout << "Entinty is in " << this->x << " " << this->y << endl;
}
int Entity :: return_x(){
    return this->x;
}
int Entity :: return_y(){
    return this->y;
}
void Entity :: change_coordinates(int x,int y){
    this->x=x;
    this->y=y;
}


Creature :: Creature (int x,int y ,int height,int width ) : Entity(x,y,height,width),power(rand()%3),health(rand()%3), defence(rand()%3) {
    //cout << "Class Creature created:\n";
}

void Creature :: MoveV (Board * b ) {
    int temp_y,temp_x;

    int mod = rand()%8;
                switch (mod)
                {
                case 0:
                    temp_y = this -> y - 1;
                    temp_x = this ->x;
                    break;
                case 1:
                    temp_y = this -> y - 1;
                    temp_x = this -> x + 1;
                    break;
                case 2:
                    temp_x = this -> x + 1;
                    temp_y = this->y;
                    break;
                case 3:
                    temp_x = this -> x + 1;
                    temp_y  = this -> y + 1;
                    break;
                case 4:
                    temp_y = this -> y + 1;
                    temp_x = this ->x;
                    break;
                   
                case 5:
                    temp_x = this -> x - 1;
                    temp_y  = this -> y + 1;
                    break;
                case 6:
                    temp_x = this -> x - 1;
                    temp_y =this ->y;
                    break;
                case 7:
                    temp_x = this -> x - 1;
                    temp_y  = this -> y - 1;
                    break;
                default:
                    break;
                }

            if(temp_x > 0 && temp_x < b->width && temp_y > 0 && temp_y < b->height) {
                if(b -> board[temp_x][temp_y]=='-'){
                    this -> x = temp_x;
                    this -> y = temp_y;
                }            
            }

}

void Creature :: MoveW (Board * b ) {
    int temp_x,temp_y;
    int mod=rand()%4;
        switch (mod)
        {
            case 0:
                    temp_y  = this -> y - 1;
                    temp_x = this->x;
                    break;
            case 1:
                    temp_x = this -> x + 1;
                    temp_y = this->y;
                    break;
            case 2:
                    temp_y  = this -> y + 1;
                    temp_x = this->x;
                    break;
            case 3:
                    temp_x = this -> x - 1;
                    temp_y = this->y;
                    break;
            default:
                    break;
        }

        if(temp_x > 0 && temp_x < b->width && temp_y > 0 && temp_y < b->height){
            if(b -> board[temp_x][temp_y]=='-'){
                this -> x = temp_x;
                this -> y = temp_y;
            } 
        }
}

void Creature :: AttackV (Board * b,int v,int w) {
    if (b->TeamW[w].health <= this->health) {
        b->TeamW[w].health=b->TeamW[w].health-1;
        cout << "Attack from  vampire : " << v << " to werewolf : " << w <<  endl;
    }
    else ;
    if (b->TeamW[w].health==0) {
        b->werewolf=b->werewolf-1;
        int x=b->TeamW[w].return_x();
        int y=b->TeamW[w].return_y();
        b->board[x][y]='-';
    }
}

void Creature :: AttackW (Board * b,int w,int v ) {
    if (b->TeamV[v].health <= this->health) {
        b->TeamV[v].health=b->TeamV[v].health-1;
        cout << "Attack from werewolf : " << w << " to vampire : " << v <<endl;
    }   
    else ;
    if (b->TeamV[v].health==0) {
        b->vampire=b->vampire-1;
        int x=b->TeamV[v].return_x();
        int y=b->TeamV[v].return_y();
        b->board[x][y]='-';
    }
}


int Creature :: CheckCoordsV (Board * b,int x,int y) {
    if(x+1<b->height && x-1>0 && y-1>0 && y+1<b->width ) {
        if (b->board[x+1][y]=='W'|| b->board[x-1][y]=='W'||b->board[x][y+1]=='W'|| b->board[x][y-1]=='W') {
            return 1;
        }
        else return 0;
    }
    else return 0;
}

int Creature :: CheckCoordsW (Board * b,int x,int y) {
    if(x+1<b->height && x-1>0 && y-1>0 && y+1<b->width ) {
        if (b->board[x+1][y]=='V'|| b->board[x-1][y]=='V' || b->board[x][y-1]=='V' || b->board[x][y+1]=='V') {
            return 1;
        }
        else return 0;
    }
    else return 0;
}

void Creature :: HealV(Board * b,int v1,int v2 ){
     if (b->TeamV[v2].health <= this->health && b->Time==1) {
        b->TeamV[v2].health=b->TeamV[v2].health+1;
        this->health=this->health-1;
        cout << "Heal from vampire : " << v1 << " to vampire : " << v2 <<endl;
    }   
    else ;
    if (b->TeamV[v1].health==0) {
        b->vampire=b->vampire-1;
        int x=b->TeamV[v1].return_x();
        int y=b->TeamV[v1].return_y();
        b->board[x][y]='-';
        b->TeamV[v1].x=-1;
        b->TeamV[v1].y=-1;
    }
    else;
}

void Creature :: HealW(Board * b,int w1,int w2 ){
     if (b->TeamV[w2].health <= this->health && b->Time==0) {
        b->TeamV[w2].health=b->TeamV[w2].health+1;
        this->health=this->health-1;
        cout << "Heal from werewolf : " << w1 << " to werewolf : " << w2 <<endl;
    }   
    else ;
    if (b->TeamW[w1].health==0) {
        b->werewolf=b->werewolf-1;
        int x=b->TeamW[w1].return_x();
        int y=b->TeamW[w1].return_y();
        b->board[x][y]='-';
        b->TeamW[w1].x=-1;
        b->TeamW[w2].y=-1;
    }
    else;
}

void Creature :: Heal_From_Avatar() {
    this->health=2;
}


Avatar :: Avatar(int x,int y,int h,int w,char team):Entity(x,y,h,w),potion(0),team(team=='V' ? 1 : 0) {
    //cout << "Class Avatar constructor : OK\n";
}
void Avatar::move (Board * b ) {
    int c;
    int oldx=this->return_x();
    int oldy=this->return_y();
    c=getchar();
    if (c=='\n') {
        c=getchar();
    }

    if(c=='d' && (b->board[oldx][oldy+1]=='-' || b->board[oldx][oldy+1])){
        this->change_coordinates(oldx,oldy+1);
        if (b->board[oldx][oldy+1]!='~' || b->board[oldx][oldy+1]!='*') {
            if (b->board[oldx][oldy+1]=='$') {
                cout << "Potion taken !\n ";
            }
            b->board[oldx][oldy]='-';
            b->board[oldx][oldy+1]='A';
        }
       
    }

    if(c=='a' && (b->board[oldx][oldy-1]=='-' || b->board[oldx][oldy-1]=='$') ){
        this->change_coordinates(oldx,oldy-1);
        if (b->board[oldx][oldy-1]!='~' || b->board[oldx][oldy-1]!='*') {
            if (b->board[oldx][oldy-1]=='$') {
                cout << "Potion taken !\n ";
            }
            b->board[oldx][oldy]='-';
            b->board[oldx][oldy-1]='A';
        }
       
    }

    if(c=='w' &&( b->board[oldx-1][oldy]=='-'|| b->board[oldx][oldy+1])){
        this->change_coordinates(oldx-1,oldy);
        if (b->board[oldx-1][oldy]!='~' || b->board[oldx-1][oldy]!='*') {
            if (b->board[oldx-1][oldy]=='$') {
                cout << "Potion taken !\n ";
            }
            b->board[oldx][oldy]='-';
            b->board[oldx-1][oldy]='A';
        }
       
    }

    if(c=='s' &&( b->board[oldx+1][oldy]=='-' || b->board[oldx][oldy+1])){
        this->change_coordinates(oldx+1,oldy);
        if (b->board[oldx+1][oldy]!='~' || b->board[oldx+1][oldy]!='*') {
            if (b->board[oldx+1][oldy]=='$') {
                cout << "Potion taken !\n ";
            }
            b->board[oldx][oldy]='-';
            b->board[oldx+1][oldy]='A';
        }
    }
}

void Avatar :: Heal_Team(Board * b){
    if(team==1){
        for(int i=0;i<b->vampire;i++){
            b->TeamV[i].Heal_From_Avatar();
        }
    }
    else{
        for(int i=0;i<b->werewolf;i++){
            b->TeamW[i].Heal_From_Avatar();
        }
    }
}


 Board :: Board( int w ,  int h ,char team) :height(h) , width(w) , vampire((h*w)/15) , werewolf((h*w)/15) , potion(1) {

            //cout << "Constructor activated \n";
            board = new char *[width];
            for(int i = 0; i < width ; i++) board[i] = new char[height];
            for (int i =0 ; i< width ; i ++  ) {
                for (int j =0; j< height; j++) {
                    board[i][j]='-';
                }
            }
            int numberw=0;
            int numberv=0;
            int water = rand() % (11*(height*width)/100);
            int trees = rand() % (20*(height*width)/100);
            TeamV= new  Creature [vampire];
            TeamW = new Creature [werewolf];

            for (int i =0 ; i< width ; i ++  ) {
                for (int j =0; j< height; j++) {
                    if (i==0 && numberv<vampire) {
                        board[i][j]='V';
                        TeamV=Create_Creature(numberv,TeamV,i,j);
                        numberv+=1;
                    }
                    else if (i==width-1 && numberw<werewolf) {
                        board[i][j]='W';
                        TeamW=Create_Creature(numberw,TeamW,i,j);
                        numberw+=1;
                    }
                    else if (i==width/2 && j==height/2) {
                        Create_Avatar(i,j,team);
                        board[i][j]='A';
                    }
                    else {
                        board[i][j]='-';
                    }
                }
            }
            srand(time(0));
            while (trees>0) {
                int rnd = rand() % (height*width);
                int x = rnd % height;
                int y = rnd / width;
                if (board[x][y]!='*' && board[x][y]!='V'  && board[x][y]!='W' && board[x][y]!='A') {
                    board[x][y]='*';
                    trees-=1;
                }
            }
            srand(time(0));
            while  (water>0) {
                int rnd = rand() % (height*width);
                int x = rnd % height;
                int y = rnd / width;
                if (board[x][y]!='~' && board[x][y]!='V'  && board[x][y]!='W' && board[x][y]!='*' && board[x][y]!='A') {
                    board[x][y]='~';
                    water-=1;
                }
            }
            int rnd =rand() % (height*width);
            int x = rnd % height;
            int y = rnd / width;
            if (board[x][y]!='~' && board[x][y]!='V'  && board[x][y]!='W' && board[x][y]!='*' && board[x][y]!='A') {
                    board[x][y]='$';
            }
        }

        Board :: ~Board(){
            cout << " \n Game over \n";
            for (int i =0 ; i < this->width; i++) {
                for (int j=0; j < this->height; j++) {
                    delete board[j];
                }
            }
            
        }

        Creature  * Board :: Create_Creature(int index,Creature * Team,int x,int y) {
            Team[index]=Creature(x,y,height,width);
            return Team;
        }
        void   Board :: Create_Avatar(int x,int y,char team){
            Player=Avatar(x,y,height,width,team);
        }
        
        void Board :: ShowBoard() {
            for (int i =0 ; i< height ; i ++  ) {
                for (int j =0; j< height; j++) {
                    cout << board[i][j] << " | ";
                }
                cout <<endl;
                for (int j =0; j< height; j++) {
                    cout << "___";
                }
                cout << endl;
            }
        }

        void Board :: GetInfo () {
            cout << "Playing now we have : " << endl;
            cout << vampire << " Vampires \n";
            cout << werewolf << " Werewolfs \n";
            for (int i =0 ; i < werewolf ; i++) {
                if (TeamW[i].return_x()!=-1) {
                    cout << "Werewolf " << i << " is in  place : ";
                    TeamW[i].return_coordinates();
                }
            }
            for (int i =0 ; i < vampire ; i++) {
                if (TeamV[i].return_x()!=-1) {
                    cout << "Vampire " << i << " is in  place : ";
                    TeamV[i].return_coordinates();
                }
            }
        }
        void Board :: Change_Coord() {
            Player.move(this);
            for (int i=werewolf-1; i>=0;i--) {
                int oldx=TeamW[i].return_x();
                int oldy=TeamW[i].return_y();
                if (oldx<0) {
                    board[oldx][oldy]='-';
                } 
                else{
                    TeamW[i].MoveW(this);
                    int newx=TeamW[i].return_x();
                    int newy=TeamW[i].return_y();
                    board[oldx][oldy]='-';
                    board[newx][newy]='W';
                }
            }
            for (int i=vampire-1; i>=0;i--) {
                int oldx=TeamV[i].return_x();
                int oldy=TeamV[i].return_y();
                if (oldx<0) {
                    board[oldx][oldy]='-';
                }
                else {
                    TeamV[i].MoveV(this);
                    int newx=TeamV[i].return_x();
                    int newy=TeamV[i].return_y();
                    board[oldx][oldy]='-';
                    board[newx][newy]='V';
                }
            }

        }

    int Board :: End() {
        if (vampire==0  || werewolf==0) {
            return 0;
        }
        else return 1;
    }

    void Board :: Check_Coord() {
        for (int i=0;i<werewolf;i++) {
                int x=TeamW[i].return_x();
                int y=TeamW[i].return_y();
                if (TeamW[i].CheckCoordsW(this,x,y)) {
                    TeamW[i].AttackW(this,i,this->Return_CoordEnemyW(x,y));
                }
                if (TeamW[i].CheckCoordsV(this,x,y) && vampire<werewolf) {
                    TeamW[i].HealW(this,i,this->Return_CoordEnemyV(x,y));
                }
        }
        for (int i=0;i<vampire;i++) {
            int x=TeamV[i].return_x();
            int y=TeamV[i].return_y();
            if (TeamV[i].CheckCoordsV(this,x,y)) {
                    TeamV[i].AttackV(this,i,this->Return_CoordEnemyV(x,y));
            }
            if (TeamV[i].CheckCoordsW(this,x,y) && werewolf < vampire) {
                    TeamV[i].HealV(this,i,this->Return_CoordEnemyW(x,y));
            }
        }
    }
    
    int Board :: Return_CoordEnemyV(int x,int y) {
        if (board[x+1][y]=='W' ) {
            for(int i=0;i<werewolf;i++) {
                int xx=TeamW[i].return_x();
                int yy=TeamW[i].return_y();
                if (xx==x+1 && yy==y) {
                    return i;
                }
                else {
                    continue;
                }
            }
        }
        else if (board[x-1][y]=='W' ) {
            for(int i=0;i<werewolf;i++) {
                int xx=TeamW[i].return_x();
                int yy=TeamW[i].return_y();
                if (xx==x-1 && yy==y) {
                    return i;
                }
                else {
                    continue;
                }
            }
        }
        else if (board[x][y+1]=='W' ) {
            for(int i=0;i<werewolf;i++) {
                int xx=TeamW[i].return_x();
                int yy=TeamW[i].return_y();
                if (xx==x && yy==y+1) {
                    return i;
                }
                else {
                    continue;
                }
            }
        }
        else if (board[x][y-1]=='W' ) {
            for(int i=0;i<werewolf;i++) {
                int xx=TeamW[i].return_x();
                int yy=TeamW[i].return_y();
                if (xx==x && yy==y-1) {
                    return i;
                }
                else {
                    continue;
                }
            }
        }
        else return -1;
    }

    int Board :: Return_CoordEnemyW(int x,int y) {
        if (board[x+1][y]=='V' ) {
            for(int i=0;i<vampire;i++) {
                int xx=TeamV[i].return_x();
                int yy=TeamV[i].return_y();
                if (xx==x+1 && yy==y) {
                    return i;
                }
                else {
                    continue;
                }
            }
        }
        else if (board[x-1][y]=='V' ) {
            for(int i=0;i<vampire;i++) {
                int xx=TeamV[i].return_x();
                int yy=TeamV[i].return_y();
                if (xx==x-1 && yy==y) {
                    return i;
                }
                else {
                    continue;
                }
            }
        }
        else if (board[x][y+1]=='V' ) {
            for(int i=0;i<vampire;i++) {
                int xx=TeamV[i].return_x();
                int yy=TeamV[i].return_y();
                if (xx==x && yy==y+1) {
                    return i;
                }
                else {
                    continue;
                }
            }
        }
        else if (board[x][y-1]=='V' ) {
            for(int i=0;i<vampire;i++) {
                int xx=TeamV[i].return_x();
                int yy=TeamV[i].return_y();
                if (xx==x && yy==y-1) {
                    return i;
                }
                else {
                    continue;
                }
            }
        }
        else return -1;
    }

        void Board :: Update () {
            
            this->Change_Coord();
            cout << endl;
            this->ShowBoard();
            cout<< endl;
            this->Check_Coord();

            this->ShowBoard();
        }

        void Board :: ChangeTime() {
            if (this->Time==0) {
                this ->Time =1;
                cout << "\n A new day is dawing \n ";
            }
            else {
                this->Time=0;
                cout << "\n Into the dark \n";
            }
        }

