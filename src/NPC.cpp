#include "NPC.h"

NPC::NPC(Node* nodoInicial, IA* intelig) : posAnterior(), posSiguiente(), debugLine(sf::Lines, 2) {
    nodoInicio = nodoInicial;
    //std::cout << nodoInicial->getCoorX() << " = " <<nodoInicio->getCoorX() <<std::endl;
    //std::string ruta("resources/audi.png");
    //TexturaContainer::instancia()->crearTextura(ruta, "Audi");

    sprite.setTextura(TexturaContainer::instancia()->getTextura("Jugador"));
    int tipo = rand() % 4;
    switch(tipo){
        case 0:  sprite.setRectTextura(sf::IntRect(0,0,119,66));
            break;
        case 1: sprite.setRectTextura(sf::IntRect(0,67,119,66));
            break;
        case 2: sprite.setRectTextura(sf::IntRect(0,134,101,45));
            break;
        case 3: sprite.setRectTextura(sf::IntRect(0,180,101,45));
            break;
    }

    sprite.setOrigin(sprite.getGlobalBounds()[0] / 2, sprite.getGlobalBounds()[1] / 2);
    sprite.setScale(0.6f, 0.6f);

    rectFrenado.setSize(sf::Vector2f(50, sprite.getGlobalBounds()[1]));
    rectFrenado.setOrigin(sprite.getGlobalBounds()[0] * -0.70, sprite.getGlobalBounds()[1] / 2);
    rectFrenado.setFillColor(sf::Color::Transparent);
    rectFrenado.setOutlineColor(sf::Color::Red);
    rectFrenado.setOutlineThickness(2);

    puntoImaginario = sf::Vector2i(0, 0);
    inteligencia = intelig;

    nodoDestino = inteligencia->getNextNode(*nodoInicial);
    //std::cout << "nodoinicio (" << nodoInicio->getCoorX() << ", " << nodoInicio->getCoorY() << "), nododestino (" << nodoDestino->getCoorX() << ", " << nodoDestino->getCoorY() << std::endl;
    anguloNuevo = anguloCalle(nodoInicio, nodoDestino);
    orientacionDeg = anguloNuevo;
    sprite.setRotation(a(orientacionDeg));
    sprite.setPosition(nodoInicio->getCoorX(), nodoInicio->getCoorY());

    setDebugLine(nodoInicio, nodoDestino);
}

void NPC::setPosicionesIniciales() {
    posAnterior.Setx(nodoInicio->getCoorX());
    posAnterior.Sety(nodoInicio->getCoorY());
    posSiguiente.Setx(nodoInicio->getCoorX());
    posSiguiente.Sety(nodoInicio->getCoorY());
}

NPC::~NPC() {
    //dtor
}

void NPC::frenar() {
    if (velocidad > 0) {
        velocidad -= MAX_VEL / 5;
    }
}

void NPC::velocidadNormal() {
    if (velocidad < MAX_VEL) {
        velocidad += MAX_VEL / 5;
    }
}
sf::Vector2f NPC::posMRU(int tiempoRecto) {
    sf::Vector2f posReturn;
    float orientacion = a(sprite.getRotation()) * M_PI/180.0;

    posReturn.x = sprite.getPosition()[0] + velocidad /*px por s */ * std::cos(orientacion) * (tiempoRecto/1000.f);
    posReturn.y = sprite.getPosition()[1] - velocidad * std::sin(orientacion) * (tiempoRecto/1000.f);
    return posReturn;
}

bool NPC::mePasoMRU(sf::Vector2f posFinalFrame) {
    float orientacion = a(sprite.getRotation()) * M_PI/180.0;
    sf::Vector2f inicioGiro = damePuntoInicioGiro(*nodoDestino);

    return ((ceroNegativo(std::sin(orientacion)) && ((posFinalFrame.x - inicioGiro.x) * std::cos(orientacion) >= 0))
            || (ceroNegativo(std::cos(orientacion)) && ((posFinalFrame.y - inicioGiro.y) * std::sin(orientacion) <= 0)));
}

int NPC::calculaTiempoRecto() {
    if (ceroNegativo(std::sin(a(sprite.getRotation()) * M_PI/180.0))) {
        return std::abs(damePuntoInicioGiro(*nodoInicio).x - sprite.getPosition()[0]) / velocidad * 1000;
    } else {
        return std::abs(damePuntoInicioGiro(*nodoInicio).y - sprite.getPosition()[1]) / velocidad * 1000;
    }
}

sf::Vector2f NPC::damePuntoInicioGiro(Node &nodo) {
    sf::Vector2f devolver;
    devolver.x = nodo.getCoorX() - RADIO_GIRO * std::cos(a(sprite.getRotation()) * M_PI/180.0);
    devolver.y = nodo.getCoorY() + RADIO_GIRO * std::sin(a(sprite.getRotation()) * M_PI/180.0);
    return devolver;
}

