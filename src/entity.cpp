#include "../include/entity.h"

const int Entity::MAX_X = 640;
const int Entity::MAX_Y = 480;
int Entity::MAX_ID = 0;
std::vector<Entity*> Entity::ALL_ENTITIES;

Entity::Entity()
{
    init();
}

Entity::Entity(int xPos, int yPos)
{
    x = xPos;
    y = yPos;
    init();
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

void Entity::updateID(unsigned int newID)
{
    id = newID;
}

void Entity::init()
{
    ALL_ENTITIES.push_back(this);
    id = MAX_ID++;
}

void Entity::remove()
{
    if (id != -1)
    {
        MAX_ID--;
        ALL_ENTITIES.erase(ALL_ENTITIES.begin()+id);
        for (unsigned int i=0;i<ALL_ENTITIES.size();i++)
        {
            ALL_ENTITIES.at(i)->updateID(i);
        }
        id = -1;
    }
}

bool Entity::cull()
{
    if (x+display->w<0 || y>MAX_Y || x>MAX_X || health==0)
    {
        remove();
        return true;
    }
    return false;
}

void Entity::attachSprite(BITMAP* b, int xOff, int yOff)
{
    bool reset = false;
    if (addons.empty()) reset = true;
    addons.push_back(Addon {b, xOff, yOff});
    if (reset) resetAddons();
}

bool Entity::hasNextAddon()
{
    return addonIt==addons.end();
}

Addon Entity::nextAddon()
{
    return *addonIt++;
}

void Entity::resetAddons()
{
    addonIt=addons.begin();
}
