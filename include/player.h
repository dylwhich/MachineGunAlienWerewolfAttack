#ifndef PLAYER_H
#define PLAYER_H

#include "../include/entity.h"
#include "../include/bullet.h"

class Player : public Entity
{
    public:
        Player();
        Player(int xPos, int yPos);
        virtual ~Player();
        void onTouch(Entity* e);
        void onTick();
        int getType();
        int getMaxHealth();
        int getCoins();
        void collectCoin();
        void setFloorHeight(int height);
        void toggleJumping(bool val);
        bool isJumping();
        int damage(int points);
        bool fire();
    protected:
    private:
        int coins, floorHeight, jumpTicks, armorLevel, shotTimer;
        bool jumping;
};

#endif // PLAYER_H
