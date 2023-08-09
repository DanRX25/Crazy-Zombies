#include "fondo.h"
Fondo::Fondo() : size(6), posX(0) {
        spritesFondo = std::make_unique<std::shared_ptr<sf::Sprite>[]>(size);
    }
    Fondo::Fondo(const sf::Sprite& spiter, float size) : size(size), posX(0) {
        spritesFondo = std::make_unique<std::shared_ptr<sf::Sprite>[]>(size);
        for (int i = 0; i < size; i++) {
            spritesFondo[i] = std::make_shared<sf::Sprite>(spiter);
        }
    }
void Fondo::moverFondo(float reco, int x) {
        if (reco >= 600 && reco <= 1360 * size) {
            for (int i = 0; i < size; i++) {
                posX += 0.075 * x;
                spritesFondo[i]->setPosition(posX + (1360 * i), 0);
            }
        }
    }
sf::Sprite Fondo::getData(int pos) {
        return *spritesFondo[pos];
    }