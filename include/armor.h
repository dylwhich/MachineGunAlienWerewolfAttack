#ifndef ARMOR_H
#define ARMOR_H

#include "../include/entity.h"


class Armor : public Entity
{
    public:
        Armor(int type);
        virtual ~Armor();
        void onTouch(Entity* e);
        void onTick();
        int getType();
        int getMaxHealth();
    protected:
    private:
};

#endif // ARMOR_H
