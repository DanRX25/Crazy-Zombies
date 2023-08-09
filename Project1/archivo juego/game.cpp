#include "game.h"
#include "barravida.h"
std::mutex enemigosMutex;
void newEnemigo(vector<Enemy>& enemigos) {
    Textura* textura1 = new Textura("images/zombie_camina.png", 10, 1);
    Enemy* enemigo1 = new Enemy(*textura1, 100, 0, 50.0f, 100.0f);
    std::lock_guard<std::mutex> lock(enemigosMutex);
    enemigos.push_back(*enemigo1);
}
Game::Game(RenderWindow& window, int alto, int ancho) {
        this->window = &window;
        this->alto = alto;
        this->ancho = ancho;
        actualPlayer = 0;
        actualObstaculo = 0;
        players = new Player[2];
        //zombies = new Enemy[20];
        cantidadPlayer =false;
    }
void Game::Inicio() {
    window->setFramerateLimit(60);
    Texture B_comenzar;
    B_comenzar.loadFromFile("images/B_Comenzar.PNG");
    Sprite Comenzar(B_comenzar);
    RectangleShape boton(Vector2f(485.0f, 114.0f));
    Button b_inicio(*window, boton, 485.0f, 114.0f, 356, 515, Color::Yellow, Comenzar);
    Texture fondo_inicio;
    fondo_inicio.loadFromFile("images/Portada.JPG");
    Sprite Fondo(fondo_inicio);
    while (window->isOpen()) {
        Event event;
        while (window->pollEvent(event))
        {
            Vector2i mousePosition = Mouse::getPosition(*window);
            if (event.type == Event::Closed)
                window->close();
            b_inicio.is_pressed(mousePosition, event);
        }
        window->clear();
        window->draw(Fondo);
        window->draw(b_inicio.getBoton());
        window->draw(b_inicio.getSprite());
        if (b_inicio.getEstado()) {
            this->Selec_Personajes();
        }
        window->display();
    }
}
void Game::Selec_Personajes() {
    Texture T_Fondo;
    T_Fondo.loadFromFile("images/Selec_Personajes.JPG");
    Sprite Fondo(T_Fondo);
    bool aux = false;
    Texture B_1;
    Texture B_2;
    Texture C_1;
    Texture C_2;
    C_1.loadFromFile("images/B_Controles_1.PNG");
    C_2.loadFromFile("images/B_Controles_2.PNG");
    B_1.loadFromFile("images/B_Personajes_1.PNG");
    B_2.loadFromFile("images/B_Personajes_2.PNG");
    Sprite Per_1(B_1);
    Sprite Per_2(B_2);
    Sprite Con_1(C_1);
    Sprite Con_2(C_2);
    RectangleShape jugadores_1(Vector2f(518.0f, 550.0f));
    Button b_jugadores1(*window, jugadores_1, 518.0f, 550.0f, 53, 55, Color::Yellow, Per_1);
    RectangleShape jugadores_2(Vector2f(518.0f, 550.0f));
    Button b_jugadores2(*window, jugadores_2, 518.0f, 550.0f, 629, 55, Color::Green, Per_2);
    RectangleShape rec(Vector2f(200.0f, 200.0f));
    rec.setFillColor(Color::Red);
    Textura makanaky2("images/loco_camina.png",8,1);
    Textura makanaky("images/maka_camina.png",8,1);
    Player p1(makanaky,700, 500,100.0f,300.0f, Keyboard::Right, Keyboard::Left, Keyboard::Up,sf::Keyboard::Space);
    this->setPlayers(p1);
    while (window->isOpen()) {
        Event event;
        while (window->pollEvent(event))
        {
            Vector2i mousePosition = Mouse::getPosition(*window);
            if (event.type == Event::Closed)
                window->close();
            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                while (Keyboard::isKeyPressed(Keyboard::Space)) {
                }
                if (aux) {
                    aux = false;
                    b_jugadores1.setSprite(Per_1);
                    b_jugadores2.setSprite(Per_2);
                }
                else {
                    aux = true;
                    b_jugadores1.setSprite(Con_1);
                    b_jugadores2.setSprite(Con_2);
                }
            }
            b_jugadores1.is_pressed(mousePosition, event);
            b_jugadores2.is_pressed(mousePosition, event);
        }
        window->clear();
        window->draw(Fondo);
        window->draw(b_jugadores1.getSprite());
        window->draw(b_jugadores2.getSprite());
        if (b_jugadores1.getEstado() || b_jugadores2.getEstado()) {
            if (b_jugadores2.getEstado()) {
               
                Player p2(makanaky2, 500, 500,100.0f,300.0f, Keyboard::D, Keyboard::A, Keyboard::W,sf::Keyboard::E);
                cantidadPlayer=true;
                this->setPlayers(p2);
            }
            this->Selec_Mapa();
        }
        window->display();
    }
}
void Game::Selec_Mapa() {
    Texture T_Fondo;
    T_Fondo.loadFromFile("images/Fondo.JPG");
    Sprite Fondo(T_Fondo);
    Texture T_Nivel_1;
    T_Nivel_1.loadFromFile("images/Nivel_1.PNG");
    Sprite Nivel1(T_Nivel_1);
    Texture T_Nivel_2;
    T_Nivel_2.loadFromFile("images/Nivel_2.PNG");
    Sprite Nivel2(T_Nivel_2);
    Texture T_Nivel_3;
    T_Nivel_3.loadFromFile("images/Nivel_3.PNG");
    Sprite Nivel3(T_Nivel_3);
    RectangleShape rec_map1(Vector2f(500.0f, 300.0f));
    Button Map1(*window, rec_map1, 500.0f, 300.0f, 50, 30, Color::Red, Nivel1);
    RectangleShape rec_map2(Vector2f(500.0f, 300.0f));
    Button Map2(*window, rec_map2, 500.0f, 300.0f, 650, 30, Color::Magenta, Nivel2);
    RectangleShape rec_map3(Vector2f(500.0f, 300.0f));
    Button Map3(*window, rec_map3, 500.0f, 300.0f, 350, 350, Color::Cyan, Nivel3);
    Map2.lock_button();
    Map3.lock_button();
    while (window->isOpen()) {
        Event event;
        while (window->pollEvent(event))
        {
            Vector2i mousePosition = Mouse::getPosition(*window);
            if (event.type == Event::Closed)
                window->close();
            Map1.is_pressed(mousePosition, event);
            Map2.is_pressed(mousePosition, event);
            Map3.is_pressed(mousePosition, event);
        }
        if (actualPlayer > 1) {
            Map2.un_lock_button();
        }
        window->clear();
        window->draw(Fondo);
        window->draw(Map3.getSprite());
        window->draw(Map2.getSprite());
        window->draw(Map1.getSprite());
        if (Map1.getEstado() || Map2.getEstado() || Map3.getEstado()) {
            if (Map1.getEstado()) {
                Mapa = Color::Red;
            }
            else if (Map2.getEstado()) {
                Mapa = Color::Magenta;
            }
            else {
                Mapa = Color::Cyan;
            }
            this->Ejecutar();
        }
        window->display();
    }
}
int Game::Ejecutar() {
    //----botones/rectangulos
    RectangleShape boton(Vector2f(50.0f, 50.0f));
    RectangleShape suelo(Vector2f(2000.0f, 50.0f));
    RectangleShape regresar(Vector2f(100.0f, 100.0f));
    //----texturas
    Texture B_comenzar;
    B_comenzar.loadFromFile("images/B_Pausa.PNG");
    Sprite Comenzar(B_comenzar);
    //----buttons
    Button b_regresar(*window, regresar, 100.0f, 100.0f, 1090, 15, Color::Yellow, Comenzar);
    //----obstaculos
    Textura pisot("images/piso_basico.png",1,1);
    Obstaculo piso(pisot, 0, 600);
    Textura piedra("images/piedra.png",1,1);
    Obstaculo o1(piedra, 600, 550);
    obstaculos.push_back(o1);
    //----enemigos
    Textura zombie("images/zombie_camina.png",10,1);
    Enemy enemigo1(zombie, -50, 500, 50.0f, 100.0f);
    Enemy enemigo2(zombie, 1300, 500, 50.0f, 100.0f);
    Enemy enemigo3(zombie, 900, 500, 50.0f, 100.0f);
    enemigos.push_back(enemigo1);
    enemigos.push_back(enemigo2);
    enemigos.push_back(enemigo3);
    //----fondos
    Texture fondo_edificio;
    fondo_edificio.loadFromFile("images/fondoCielo.PNG");
    Sprite fondo_e1(fondo_edificio);
    fondo_e1.setPosition(0.0f, 0.0f);
    Fondo f1(fondo_e1, 6);
    f1.moverFondo(0, 1);
    Texture fondo_cielo;
    fondo_cielo.loadFromFile("images/fondoEdificios.PNG");
    Sprite fondo_e2(fondo_cielo);
    Texture fondo_cielos;
    fondo_cielos.loadFromFile("images/fondoCielo.PNG");
    Sprite fondo_e3(fondo_cielos);
    //----vidas/reloj/control
    sf::Clock clock;
    JuegoControlador juegoC(cantidadPlayer,players,&obstaculos,enemigo1,piso,&f1);
    BarraVida vida_p1(10, 5, players[0].getPosX(), 50, sf::Color::Green, sf::Color::Red);
    BarraVida vida_p2(10, 5, players[1].getPosX(), 50, sf::Color::Green, sf::Color::Red);
    vida_p2.perderVida(5);
    std::thread zombieThread;
    int generador = 0;
    while (window->isOpen()) {
        generador++;
        Vector2i mousePosition = Mouse::getPosition(*window);
        Event event;
        while (window->pollEvent(event))
        {
            if (event.type == Event::Closed)
                window->close();
            b_regresar.is_pressed(mousePosition, event);
        }
        if (generador % 300 == 0)
        {
            if (zombieThread.joinable()) {
                zombieThread.join();
            }
            zombieThread = std::thread(newEnemigo, ref(enemigos));
        }
        float deltaTime = clock.restart().asSeconds();
        juegoC.controlarInput(deltaTime);
        for (int i = 0; i < actualPlayer; i++) {
            if (cont % 10 == 0) {
               players[i].mover(deltaTime, &obstaculos, piso, f1);
            }
        }

        for (int i = 0; i < enemigos.size();i++) {
            enemigos[i].mover(deltaTime, &obstaculos, players, piso, f1);
            enemigos[i].perseguir(deltaTime, &obstaculos, players, piso, f1);
        }
        for (int i = 0; i < actualPlayer; i++) {
            for (int j = 0; j < enemigos.size();j++) {
                for (int k = 0; k < players[i].getProyects().size();k++) {
                    if (colision<Proyectil, Enemy>(players[i].getProyects()[k], enemigos[j])) {
                        enemigos.erase(enemigos.begin() + j);
                        cantZombies--;
                        players[i].borrarProyectil(k);
                        if (i == 0) {
                            vida_p1.ganarVida(1);
                        }
                        else {
                            vida_p2.ganarVida(1);
                        }
                    }
                }
            }
        }
        for (int i = 0; i < actualPlayer; i++) {
            for (int j = 0; j < enemigos.size(); j++) {
                if (colision<Player, Enemy>(players[i], enemigos[j]) != 0) {
                    sf::Color redColor(255, 0, 0);
                    sf::Color originalColor = players[i].getSprite().getColor();
                    sf::Uint8 alpha = originalColor.a;
                    redColor.a = alpha;
                    players[i].getSprite().setColor(redColor);
                    vida_p1.perderVida(1);
                }
            }
        }
        for (int i = 0; i < actualPlayer; i++) {
            players[i].disparar();
        }
        for (int i = 0; i < actualPlayer; i++) {
            players[i].getArma().update(deltaTime);
        }
        window->clear(Mapa);
        window->draw(fondo_e3);
        window->draw(fondo_e2);
        if (b_regresar.getEstado()) {
            this->Pausa(b_regresar);
        }
        for (int i = 0; i < 6; i++) {
            window->draw(f1.getData(i));
        }
        window->draw(b_regresar.getSprite());
        window->draw(piso.getSprite(deltaTime));
        window->draw(o1.getSprite(deltaTime));
        for (int i = 0; i < actualPlayer; i++) {
            window->draw(players[i].getSprite());
        }
        vida_p1.mover(players[0].getPosX(), players[0].getPosY());
        if (actualPlayer == 2) {
            vida_p2.mover(players[1].getPosX(), players[1].getPosY());
        }
        for (int i = 0; i < 10; i++) {
            window->draw(vida_p1.getData(i));
            if (actualPlayer == 2) { window->draw(vida_p2.getData(i)); }

        }
        for (int i = 0; i < enemigos.size();i++) {
            window->draw(enemigos[i].getSprite());
        }
        for (int i = 0; i < actualPlayer; i++) {
            players[i].getArma().draw(*window);
        }
        window->display();
    }
    return EXIT_SUCCESS;
}
void Game::Pausa(Button& b_regresar) {
    Texture B_comenzar;
    B_comenzar.loadFromFile("images/B_Continuar.PNG");
    Sprite Comenzar(B_comenzar);
    Texture B_comenzar1;
    B_comenzar1.loadFromFile("images/B_Regresar.PNG");
    Sprite Comenzar1(B_comenzar1);
    RectangleShape rec_menu(Vector2f(600.0f, 500.0f));
    rec_menu.setPosition(300, 90);
    rec_menu.setFillColor(Color::White);
    RectangleShape rec_continue(Vector2f(250.0f, 200));
    Button Continue(*window, rec_continue, 550.0f, 100.0f, 325, 276, Color::Green, Comenzar);
    RectangleShape rec_salir(Vector2f(250.0f, 200));
    Button Salir(*window, rec_salir, 550.0f, 100.0f, 325, 431, Color::Red, Comenzar1);
    Texture Text_Fondo;
    Text_Fondo.loadFromFile("images/Pausa.JPG");
    Sprite Fondo(Text_Fondo);
    while (window->isOpen()) {
        Event event;
        while (window->pollEvent(event))
        {
            Vector2i mousePosition = Mouse::getPosition(*window);
            if (event.type == Event::Closed)
                window->close();
            Continue.is_pressed(mousePosition, event);
            Salir.is_pressed(mousePosition, event);
        }
        window->clear();
        window->draw(Fondo);
        window->draw(Continue.getSprite());
        window->draw(Salir.getSprite());
        if (Continue.getEstado()) {
            b_regresar.changeEstado();
            break;
        }
        if (Salir.getEstado()) {
            delete[] players;
            actualPlayer = 0;
            players = new Player[2];
            for (int i = 0; i < enemigos.size(); i++) {
                delete& enemigos[i];
            }
            this->Inicio();
        }
        window->display();
    }
}