sf::Vector2f NPC::damePuntoFinGiro(Node &nodo) {
    sf::Vector2f devolver;
    devolver.x = nodo.getCoorX() + RADIO_GIRO * std::cos(anguloNuevo * M_PI/180.0);
    devolver.y = nodo.getCoorY() - RADIO_GIRO * std::sin(anguloNuevo * M_PI/180.0);
    return devolver;
}

void NPC::update(int time) {
    posAnterior.Setx(posSiguiente.Getx());
    posAnterior.Sety(posSiguiente.Gety());

    if (choque) {
        desvanecerse();
    } else {    // Update normal
        int tiempoRecto, tiempoGiro;
        tiempoRecto = tiempoGiro = 0;

        if (estoyRecto()) {
            if (mePasoMRU(posMRU(time))) {
                nodoInicio = nodoDestino;
                nodoDestino = inteligencia->getNextNode(*nodoInicio);
                //setDebugLine(nodoInicio, nodoDestino);
                anguloNuevo = anguloCalle(nodoInicio, nodoDestino);

                if (a(sprite.getRotation()) != anguloNuevo) {
                    sentidoGiro = calculaSentidoGiro();
                    centroGiro = calculaPuntoImaginario(nodoInicio);
                    anguloBarrido = calculaAngBarridoInicial();

                    tiempoGiro = time - calculaTiempoRecto();

                    sf::Vector2f inicGiro = damePuntoInicioGiro(*nodoInicio);
                    sprite.setPosition(inicGiro.x, inicGiro.y);
                } else {
                    tiempoRecto = time;
                }
            } else {
                tiempoRecto = time;
            }
        } else {
            tiempoGiro = time;
            float anguloIncremento = sentidoGiro * (tiempoGiro/1000.f) * velocidad / RADIO_GIRO;
            float anguloBarridoFinal = anguloNuevo - 90 * sentidoGiro;
            if (anguloBarridoFinal >= 360) anguloBarridoFinal = 0;
            else if (anguloBarridoFinal <= 0) anguloBarridoFinal = 360;
            anguloBarridoFinal *= M_PI/180.0;

            if (sentidoGiro > 0) {
                if (anguloBarrido + anguloIncremento > anguloBarridoFinal) {
                    tiempoRecto = time - (anguloBarridoFinal - anguloBarrido) * RADIO_GIRO / velocidad * 1000;
                    tiempoGiro = 0;
                    sprite.setRotation(a(anguloNuevo));
                    sf::Vector2f finGiro = damePuntoFinGiro(*nodoInicio);
                    sprite.setPosition(finGiro.x, finGiro.y);
                }
            } else {
                if (anguloBarrido + anguloIncremento < anguloBarridoFinal) {
                    tiempoRecto = time - (anguloBarrido - anguloBarridoFinal) * RADIO_GIRO / velocidad * 1000;
                    tiempoGiro = 0;
                    sprite.setRotation(a(anguloNuevo));
                    sf::Vector2f finGiro = damePuntoFinGiro(*nodoInicio);
                    sprite.setPosition(finGiro.x, finGiro.y);
                }
            }
        }

        sf::Vector2f posAuxiliar;
        if (tiempoGiro > 0) {
            anguloBarrido += sentidoGiro * (tiempoGiro/1000.f) * velocidad / RADIO_GIRO;
            posAuxiliar.x = centroGiro.x + RADIO_GIRO * std::cos(anguloBarrido);
            posAuxiliar.y = centroGiro.y - RADIO_GIRO * std::sin(anguloBarrido);
            sprite.setPosition(posAuxiliar.x, posAuxiliar.y);
            sprite.setRotation(a((anguloBarrido * 180.0/M_PI) + 90 * sentidoGiro));
        }
        if (tiempoRecto > 0) {
            posAuxiliar = posMRU(tiempoRecto);
            sprite.setPosition(posAuxiliar.x, posAuxiliar.y);
        }
        posSiguiente.Setx(sprite.getPosition()[0]);
        posSiguiente.Sety(sprite.getPosition()[1]);
    }
};

void NPC::setDebugLine(Node *nodo1, Node *nodo2) {
    debugLine[0].position = sf::Vector2f(nodo1->getCoorX(), nodo1->getCoorY());
    debugLine[0].color = sf::Color::Red;
    debugLine[1].position = sf::Vector2f(nodo2->getCoorX(), nodo2->getCoorY());
    debugLine[1].color = sf::Color::Green;
}

