#pragma once
#include "player.h"
class JuegoControlador{
    Player* ps;
    Player* p2;
    vector<Obstaculo>* o1;
    Obstaculo piso;
    Enemy e1;
    Fondo* f1;
    float dt;
    bool nplayer;


    public:
        JuegoControlador();
        JuegoControlador(bool ,Player* player1,vector<Obstaculo>* o1,Enemy e1, Obstaculo piso,Fondo* ff);
        void controlarInput(float);
};