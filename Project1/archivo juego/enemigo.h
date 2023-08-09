#ifndef ENEMIGO_H  
#define ENEMIGO_H
#include <SFML/Graphics.hpp>
#include "textura.h"
#include "colisiones.h"
#include "obstaculo.h"
#include "fondo.h"
using namespace sf;
class Enemy;
class Player;
class Obstaculo;
class Enemy {
    float ancho, alto;
    float posX, posY;
    RectangleShape enemigo;
    Textura personajeT;
    Sprite personajeS;
    float ajustexsprite;
    float direccion;
    float velocidadX;
    float velocidadY;
    float recorrido;
    bool enAire;
    float vgravedad;
    float velocidad;
    bool hayColision;
public:
    Enemy();
    Enemy(Textura& rec, float x, float y, float velx, float vely);
    float getPosX();
    float getPosY();
    float getAlto();
    float getAncho();
    void mover(RectangleShape&);
    Sprite getSprite();
    void establecerSprite(float,float);
    void moverIzq(float dt,vector<Obstaculo>* o1, Player* p1, Obstaculo piso, Fondo &ff);
    void moverDer(float dt,vector<Obstaculo>* o1, Player* p1, Obstaculo piso, Fondo &ff);
    void help_move(float x,float arregloxsprite);
    void mover(float dt,vector<Obstaculo>* o1, Player* p1, Obstaculo piso, Fondo &ff);
    void perseguir(float dt,vector<Obstaculo>* o1, Player* p1, Obstaculo piso, Fondo &ff);
    };
    

#endif