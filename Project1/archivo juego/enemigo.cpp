#include "enemigo.h"

Enemy::Enemy() {
    posX = 0; posY = 0;
    alto = 0; ancho = 0;
}
Enemy::Enemy(Textura& rec, float x, float y, float velx, float vely) {
    personajeT = rec;
    personajeS = personajeT.getSprite(0,1.0f);
    posX = x; 
    posY = y;
    alto = rec.getAltura(); 
    ancho = rec.getAncho();
    enemigo.setPosition(posX, posY);
    ajustexsprite =0;
    velocidadX = velx;
    velocidadY = vely;
    vgravedad = 450.0f;
    enAire = true;
    velocidad=0;
    recorrido =0;
    hayColision=false;
}
float Enemy::getPosX() { return posX; }
float Enemy::getPosY() { return posY; }
float Enemy::getAlto() { return alto; }
float Enemy::getAncho() { return ancho; }
void Enemy::moverDer(float dt,vector<Obstaculo>* o1, Player* p1, Obstaculo piso, Fondo &ff){
    hayColision=false;
    ajustexsprite=ancho;
        direccion=-1;
    for (vector<Obstaculo>::size_type i=0;i<o1->size();++i) {
        if (colision<Enemy, Obstaculo>(*this, (*o1)[i]) == 1 || colision<Enemy, Player>(*this, *p1) == 1) {
            hayColision = true;
            break;
        }
    }
    if (!hayColision) {
        establecerSprite(dt, direccion);
        this->help_move(1 * dt, ajustexsprite);
        for (vector<Obstaculo>::size_type i=0;i<o1->size();++i) {
            if (colision<Enemy, Obstaculo>(*this, (*o1)[i])) {
                this->help_move(-1 * dt, ajustexsprite);
                break;
            }
        }
        enAire = true;
    }
}
void Enemy::moverIzq(float dt,vector<Obstaculo>* o1, Player* p1, Obstaculo piso, Fondo &ff){
        ajustexsprite=0;
        direccion=1;
        hayColision=false;
        for (vector<Obstaculo>::size_type i=0;i<o1->size();++i) {
        if (colision<Enemy, Obstaculo>(*this, (*o1)[i]) == -1 || colision<Enemy, Player>(*this, *p1) == -1) {
            hayColision = true;
            break;
        }
    }
    if (!hayColision) {
        establecerSprite(dt, direccion);
        this->help_move(-1 * dt, ajustexsprite);
        for (vector<Obstaculo>::size_type i=0;i<o1->size();++i) {
            if (colision<Enemy, Obstaculo>(*this, (*o1)[i])) {
                this->help_move(1 * dt, ajustexsprite);
                break;
            }
        }
        enAire = true;
    }
}
void Enemy::mover(float dt,vector<Obstaculo>* o1, Player* e1, Obstaculo piso, Fondo &ff) {
        if (enAire) {
            posY -= velocidad * dt;
            velocidad -= vgravedad * dt;
            for (vector<Obstaculo>::size_type i=0;i<o1->size();++i) {
                if ((posY > (*o1)[i].getPosY() - alto) && posX + ancho >= (*o1)[i].getPosX() && posX <= (*o1)[i].getPosX() + (*o1)[i].getAncho()) {
                    posY = (*o1)[i].getPosY() - alto;
                    velocidad = 0;
                    enAire = false;
                }

            }
            if ((posY > piso.getPosY() - alto) && posX + ancho >= piso.getPosX() && posX <= piso.getPosX() + piso.getAncho()) {
                posY = piso.getPosY() - alto;
                velocidad = 0;
                enAire = false;
            }
            this->personajeS.setPosition(posX+ajustexsprite, posY);
        }
}
void Enemy::perseguir(float dt,vector<Obstaculo>* o1, Player* p1, Obstaculo piso, Fondo &ff){
    if (p1[0].getPosX() <= posX && p1[0].getPosY() <= posY){
        moverIzq(dt,o1,p1,piso,ff);
    }else if (p1[0].getPosX() >= posX && p1[0].getPosY() >= posY){
        moverDer(dt,o1,p1,piso,ff);
    }else if (p1[0].getPosX() <= posX && p1[0].getPosY() >= posY){
        moverIzq(dt,o1,p1,piso,ff);
    }else if (p1[0].getPosX() >= posX && p1[0].getPosY() <= posY){
        moverDer(dt,o1,p1,piso,ff);
    }
}
Sprite Enemy::getSprite() {
     return personajeS; 
     }
void Enemy::establecerSprite(float dt,float dir){
    personajeS=personajeT.getSprite(dt,dir);
}
void Enemy::mover(RectangleShape& jugador) {
    jugador.setPosition(posX, posY);
}
void Enemy::help_move(float x,float arregloxsprite) {
    posX += velocidadX * x;
    recorrido += velocidadX * x;
    this->personajeS.setPosition(posX+arregloxsprite, posY);
}
