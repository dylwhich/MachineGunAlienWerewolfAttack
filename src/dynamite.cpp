#include "../include/dynamite.h"

Dynamite::Dynamite()
{
    //ctor
}

Dynamite::Dynamite(int xPos, int yPos) : Entity(xPos,yPos)
{
    //Entity::Entity(xPos,yPos);
    setHealth(getMaxHealth());
    speed = 2*(rand()%7+1);
}

Dynamite::~Dynamite()
{
    //dtor
}

void Dynamite::onTick()
{
    setX(getX()-speed);
    setY(getY()+rand()%21-10);
}

void Dynamite::onTouch(Entity* e)
{
    if (e->getType()==PLAYER) setHealth(0);
}

int Dynamite::getType()
{
    return Entity::DYNAMITE;
}

int Dynamite::getMaxHealth()
{
    return 1;
}
