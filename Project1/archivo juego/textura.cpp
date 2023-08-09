#include "textura.h"
Textura::Textura(){}
Textura::Textura(std::string ruta, int nCol, int nFil)
{
    textura = sf::Texture{};
    textura.loadFromFile(ruta);
    nColumnas=nCol;
    nFilas=nFil;
    tiempoTranscurrido=0.0f;
    tiempoXframe=0.25f;
    ancho = textura.getSize().x/nCol;
    alto = textura.getSize().y/nFil;
    sprite=sf::Sprite{textura};
    actualFrameX=-1;
    actualFrameY=-1;
}

Textura::~Textura()
{
}
void Textura::cambioSprite(float dt){
    tiempoTranscurrido += dt;
    if(tiempoTranscurrido!=0){
        if (tiempoTranscurrido >= tiempoXframe) {
            actualFrameX = (actualFrameX + 1) % nColumnas;

            if (actualFrameX == 0) {
                actualFrameY = (actualFrameY + 1) % nFilas;
            }

            sprite.setTextureRect(sf::IntRect(actualFrameX * ancho, actualFrameY * alto, ancho  , alto));

            tiempoTranscurrido -= tiempoXframe;
        }
    }else
        sprite.setTextureRect(sf::IntRect(0, 0, ancho, alto));
    
}
sf::Sprite Textura::getSprite(float dt,float dir){
    cambioSprite(dt);
    sprite.setScale(dir,1.0f);/*
    sf::Color redColor(255, 0, 0); // Rojo
    // Obtener el color actual del sprite (para no afectar los píxeles transparentes)
    sf::Color originalColor = sprite.getColor();

    // Aplicar el color rojo solo a los píxeles no transparentes
    sf::Uint8 alpha = originalColor.a;
    redColor.a = alpha; // Mantener el canal alfa del color original
    sprite.setColor(redColor);*/
    return sprite;
}
float Textura::getAltura(){
    return alto;
}
float Textura::getAncho(){
    return ancho;
}