#ifndef OBSTACULO_H  
#define OBSTACULO_H
//#include "enemigo.h"
//#include "player.h"
#include <SFML/Graphics.hpp>
#include "textura.h"
#include <iostream>
using namespace std;
using namespace sf;

class Obstaculo {
    float ancho, alto;
    float posX, posY;
    float falsoPosx;
    
    Sprite obstaculoS;
    Textura obstaculoT;
public:
    Obstaculo();
    Obstaculo(Textura& rec, float x, float y); 
    float getPosX() ; 
    float getPosY();
    float getAlto() ;
    float getAncho() ;
    Sprite getSprite(float);
    

};

#endif