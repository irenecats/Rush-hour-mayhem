#include "NPC.h"

NPC::NPC(Node* nodoInicial, IA* intelig) : posAnterior(), posSiguiente() {
    nodoInicio = nodoInicial;
    //std::cout << nodoInicial->getCoorX() << " = " <<nodoInicio->getCoorX() <<std::endl;
    std::string ruta("resources/audi.png");
    TexturaContainer::instancia()->crearTextura(ruta, "Audi");

    sprite.setTextura(TexturaContainer::instancia()->getTextura("Audi"));
    //sprite.setRectTextura(sf::IntRect(1*70 + 5, 1*145 - 12, 70, 117));
    sprite.setOrigin(sprite.getGlobalBounds()[0] / 2, sprite.getGlobalBounds()[1] / 2);
    sprite.setScale(0.4, 0.4);

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
    sprite.setRotation(orientacionDeg);
    sprite.setPosition(nodoInicio->getCoorX(), nodoInicio->getCoorY());
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
    float orientacion = sprite.getRotation() * M_PI/180.0;

    posReturn.x = sprite.getPosition()[0] + velocidad /*px por s */ * std::cos(orientacion) * (tiempoRecto/1000.f);
    posReturn.y = sprite.getPosition()[1] + velocidad * std::sin(orientacion) * (tiempoRecto/1000.f);
    return posReturn;
}

bool NPC::mePasoMRU(sf::Vector2f posFinalFrame) {
    float orientacion = sprite.getRotation() * M_PI/180.0;
    sf::Vector2f inicioGiro = damePuntoInicioGiro(*nodoDestino);

    return ((ceroNegativo(sin(orientacion)) && ((posFinalFrame.x - inicioGiro.x) * std::cos(orientacion) >= 0))
           || (ceroNegativo(cos(orientacion)) && ((posFinalFrame.x - inicioGiro.x) * std::sin(orientacion) <= 0)));
}

int NPC::calculaTiempoRecto() {
    if (ceroNegativo(std::sin(sprite.getRotation() * M_PI/180.0))) {
        return std::abs(damePuntoInicioGiro(*nodoInicio).x - sprite.getPosition()[0]) / velocidad * 1000;
    } else {
        return std::abs(damePuntoInicioGiro(*nodoInicio).y - sprite.getPosition()[1]) / velocidad * 1000;
    }
}

sf::Vector2f NPC::damePuntoInicioGiro(Node &nodo) {
    sf::Vector2f devolver;
    devolver.x = nodo.getCoorX() - RADIO_GIRO * std::cos(sprite.getRotation() * M_PI/180.0);
    devolver.y = nodo.getCoorY() + RADIO_GIRO * std::sin(sprite.getRotation() * M_PI/180.0);
    return devolver;
}

sf::Vector2f NPC::damePuntoFinGiro(Node &nodo) {
    sf::Vector2f devolver;
    devolver.x = nodo.getCoorX() + RADIO_GIRO * std::cos(anguloNuevo * M_PI/180.0);
    devolver.y = nodo.getCoorY() - RADIO_GIRO * std::sin(anguloNuevo * M_PI/180.0);
    return devolver;
}

void NPC::update(int time) {
    int tiempoRecto, tiempoGiro;
    tiempoRecto = tiempoGiro = 0;
    posAnterior.Setx(posSiguiente.Getx());
    posAnterior.Sety(posSiguiente.Gety());

    if (estoyRecto()) {
        if (mePasoMRU(posMRU(tiempoRecto))) {
            nodoInicio = nodoDestino;
            nodoDestino = inteligencia->getNextNode(*nodoInicio);
            anguloNuevo = anguloCalle(nodoInicio, nodoDestino);

            if (sprite.getRotation() != anguloNuevo) {
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
        float anguloIncremento = sentidoGiro * (tiempoGiro/1000.f) * velocidad / RADIO_GIRO;

        if (sentidoGiro > 0) {
            if (anguloBarrido + anguloIncremento > anguloNuevo * M_PI/180.0) {
                tiempoRecto = (time/1000.f) - (anguloNuevo * M_PI/180.0 - anguloBarrido) * RADIO_GIRO / velocidad;
                sprite.setRotation(anguloNuevo);
                sf::Vector2f finGiro = damePuntoFinGiro(*nodoInicio);
                sprite.setPosition(finGiro.x, finGiro.y);
            } else {
                tiempoGiro = time;
            }
        } else {
            if (anguloBarrido + anguloIncremento < anguloNuevo * M_PI/180.0) {
                tiempoRecto = (time/1000.f) - (anguloBarrido - anguloNuevo * M_PI/180.0) * RADIO_GIRO / velocidad;
                sprite.setRotation(anguloNuevo);
                sf::Vector2f finGiro = damePuntoFinGiro(*nodoInicio);
                sprite.setPosition(finGiro.x, finGiro.y);
            } else {
                tiempoGiro = time;
            }
        }
    }

    sf::Vector2f posAuxiliar;
    if (tiempoGiro > 0) {
        anguloBarrido += sentidoGiro * (tiempoGiro/1000.f) * velocidad / RADIO_GIRO;
        posAuxiliar.x = centroGiro.x + RADIO_GIRO * std::cos(anguloBarrido);
        posAuxiliar.y = centroGiro.y - RADIO_GIRO * std::sin(anguloBarrido);
        sprite.setPosition(posAuxiliar.x, posAuxiliar.y);
        sprite.setRotation((anguloBarrido * 180.0/M_PI) + 90 * sentidoGiro);
    }
    if (tiempoRecto > 0) {
        posAuxiliar = posMRU(tiempoRecto);
        sprite.setPosition(posAuxiliar.x, posAuxiliar.y);
    }
    posSiguiente.Setx(sprite.getPosition()[0]);
    posSiguiente.Sety(sprite.getPosition()[1]);
};

void NPC::render(Window &ventana, float ptick) {
    float interPosX = posAnterior.Getx() * (1 - ptick) + posSiguiente.Getx() * ptick;
    float interPosY = posAnterior.Gety() * (1 - ptick) + posSiguiente.Gety() * ptick;

    sprite.setPosition(interPosX, interPosY);
    //std::cout << "posSprite(" << sprite.getPosition()[0] << ", " << sprite.getPosition()[1] << ")" << std::endl;
    rectFrenado.setPosition(sprite.getPosition()[0], sprite.getPosition()[1]);
    rectFrenado.setRotation(sprite.getRotation());

    ventana.draw(sprite);
    ventana.draw(rectFrenado);
};

bool NPC::estoyRecto() {
    int r = sprite.getRotation();
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
    orientacionDeg = sprite.getRotation();

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
