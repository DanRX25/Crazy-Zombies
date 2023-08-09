
#include "juegoControlador.h"
JuegoControlador::JuegoControlador(){}
JuegoControlador::JuegoControlador(bool nPlayers,Player* players,vector<Obstaculo>* o1,Enemy e1, Obstaculo piso,Fondo* ff){
    ps=players;
    this->e1=e1;
    this->o1=o1;
    this->piso = piso;
    this->f1 = ff;
    this->nplayer = nPlayers;
}
void JuegoControlador::controlarInput(float dt){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            ps->moverDer(dt,o1,e1,piso,*f1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            ps->moverIzq(dt,o1,e1,piso,*f1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            ps->saltar(dt,o1,e1,piso,*f1);
    }
    if (nplayer)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                (ps+1)->moverDer(dt,o1,e1,piso,*f1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                    (ps+1)->moverIzq(dt,o1,e1,piso,*f1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                    (ps+1)->saltar(dt,o1,e1,piso,*f1);
        }
    }
}
