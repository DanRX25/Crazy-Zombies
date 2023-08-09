#include "obstaculo.h"

Obstaculo::Obstaculo() {
        
    }
Obstaculo::Obstaculo(Textura& rec, float x, float y) {
        
        this->obstaculoT=rec;
        this->obstaculoS=obstaculoT.getSprite(0,1.0f);
        
        alto = rec.getAltura(); 
        ancho = rec.getAncho()-20;
        falsoPosx=x;
        posX = x;
        posY = y;
    }
float Obstaculo::getPosX() { return posX; }
float Obstaculo::getPosY() { return posY; }
float Obstaculo::getAlto() { return alto; }
float Obstaculo::getAncho() { return ancho; }

Sprite Obstaculo::getSprite(float dt){
   this-> obstaculoS.setPosition(posX, posY);
    
    return obstaculoS;
}

