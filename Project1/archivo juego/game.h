#ifndef GAME_H
#define GAME_H
//#include <SFML/Graphics.hpp>
//#include <time.h>
//#include <type_traits>
//#include <cmath>
//#include "player.h"
//#include "enemigo.h"
//#include "obstaculo.h"
#include "button.h"
//#include "fondo.h"
#include "colisiones.h"
#include "juegoControlador.h"
#include <thread>
#include <chrono>
#include <mutex>
using namespace sf;
using namespace std;
class Game {
    RenderWindow* window;
    Player* players;
    vector<Obstaculo> obstaculos;
    vector<Enemy> enemigos;
    Color Mapa;
    int ancho, alto;
    int actualPlayer;
    int actualObstaculo;
    int cont = 0;
    bool cantidadPlayer;
    int cantidadObstaculo;
    int cantZombies=3;
public:
    Game(RenderWindow& window, int alto, int ancho);
    void setPlayers(Player& p) { players[actualPlayer] = p; ++actualPlayer; }
    void setObstaculos(Obstaculo& o) { obstaculos[actualObstaculo] = o; ++actualObstaculo; }
    void Inicio();
    int Ejecutar();
    void Selec_Personajes();
    void Selec_Mapa();
    void Pausa(Button&);
};

#endif

