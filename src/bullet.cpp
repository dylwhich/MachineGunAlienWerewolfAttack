#include "../include/bullet.h"

Bullet::Bullet()
{
    init();
}

Bullet::Bullet(int xPos, int yPos) : Entity::Entity(xPos,yPos)
{
    setHealth(getMaxHealth());
}

Bullet::~Bullet()
{
    //dtor
}

void Bullet::onTick()
{
    setX(getX()+6);
    if (getX()>MAX_X) setHealth(0);
}

void Bullet::onTouch(Entity* e)
{
    e->damage(2);
    remove();
}

int Bullet::getType()
{
    return Entity::BULLET;
}

int Bullet::getMaxHealth()
{
    return 1;
}
