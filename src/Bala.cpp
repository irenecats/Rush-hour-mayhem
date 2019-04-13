#include "Bala.h"

Bala::Bala(float _x, float _y,float rot, float _dirx, float _diry){

    std::string url ("resources/spritesheet_vehiclesmod.png");
    TexturaContainer::instancia()->crearTextura(url, "Bala");

    bala.setTextura(TexturaContainer::instancia()->getTextura("Bala"));

    bala.setRectTextura(sf::IntRect(3*70 + 5, 3*131 - 12, 70, 128));
    bala.setPosition(_x, _y);
    bala.setRotation(rot);
    bala.setScale(0.5f, 0.5f);
    bala.setOrigin(35, 35);

    dirx = _dirx;
    diry = _diry;
}


void Bala::update(){

    lastState.Setx(newState.Getx());
    lastState.Sety(newState.Gety());

    if(clock.getElapsedTime()<4000){
        bala.mover(dirx*20, diry*20);
    }else{
        aborrar = true;
    }

    newState.Setx(bala.getPosition()[0]);
    newState.Sety(bala.getPosition()[1]);

}

void Bala::render(Window &window, float ptick){
    bala.setPosition(lastState.Getx()*(1-ptick) + newState.Getx()*(ptick), lastState.Gety()*(1-ptick) + newState.Gety()*(ptick));
    window.draw(bala);
}



Sprite Bala::getBala(){
    return bala;
}


bool Bala::getaborrar(){
    return aborrar;
}

