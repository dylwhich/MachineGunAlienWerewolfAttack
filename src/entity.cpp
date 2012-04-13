#include "../include/entity.h"

const int Entity::MAX_X = 640;
const int Entity::MAX_Y = 480;

/*const int Entity::COIN = 1;
const int Entity::PLAYER = 2;
const int Entity::DYNAMITE = 3;
const int Entity::APPLE = 4;
const int Entity::ARMOR = 5;
const int Entity::TUTORIAL = 6;
const int Entity::AMBIENT = 7;*/

Entity::Entity()
{
    //ctor
}

Entity::Entity(int xPos, int yPos)
{
    x = xPos;
    y = yPos;
}

Entity::~Entity()
{
    delete display;
}

int Entity::getX()
{
    return x;
}

int Entity::getY()
{
    return y;
}

void Entity::setX(int newX)
{
    x = newX;
}

void Entity::setY(int newY)
{
    y = newY;
}

int Entity::getWidth()
{
    return display->w;
}

int Entity::getHeight()
{
    return display->h;
}

int Entity::getHealth()
{
   return health;
}

int Entity::damage(int points)
{
    health -= points;
    if (health<0) health = 0;
    return health;
}

int Entity::heal(int points)
{
    health += points;
    if (health>getMaxHealth()) health = getMaxHealth();
    return health;
}

void Entity::setHealth(int newHealth)
{
    health = newHealth;
}

Entity* Entity::setDisplay(BITMAP* newDisplay)
{
    display = newDisplay;
    return this;
}

BITMAP* Entity::getDisplay()
{
    return display;
}

bool Entity::collides(Entity* e)
{
    return !((x > e->getX() + e->getWidth() - 1) || // is b1 on the right side of b2?
    (y > e->getY() + e->getHeight() - 1) || // is b1 under b2?
    (e->getX() > x + getWidth() - 1) || // is b2 on the right side of b1?
    (e->getY() > y + getHeight() - 1));   // is b2 under b1?
}
