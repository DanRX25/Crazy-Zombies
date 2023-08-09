#ifndef BARRAVIDA_H
#define BARRAVIDA_H
#include <SFML/Graphics.hpp>

class BarraVida; // Declaración anticipada de la clase BarraVida

// Interfaz State que define el comportamiento común para todos los estados concretos.
class State {
public:
    virtual sf::Color getColor() = 0;
    // Cambiamos el método a getColor() y lo hacemos virtual puro
};

class SuficienteVidaState : public State {
public:
    sf::Color getColor() override {
        return sf::Color::Green; // Devolvemos el color verde para "Suficiente Vida"
    }
};

class PocaVidaState : public State {
public:
    sf::Color getColor() override {
        return sf::Color(255, 165, 0); // Devolvemos el color naranja para "Poca Vida"
    }
};

class BarraVida {
private:
    std::unique_ptr<std::shared_ptr<sf::RectangleShape>[]> cuadrados;
    float size, posX, posY;
    int vidaActual, vidaMaxima;
    sf::Color colorVida, colorVacio;
    State* state_;

public:
    BarraVida(int vidaMaxima, float size, float posX, float posY, const sf::Color& colorVida, const sf::Color& colorVacio)
        :state_(new SuficienteVidaState), vidaActual(vidaMaxima), vidaMaxima(vidaMaxima), size(size), posX(posX), posY(posY), colorVida(colorVida), colorVacio(colorVacio) {

        cuadrados = std::make_unique<std::shared_ptr<sf::RectangleShape>[]>(vidaMaxima);
        for (int i = 0; i < vidaMaxima; i++) {
            cuadrados[i] = std::make_shared<sf::RectangleShape>(sf::Vector2f(size, size));
            cuadrados[i]->setPosition(posX + (i * (size + 2)), posY);
            cuadrados[i]->setFillColor(state_->getColor());

        }
    }

    void perderVida(int cantidad) {
        if (vidaActual > 0) {
            vidaActual -= cantidad;
            if (vidaActual < 0) vidaActual = 0;
            actualizarBarra();
        }
    }

    void ganarVida(int cantidad) {
        if (vidaActual < vidaMaxima) {
            vidaActual += cantidad;
            if (vidaActual > vidaMaxima) vidaActual = vidaMaxima;
            actualizarBarra();
        }
    }

    void mover(float offsetX, float offsetY) {
        posX = offsetX;
        posY = offsetY;
        for (int i = 0; i < vidaMaxima; i++) {
            cuadrados[i]->setPosition(posX + (i * (size + 2)), posY);
        }
    }

    void actualizarBarra() {
        if (vidaActual < 6) {
            cambiarEstado(new PocaVidaState());
        }
        for (int i = 0; i < vidaMaxima; i++) {
            if (i < vidaActual) {
                cuadrados[i]->setFillColor(state_->getColor()); // Utilizamos el color del estado actual
            }
            else {
                cuadrados[i]->setFillColor(colorVacio);
            }
        }
    }

    void cambiarEstado(State* nuevoEstado) {

        if (state_ != nuevoEstado) {
            delete state_;
            state_ = nuevoEstado;
            // Actualizamos el color de los cuadrados al cambiar de estado
        }
    }

    void draw(sf::RenderWindow& window) {
        for (int i = 0; i < vidaMaxima; i++) {
            window.draw(*cuadrados[i]);
        }
    }
    sf::RectangleShape getData(int pos) {
        return *cuadrados[pos];
    }
};
#endif