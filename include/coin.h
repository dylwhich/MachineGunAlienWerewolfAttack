#ifndef COIN_H
#define COIN_H

#include "../include/entity.h"
//#include "../include/player.h"

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
        void interact(Entity* e);
    protected:
    private:
        int speed, lifetime;
};

#endif // COIN_H
