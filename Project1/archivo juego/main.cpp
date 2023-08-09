#include "game.h"

using namespace sf;
/* int main() {
    Texture fondo;
    fondo.loadFromFile("ima/fondo1.jpg");
    Sprite fondoSprite(fondo);
    Escenario escenario(fondoSprite);

    sf::RenderWindow window(VideoMode(1360, 768), "My game");
    Game juego(&window,&escenario);

    Textura makanaky("ima/maka_camina.png",8,1);
    Player p1(makanaky,50, 50,100.0f,300.0f, Keyboard::Right, Keyboard::Left, Keyboard::Up,sf::Keyboard::Space);
    juego.setPlayers(p1);


    juego.Ejecutar();


} */
int main()
{
    RenderWindow window(VideoMode(1200, 680), "Crazy-Zombies");
    Game juego(window, 1200, 680);
    juego.Inicio();
    return 0;
}
