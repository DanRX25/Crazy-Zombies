/*
#include <SFML/Graphics.hpp>
#include <time.h>
#include <type_traits>
using namespace sf;
using namespace std;
#include <cmath>
#include <iostream>

class Player {
    float posX, posY, ancho, alto;
    int velocidad;
public:
    Player() { posX = 100; posY = 100; velocidad = 1; alto = 128.0f; ancho = 128.0f; }
    void mover(RectangleShape&, int);
    void gravedad(RectangleShape& p1) { posY += 1; p1.setPosition(posX, posY); }
    void salto(RectangleShape& p1) { posY -= 5; p1.setPosition(posX, posY); }
    float getPosX() { return posX; }
    float getPosY() { return posY; }
    float getAlto() { return alto; }
    float getAncho() { return ancho; }
    int getVelo() { return velocidad; }
    void setPosX(int x) { posX = x; }
    void actPos(RectangleShape& jugador){ jugador.setPosition(posX, posY); }
};
void Player::mover(RectangleShape& jugador, int x) {
    posX += velocidad * x;
    jugador.setPosition(posX, posY);
}

class Obstaculo {
    float posX, posY, ancho, alto;
public:
    Obstaculo() { posX = 100; posY = 500; alto = 128.0f; ancho = 128.0f; }
    Obstaculo(int x, int y, float alto, float ancho) { posX = x; posY = y; this->alto = alto; this->ancho = ancho; }
    void mover(RectangleShape&);
    float getPosX() { return posX; }
    float getPosY() { return posY; }
    float getAlto() { return alto; }
    float getAncho() { return ancho; }
};
void Obstaculo::mover(RectangleShape& jugador) {
    jugador.setPosition(posX, posY);
}

class Enemy {
    float posX, posY, ancho, alto;
public:
    Enemy() { posX = 800; posY = 500; alto = 128.0f; ancho = 128.0f; }
    void mover(RectangleShape&);
    float getPosX() { return posX; }
    float getPosY() { return posY; }
    float getAlto() { return alto; }
    float getAncho() { return ancho; }
};
void Enemy::mover(RectangleShape& jugador) {
    jugador.setPosition(posX, posY);
}

class Juego{
    Player player;
    Enemy enemies;
    Obstaculo obstaculos;
public:
    Juego(Player p1, Enemy e1, Obstaculo o1) { player = p1; enemies = e1; obstaculos = o1; }
};

template <typename T, typename U>
bool DetectColisionsDer(T user, U object) {
    bool altura = (user.getPosY() + user.getAlto()) > object.getPosY() && (user.getPosY() + user.getAlto()) < (object.getPosY() + object.getAlto());
    if((is_same<T, Player>::value || is_same<T, Enemy>::value || is_same<T, RectangleShape>::value) && is_same<U, Enemy>::value) {
        if ((user.getPosX() + user.getAncho()) >= object.getPosX() && (user.getPosX() + user.getAncho()) <= (object.getPosX() + object.getAncho()/2) && altura)
            return true;
        return false;
    }
    if((is_same<T, Player>::value || is_same<T, Enemy>::value || is_same<T, RectangleShape>::value) && is_same<U, Obstaculo>::value) {
        if ((user.getPosX() + user.getAncho()) >= object.getPosX() && (user.getPosX() + user.getAncho()) <= (object.getPosX() + object.getAncho()/2) && altura)
            return true;
        return false;
    }
}
template <typename T, typename U>
bool DetectColisionsIzq(T user, U object) {
    bool altura = (user.getPosY() + user.getAlto()) > object.getPosY() && (user.getPosY() + user.getAlto()) < (object.getPosY() + object.getAlto());
    if ((is_same<T, Player>::value || is_same<T, Enemy>::value || is_same<T, RectangleShape>::value) && is_same<U, Enemy>::value) {
        if (user.getPosX() <= (object.getPosX() + object.getAncho()) && (user.getPosX() >= object.getPosX() + object.getAncho() / 2) && altura)
            return true;
        return false;
    }
    if ((is_same<T, Player>::value || is_same<T, Enemy>::value || is_same<T, RectangleShape>::value) && is_same<U, Obstaculo>::value) {
        if (user.getPosX() <= (object.getPosX() + object.getAncho()) && (user.getPosX() >= object.getPosX() + object.getAncho() / 2) && altura)
            return true;
        return false;
    }
}
template <typename T, typename U>
bool DetectSuelo(T user, U object) {
    bool ancho = user.getPosX() <= (object.getPosX() + object.getAncho()) && (user.getPosX() + user.getAncho() >= object.getPosX());
    if ((is_same<T, Player>::value || is_same<T, Enemy>::value) && is_same<U, Obstaculo>::value) {
        if ((user.getPosY() + user.getAlto()) >= object.getPosY() && (user.getPosY() + user.getAlto()) <= (object.getPosY() + object.getAlto()) && ancho)
            return true;
        return false;
    }
}
int cont = 0;
int main()
{
    RenderWindow window(VideoMode(1360, 768), "My game");
    RectangleShape rectangle(Vector2f(128.0f, 128.0f));
    rectangle.setFillColor(Color::Red);
    rectangle.setPosition(100,100);
    RectangleShape rectangle2(Vector2f(128.0f, 128.0f));
    rectangle2.setFillColor(Color::Green);
    RectangleShape rectangle3(Vector2f(128.0f, 128.0f));
    rectangle3.setFillColor(Color::Black);
    RectangleShape piso(Vector2f(2000.0f, 50.0f));
    piso.setFillColor(Color::Blue);
    piso.setPosition(0,600);
    Player p1;
    Obstaculo o1(100, 500, 128.0f, 128.0f);
    Obstaculo o2(0,600, 50.0f, 2000.0f);
    Enemy e1;
    Juego game (p1,e1,o1);
    bool derecha=false, izquierda=false;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();        
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            if (!DetectColisionsIzq<Player, Obstaculo>(p1, o1) && !DetectColisionsIzq<Player, Enemy>(p1, e1)) {
                p1.mover(rectangle, -1);
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            if (!DetectColisionsDer<Player, Obstaculo>(p1, o1) && !DetectColisionsDer<Player, Enemy>(p1, e1)) {
                p1.mover(rectangle, 1);
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            p1.salto(rectangle);
        }
        window.clear(Color::White);
        o1.mover(rectangle2);
        e1.mover(rectangle3);
        window.draw(rectangle);
        if (cont % 10 == 0) {
            if (!(DetectSuelo<Player, Obstaculo>(p1, o2) || DetectSuelo<Player, Obstaculo>(p1, o1)))
                p1.gravedad(rectangle);
            
        }
        window.draw(rectangle2);
        window.draw(piso);
        window.draw(rectangle3);
        window.display();
        cont++;
    }
    return EXIT_SUCCESS;
}
*/
/*
Template<typename T,U>
class Juego{
    Player Player1;
    Enemy* ListaEnemies[];
    Obstaculo* ListaObstaulos[];
    int acutalEn, actualObs;
public:
    bool DetectColisions(cons T user, const U* object[]);
};

Template<typename T,U>
bool Juego::DetectColisions(cons T user, const U* object[]){
    enable_if<(is_same<T,Player>::value||is_same<T,Enemy>::value||is_same<T,RectangleShape>::value)&&is_same<U,Enemy>::value>::type;
    for(int i=0; i<acutalEn; i++){
        if(user.PosX+user.ancho<=object[i]->PosX+object[i]->Ancho)
            return true;
    }
    return false;
    enable_if<(is_same<T,Player>::value||is_same<T,Enemy>::value|| is_same<T, RectangleShape>::value)&&is_same<U,Obstaculo>::value>::type;
    for(int i=0; i<acutalObs; i++){
        if(user.PosX+user.ancho<=object[i]->PosX+object[i]->Ancho)
            return true;
    }
    return false;
}

Template<typename T, typename U>
bool Juego::DetectColisions(const T user, const U object) {
    enable_if<(is_same<T, Player>::value || is_same<T, Enemy>::value || is_same<T, RectangleShape>::value) && is_same<U, Enemy>::value>::type;
    if (user.PosX + user.ancho <= object[i]->PosX + object[i]->Ancho)
        return true;
    return false;
    enable_if<(is_same<T, Player>::value || is_same<T, Enemy>::value || is_same<T, RectangleShape>::value) && is_same<U, Obstaculo>::value>::type;
    if (user.PosX + user.ancho >= object[i]->PosX && user.PosX <= object[i]->PosX + object[i]->Ancho)
        return true;
    return false;
}
*/
