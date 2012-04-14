#include "../include/ambient.h"

Ambient::Ambient(BITMAP* disp)
{
    setX(MAX_X);
    setY(0);
    setDisplay(disp);
    setHealth(getMaxHealth());
    init();
}

Ambient::~Ambient()
{
    //dtor
}

void Ambient::onTick()
{
    setX(getX()-5);
    if (getX()+getWidth()<=0) setX(MAX_X+800);
}

void Ambient::onTouch(Entity* e)
{
}

int Ambient::getType()
{
    return Entity::AMBIENT;
}

int Ambient::getMaxHealth()
{
    return -1;
}
