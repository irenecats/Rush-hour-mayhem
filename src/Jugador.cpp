#include "Jugador.h"

Jugador* Jugador::claseJugador = nullptr;

Jugador* Jugador::instancia() {
    if(claseJugador == nullptr)
        claseJugador = new Jugador();

    return claseJugador;
}

//Al inicializar el jugador se carga la textura, se le asigna al Sprite y se posiciona en el juego
Jugador::Jugador(){
    std::string url ("resources/vehicles.png");
    TexturaContainer::instancia()->crearTextura(url, "Jugador");

    jugador.setTextura(TexturaContainer::instancia()->getTextura("Jugador"));

    jugador.setRectTextura(sf::IntRect(123,0, 67, 122));
    jugador.setPosition(151*32, 473*32); //(7232.0, 11072.0);
    jugador.setScale(0.6f, 0.6f);
    jugador.setOrigin(35, 45);

    lastState.Setx(jugador.getPosition()[0]);
    lastState.Sety(jugador.getPosition()[1]);

    newState.Setx(jugador.getPosition()[0]);
    newState.Sety(jugador.getPosition()[1]);


    url = "resources/arrow_1.png";
    TexturaContainer::instancia()->crearTextura(url, "Brujula");
    brujula.setTextura(TexturaContainer::instancia()->getTextura("Brujula"));
    brujula.getSprite().setColor(sf::Color::Red);

    brujula.setOrigin(brujula.getGlobalBounds()[0]/2,brujula.getGlobalBounds()[1]/2);
    brujula.setColor(sf::Color::Red);
    brujula.setScale(0.08f, 0.08f);
    brujula.setPosition(jugador.getPosition()[0], jugador.getPosition()[1]); //Al principio se coloca donde el personaje

    lastStateB.Setx(brujula.getPosition()[0]);
    lastStateB.Sety(brujula.getPosition()[1]);

    newStateB.Setx(brujula.getPosition()[0]);
    newStateB.Sety(brujula.getPosition()[1]);

    powerUp = 1;
    powerUp = 6;

}

Jugador::~Jugador()
{
    //dtor
}

Jugador::Jugador(const Jugador& other)
{
    //copy ctor
}

//Update con interpolacion que gestiona el movimiento del coche
void Jugador::update(int tiempo){

bool left=false, right=false, delante = false, atras = false, space = false/*, clocktwo=false, tope=false*/;
float dirx, diry, mv, kr;

    lastState.Setx(newState.Getx());
    lastState.Sety(newState.Gety());

    if(!chocando){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) delante = true;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) atras = true;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) right = true;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) left = true;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
            space = true;
            if(!powerUpActivado && powerUp==1){
                powerUpActivado=true;
                turbo.restart();
            }
            if(!powerUpActivado && powerUp==7){
                powerUpActivado=true;
                turbo.restart();
            }
        }
    }

        if(delante){
            if(vel<kMaxSpeed) vel+=0.1*kVel;
            if(vel<0) vel+=0.2*kVel;
        }

        if(atras){
            if(vel>-kMaxSpeed) vel-=0.1*kVel;
            if(vel>0) vel-=0.2*kVel;
        }


        if(!delante && !atras){
            if(vel>0){
                if(vel>0) vel -= kFr;
            }else if(vel<0){
                if(vel<0) vel += kFr;
            }
        }

        kr=kRot;

        if(powerUp==2 && space) kr = 0.5;

        if(vel!=0){
            //ajustar frenada
            if(vel<0.4 && vel>-0.4) vel = 0;
            if(right){
                jugador.rotar(1.0f*kr*vel);
            }
            if(left){
                jugador.rotar(-1.0f*kr*vel);
            }
        }

        mv = vel;

        if(powerUp==1 && powerUpActivado){
            if(turbo.getElapsedTime()<3000){
                if(space){
                    if(mv<kMaxSpeed*2) mv=mv*2;
                    zoom=true;
                }
            }else{
                zoom = false;
                if(turbo.getElapsedTime()>7000){
                    powerUpActivado=false;
                }
            }
        }

        dirx = sin(jugador.getRotation()*rad);
        diry = -cos(jugador.getRotation()*rad);

        //if(!chocando)jugador.mover(dirx*mv*tiempo*0.01, diry*mv*tiempo*0.01);
        if(!chocando)jugador.mover(dirx*mv, diry*mv);

        newState.Setx(jugador.getPosition()[0]);
        newState.Sety(jugador.getPosition()[1]);

        if(space && powerUp==5 && bala==nullptr){
            bala = new Bala(jugador.getPosition()[0], jugador.getPosition()[1], jugador.getRotation(), dirx, diry, mv);
        }

        if(bala!=nullptr && bala->getaborrar()){
            delete bala;
            bala = nullptr;
        }

        if(powerUp==7 && powerUpActivado){
            if(turbo.getElapsedTime()<4000){
                jugador.setColor(sf::Color(255,255,255,127));
                fant = true;
            }else{
                fant=false;
                jugador.setColor(sf::Color(255,255,255,255));
                if(turbo.getElapsedTime()>8000){
                    powerUpActivado=false;
                }
            }
        }
}

//Render con interpolacion
void Jugador::interpolar(float ptick){
    jugador.setPosition(lastState.Getx()*(1-ptick) + newState.Getx()*(ptick), lastState.Gety()*(1-ptick) + newState.Gety()*(ptick));
}

