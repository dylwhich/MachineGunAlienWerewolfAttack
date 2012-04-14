#include "../include/tutorial.h"
#include <math.h>

Tutorial::Tutorial(BITMAP* disp, int minX, int yPos)
{
    setDisplay(disp);
    lifetime = 0;
    setX(Entity::MAX_X+1);
    done = false;
    setHealth(getMaxHealth());
    leftBound = minX;
    yFloat = yPos;
    setY(yPos);
    lifeEnd = -1;
}

Tutorial::~Tutorial()
{
    //dtor
}

void Tutorial::onTick()
{
    if (lifetime==lifeEnd) remove();
    if (getX()>(leftBound)) setX(getX()-4);
    else setY((int)(/*MAX_Y-180-getHeight()/2*/yFloat+4*sin(lifetime++/4.0)));
}

void Tutorial::onTouch(Entity* e)
{
    if (e->getType()==Entity::PLAYER || e->getType()==Entity::BULLET)
    {
        done = true;
        lifeEnd = lifetime+1;
    }
}

int Tutorial::getType()
{
    return Entity::TUTORIAL;
}

int Tutorial::getMaxHealth()
{
    return 1;
}

bool Tutorial::isDone()
{
    return done;
}
