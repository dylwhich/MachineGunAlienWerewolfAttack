#include "../include/coin.h"
#include <math.h>

Coin::Coin()
{
    setX(Entity::MAX_X+1);
    setY(MAX_Y-rand()%180);
    speed = 2*(rand()%2+5);
    lifetime = rand()%10;
    setHealth(getMaxHealth());
}

Coin::Coin(int xPos, int yPos) : Entity::Entity(xPos,yPos)
{
    //Entity::Entity(xPos,yPos);
    speed = 2*rand()%2+5;
    lifetime = 0;
    setHealth(getMaxHealth());
}

Coin::~Coin()
{

}

void Coin::onTouch(Entity* e)
{
    if (e->getType()==PLAYER)
    {
//        ((Player*)e)->collectCoin();
        remove();
    }
}

void Coin::onTick()
{
    setX(getX()-speed);
    setY((int)(getY()+3*cos(lifetime/3.5)));
    lifetime++;
}

int Coin::getMaxHealth()
{
    return 1;
}

int Coin::getType()
{
    return Entity::COIN;
}
