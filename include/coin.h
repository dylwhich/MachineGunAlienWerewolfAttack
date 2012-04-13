#ifndef COIN_H
#define COIN_H

#include "../include/entity.h"

class Coin : public Entity
{
    public:
        Coin();
        Coin(int xPos, int yPos);
        virtual ~Coin();
        void onTick();
        int getMaxHealth();
        void onTouch(Entity* e);
        int getType();
    protected:
    private:
        int speed, lifetime;
};

#endif // COIN_H
