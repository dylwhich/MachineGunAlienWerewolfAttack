#include "../include/zombie.h"
#include <math.h>

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
    //setX(getX()-2);
}

void Zombie::interact(Entity* e)
{
    if (e->getType()==PLAYER)
    {
        if (retreatTime==0)
        {

            double totalDist = sqrt(
                                    pow(e->getX()-getX(),2)+
                                    pow(e->getY()-getY(),2));    ///home/dylan/Documents/Programming/MinecartMadLibs/src/zombie.cpp|47|error: could not convert ‘((double)(((e)->Entity::getX()() - ((Zombie*)this)->Zombie::<unnamed>.getX()()) * ((e)->Entity::getX()() - ((Zombie*)this)->Zombie::<unnamed>.getX()()) + ((e)->Entity::getY()() - ((Zombie*)this)->Zombie::<unnamed>.getY()()) * ((e)->Entity::getY()() - ((Zombie*)this)->Zombie::<unnamed>.getY()())) + 0.0)’ from ‘double’ to ‘fix’|

            int factor = 1;//MAX_X-totalDist;//(int)(totalDist/5.0);
            if (getX()<e->getX()) setX(getX()+factor);
            else setX(getX()-factor);
            if (getY()<e->getY()) setY(getY()+factor);
            else setY(getY()-factor);
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
