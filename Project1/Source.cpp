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
    void actPos(RectangleShape& jugador) { jugador.setPosition(posX, posY); }
};
void Player::mover(RectangleShape& jugador, int x) {
    posX += velocidad * x;
    jugador.setPosition(posX, posY);
}

void reinicio(Player& p, RectangleShape& r) {
    //p.setPosX(0);
    r.setSize(Vector2f(128.0f, 128.0f));
}

class Button {
protected:
    float Ancho, Alto;
    float posX, posY;
    RectangleShape* boton;
public:
    Button(RectangleShape& button, float ancho, float alto, int x, int y, Color c) { Ancho = ancho; Alto = alto; posX = x; posY = y; button.setPosition(posX, posY); button.setFillColor(c); boton = &button; }
    virtual void funcion(Player&, RectangleShape&) = 0;
    virtual RectangleShape dibujar() = 0;
};


class Button1 :public Button {
    int cont = 0;
public:
    Button1(RectangleShape& button, float ancho, float alto, int x, int y, Color c) : Button(button, ancho, alto, x, y, c) {}
    void funcion(Player&, RectangleShape&)override;
    RectangleShape dibujar() override;
    float getposX() { return posX; }
    float getposY() { return posY; }
    float getAncho() { return Ancho; }
    float getAlto() { return Alto; }
    void increment() { cont += 1; }
    int getCont() { return cont; }
    void pressed(int);
};
void Button1::funcion(Player& p, RectangleShape& r) {
    int x = 0;
    reinicio(p, r);
}
RectangleShape Button1::dibujar() {
    RectangleShape creacion(Vector2f(100.0f, 100.0f));
    creacion.setPosition(300, 300);
    if (cont % 3 == 0)
        creacion.setFillColor(Color::Blue);
    else if (cont % 3 == 1)
        creacion.setFillColor(Color::White);
    return creacion;
}
void Button1::pressed(int i) {
    boton->setSize(Vector2f(Ancho + (10 * i), Alto + (10 * i)));
    boton->setPosition(posX - (5 * i), posY - (5 * i));
}


class Button2 :public Button {
public:
    Button2(RectangleShape& button, float ancho, float alto, int x, int y, Color c) : Button(button, ancho, alto, x, y, c) {}
    void funcion(Player&, RectangleShape&);
    RectangleShape dibujar() override;
    float getposX() { return posX; }
    float getposY() { return posY; }
    float getAncho() { return Ancho; }
    float getAlto() { return Alto; }
    void pressed(int);
};
void Button2::funcion(Player& p, RectangleShape& r) {
    boton->setSize(Vector2f(0.0f, 0.0f));
}
RectangleShape Button2::dibujar() {
    RectangleShape creacion(Vector2f(100.0f, 100.0f));
    creacion.setPosition(300, 300);
    creacion.setFillColor(Color::Blue);
    return creacion;
}
void Button2::pressed(int i) {
    boton->setSize(Vector2f(Ancho + (10 * i), Alto + (10 * i)));
    boton->setPosition(posX - (5 * i), posY - (5 * i));
}
//-----------CLASE PLAYER---------------

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

class Juego {
    Player player;
    Enemy enemies;
    Obstaculo obstaculos;
public:
    Juego(Player p1, Enemy e1, Obstaculo o1) { player = p1; enemies = e1; obstaculos = o1; }
};

