
/*#include <SFML/Graphics.hpp>
#include <time.h>
#include <type_traits>
#include <cmath>
#include <iostream>
using namespace sf;
using namespace std;

//------------------------------------------CLASE PROYECTIL-----------------------------------------------
class Proyectil {
public:
    Proyectil(sf::Vector2f, float, float);
    void update(float);
    void draw(sf::RenderWindow&);
    float getTiempoVidaActual();
    void setTiempoVidaActual(float);
    float getTiempoVidaMaximo();
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float tiempoDeVidaMaximo;
    float tiempoDeVidaActual;
};
Proyectil::Proyectil(sf::Vector2f position, float velocity, float tiempoDeVidaMaximo)
    : velocity(velocity, 0.0f), tiempoDeVidaMaximo(tiempoDeVidaMaximo), tiempoDeVidaActual(0) {
    shape.setRadius(5.0f);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Red);
}
void Proyectil::update(float deltaTime) {
    shape.move(velocity * deltaTime);
}
void Proyectil::draw(sf::RenderWindow& window) {
    window.draw(shape);
}
float Proyectil::getTiempoVidaActual() {
    return tiempoDeVidaActual;
}
void Proyectil::setTiempoVidaActual(float a) {
    tiempoDeVidaActual += a;
}
float Proyectil::getTiempoVidaMaximo() {
    return tiempoDeVidaMaximo;
}

//------------------------------------------CLASE ARMA-----------------------------------------------
class Arma {
public:
    Arma();
    void disparar(sf::Vector2f position, bool dir);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
private:
    std::vector<Proyectil> proyectiles;
    std::vector<bool> sentido_proyectiles;
    float velocidad;
    int intervalo_disparo;
    bool disparo_listo;
};
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

//------------------------------------------CLASE TEXTURA-----------------------------------------
class Textura
{
private:
    sf::Texture textura;
    int nColumnas;
    int nFilas;
    float tiempoTranscurrido;
    float tiempoXframe;
    int ancho;
    int alto;
    int actualFrameX;
    int actualFrameY;
    sf::Sprite sprite;
public:
    Textura();
    Textura(std::string ruta, int nCol, int nFil);
    ~Textura();
    sf::Sprite getSprite(float dt, float);
    void cambioSprite(float dt);
    float getAncho();
    float getAltura();
};
Textura::Textura() {
}
Textura::Textura(std::string ruta, int nCol, int nFil)
{
    textura = sf::Texture{};
    textura.loadFromFile(ruta);
    nColumnas = nCol;
    nFilas = nFil;
    tiempoTranscurrido = 0.0f;
    tiempoXframe = 0.25f;
    ancho = textura.getSize().x / nCol;
    alto = textura.getSize().y / nFil;
    sprite = sf::Sprite{ textura };
    actualFrameX = 0;
    actualFrameY = 0;
}
Textura::~Textura()
{
}
void Textura::cambioSprite(float dt) {
    tiempoTranscurrido += dt;
    if (tiempoTranscurrido != 0) {
        if (tiempoTranscurrido >= tiempoXframe) {
            actualFrameX = (actualFrameX + 1) % nColumnas;


            if (actualFrameX == 0) {
                actualFrameY = (actualFrameY + 1) % nFilas;
            }


            sprite.setTextureRect(sf::IntRect(actualFrameX * ancho, actualFrameY * alto, ancho, alto));


            tiempoTranscurrido -= tiempoXframe;
        }
    }
    else
        sprite.setTextureRect(sf::IntRect(0, 0, ancho, alto));

}
sf::Sprite Textura::getSprite(float dt, float dir) {
    cambioSprite(dt);

    sprite.setScale(dir, 1.0f);
    return sprite;
}
float Textura::getAltura() {
    return alto;
}
float Textura::getAncho() {
    return ancho;
}

//------------------------------------------CLASE OBSTACULO------------------------------------------
class Obstaculo {
    float ancho, alto;
    float posX, posY;
    float falsoPosx;
    RectangleShape obstaculo;
    Sprite obstaculoS;
    Textura obstaculoT;
public:
    Obstaculo();
    Obstaculo(Textura& rec, float x, float y);
    float getPosX();
    float getPosY()const;
    float getAlto();
    float getAncho();
    Sprite getSprite(float);

    void establecerSprite(float dt, float dir);
};
Obstaculo::Obstaculo() {
    posX = 0; posY = 0;
    alto = 0; ancho = 0;
}
Obstaculo::Obstaculo(Textura& rec, float x, float y) {
    posX = x;
    falsoPosx = x;
    posY = y;
    alto = rec.getAltura();
    ancho = rec.getAncho();
    obstaculoS.setPosition(posY, posY);
    obstaculoT = rec;
    obstaculoS = obstaculoT.getSprite(0, 1.0f);
}
float Obstaculo::getPosX() { return posX; }
float Obstaculo::getPosY()const { return posY; }
float Obstaculo::getAlto() { return alto; }
float Obstaculo::getAncho() { return ancho; }
Sprite Obstaculo::getSprite(float dt) {

    return obstaculoS;
}
void Obstaculo::establecerSprite(float dt, float dir) {
    obstaculoS = obstaculoT.getSprite(dt, dir);
}


//------------------------------------------CLASE FONDO-----------------------------------------
class fondo {
private:
    std::unique_ptr<std::shared_ptr<sf::Sprite>[]> spritesFondo;
    float size, posX;

public:
    fondo() : size(6), posX(0) {
        spritesFondo = std::make_unique<std::shared_ptr<sf::Sprite>[]>(size);
    }

    fondo(const sf::Sprite& spiter, float size) : size(size), posX(0) {
        spritesFondo = std::make_unique<std::shared_ptr<sf::Sprite>[]>(size);
        for (int i = 0; i < size; i++) {
            spritesFondo[i] = std::make_shared<sf::Sprite>(spiter);
        }
    }
    void moverFondo(float reco, int x) {
        if (reco >= 600 && reco <= 1360 * size) {
            for (int i = 0; i < size; i++) {
                posX += 0.075 * x;
                spritesFondo[i]->setPosition(posX + (1360 * i), 0);
            }
        }
    }
    sf::Sprite getData(int pos) {
        return *spritesFondo[pos];
    }
};

//------------------------------------------CLASE WAVE-------------------------------------------
class Wave {
private:
    int nivel, actualOleada, cantOleadas;
    Enemy* Enemigos;
public:
    Wave() { nivel = 0; actualOleada = 0; cantOleadas = 0; Enemigos = new Enemy[0]; }
    Wave(int level, Enemy& Enemies){
        this->nivel = level;
        cantOleadas = nivel + 1;
        actualOleada = 1;
        Enemigos = &Enemies;
    }
    void Start_Wave() {
        delete[] Enemigos;
        Enemigos = new Enemy[20 * nivel];
        for (int i = 0; i < cantOleadas * 20; i++) {
            Textura text_zombie("images/zombie_camina.png", 10, 1);
            Enemy zombie(text_zombie, 100, 0, 50.0f, 100.0f);
            Enemigos[i] = zombie;
        }
        for (int i = 20 * (actualOleada - 1); i < 20 * actualOleada; i++) {
            
        }
    }
};
*/
//------------------------------------------CLASE PLAYER------------------------------------------
/*
class Player {
protected:
    int velocidad;
    float alto, ancho;
    float posX, posY;
    Keyboard::Key derecha, izquierda, arriba;
    RectangleShape personaje;
public:
    Player() { 
        alto = 0; ancho = 0; 
        posX = 0; posY = 0; velocidad = 0;
        derecha = Keyboard::Right; izquierda = Keyboard::Left; arriba = Keyboard::Up;
    }
    Player(RectangleShape& rec, float heigh, float width, float x, float y, Keyboard::Key right, Keyboard::Key left, Keyboard::Key up, int vel) { 
        personaje = rec; 
        alto = heigh; ancho = width; 
        posX = x;posY = y; 
        derecha = right; izquierda = left; arriba = up; 
        personaje.setPosition(posX, posY); 
        velocidad = vel; 
    }
    ~Player() {
        velocidad = 0;
        alto = ancho = posX = posY = 0;
    }
    float getPosX() { return posX; }
    float getPosY() { return posY; }
    float getAlto() { return alto; }
    float getAncho() { return ancho; }
    int getVelocidad() { return velocidad; }
    void help_move(int);
    void mover(Obstaculo, Enemy, Obstaculo);
    void gravedad() { posY += 2; this->personaje.setPosition(posX, posY); }
    void salto() { posY -= 100; this->personaje.setPosition(posX, posY); }
    Keyboard::Key getDerecha() { return derecha; }
    Keyboard::Key getIzquierda() { return izquierda; }
    Keyboard::Key getArriba() { return arriba; }
    RectangleShape getSprite() { return personaje; }
};
void Player::help_move(int x) {
    posX += velocidad * x;
    this->personaje.setPosition(posX, posY);
}*/
//---------------------------------------------------------------------------------
/*
class Player {
protected:
    float velocidadX;
    float velocidadY;
    float velocidad;
    float vgravedad;
    float alto, ancho;
    float posX, posY;
    float recorrido;
    float direccion;
    bool enAire;
    Keyboard::Key derecha, izquierda, arriba, disparo;
    Textura personajeT;
    sf::Sprite personajeS;
    Arma arma;
    float ajustexsprite;
    bool hayColision;
public:
    Player() {
        alto = 0; ancho = 0;
        posX = 0; posY = 0; velocidadX = 0; recorrido = 0; direccion = 0;
        personajeS.setPosition(posX, posY);
    }
    Player(Textura& rec, float x, float y, float veloX, float veloY, Keyboard::Key right, Keyboard::Key left, Keyboard::Key up, sf::Keyboard::Key shoot) {
        personajeT = rec;
        personajeS = personajeT.getSprite(0, 1.0f);
        alto = rec.getAltura();
        ancho = rec.getAncho();
        posX = x;
        posY = y;
        recorrido = x;
        direccion = 1;
        derecha = right;
        izquierda = left;
        arriba = up;
        disparo = shoot;
        personajeS.setPosition(posX, posY);
        velocidadX = veloX;
        velocidadY = veloY;
        vgravedad = 450.0f;
        enAire = true;
        velocidad = 0;
        ajustexsprite = 0;
        hayColision = false;
    }
    ~Player() {
        velocidad = 0;
        alto = ancho = posX = posY = recorrido = 0;
    }
    float getPosX() { return posX; }
    float getPosY() { return posY; }
    float getAlto() { return alto; }
    float getAncho() { return ancho; }
    float getRecorrido() { return recorrido; }
    int getdireccion() { return direccion; }
    void help_move(float, float);
    void mover(float, vector<Obstaculo>* o1, Enemy, Obstaculo, fondo&);
    void salto() {
        this->personajeS.setPosition(posX, posY);
    }

    Sprite getSprite() {
        return personajeS;
    }
    void establecerSprite(float, float);
    Arma& getArma();
    void disparar();
    void moverDer(float, vector<Obstaculo>* o1, Enemy, Obstaculo, fondo&);
    void moverIzq(float, vector<Obstaculo>* o1, Enemy, Obstaculo, fondo&);
    void saltar(float, vector<Obstaculo>* o1, Enemy, Obstaculo, fondo&);
};
void Player::help_move(float x, float arregloxsprite) {
    posX += velocidadX * x;
    recorrido += velocidadX * x;
    this->personajeS.setPosition(posX + arregloxsprite, posY);
}

void Player::disparar() {
    if (sf::Keyboard::isKeyPressed(disparo))
    {
        if (direccion == 1)
        {
            arma.disparar(sf::Vector2f(posX + ancho, posY), true);
        }
        else {
            arma.disparar(sf::Vector2f(posX + ancho, posY), false);
        }
    }
}
Arma& Player::getArma() {
    return arma;
}
void Player::establecerSprite(float dt, float dir) {
    personajeS = personajeT.getSprite(dt, dir);
}

//------------------------------------------CLASE ENEMY------------------------------------------
class Enemy {
    float ancho, alto;
    float posX, posY;
    RectangleShape enemigo;
    Textura personajeT;
    Sprite personajeS;
    float ajustexsprite;
    float direccion;
    float velocidadX;
    float velocidadY;
    float recorrido;
    bool enAire;
    float vgravedad;
    float velocidad;
    bool hayColision;
public:
    Enemy();
    Enemy(Textura& rec, float x, float y, float velx, float vely);
    float getPosX();
    float getPosY();
    float getAlto();
    float getAncho();
    void mover(RectangleShape&);
    Sprite getSprite();
    void establecerSprite(float, float);
    void moverIzq(float dt, vector<Obstaculo>* o1, Player* p1, Obstaculo piso, fondo& ff);
    void moverDer(float dt, vector<Obstaculo>* o1, Player* p1, Obstaculo piso, fondo& ff);
    void help_move(float x, float arregloxsprite);
    void mover(float dt, vector<Obstaculo>* o1, Player* p1, Obstaculo piso, fondo& ff);
    void perseguir(float dt, vector<Obstaculo>* o1, Player* p1, Obstaculo piso, fondo& ff);
};

//------------------------------------------CLASE BUTTON------------------------------------------
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
    void changeEstado(){
        if (estado == true) {
            estado = false;
        }
        else
            estado = true;
    }
    void lock_button() { lock = true; }
    void un_lock_button() { lock = false; }
};
void Button::is_pressed(Vector2i mousePosition, Event event) {
    if (mousePosition.x >= posX && mousePosition.x <= posX + Ancho && mousePosition.y >= posY && mousePosition.y <= posY + Alto && estado == false) {
        if (event.type == Event::MouseButtonPressed && !lock) {
                estado = true;
        }
        spr.setScale(1 + 0.01f, 1 + 0.01f);
        spr.setPosition(posX - 1.5, posY - 1.5);
    }
    else {
        spr.setScale(1, 1);
        spr.setPosition(posX, posY);
    }
}

//------------------------------------CLASE JUEGOCONTROLADOR---------------------------------------
class JuegoControlador {
    Player* ps;
    Player* p2;
    vector<Obstaculo>* o1;
    Obstaculo piso;
    Enemy e1;
    fondo* f1;
    float dt;
    bool nplayer;
public:
    JuegoControlador();
    JuegoControlador(bool, Player* player1, vector<Obstaculo>* o1, Enemy e1, Obstaculo piso, fondo* ff);
    void controlarInput(float);
};
    JuegoControlador::JuegoControlador() {}
    JuegoControlador::JuegoControlador(bool nPlayers, Player* players, vector<Obstaculo>* o1, Enemy e1, Obstaculo piso, fondo* ff) {
        ps = players;
        this->e1 = e1;
        this->o1 = o1;
        this->piso = piso;
        this->f1 = ff;
        this->nplayer = nPlayers;
    }
    void JuegoControlador::controlarInput(float dt) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            ps->moverDer(dt, o1, e1, piso, *f1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            ps->moverIzq(dt, o1, e1, piso, *f1);

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            ps->saltar(dt, o1, e1, piso, *f1);

        }
        if (nplayer)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                (ps + 1)->moverDer(dt, o1, e1, piso, *f1);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                (ps + 1)->moverIzq(dt, o1, e1, piso, *f1);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                (ps + 1)->saltar(dt, o1, e1, piso, *f1);
            }
        }
    }

//------------------------------------------CLASE GAME-----------------------------------------
class Game {
    RenderWindow* window;
    Player* players;
    vector<Obstaculo> obstaculos;
    Color Mapa;
    int ancho, alto;
    int actualPlayer;
    int actualObstaculo;
    int cont = 0;
    bool cantidadPlayer;
    int cantidadObstaculo;
public:
    Game(RenderWindow& window, int alto, int ancho);
    void setPlayers(Player& p) { players[actualPlayer] = p; ++actualPlayer; }
    void setObstaculos(Obstaculo& o) { obstaculos[actualObstaculo] = o; ++actualObstaculo; }

    void Inicio();
    int Ejecutar();
    void Selec_Personajes();
    void Selec_Mapa();
    void Pausa(Button&);
};
Game::Game(RenderWindow& window, int alto, int ancho) {
    this->window = &window;
    this->alto = alto;
    this->ancho = ancho;
    actualPlayer = 0;
    actualObstaculo = 0;
    players = new Player[3];
    cantidadPlayer = false;
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
        window->draw(b_inicio.getSprite());
        if (b_inicio.getEstado()) {
            this->Selec_Personajes();
        }
        window->display();
    }
}

//------------------------------------------COLISIONES------------------------------------------

template <typename T, typename U>
int colision(T user, U object) {
    bool altura = (user.getPosY() + user.getAlto()) > object.getPosY() && (user.getPosY() + user.getAlto()) < (object.getPosY() + object.getAlto());
    if (user.getPosX() <= object.getPosX() + object.getAncho() && user.getPosX() >= object.getPosX() + (object.getAncho() / 2) && altura)
        return -1;
    if (user.getPosX() + user.getAncho() >= object.getPosX() && user.getPosX() + user.getAncho() <= object.getPosX() + (object.getAncho() / 2) && altura)
        return 1;
    return 0;
}
template <typename T, typename U>
bool DetectSuelo(T user, U object) {
    bool ancho = user.getPosX() <= (object.getPosX() + object.getAncho()) && (user.getPosX() + user.getAncho() >= object.getPosX());
    if ((is_same<T, Player>::value || is_same<T, Enemy>::value) && is_same<U, Obstaculo>::value) {
        if ((user.getPosY() + user.getAlto()) >= object.getPosY() && (user.getPosY() + user.getAlto()) <= (object.getPosY() + object.getAlto()) && ancho)
            return true;
        return false;
    }
}

template<typename T, typename U>
bool colision(const T user, const U* object, const int actualEn, const int actualObs) {
    if (is_same<T, Player>::value || is_same<T, Enemy>::value || is_same<T, RectangleShape>::value && is_same<U, Enemy>::value){
        for (int i = 0; i < actualEn; i++) {
            bool altura = (user.getPosY() + user.getAlto()) > object[i]->getPosY() && (user.getPosY() + user.getAlto()) < (object[i]->getPosY() + object[i]->getAlto());
            if (user.getPosX() <= object[i]->getPosX() + object[i]->getAncho() && user.getPosX() >= object[i]->getPosX() + (object[i]->getAncho() / 2) && altura)
                return -1;
            if (user.getPosX() + user.getAncho() >= object[i]->getPosX() && user.getPosX() + user.getAncho() <= object[i]->getPosX() + (object[i]->getAncho() / 2) && altura)
                return 1;
        }
        return 0;
    }
    if (is_same<T, Player>::value || is_same<T, Enemy>::value || is_same<T, RectangleShape>::value && is_same<U, Obstaculo>::value){
        for (int i = 0; i < actualObs; i++) {
            bool altura = (user.getPosY() + user.getAlto()) > object[i]->getPosY() && (user.getPosY() + user.getAlto()) < (object[i]->getPosY() + object[i]->getAlto());
            if (user.getPosX() <= object[i]->getPosX() + object[i]->getAncho() && user.getPosX() >= object[i]->getPosX() + (object[i]->getAncho() / 2) && altura)
                return -1;
            if (user.getPosX() + user.getAncho() >= object[i]->getPosX() && user.getPosX() + user.getAncho() <= object[i]->getPosX() + (object[i]->getAncho() / 2) && altura)
                return 1;
        }
        return 0;
    }
}
*/
//------------------------------------------PLAYER - MOVER------------------------------------------
/*
void Player::mover(Obstaculo o1, Enemy e1, Obstaculo piso) {
    if (Keyboard::isKeyPressed(izquierda)) {
        if (!(colision<Player, Obstaculo>(*this, o1) == -1 || colision<Player, Enemy>(*this, e1) == -1)) {
            this->help_move(-1);
        }
    }
    if (Keyboard::isKeyPressed(derecha)) {
        if (!(colision<Player, Obstaculo>(*this, o1) == 1 || colision<Player, Enemy>(*this, e1) == 1)) {
            this->help_move(1);
        }
    }
    if (Keyboard::isKeyPressed(arriba)) {
        if (DetectSuelo<Player, Obstaculo>(*this, piso) || DetectSuelo<Player, Obstaculo>(*this, o1))
            this->salto();
    }
}
*//*
void Player::moverDer(float dt, vector<Obstaculo>* o1, Enemy e1, Obstaculo piso, fondo& ff) {
    ajustexsprite = 0;
    direccion = 1;
    hayColision = false;
    for (vector<Obstaculo>::size_type i = 0;i < o1->size();++i) {
        if (colision<Player, Obstaculo>(*this, (*o1)[i]) == 1 || colision<Player, Enemy>(*this, e1) == 1) {
            hayColision = true;
            break;

        }
    }
    if (!hayColision) {
        establecerSprite(dt, direccion);
        this->help_move(1 * dt, ajustexsprite);
        for (vector<Obstaculo>::size_type i = 0;i < o1->size();++i) {
            if (colision<Player, Obstaculo>(*this, (*o1)[i])) {
                this->help_move(-1 * dt, ajustexsprite);
                break;
            }
        }
        enAire = true;
    }
}
void Player::moverIzq(float dt, vector<Obstaculo>* o1, Enemy e1, Obstaculo piso, fondo& ff) {
    ajustexsprite = ancho;
    direccion = -1;
    hayColision = false;
    for (vector<Obstaculo>::size_type i = 0;i < o1->size();++i) {
        if (colision<Player, Obstaculo>(*this, (*o1)[i]) == -1 || colision<Player, Enemy>(*this, e1) == -1) {
            hayColision = true;
            break;
        }
        enAire = true;
    }
    if (!hayColision) {
        establecerSprite(dt, direccion);
        this->help_move(-1 * dt, ajustexsprite);
        for (vector<Obstaculo>::size_type i = 0;i < o1->size();++i) {
            if (colision<Player, Obstaculo>(*this, (*o1)[i])) {
                this->help_move(1 * dt, ajustexsprite);
                break;
            }
        }
    }
}
void Player::saltar(float dt, vector<Obstaculo>* o1, Enemy e1, Obstaculo piso, fondo& ff) {
    for (vector<Obstaculo>::size_type i = 0;i < o1->size();++i) {
        if (DetectSuelo<Player, Obstaculo>(*this, piso) || DetectSuelo<Player, Obstaculo>(*this, (*o1)[i])) {
            velocidad = velocidadY;
            enAire = true;
            break;
        }
    }
}
void Player::mover(float dt, vector<Obstaculo>* o1, Enemy e1, Obstaculo piso, fondo& ff) {
    if (enAire) {
        posY -= velocidad * dt;
        velocidad -= vgravedad * dt;
        for (vector<Obstaculo>::size_type i = 0;i < o1->size();++i) {
            if ((posY > (*o1)[i].getPosY() - alto) && posX + ancho >= (*o1)[i].getPosX() && posX <= (*o1)[i].getPosX() + (*o1)[i].getAncho()) {
                posY = (*o1)[i].getPosY() - alto;
                velocidad = 0;
                enAire = false;
            }
        }
        if ((posY > piso.getPosY() - alto) && posX + ancho >= piso.getPosX() && posX <= piso.getPosX() + piso.getAncho()) {
            posY = piso.getPosY() - alto;
            velocidad = 0;
            enAire = false;
        }
        this->personajeS.setPosition(posX + ajustexsprite, posY);
    }
}

//------------------------------------------ENEMY - MOVER------------------------------------------
Enemy::Enemy() {
    posX = 0; posY = 0;
    alto = 0; ancho = 0;
}
Enemy::Enemy(Textura& rec, float x, float y, float velx, float vely) {
    personajeT = rec;
    personajeS = personajeT.getSprite(0, 1.0f);
    posX = x;
    posY = y;
    alto = rec.getAltura();
    ancho = rec.getAncho();
    enemigo.setPosition(posX, posY);
    ajustexsprite = 0;
    velocidadX = velx;
    velocidadY = vely;
    vgravedad = 450.0f;
    enAire = true;
    velocidad = 0;
    recorrido = 0;
    hayColision = false;
}
float Enemy::getPosX() { return posX; }
float Enemy::getPosY() { return posY; }
float Enemy::getAlto() { return alto; }
float Enemy::getAncho() { return ancho; }
void Enemy::moverDer(float dt, vector<Obstaculo>* o1, Player* p1, Obstaculo piso, fondo& ff) {
    hayColision = false;
    ajustexsprite = ancho;
    direccion = -1;
    for (vector<Obstaculo>::size_type i = 0;i < o1->size();++i) {
        if (colision<Enemy, Obstaculo>(*this, (*o1)[i]) == 1 || colision<Enemy, Player>(*this, *p1) == 1) {
            hayColision = true;
            break;
        }
    }
    if (!hayColision) {
        establecerSprite(dt, direccion);
        this->help_move(1 * dt, ajustexsprite);
        for (vector<Obstaculo>::size_type i = 0;i < o1->size();++i) {
            if (colision<Enemy, Obstaculo>(*this, (*o1)[i])) {
                this->help_move(-1 * dt, ajustexsprite);
                break;
            }
        }
        enAire = true;
    }
}
void Enemy::moverIzq(float dt, vector<Obstaculo>* o1, Player* p1, Obstaculo piso, fondo& ff) {
    ajustexsprite = 0;
    direccion = 1;
    hayColision = false;
    for (vector<Obstaculo>::size_type i = 0;i < o1->size();++i) {
        if (colision<Enemy, Obstaculo>(*this, (*o1)[i]) == -1 || colision<Enemy, Player>(*this, *p1) == -1) {
            hayColision = true;
            break;
        }
    }
    if (!hayColision) {
        establecerSprite(dt, direccion);
        this->help_move(-1 * dt, ajustexsprite);
        for (vector<Obstaculo>::size_type i = 0;i < o1->size();++i) {
            if (colision<Enemy, Obstaculo>(*this, (*o1)[i])) {
                this->help_move(1 * dt, ajustexsprite);
                break;
            }
        }
        enAire = true;
    }
}
void Enemy::mover(float dt, vector<Obstaculo>* o1, Player* e1, Obstaculo piso, fondo& ff) {
    if (enAire) {
        posY -= velocidad * dt;
        velocidad -= vgravedad * dt;
        for (vector<Obstaculo>::size_type i = 0;i < o1->size();++i) {
            if ((posY > (*o1)[i].getPosY() - alto) && posX + ancho >= (*o1)[i].getPosX() && posX <= (*o1)[i].getPosX() + (*o1)[i].getAncho()) {
                posY = (*o1)[i].getPosY() - alto;
                velocidad = 0;
                enAire = false;
            }
        }
        if ((posY > piso.getPosY() - alto) && posX + ancho >= piso.getPosX() && posX <= piso.getPosX() + piso.getAncho()) {
            posY = piso.getPosY() - alto;
            velocidad = 0;
            enAire = false;
        }
        this->personajeS.setPosition(posX + ajustexsprite, posY);
    }
}
void Enemy::perseguir(float dt, vector<Obstaculo>* o1, Player* p1, Obstaculo piso, fondo& ff) {
    if (p1[0].getPosX() <= posX && p1[0].getPosY() <= posY) {
        moverIzq(dt, o1, p1, piso, ff);
    }
    else if (p1[0].getPosX() >= posX && p1[0].getPosY() >= posY) {
        moverDer(dt, o1, p1, piso, ff);
    }
    else if (p1[0].getPosX() <= posX && p1[0].getPosY() >= posY) {
        moverIzq(dt, o1, p1, piso, ff);
    }
    else if (p1[0].getPosX() >= posX && p1[0].getPosY() <= posY) {
        moverDer(dt, o1, p1, piso, ff);
    }
}
Sprite Enemy::getSprite() {
    return personajeS;
}
void Enemy::establecerSprite(float dt, float dir) {
    personajeS = personajeT.getSprite(dt, dir);
}
void Enemy::mover(RectangleShape& jugador) {
    jugador.setPosition(posX, posY);
}
void Enemy::help_move(float x, float arregloxsprite) {
    posX += velocidadX * x;
    recorrido += velocidadX * x;
    this->personajeS.setPosition(posX + arregloxsprite, posY);
}

//------------------------------------------GAME - FUNCTIONS------------------------------------------
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
    Textura makanaky2("images/loco_camina.png", 8, 1);
    Textura makanaky("images/maka_camina.png", 8, 1);
    Player p1(makanaky, 50, 50, 100.0f, 300.0f, Keyboard::Right, Keyboard::Left, Keyboard::Up, sf::Keyboard::Space);
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
        window->draw(b_jugadores1.getBoton());
        window->draw(b_jugadores2.getBoton());
        window->draw(b_jugadores1.getSprite());
        window->draw(b_jugadores2.getSprite());
        if (b_jugadores1.getEstado() || b_jugadores2.getEstado()) {
            if (b_jugadores2.getEstado()) {

                Player p2(makanaky2, 50, 50, 100.0f, 300.0f, Keyboard::D, Keyboard::A, Keyboard::W, sf::Keyboard::E);
                cantidadPlayer = true;
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
    Texture B_comenzar;
    B_comenzar.loadFromFile("images/Nivel.JPG");
    Sprite Comenzar(B_comenzar);
    RectangleShape rec_map1(Vector2f(500.0f, 300.0f));
    Button Map1(*window, rec_map1, 500.0f, 300.0f, 50, 30, Color::Red, Comenzar);
    RectangleShape rec_map2(Vector2f(500.0f, 300.0f));
    Button Map2(*window, rec_map2, 500.0f, 300.0f, 650, 30, Color::Magenta, Comenzar);
    RectangleShape rec_map3(Vector2f(500.0f, 300.0f));
    Button Map3(*window, rec_map3, 500.0f, 300.0f, 350, 350, Color::Cyan, Comenzar);
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
    RectangleShape boton(Vector2f(50.0f, 50.0f));
    RectangleShape suelo(Vector2f(2000.0f, 50.0f));
    RectangleShape regresar(Vector2f(100.0f, 100.0f));
    Texture B_Pausa;
    B_Pausa.loadFromFile("images/B_Pausa.PNG");
    Sprite Pausa(B_Pausa);
    Button b_regresar(*window, regresar, 100.0f, 100.0f, 1090, 10, Color::Yellow, Pausa);
    Textura pisot("images/piso_basico.png", 1, 1);
    Obstaculo piso(pisot, 0, 600);
    suelo.setFillColor(Color::Green);
    Texture fondo_edificio;
    fondo_edificio.loadFromFile("images/fondo1.jpg");
    Sprite fondo_e1(fondo_edificio);
    fondo_e1.setPosition(0.0f, 0.0f);
    fondo f1(fondo_e1, 6);
    f1.moverFondo(0, 1);
    Textura piedra("images/piedra.png", 1, 1);
    Obstaculo o1(piedra, 600, 550);
    obstaculos.push_back(o1);
    Textura zombie("images/zombie_camina.png", 10, 1);
    Enemy enemigo1(zombie, 100, 0, 50.0f, 100.0f);
    sf::Clock clock;
    JuegoControlador juegoC(cantidadPlayer, players, &obstaculos, enemigo1, piso, &f1);
    while (window->isOpen()) {
        Vector2i mousePosition = Mouse::getPosition(*window);
        Event event;
        while (window->pollEvent(event))
        {
            if (event.type == Event::Closed)
                window->close();
            b_regresar.is_pressed(mousePosition, event);
        }
        float deltaTime = clock.restart().asSeconds();
        juegoC.controlarInput(deltaTime);
        for (int i = 0; i < actualPlayer; i++) {
            if (cont % 10 == 0) {
                players[i].mover(deltaTime, &obstaculos, enemigo1, piso, f1);
            }
        }
        enemigo1.mover(deltaTime, &obstaculos, players, piso, f1);
        enemigo1.perseguir(deltaTime, &obstaculos, players, piso, f1);
        for (int i = 0; i < actualPlayer; i++) {
            players[i].disparar();
        }
        for (int i = 0; i < actualPlayer; i++) {
            players[i].getArma().update(deltaTime);
        }
        window->clear(Mapa);
        if (b_regresar.getEstado()) {
            this->Pausa(b_regresar);
        }
        for (int i = 0; i < 6; i++) {
            window->draw(f1.getData(i));
        }
        window->draw(b_regresar.getBoton());
        window->draw(piso.getSprite(deltaTime));
        window->draw(o1.getSprite(deltaTime));
        for (int i = 0; i < actualPlayer; i++) {
            window->draw(players[i].getSprite());
        }
        window->draw(enemigo1.getSprite());
        for (int i = 0; i < actualPlayer; i++) {
            players[i].getArma().draw(*window);
        }
        window->display();
    }
    return EXIT_SUCCESS;
}
void Game::Pausa(Button &b_regresar) {
    Texture B_Cotinuar;
    B_Cotinuar.loadFromFile("images/B_Continuar.PNG");
    Sprite Continuar(B_Cotinuar);
    Texture B_Exit;
    B_Exit.loadFromFile("images/B_Regresar.PNG");
    Sprite Exit(B_Exit);
    RectangleShape rec_menu(Vector2f(600.0f, 500.0f));
    rec_menu.setPosition(300, 90);
    rec_menu.setFillColor(Color::White);
    RectangleShape rec_continue(Vector2f(250.0f, 200));
    Button Continue(*window, rec_continue, 550.0f, 100.0f, 325, 276, Color::Green, Continuar);
    RectangleShape rec_salir(Vector2f(250.0f, 200));
    Button Salir(*window, rec_salir, 550.0f, 100.0f, 325, 431, Color::Red, Exit);
    Texture T_Fondo;
    T_Fondo.loadFromFile("images/Pausa.JPG");
    Sprite Fondo(T_Fondo);
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
        //---Botones
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
            this->Inicio();
        }
        window->display();
    }
}

//------------------------------------------INT MAIN------------------------------------------
int main()
{
    RenderWindow window(VideoMode(1200, 680), "Crazy-Zombies");
    Game juego(window, 1200, 680);
    juego.Inicio();
    return 0;
}*/