void NPC::render(Window &ventana, float ptick) {
    float interPosX = posAnterior.Getx() * (1 - ptick) + posSiguiente.Getx() * ptick;
    float interPosY = posAnterior.Gety() * (1 - ptick) + posSiguiente.Gety() * ptick;

    sprite.setPosition(interPosX, interPosY);
    //std::cout << "posSprite(" << sprite.getPosition()[0] << ", " << sprite.getPosition()[1] << ")" << std::endl;
    rectFrenado.setPosition(sprite.getPosition()[0], sprite.getPosition()[1]);
    rectFrenado.setRotation(sprite.getRotation());

    ventana.draw(sprite);
    //ventana.draw(debugLine);
    //ventana.draw(rectFrenado);
};

bool NPC::estoyRecto() {
    int r = a(sprite.getRotation());
    return (r == 0 || r == 90 || r == 180 || r == 270);
}

int NPC::anguloCalle(Node* inicio, Node* fin) {
    sf::Vector2i vect((int) fin->getCoorX() - inicio->getCoorX(), (int) fin->getCoorY() - inicio->getCoorY());
    if(vect.x == 0) {
        if(vect.y > 0) {
            return(270);
        } else {
            return(90);
        }
    } else if(vect.y == 0) {
        if(vect.x < 0) {
            return(180);
        } else {
            return(0);
        }
    }
    return -1;
}

sf::Vector2i NPC::calculaPuntoImaginario(Node* puntoCurva) {
    sf::Vector2i puntoImaginario = sf::Vector2i(puntoCurva->getCoorX(), puntoCurva->getCoorY());

    if (orientacionDeg == 90 || orientacionDeg == 270) {
        if (orientacionDeg == 90) {
            puntoImaginario.y += RADIO_GIRO;
        } else {
            puntoImaginario.y -= RADIO_GIRO;
        }
        if (anguloNuevo == 0 || anguloNuevo == 360) {
            puntoImaginario.x += RADIO_GIRO;
        } else {
            puntoImaginario.x -= RADIO_GIRO;
        }
    } else {
        if (orientacionDeg == 0 || orientacionDeg == 360) {
            puntoImaginario.x -= RADIO_GIRO;
        } else {
            puntoImaginario.x += RADIO_GIRO;
        }
        if (anguloNuevo == 90) {
            puntoImaginario.y -= RADIO_GIRO;
        } else {
            puntoImaginario.y += RADIO_GIRO;
        }
    }

    return puntoImaginario;
}

int NPC::calculaSentidoGiro() {
    int devolver;
    orientacionDeg = a(sprite.getRotation());

    if (orientacionDeg == 270) {
        if (anguloNuevo == 180) {
            devolver = -1;
        } else {
            devolver = 1;
            anguloNuevo = 360;  // Cambio el angulo de 0 a 360 para que el angulo destino sea mayor que el anterior.
        }
    } else if (orientacionDeg == 180) {
        if (anguloNuevo == 90) {
            devolver = -1;
        } else
            devolver = 1;
    } else if (orientacionDeg == 0 || orientacionDeg == 360) {
        if (anguloNuevo == 90) {
            devolver = 1;
        } else {
            devolver = -1;
            orientacionDeg = 360;  // Cambio el angulo de 0 a 360 para que el angulo inicial sea mayor que el destino.
        }
    } else {
        if (anguloNuevo == 0 || anguloNuevo == 360) {
            devolver = -1;
        } else {
            devolver = 1;
        }
    }
    return devolver;
}

float NPC::calculaAngBarridoInicial() {
    float devolver = M_PI / 4; // Para que se note mucho si va mal.

    switch (orientacionDeg) {
    case 90:
        if (anguloNuevo == 0) {
            devolver = M_PI;
        } else {
            devolver = 0;
        }
        break;
    case 0:
        devolver = 3 * M_PI / 2;
        break;
    case 360:
        devolver = M_PI / 2;
        break;
    case 270:
        if (anguloNuevo == 360) {
            devolver = M_PI;
        } else {
            devolver = 2 * M_PI;
        }
        break;
    case 180:
        if (anguloNuevo == 270) {
            devolver = M_PI / 2;
        } else {
            devolver = 3 * M_PI / 2;
        }
        break;
    }
    return devolver;

};

bool NPC::ceroNegativo(float valor) {
    return valor > -0.00001 && valor < 0.00001;
}

void NPC::setInterpolaciones(float x, float y) {
    posAnterior.Setx(posSiguiente.Getx());
    posAnterior.Sety(posSiguiente.Gety());
    posSiguiente.Setx(x);
    posSiguiente.Sety(y);
}

float NPC::a(float angulo) {
    //Laurent te odio con toda mi alma.
    float r = 360 - angulo;
    if (r >= 360) r -= 360;
    return r;
};

void NPC::desvanecerse() {
    int alfa = sprite.getColor().a;
    if (alfa > 0) {
        sprite.setColor(sf::Color(255, 255, 255, alfa - 85));
    } else {
        borrame = true;
    }
}
