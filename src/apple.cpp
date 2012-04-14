#include "../include/apple.h"

Apple::Apple()
{
    //ctor
}

Apple::Apple(int xPos, int yPos) : Entity::Entity(xPos,yPos)
{
    //Entity::Entity(xPos,yPos);
    speed = 2*(rand()%10+1);
    setHealth(getMaxHealth());
}

Apple::~Apple()
{

}

void Apple::onTick()
{
    setX(getX()-speed);
}

void Apple::onTouch(Entity* e)
{
    if (e->getType()==PLAYER)
    {
        remove();
        e->heal(1);
    }
}

int Apple::getType()
{
    return Entity::APPLE;
}

int Apple::getMaxHealth()
{
    return 1;
}
