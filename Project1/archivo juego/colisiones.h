#ifndef COLISIONES_H  
#define COLISIONES_H

#include <type_traits>
#include "enemigo.h"
#include "player.h"
#include "obstaculo.h"
#include "proyectil.h"

class Proyectil;
class Enemy;
class Obstaculo;
class Player;

template <typename T, typename U>
int colision(T user, U object) {
    bool altura = (user.getPosY() + user.getAlto()) > object.getPosY() && (user.getPosY() + user.getAlto()) < (object.getPosY() + object.getAlto());//solo pa los pies del personaje, no pa la cabeza
    if (user.getPosX() <= object.getPosX() + object.getAncho() && user.getPosX() >= object.getPosX() + (object.getAncho() / 2) && altura)
        return -1;
    if (user.getPosX() + user.getAncho() >= object.getPosX() && user.getPosX() + user.getAncho() <= object.getPosX() + (object.getAncho() / 2) && altura)
        return 1;
    return 0;
}

template <typename T, typename U>
bool DetectSuelo(T user, U object) {
    bool ancho = user.getPosX() <= (object.getPosX() + object.getAncho()) && (user.getPosX() + user.getAncho() >= object.getPosX());
    if ((std::is_same<T, Player>::value || std::is_same<T, Enemy>::value) && std::is_same<U, Obstaculo>::value) {
        if ((user.getPosY() + user.getAlto()) >= object.getPosY() && (user.getPosY() + user.getAlto()) <= (object.getPosY() + object.getAlto()) && ancho)
            return true;
        return false;
    }
}
template <typename T, typename U>
bool detectDanio(T user,U object){
        bool altura = (user.getPosY() + user.getAlto()) > object.getPosY() || user.getPosY()  < (object.getPosY() + object.getAlto());
    if (user.getPosX() <= object.getPosX() + object.getAncho() && user.getPosX() +user.getAncho() >= object.getPosX() && altura)
        return -true;
   
    return false;
}

#endif