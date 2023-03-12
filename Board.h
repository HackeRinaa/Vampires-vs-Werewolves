#pragma once
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "MyClasses.h"
 using namespace std;


class  Board {
    private :
        char  * * board;
        short int height, width;
        short int vampire , werewolf; 
        Creature * TeamV, *TeamW;
        Avatar  Player;
        bool Time;
        int potion;
    public :
        friend class Entity;
        friend class Avatar;
        friend class Creature;
        Creature * Create_Creature(int,Creature *,int,int ) ;
        void  Create_Avatar(int,int,char);
        Board(int,int,char);
        ~Board();
        int End();
        void ShowBoard();
        void GetInfo ();
        void Change_Coord();
        void Check_Coord();
        int Return_CoordEnemyW(int,int);
        int Return_CoordEnemyV(int,int);
        void Update ();
        void ChangeTime();
} ;