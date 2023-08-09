#ifndef PLAYER_H
#define PLAYER_H
//#include <SFML/Graphics.hpp>
#include <time.h>
//#include <type_traits>
//#include <iostream>
#include "colisiones.h"
#include "fondo.h"
//#include "enemigo.h"
#include "textura.h"
#include "arma.h"
#include "obstaculo.h"
using namespace sf;
using namespace std;


class Enemy;
class Player;
class Player {
protected:

    float velocidadX;
    float velocidadY;
    float velocidad;
    float vgravedad;
    float alto, ancho;
    float posX, posY;
    float recorrido;
    float direccion;
    bool enAire;
    Keyboard::Key derecha, izquierda, arriba, disparo;
    Textura personajeT;
    sf::Sprite personajeS;
    Arma arma;


    float ajustexsprite;
    bool hayColision;
public:
    Player() {
        alto = 0; ancho = 0;
        posX = 0; posY = 0; velocidadX = 0; recorrido = 0; direccion = 0;
        personajeS.setPosition(posX, posY);
    }
    Player(Textura& rec, float x, float y, float veloX, float veloY, Keyboard::Key right, Keyboard::Key left, Keyboard::Key up, sf::Keyboard::Key shoot) {
        personajeT = rec;
        personajeS = personajeT.getSprite(0, 1.0f);
        alto = rec.getAltura();
        ancho = rec.getAncho();
        posX = x;
        posY = y;
        recorrido = x;
        direccion = 1;
        derecha = right;
        izquierda = left;
        arriba = up;
        disparo = shoot;
        personajeS.setPosition(posX, posY);
        velocidadX = veloX;
        velocidadY = veloY;
        vgravedad = 450.0f;
        enAire = true;
        velocidad = 0;
        ajustexsprite = 0;
        hayColision = false;
    }
    ~Player() {
        velocidad = 0;
        alto = ancho = posX = posY = recorrido = 0;
    }
    float getPosX() { return posX; }
    float getPosY() { return posY; }
    float getAlto() { return alto; }
    float getAncho() { return ancho; }
    float getRecorrido() { return recorrido; }
    int getdireccion() { return direccion; }
    void help_move(float, float);
    void mover(float, vector<Obstaculo>* o1, Obstaculo, Fondo&);
    void salto() {
        this->personajeS.setPosition(posX, posY);
    }
    Sprite getSprite() {
        return personajeS;
    }
    void establecerSprite(float, float);
    Arma& getArma();
    void disparar();
    void moverDer(float, vector<Obstaculo>* o1, Enemy, Obstaculo, Fondo&);
    void moverIzq(float, vector<Obstaculo>* o1, Enemy, Obstaculo, Fondo&);
    void saltar(float, vector<Obstaculo>* o1, Enemy, Obstaculo, Fondo&);
    std::vector<Proyectil> getProyects() { return arma.getProyects(); }
    void borrarProyectil(int index) { arma.borrarProyectil(index); }
};

#endif

