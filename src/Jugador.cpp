#include "Jugador.h"

Jugador* Jugador::claseJugador = nullptr;

Jugador* Jugador::instancia() {
    if(claseJugador == nullptr)
        claseJugador = new Jugador();

    return claseJugador;
}

//Al inicializar el jugador se carga la textura, se le asigna al Sprite y se posiciona en el juego
Jugador::Jugador(){
    std::string url ("resources/spritesheet_vehicles.png");
    TexturaContainer::instancia()->crearTextura(url, "Jugador");

    jugador.setTextura(TexturaContainer::instancia()->getTextura("Jugador"));

    jugador.setRectTextura(sf::IntRect(2*70 + 5, 3*131 - 12, 70, 128));
    jugador.setPosition(1000, 1000);
    jugador.setScale(0.25f, 0.25f);
    jugador.setOrigin(35, 35);

    lastState.Setx(jugador.getPosition()[0]);
    lastState.Sety(jugador.getPosition()[1]);

    newState.Setx(jugador.getPosition()[0]);
    newState.Sety(jugador.getPosition()[1]);


    url = "resources/arrow.png";
    TexturaContainer::instancia()->crearTextura(url, "Brujula");
    brujula.setTextura(TexturaContainer::instancia()->getTextura("Brujula"));

    brujula.setOrigin(brujula.getGlobalBounds()[0]/2,brujula.getGlobalBounds()[1]/2);
    brujula.setScale(0.03f, 0.03f);
    brujula.setPosition(jugador.getPosition()[0], jugador.getPosition()[1]); //Al principio se coloca donde el personaje


    powerUp = 3;
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
void Jugador::update(){

bool left=false, right=false, delante = false, atras = false, space = false, clocktwo=false, tope=false;
float dirx, diry, mv, kr;

    lastState.Setx(newState.Getx());
    lastState.Sety(newState.Gety());

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) delante = true;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) atras = true;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) right = true;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) left = true;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) space = true;
    //Controlar aqui tambien si se activa el powerup

        if(delante){
            if(vel<kMaxSpeed) vel+=0.1*kVel;
        }

        if(atras){
            if(vel>-kMaxSpeed) vel-=0.1*kVel;
        }


        if(!delante && !atras){
            if(vel>0){
                if(vel>0) vel -= kFr;
            }else if(vel<0){
                if(vel<0) vel += kFr;
            }
        }

        kr=kRot;

        if(powerUpActivado){

            switch(powerUp){
                case 1:
                    std::cout << "Tenemos el turbo" << std::endl;

                    if(space){
                        if(mv<kMaxSpeed*2) mv=mv*2;
                    //if(abs(vel)>0.1 && view.getSize().x<640) view.zoom(1.001f);
                    //if(abs(vel)<0.1 && view.getSize().x>512)view.zoom(0.999f);
                    } //else if(view.getSize().x>512) view.zoom(0.999f);

                    break;
                case 2:
                    std::cout << "Tenemos el giro cerrado" << std::endl;
                    if(space){ kr = 1;}
                    break;
                case 3:
                    std::cout << "Tenemos el lanzacohetes" << std::endl;
                    break;
                default:
                    std::cout << "No tenemos powerUp" << std::endl;
                    break;

            }

        }


        if(vel!=0){
            //ajustar frenada
            if(vel<0.01 && vel>-0.01) vel = 0;
            if(right){
                jugador.rotar(1.0f*kr*vel);
            }
            if(left){
                jugador.rotar(-1.0f*kr*vel);
            }
        }

        mv = vel;

        dirx = sin(jugador.getRotation()*rad);
        diry = -cos(jugador.getRotation()*rad);

        jugador.mover(dirx*mv, diry*mv);

        newState.Setx(jugador.getPosition()[0]);
        newState.Sety(jugador.getPosition()[1]);

        if(space && powerUp==3 && bala==nullptr){
            bala = new Bala(jugador.getPosition()[0], jugador.getPosition()[1], jugador.getRotation(), dirx, diry);
        }

        if(bala!=nullptr && bala->getaborrar()){
            delete bala;
            bala = nullptr;
        }

}

//Render con interpolacion
void Jugador::render(Window& window, float ptick){
    jugador.setPosition(lastState.Getx()*(1-ptick) + newState.Getx()*(ptick), lastState.Gety()*(1-ptick) + newState.Gety()*(ptick));
    window.draw(jugador);
}

void Jugador::renderBrujula(Window& window, float ptick){
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

bool Jugador::disparando(){
    if(bala == nullptr) return false;
    else return true;
}

Bala* Jugador::getBala(){
    return bala;
}

void Jugador::updateBrujula(float targetX, float targetY){
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



    //Cálculos que giran la flecha para que apunte al objetivo
    if(jugador.getPosition()[1] > targetY) {
        brujula.setRotation(-angulo+180);

    } else {
        brujula.setRotation(-angulo);
    }

}


void Jugador::setDinero(int money) {
    dinero = money;

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
