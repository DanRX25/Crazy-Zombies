#ifndef TEXTURA_H  
#define TEXTURA_H
#pragma once
#include <SFML/Graphics.hpp>

class Textura
{
private:
    sf::Texture textura;
    int nColumnas;
    int nFilas;
    float tiempoTranscurrido;
    float tiempoXframe;
    int ancho;
    int alto;
    int actualFrameX;
    int actualFrameY;
    sf::Sprite sprite;
public:
    Textura();
    Textura(std::string ruta, int nCol, int nFil);
    ~Textura();
    sf::Sprite getSprite(float dt,float);
    void cambioSprite(float dt);
    float getAncho();
    float getAltura();
};

#endif