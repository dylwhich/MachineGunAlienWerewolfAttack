#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "../include/entity.h"


class Zombie : public Entity
{
    public:
        Zombie();
        Zombie(int xPos, int yPos);
        virtual ~Zombie();
        void onTouch(Entity* e);
        void onTick();
        void interact(Entity* e);
        int getType();
        int getMaxHealth();
        int damage(int points);
    protected:
    private:
        int retreatTime, damageGrace;
};

#endif // ZOMBIE_H
