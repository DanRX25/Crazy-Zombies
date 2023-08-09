/*
#include <SFML/Graphics.hpp>
#include <time.h>
#include <memory>
#include <type_traits>
#include <iostream>
using namespace sf;
using  namespace std;

class Mapa {
    Sprite* spritesFondo;
    float size, posX;
public:
    Mapa() {
        this->spritesFondo = new Sprite[0];
        this->size = 3;
        this->posX = 0;
    }
    Mapa(const Sprite spiter, int size) {


        this->size = size;
        this->spritesFondo = new Sprite[size];
        for (int i = 0; i < size; i++) {
            spritesFondo[i] = spiter;
        }
    }
    ~Mapa() {
        delete[] spritesFondo;
    }
    Sprite getData(int pos) {
        return spritesFondo[pos];
    }
    void moverFondo(int, int);
};
void Mapa::moverFondo(int recorrido, int x) {
    if (recorrido >= 600 && recorrido <= 1360 * size) {
        for (int i = 0; i < size; i++)
        {
            posX += 0.075 * x;
            spritesFondo[i].setPosition(posX + (1360 * i), 0);
        }
    }
}


class Proyectil {
    float po_x;
    float po_y;

public:
    Proyectil(float, float);
    float get_pox();
    float get_poy();

    void mover();
};
Proyectil::Proyectil(float px, float py) {
    po_x = px;
    po_y = py;

}
float Proyectil::get_pox() {
    return po_x;
}
float Proyectil::get_poy() {
    return po_y;
}
void Proyectil::mover() {
    //cout<<po_x<<endl;
    po_x = po_x - 1.2;
    //forma.setPosition(po_x,po_y);
    //cout<<po_y<<endl;
}


class Player {
    float posX, posY, velocidad;
    float recorrido = 0;
    int direccion;
    vector<Proyectil> balas;
public:
    int cant = 0;
    Player() { posX = 0; posY = 500; velocidad = 100.0f; recorrido = 0; direccion = 0; }
    float getRecorrido() {
        return recorrido;
    }
    int getDireccion() {
        return direccion;
    }
    void mover(Sprite*, float);
    void disparar();
    Proyectil get_balas(int);
};
void Player::mover(Sprite* jugador, float x) {

    posX += velocidad * x;

    recorrido += velocidad * x;
    if (x > 0) { direccion = 0; }
    else { direccion = 1; }
    jugador[direccion].setPosition(posX, posY);
}
void Player::disparar() {
    Proyectil pro1(posX, posY);
    //cout<<posX<<posY<<endl;
    balas.push_back(pro1);
    cant++;
}
Proyectil Player::get_balas(int a) {
    return balas[a];
}


int main()
{
    float vel = 100.0f;
    sf::View view(sf::FloatRect(0, 0, 1360, 768));
    sf::RectangleShape rectangle2(sf::Vector2f(100.0f, 100.0f));
    rectangle2.setFillColor(sf::Color::Green);
    rectangle2.setPosition(620, 500);
    RenderWindow window(VideoMode(1360, 768), "My game");
    RectangleShape rectangle(Vector2f(128.0f, 128.0f));
    rectangle.setFillColor(Color::Yellow);
    rectangle.setPosition(0, 500);
    vector<RectangleShape> balas;
    vector<int> sentido;
    Player p1;
    Texture fondo;
    if (!fondo.loadFromFile("images/Mi proyecto.jpg"))
    {
        return -1;
    }
    Sprite sprite(fondo);
    sprite.setPosition(0.0f, 0.0f);

    Mapa mapa(sprite, 6);

    mapa.moverFondo(0, 1);
    float count = 0;
    sf::Clock clock;
    Texture personaje;
    if (!personaje.loadFromFile("images/Personaje.JPG"))
    {
        return -1;
    }

    Sprite spriteper(personaje);
    spriteper.setPosition(0.0f, 500.0f);

    Texture personaje1;
    if (!personaje1.loadFromFile("images/Personaje.JPG"))
    {
        return -1;
    }

    Sprite spriteper1(personaje1);
    spriteper1.setPosition(0.0f, 500.0f);
    bool mouse_dispara = true;
    Sprite ArraySpr[2]{ spriteper,spriteper1 };
    while (window.isOpen())
    {
        rectangle.setFillColor(Color::Yellow);
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        sf::Time deltaTime = clock.restart(); // Obtener el tiempo transcurrido desde la última iteración
        float dt = deltaTime.asSeconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            p1.mover(ArraySpr, -1 * dt);
            count++;
            rectangle.setFillColor(Color::Red);
            if (p1.getRecorrido() >= 680)
            {
                view.move(-0.5 * vel * dt, 0);
                ArraySpr[p1.getDireccion()].move(-0.5 * vel * dt, 0);
                for (int i = 0; i < 6; i++) {
                    mapa.getData(i).move(-0.5 * vel * dt, 0);
                }
            }
            //mapa.moverFondo(p1.getRecorrido(), 1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            p1.mover(ArraySpr, 1 * dt);
            count--;
            rectangle.setFillColor(Color::Green);
            if (p1.getRecorrido() >= 680)
            {
                view.move(0.5 * vel * dt, 0);
                ArraySpr[p1.getDireccion()].move(0.5 * vel * dt, 0);
                for (int i = 0; i < 6; i++) {
                    mapa.getData(i).move(0.5 * vel * dt, 0);
                }
            }
            //mapa.moverFondo(p1.getRecorrido(), -1);
        }

        float des = p1.getRecorrido();
        cout << des << endl;

        if (ArraySpr[p1.getDireccion()].getPosition().x <= rectangle2.getPosition().x && ArraySpr[p1.getDireccion()].getPosition().y <= rectangle2.getPosition().y)
        {
            rectangle2.setPosition(rectangle2.getPosition().x - 0.3 * vel * dt, rectangle2.getPosition().y - 0.1 * vel * dt);
        }
        else if (ArraySpr[p1.getDireccion()].getPosition().x >= rectangle2.getPosition().x && ArraySpr[p1.getDireccion()].getPosition().y >= rectangle2.getPosition().y) {
            rectangle2.setPosition(rectangle2.getPosition().x + 0.3 * vel * dt, rectangle2.getPosition().y + 0.1 * vel * dt);

        }
        else if (ArraySpr[p1.getDireccion()].getPosition().x <= rectangle2.getPosition().x && ArraySpr[p1.getDireccion()].getPosition().y >= rectangle2.getPosition().y) {
            rectangle2.setPosition(rectangle2.getPosition().x - 0.3 * vel * dt, rectangle2.getPosition().y + 0.1 * vel * dt);

        }
        else if (ArraySpr[p1.getDireccion()].getPosition().x >= rectangle2.getPosition().x && rectangle.getPosition().y <= rectangle2.getPosition().y) {
            rectangle2.setPosition(rectangle2.getPosition().x + 0.3 * vel * dt, rectangle2.getPosition().y - 0.1 * vel * dt);

        }

        if (Mouse::isButtonPressed(sf::Mouse::Left) && mouse_dispara)
        {
            if (p1.getDireccion() == 1) {
                sentido.push_back(0);
            }
            else {
                sentido.push_back(1);
            }
            RectangleShape reca(Vector2f(20.0f, 20.0f));
            reca.setPosition(ArraySpr[p1.getDireccion()].getPosition().x, ArraySpr[p1.getDireccion()].getPosition().y);
            balas.push_back(reca);
            //p1.disparar();
            mouse_dispara = false;
            //cout<<p1.get_balas().size()<<endl;
        }
        if (!Mouse::isButtonPressed(sf::Mouse::Left))
        {
            mouse_dispara = true;
        }
        window.clear(Color::Black);
        window.setView(view);
        for (int i = 0; i < 6; i++) {
            window.draw(mapa.getData(i));
        }
        window.draw(mapa.getData(0));

        window.draw(ArraySpr[p1.getDireccion()]);
        for (int i = 0; i < balas.size(); i++)
        {

            //p1.get_balas(i).mover();
            float proyectilPosX = balas[i].getPosition().x;
            float proyectilPosY = balas[i].getPosition().y;
            if (sentido[i] == 0)
            {
                balas[i].setPosition(proyectilPosX - vel * dt, proyectilPosY);
            }
            else {
                balas[i].setPosition(proyectilPosX + vel * dt, proyectilPosY);
            }

            //cout<<proyectilPosX<<endl;
            window.draw(balas[i]);

        }
        window.draw(rectangle2);

        window.display();
    }
    return EXIT_SUCCESS;
}
*/