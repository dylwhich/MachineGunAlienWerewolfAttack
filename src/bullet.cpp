#include "../include/bullet.h"

Bullet::Bullet()
{
    init();
}

Bullet::Bullet(int xPos, int yPos, int xCoef, int yCoef, int additX, int additY) : Entity::Entity(xPos,yPos)
{
    setHealth(getMaxHealth());
    yVelocity = yCoef * 6 + additY;
    xVelocity = xCoef * 6 + additX;
}

Bullet::~Bullet()
{
    //dtor
}

void Bullet::onTick()
{
    setX(getX()+xVelocity);
    setY(getY()+yVelocity);
    if (getX()>MAX_X || xVelocity==0 && yVelocity==0) setHealth(0);
}

void Bullet::onTouch(Entity* e)
{
    if (e->getType() != BULLET && e->getType() != PLAYER)
    {
        e->damage(2);
        remove();
    }
}

int Bullet::getType()
{
    return Entity::BULLET;
}

int Bullet::getMaxHealth()
{
    return 1;
}

void Bullet::interact(Entity* e)
{
    //do nothing
}
