/*
#include <time.h>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <type_traits>
#include <iostream>
using namespace sf;
using namespace std;

class Button {
protected:
    float Ancho, Alto;
    float posX, posY;
    RectangleShape* boton;
public:
    Button(RectangleShape& button, float ancho, float alto, int x, int y, Color c) { Ancho = ancho; Alto = alto; posX = x; posY = y; button.setPosition(posX, posY); button.setFillColor(c); boton = &button; }
    virtual void funcion() = 0;
};


class Button1 :public Button {
    bool estado = false;
    int cont = 0;
public:
    Button1(RectangleShape& button, float ancho, float alto, int x, int y, Color c) : Button(button, ancho, alto, x, y, c) {}
    void funcion() override;
    float getposX() { return posX; }
    float getposY() { return posY; }
    float getAncho() { return Ancho; }
    float getAlto() { return Alto; }
    bool getEstado() { return estado; }
    void pressed(int);
};
void Button1::funcion() {
    if (cont % 2 == 0) {
        estado = true;
    }
    else {
        estado = false;
    }
    cont++;
}
void Button1::pressed(int i) {
    boton->setSize(Vector2f(Ancho + (10 * i), Alto + (10 * i)));
    boton->setPosition(posX - (5 * i), posY - (5 * i));
}


int main()
{
    RenderWindow window(sf::VideoMode(840, 680), "First window!");
    RectangleShape b1(Vector2f(100.0f, 100.0f));
    RectangleShape b2(Vector2f(400.0f, 400.0f));
    Button1 boton1(b1, 100.0f, 100.0f, 50, 50, Color::Yellow);
    b2.setPosition(100, 100);
    b2.setFillColor(Color::Blue);
    Clock marca_tiempo;
    Time intervalo;
    bool hola;
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                // Close window button clicked.
                window.close();
            }
            Vector2i mousePosition = Mouse::getPosition(window);

            if (mousePosition.x >= boton1.getposX() && mousePosition.x <= boton1.getposX() + boton1.getAlto() && mousePosition.y >= boton1.getposY() && mousePosition.y <= boton1.getposY() + boton1.getAlto()) {
                if (event.type == Event::MouseButtonPressed) {
                    boton1.funcion();
                }
                boton1.pressed(1);
            }
            else
                boton1.pressed(0);
        }

        //mousePosition.x>=boton1.getposX()&&mousePosition.x<=boton1.getposX()+boton1.getAlto()&&mousePosition.y<=boton1.getposY()&&mousePosition.y>=boton1.getposY()-boton1.getAlto()

        intervalo = marca_tiempo.restart();

        // Obtener el tiempo transcurrido en segundos
        float intervalo_s = intervalo.asSeconds();
        //cout<<intervalo_s<<endl;

        window.clear(Color::Black);
        // Draw here.
        if (boton1.getEstado())
            window.draw(b2);
        window.draw(b1); // Render our shape
        window.display();

    }
    return 0;
}
*/
/*
#include <time.h>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <type_traits>
#include <iostream>
using namespace sf;
using namespace std;

class Button {
protected:
    float Ancho, Alto;
    float posX, posY;
    RectangleShape* boton;
public:
    Button(RectangleShape& button, float ancho, float alto, int x, int y, Color c) { Ancho = ancho; Alto = alto; posX = x; posY = y; button.setPosition(posX, posY); button.setFillColor(c); boton = &button; }
    virtual void funcion() = 0;
};


class Button1 :public Button {
    bool estado = false;
    int cont = 0;
public:
    Button1(RectangleShape& button, float ancho, float alto, int x, int y, Color c) : Button(button, ancho, alto, x, y, c) {}
    void funcion() override;
    float getposX() { return posX; }
    float getposY() { return posY; }
    float getAncho() { return Ancho; }
    float getAlto() { return Alto; }
    bool getEstado() { return estado; }
    void setEstadoFalse() { estado = false; }
    void pressed(int);
};
void Button1::funcion() {
    estado = true;
}
void Button1::pressed(int i) {
    boton->setSize(Vector2f(Ancho + (10 * i), Alto + (10 * i)));
    boton->setPosition(posX - (5 * i), posY - (5 * i));
}


int main()
{
    unsigned int ancho = 800, alto = 800;
    RenderWindow window(sf::VideoMode(ancho, alto), "Menu");
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Images/map.jpg")) {
        std::cerr << "Error al cargar la imagen de fondo." << std::endl;
        return EXIT_FAILURE;
    }
    sf::Sprite backgroundSprite(backgroundTexture);
    sf::Vector2u windowSize = window.getSize();
    backgroundSprite.setScale(
        static_cast<float>(windowSize.x) / backgroundTexture.getSize().x,
        static_cast<float>(windowSize.y) / backgroundTexture.getSize().y
    );
    RectangleShape b1(Vector2f(100.0f, 100.0f));
    RectangleShape b2(Vector2f(110.0f, 500.0f));
    RectangleShape b3(Vector2f(100.0f, 100.0f));
    RectangleShape* cuadros = new RectangleShape[6];
    b2.setPosition(100, 100);
    b2.setFillColor(Color::Blue);
    for (int i = 0; i < 6; i++) {
        cuadros[i] = b2;
        cuadros[i].setFillColor(Color::Blue);
        cuadros[i].setPosition(20 + 130 * i, 200);
    }
    Button1 boton1(b1, 100.0f, 100.0f, ancho / 2, alto / 2, Color::Yellow);
    Button1 boton2(b3, 100.0f, 100.0f, 690, 690, Color::Red);
    Clock marca_tiempo;
    Time intervalo;
    bool hola;
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                // Close window button clicked.
                window.close();
            }
            Vector2i mousePosition = Mouse::getPosition(window);

            if (mousePosition.x >= boton1.getposX() && mousePosition.x <= boton1.getposX() + boton1.getAlto() && mousePosition.y >= boton1.getposY() && mousePosition.y <= boton1.getposY() + boton1.getAlto() && boton1.getEstado() == false) {
                if (event.type == Event::MouseButtonPressed) {
                    boton1.funcion();
                    boton2.setEstadoFalse();
                }
                boton1.pressed(1);
            }
            else
                boton1.pressed(0);

            if (mousePosition.x >= boton2.getposX() && mousePosition.x <= boton2.getposX() + boton2.getAlto() && mousePosition.y >= boton2.getposY() && mousePosition.y <= boton2.getposY() + boton2.getAlto() && boton2.getEstado() == false) {
                if (event.type == Event::MouseButtonPressed) {
                    boton2.funcion();
                    boton1.setEstadoFalse();
                }
                boton2.pressed(1);
            }
            else
                boton2.pressed(0);
        }

        //mousePosition.x>=boton1.getposX()&&mousePosition.x<=boton1.getposX()+boton1.getAlto()&&mousePosition.y<=boton1.getposY()&&mousePosition.y>=boton1.getposY()-boton1.getAlto()

        intervalo = marca_tiempo.restart();

        // Obtener el tiempo transcurrido en segundos
        float intervalo_s = intervalo.asSeconds();
        //cout<<intervalo_s<<endl;

        window.clear(Color::Black);
        window.draw(backgroundSprite);
        // Draw here.
        if (boton1.getEstado()) {
            for (int i = 0; i < 6; i++)
                window.draw(cuadros[i]);
            window.draw(b3);
        }
        if (!boton1.getEstado() || boton2.getEstado()) {
            window.draw(b1);
        }
        window.display();

    }
    return EXIT_SUCCESS;
}*/