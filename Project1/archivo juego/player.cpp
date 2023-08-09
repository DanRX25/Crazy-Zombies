#include "player.h"
void Player::help_move(float x, float arregloxsprite) {
    /* if ((recorrido >= 0 && recorrido < 600) || (recorrido >= 1300 * 6 && recorrido < (1310 * 6) + 600)) {
    } */
    posX += velocidadX * x;
    recorrido += velocidadX * x;


    this->personajeS.setPosition(posX + arregloxsprite, posY);
}
void Player::moverDer(float dt, vector<Obstaculo>* o1, Enemy e1, Obstaculo piso, Fondo& ff) {
    /*  ajustexsprite=0;
     direccion=1;
     if (!(colision<Player, Obstaculo>(*this, o1) == 1 || colision<Player, Enemy>(*this, e1) == 1)) {
         establecerSprite(dt,direccion);
         this->help_move(1*dt,ajustexsprite);
         if (colision<Player, Obstaculo>(*this,o1))
         {
             this->help_move(-1*dt,ajustexsprite);

         }

         enAire=true;
     } */


    ajustexsprite = 0;
    direccion = 1;

    hayColision = false;


    // Verificar colisiones con cada obstáculo
    for (vector<Obstaculo>::size_type i = 0;i < o1->size();++i) {
        if (colision<Player, Obstaculo>(*this, (*o1)[i]) == 1 || colision<Player, Enemy>(*this, e1) == 1) {
            hayColision = true;
            break;

        }
    }
    if (!hayColision) {
        establecerSprite(dt, direccion);
        this->help_move(1 * dt, ajustexsprite);


        for (vector<Obstaculo>::size_type i = 0;i < o1->size();++i) {
            if (colision<Player, Obstaculo>(*this, (*o1)[i])) {
                this->help_move(-1 * dt, ajustexsprite);
                break;
            }
        }


        enAire = true;
    }
    //ff.moverFondo(getRecorrido(), -1);
}
void Player::moverIzq(float dt, vector<Obstaculo>* o1, Enemy e1, Obstaculo piso, Fondo& ff) {
    /* ajustexsprite=ancho;
    direccion=-1;
    if (!(colision<Player, Obstaculo>(*this, o1) == -1 || colision<Player, Enemy>(*this, e1) == -1)) {
        establecerSprite(dt,direccion);
        this->help_move(-1*dt,ajustexsprite);
        if (colision<Player, Obstaculo>(*this,o1))
        {
            this->help_move(1*dt,ajustexsprite);

        }
        enAire=true;
    } */

    ajustexsprite = ancho;
    direccion = -1;

    hayColision = false;


    for (vector<Obstaculo>::size_type i = 0;i < o1->size();++i) {
        if (colision<Player, Obstaculo>(*this, (*o1)[i]) == -1 || colision<Player, Enemy>(*this, e1) == -1) {
            hayColision = true;
            break;
        }
        enAire = true;
    }


    if (!hayColision) {
        establecerSprite(dt, direccion);
        this->help_move(-1 * dt, ajustexsprite);


        // Verificar si hay colisión después del movimiento
        for (vector<Obstaculo>::size_type i = 0;i < o1->size();++i) {
            if (colision<Player, Obstaculo>(*this, (*o1)[i])) {
                this->help_move(1 * dt, ajustexsprite);
                break;
            }
        }



    }
    //ff.moverFondo(getRecorrido(), 1);
}
void Player::saltar(float dt, vector<Obstaculo>* o1, Enemy e1, Obstaculo piso, Fondo& ff) {

    for (vector<Obstaculo>::size_type i = 0;i < o1->size();++i) {
        if (DetectSuelo<Player, Obstaculo>(*this, piso) || DetectSuelo<Player, Obstaculo>(*this, (*o1)[i])) {
            velocidad = velocidadY;
            enAire = true;
            break;
        }
    }
    /* if (DetectSuelo<Player, Obstaculo>(*this, piso) || DetectSuelo<Player, Obstaculo>(*this, o1)){
        velocidad=velocidadY;
        enAire=true;
    } */
}
void Player::mover(float dt, vector<Obstaculo>* o1, Obstaculo piso, Fondo& ff) {
    if (enAire) {
        posY -= velocidad * dt;
        velocidad -= vgravedad * dt;
        for (vector<Obstaculo>::size_type i = 0;i < o1->size();++i) {
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
        this->personajeS.setPosition(posX + ajustexsprite, posY);
    }
}
void Player::disparar() {
    if (sf::Keyboard::isKeyPressed(disparo))
    {
        if (direccion == 1) {
            arma.disparar(sf::Vector2f(posX + ancho, posY + (alto/2)), true);
        }
        else {
            arma.disparar(sf::Vector2f(posX + ancho, posY + (alto / 2)), false);
        }
    }
}
Arma& Player::getArma() {
    return arma;
}
void Player::establecerSprite(float dt, float dir) {
    personajeS = personajeT.getSprite(dt, dir);
}
