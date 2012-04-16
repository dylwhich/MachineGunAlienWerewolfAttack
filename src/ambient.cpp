#include "../include/ambient.h"

Ambient::Ambient(BITMAP* disp)
{
    setX(MAX_X);
    setY(0);
    setDisplay(disp);
    setHealth(getMaxHealth());
    init();
    waitTime = 0;
}

Ambient::~Ambient()
{
    //dtor
}

void Ambient::onTick()
{
    if (waitTime>0) waitTime--;
    if (waitTime==0) setX(getX()-5);
    if (getX()+getWidth()<=0)
    {
        setX(MAX_X);
        waitTime=160;
    }
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

void Ambient::interact(Entity* e)
{
    //do nothing
}