template <typename T, typename U>
bool DetectColisionsDer(T user, U object) {
    bool altura = (user.getPosY() + user.getAlto()) > object.getPosY() && (user.getPosY() + user.getAlto()) < (object.getPosY() + object.getAlto());
    if ((is_same<T, Player>::value || is_same<T, Enemy>::value || is_same<T, RectangleShape>::value) && is_same<U, Enemy>::value) {
        if ((user.getPosX() + user.getAncho()) >= object.getPosX() && (user.getPosX() + user.getAncho()) <= (object.getPosX() + object.getAncho() / 2) && altura)
            return true;
        return false;
    }
    if ((is_same<T, Player>::value || is_same<T, Enemy>::value || is_same<T, RectangleShape>::value) && is_same<U, Obstaculo>::value) {
        if ((user.getPosX() + user.getAncho()) >= object.getPosX() && (user.getPosX() + user.getAncho()) <= (object.getPosX() + object.getAncho() / 2) && altura)
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
    RectangleShape bot1(Vector2f(100.0f, 100.0f));
    Button1 b1(bot1, bot1.getLocalBounds().width, bot1.getLocalBounds().height, 10.0f, 10.0f, Color::Yellow);

    RenderWindow window(VideoMode(1360, 768), "My game");
    RectangleShape rectangle(Vector2f(128.0f, 128.0f));
    rectangle.setFillColor(Color::Red);
    rectangle.setPosition(100, 100);
    RectangleShape rectangle2(Vector2f(128.0f, 128.0f));
    rectangle2.setFillColor(Color::Green);
    RectangleShape rectangle3(Vector2f(128.0f, 128.0f));
    rectangle3.setFillColor(Color::Black);
    RectangleShape piso(Vector2f(2000.0f, 50.0f));
    piso.setFillColor(Color::Blue);
    piso.setPosition(0, 600);
    Player p1;
    Obstaculo o1;
    Obstaculo o2(0, 600, 50.0f, 2000.0f);
    Enemy e1;
    Juego game(p1, e1, o1);
    bool derecha = false, izquierda = false;


    vector<RectangleShape> balas;
    vector<int> sentido;
    bool mouse_dispara = true;
    bool tecla_reinicio = true;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            Vector2i mousePosition = Mouse::getPosition(window);
            if (mousePosition.x >= b1.getposX() && mousePosition.x <= b1.getposX() + b1.getAlto() && mousePosition.y >= b1.getposY() && mousePosition.y <= b1.getposY() + b1.getAlto()) {
                if (event.type == Event::MouseButtonPressed) {
                    b1.funcion(p1, rectangle3);
                }
                b1.pressed(1);
            }
            else
                b1.pressed(0);
        }
        if (Keyboard::isKeyPressed(Keyboard::A) && tecla_reinicio)
        {
            tecla_reinicio = false;
            reinicio(p1, rectangle3);
        }
        if (!Keyboard::isKeyPressed(Keyboard::A))
        {
            tecla_reinicio = true;
        }


        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            if (!DetectColisionsIzq<Player, Obstaculo>(p1, o1) && !DetectColisionsIzq<Player, Enemy>(p1, e1)) {
                p1.mover(rectangle, -1);
            }
            sentido.push_back(0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            if (!(DetectColisionsDer<Player, Obstaculo>(p1, o1) || DetectColisionsDer<Player, Enemy>(p1, e1))) {
                p1.mover(rectangle, 1);
            }
            sentido.push_back(1);
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            p1.salto(rectangle);
        }



        if (Mouse::isButtonPressed(sf::Mouse::Left) && mouse_dispara)
        {
            mouse_dispara = false;

            RectangleShape reca(Vector2f(20.0f, 20.0f));
            reca.setFillColor(Color::Red);
            reca.setPosition(p1.getPosX(), p1.getPosY() + 30);
            balas.push_back(reca);
            //p1.disparar();
            //cout<<p1.get_balas().size()<<endl;
        }
        if (!Mouse::isButtonPressed(sf::Mouse::Left))
        {
            mouse_dispara = true;
        }


        window.clear(Color::White);
        o1.mover(rectangle2);
        e1.mover(rectangle3);


        //--------------


        for (int i = 0; i < balas.size(); i++)
        {

            //p1.get_balas(i).mover();
            float proyectilPosX = balas[i].getPosition().x;
            float proyectilPosY = balas[i].getPosition().y;
            if (sentido[i] == 0)
            {
                balas[i].setPosition(proyectilPosX - 0.5, proyectilPosY);
            }
            else {
                balas[i].setPosition(proyectilPosX + 0.5, proyectilPosY);

            }
            bool altura = (balas[i].getPosition().y + balas[i].getLocalBounds().height) > e1.getPosY() && (balas[i].getPosition().y + balas[i].getLocalBounds().height) < (e1.getPosY() + e1.getAlto());
            if (balas[i].getPosition().x <= (e1.getPosX() + e1.getAncho()) && (balas[i].getPosition().x >= e1.getPosX() + e1.getAncho() / 2) && altura) {
                rectangle3.setSize(Vector2f(0.0f, 0.0f));
            }

            //cout<<proyectilPosX<<endl;
            window.draw(balas[i]);

        }

        //------------------

        window.draw(rectangle);
        if (cont % 10 == 0) {
            if (!DetectSuelo<Player, Obstaculo>(p1, o2) && !DetectSuelo<Player, Obstaculo>(p1, o1)) {
                p1.gravedad(rectangle);
            }
        }
        window.draw(bot1);
        window.draw(rectangle2);
        window.draw(piso);
        window.draw(rectangle3);
        window.display();
        cont++;
    }
    return EXIT_SUCCESS;
}
*/