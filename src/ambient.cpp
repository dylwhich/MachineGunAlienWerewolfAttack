#include "../include/ambient.h"

Ambient::Ambient(BITMAP* disp)
{
    setX(MAX_X);
    setY(0);
    setDisplay(disp);
    setHealth(getMaxHealth());
}

Ambient::~Ambient()
{
    //dtor
}

void Ambient::onTick()
{
    setX(getX()-5);
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