void Jugador::dibujar(Window& window){
    window.draw(jugador);
}

void Jugador::renderBrujula(Window& window, float ptick){
    brujula.setPosition(lastStateB.Getx()*(1-ptick) + newStateB.Getx()*(ptick), lastStateB.Gety()*(1-ptick) + newStateB.Gety()*(ptick));
    window.draw(brujula);
}

//Devuelve el Sprite del jugador
Sprite Jugador::getJugador(){
    return jugador;
}

Sprite Jugador::getBrujula(){
    return brujula;
}

//Asignamos el powerUp que tendra el jugador esta ronda
void Jugador::setPowerUp(int pw){
    powerUp = pw;
}

//Activamos el powerUp
void Jugador::activarPowerUp(){
    powerUpActivado = true;
}

bool Jugador::esFantasma(){
    return fant;
}

bool Jugador::muestroGuia(){
    bool guia = false;
    if(powerUp == 6){
        guia = true;
    }
    return guia;
}

bool Jugador::disparando(){
    if(bala == nullptr) return false;
    else return true;
}

Bala* Jugador::getBala(){
    return bala;
}

void Jugador::updateBrujula(float targetX, float targetY){

    lastStateB.Setx(newStateB.Getx());
    lastStateB.Sety(newStateB.Gety());

    float angulo = atan ((targetX - jugador.getPosition()[0]) /
                         (targetY - jugador.getPosition()[1])) * 180.0 / PI;

    //Ángulo desde el punto del personaje (el tercer ángulo es 90º pq es un triángulo rectángulo)
    float angulo2 = atan ((jugador.getPosition()[1] - targetY) /
                          (jugador.getPosition()[0] - targetX)) * 180.0 / PI;



    //Cálculos para que la flecha se coloque en un radio de 75 píxeles del personaje, en línea con el target
    if(jugador.getPosition()[0] < targetX)
        brujula.setPosition(jugador.getPosition()[0] + 75*cos(angulo2 * PI/180), jugador.getPosition()[1] + 75*sin(angulo2 * PI/180));

    else
        brujula.setPosition(jugador.getPosition()[0] - 75*cos(angulo2 * PI/180), jugador.getPosition()[1] - 75*sin(angulo2 * PI/180));

        newStateB.Setx(brujula.getPosition()[0]);
        newStateB.Sety(brujula.getPosition()[1]);

    //Cálculos que giran la flecha para que apunte al objetivo
    if(jugador.getPosition()[1] > targetY) {
        brujula.setRotation(-angulo+180);

    } else {
        brujula.setRotation(-angulo);
    }

}

void Jugador::setDinero(int money) {
    dinero += money;

    //Solo cuando se gana dinero se actualiza esta variable
    if(money > 0)
        dineroTotal += money;
}

int Jugador::getDinero() {
    return dinero;
}

int Jugador::getDineroTotal() {
    return dineroTotal;
}

void Jugador::frenar(float colx, float coly){
int retr=10;
if(powerUp==4) retr=5;

    jugador.setPosition(lastState.Getx(), lastState.Gety());
    newState.Setx(jugador.getPosition()[0]);
    newState.Sety(jugador.getPosition()[1]);

    chocando = true;


    float angulo2 = atan2 ((jugador.getPosition()[1] - coly),
                     (jugador.getPosition()[0] - colx)) * 180.0 / PI;

    if(angulo2<0) angulo2 = 360 + angulo2;

    if(angulo2>=45&&angulo2<135) jugador.mover(0, retr);
    if(angulo2>=135&&angulo2<225) jugador.mover(-1*retr, 0);
    if(angulo2>=225&&angulo2<315) jugador.mover(0, -1*retr);
    if(angulo2>=315||angulo2<45) jugador.mover(retr, 0);

    newState.Setx(jugador.getPosition()[0]);
    newState.Sety(jugador.getPosition()[1]);

    vel=0;

    if(powerUp!=3)colisiones++;
}

void Jugador::nofrenar(){
    chocando = false;
}

void Jugador::frenacoche(){
int retr=30;
if(powerUp==4) retr=20;
    jugador.setPosition(lastState.Getx(), lastState.Gety());
    newState.Setx(jugador.getPosition()[0]);
    newState.Sety(jugador.getPosition()[1]);

    chocando = true;

    float dirx = sin(jugador.getRotation()*rad);
    float diry = -cos(jugador.getRotation()*rad);

    jugador.mover(dirx*retr, diry*retr);

    newState.Setx(jugador.getPosition()[0]);
    newState.Sety(jugador.getPosition()[1]);

    vel=0;

    if(powerUp!=3)colisiones++;
}

int Jugador::getColisiones(){
    return colisiones;
}

void Jugador::borrarColisiones(){
    colisiones=0;
}

void Jugador::borraBala(){
     if(bala!=nullptr){
        delete bala;
        bala = nullptr;
    }
}

bool Jugador::getPowerUpActivado(){
    return powerUpActivado;
}

bool Jugador::getZoom(){
    return zoom;
}

float Jugador::getVel(){
    return vel;
}

int Jugador::getNumColisiones() {
    return numColisiones;
}

void Jugador::setNumColisiones(int numero) {
    if(numero > 0)
        numColisiones += numero;

    else
        numColisiones = 0;
}
