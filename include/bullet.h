#ifndef BULLET_H
#define BULLET_H

#include "../include/entity.h"


class Bullet : public Entity
{
    public:
        Bullet();
        Bullet(int xPos, int yPos, int xCoef, int yCoef, int additX, int additY);
        virtual ~Bullet();
        void onTick();
        void onTouch(Entity* e);
        int getMaxHealth();
        int getType();
        void interact(Entity* e);
    protected:
    private:
        int xVelocity, yVelocity;
};

#endif // BULLET_H
