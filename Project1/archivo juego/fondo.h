#ifndef FONDO_H
#define FONDO_H
#include <SFML/Graphics.hpp>
//#include <time.h>
//#include <type_traits>
#include <memory>

class Fondo {
private:
    std::unique_ptr<std::shared_ptr<sf::Sprite>[]> spritesFondo;
    float size, posX;

public:
    Fondo() ;

    Fondo(const sf::Sprite& spiter, float size)  ;

    void moverFondo(float reco, int x) ;

    sf::Sprite getData(int pos) ;
};
#endif
