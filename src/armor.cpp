#include "../include/armor.h"

Armor::Armor(int type)
{
    //ctor
}

Armor::~Armor()
{
    //dtor
}

void Armor::onTouch(Entity* e)
{

}

void Armor::onTick()
{

}

int Armor::getType()
{
   return Entity::ARMOR;
}

int Armor::getMaxHealth()
{
    return -1;
}
