#pragma once 
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "Board.h"

using namespace std;

class Board;

class Entity {
    protected :
        int x,y;
        int h,w;
    public :
        Entity ();
        Entity (int,int,int,int);
        void virtual return_coordinates ();
        int return_x();
        int return_y();
        void change_coordinates(int,int);

};


class Avatar:public Entity{
    private:
    //Player has to choose a team
    //1 Vampires,0 Warewolfs
    //1 Day,0 Night
    int team;
    unsigned short int potion;

    public:
    Avatar(int,int,int,int,char);
    Avatar() {};
    //void return_coordinates();
    void move (Board * );
    void Heal_Team(Board *);
    friend class Creature;

};

class Creature:public Entity{
    private:
    unsigned short int power;
    unsigned short int health;
    unsigned short int defence;
    public:
    Creature () {};
    Creature(int,int,int,int);
    void MoveW(Board *);
    void MoveV(Board *);
    int CheckCoordsV(Board *,int,int);
    int CheckCoordsW(Board *,int,int);
    void AttackW(Board * ,int,int);
    void AttackV(Board *,int,int);
    void HealV(Board * ,int,int);
    void HealW(Board * ,int,int);
    void Heal_From_Avatar();
};

