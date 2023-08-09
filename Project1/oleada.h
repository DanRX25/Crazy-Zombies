#ifndef WAVE_H  
#define WAVE_H
#pragma once
#include "SFML/Graphics.hpp"
#include "archivo juego/enemigo.h"
#include "archivo juego/textura.h"

class Enemy;
class Textura;
class Wave;
class Wave {
private:
    int nivel, actualOleada, cantOleadas;
    Enemy* Enemigos;
public:
    Wave() {
        nivel = 0;
        actualOleada = 0;
        cantOleadas = 0;
        Enemigos = new Enemy[0];
    }
    Wave(int level, Enemy& Enemies) {
        this->nivel = level;
        cantOleadas = nivel + 1;
        actualOleada = 1;
        Enemigos = &Enemies;
    }
    void Start_Wave() {
        delete[] Enemigos;
        Enemigos = new Enemy[20 * nivel];
        for (int i = 0; i < cantOleadas * 20; i++) {
            Textura text_zombie("images/zombie_camina.png", 10, 1);
            Enemy zombie(text_zombie, 100, 0, 50.0f, 100.0f);
            Enemigos[i] = zombie;
        }
    }
    int getOleadaAct() { return actualOleada; }
    int getCantOleadas() { return cantOleadas; }
};

#endif