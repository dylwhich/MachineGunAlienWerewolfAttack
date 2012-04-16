#include "../include/zombie.h"

Zombie::Zombie()
{
    //ctor
}

Zombie::Zombie(int xPos, int yPos) : Entity::Entity(xPos, yPos)
{
    damageGrace = 0;
    retreatTime = 0;
    setHealth(getMaxHealth());
}

Zombie::~Zombie()
{
    //dtor
}

void Zombie::onTouch(Entity* e)
{
    if (e->getType()==PLAYER && damageGrace==0)
    {
        e->damage(1);
        retreatTime = 95;
        damageGrace = 10;
    }
}

void Zombie::onTick()
{
    if (retreatTime>0) retreatTime--;
    if (damageGrace>0) damageGrace--;
    setX(getX()-2);
}

void Zombie::interact(Entity* e)
{
    if (e->getType()==PLAYER)
    {
        if (retreatTime==0)
        {
            //if (getX()<e->getX()) setX(getX()+1);
            //else setX(getX()-rand()%3-1);
            if (getY()<e->getY()) setY(getY()+1);
            else setY(getY()-1);
        } else
        {
            setX(getX()+rand()%30-15);
            setY(getY()+rand()%30-15);
        }
    }
}

int Zombie::getType()
{
    return ZOMBIE;
}

int Zombie::getMaxHealth()
{
    return 4;
}

int Zombie::damage(int points)
{
    setX(getX()+rand()%30-15);
    setY(getY()+rand()%30-15);
    return Entity::damage(points);
}
