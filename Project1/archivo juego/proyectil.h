#ifndef PROYECTIL_H  
#define PROYECTIL_H
#pragma once
#include <SFML/Graphics.hpp>

class Proyectil {
public:
    Proyectil(sf::Vector2f , float, float);
    void update(float );
    void draw(sf::RenderWindow&);
    float getTiempoVidaActual();
    void setTiempoVidaActual(float);
    float getTiempoVidaMaximo();
    float getPosX();
    float getPosY();
    float getAncho();
    float getAlto();

private:
    sf::CircleShape forma;
    sf::Vector2f velocity;
    float tiempoDeVidaMaximo;
    float tiempoDeVidaActual;
    float ancho;
    float alto;
};
#endif