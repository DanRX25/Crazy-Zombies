#ifndef BUTTON_H 
#define BUTTON_H 
#include <SFML/Graphics.hpp>
using namespace sf;
class Button {
    RenderWindow* window;
    RectangleShape boton;
    Sprite spr;
    float Ancho, Alto;
    int posX, posY, cont = 0;
    bool estado = false;
    bool lock = false;
public:
    Button(RenderWindow& window, RectangleShape& button, float ancho, float alto, int x, int y, Color c, Sprite& spr) {
        this->window = &window;
        this->spr = spr;
        Ancho = ancho;
        Alto = alto;
        posX = x;
        posY = y;
        button.setPosition(posX, posY);
        button.setFillColor(c);
        this->spr.setPosition(posX, posY);
        boton = button;
    }
    float getposX() { return posX; }
    float getposY() { return posY; }
    float getAncho() { return Ancho; }
    float getAlto() { return Alto; }
    bool getEstado() { return estado; }
    RectangleShape getBoton() { return boton; }
    Sprite getSprite() { return spr; }
    void setSprite(Sprite& spr) { this->spr = spr; }
    void is_pressed(Vector2i, Event);
    void changeEstado() {
        if (estado == true) {
            estado = false;
        }
        else
            estado = true;
    }
    void lock_button() { lock = true; }
    void un_lock_button() { lock = false; }
};

#endif
