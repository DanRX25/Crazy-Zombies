#include "proyectil.h"
Proyectil::Proyectil(sf::Vector2f position, float velocity, float tiempoDeVidaMaximo)
    : velocity(velocity, 0.0f),tiempoDeVidaMaximo(tiempoDeVidaMaximo), tiempoDeVidaActual(0) {
    forma.setRadius(5.0f);
    forma.setPosition(position);
    forma.setFillColor(sf::Color::Red);
    ancho=forma.getRadius()*2;
    alto=ancho;
}

void Proyectil::update(float deltaTime) {
    forma.move(velocity * deltaTime);
}

void Proyectil::draw(sf::RenderWindow& window) {
    window.draw(forma);
}
float Proyectil::getTiempoVidaActual(){
    return tiempoDeVidaActual;
}
void Proyectil::setTiempoVidaActual(float a){
    tiempoDeVidaActual+=a;
}
float Proyectil::getTiempoVidaMaximo(){
    return tiempoDeVidaMaximo;
}
float Proyectil::getPosX(){
    return forma.getPosition().x;
}
float Proyectil::getPosY(){
    return forma.getPosition().y;
}
float Proyectil::getAlto(){
    return alto;
}
float Proyectil::getAncho(){
    return ancho;
}