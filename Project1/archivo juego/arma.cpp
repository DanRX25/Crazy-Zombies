#include "Arma.h"


Arma::Arma() {
    velocidad = 400.0f;
    intervalo_disparo = 0;
    disparo_listo = true;
}
void Arma::disparar(sf::Vector2f position, bool dir) {
    if (disparo_listo) {
        proyectiles.emplace_back(position, velocidad, 1);
        sentido_proyectiles.push_back(dir);
        disparo_listo = false;
    }
    if (intervalo_disparo == 10) {
        intervalo_disparo = 0;
        disparo_listo = true;
    }
    if (!disparo_listo)
    {
        ++intervalo_disparo;
    }
}
void Arma::update(float deltaTime) {
    for (auto it = proyectiles.begin(); it != proyectiles.end();) {
        int indice = std::distance(proyectiles.begin(), it);
        if (sentido_proyectiles[indice]) {
            it->update(deltaTime);
        }
        else {
            it->update(deltaTime * -1);
        }
        it->setTiempoVidaActual(1 * deltaTime);
        if (it->getTiempoVidaActual() >= it->getTiempoVidaMaximo()) {

            it = proyectiles.erase(it);
            sentido_proyectiles.erase(sentido_proyectiles.begin() + indice);
        }
        else {
            ++it;
        }
    }
}
void Arma::draw(sf::RenderWindow& window) {
    for (auto& proyectil : proyectiles) {
        proyectil.draw(window);
    }
}
