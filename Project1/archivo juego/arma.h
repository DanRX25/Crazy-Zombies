#ifndef ARMA_H  
#define ARMA_H
#pragma once
#include "Proyectil.h"
#include <iostream>
class Arma {
public:
    Arma();
    void disparar(sf::Vector2f position, bool dir);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void borrarProyectil(int index) { 
        proyectiles.erase(proyectiles.begin() + index); 
        sentido_proyectiles.erase(sentido_proyectiles.begin() + index);
    }
    std::vector<Proyectil> getProyects() { return proyectiles; }

private:
    std::vector<Proyectil> proyectiles;
    std::vector<bool> sentido_proyectiles;
    float velocidad;
    int intervalo_disparo;
    bool disparo_listo;
};
#endif
