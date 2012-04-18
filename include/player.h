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
        void interact(Entity* e);
        int getCoins();
        void collectCoin();
        void setFloorHeight(int height);
        void toggleJumping(bool val);
        bool isJumping();
        int damage(int points); //does not work because C++ is lame about polymorphism...
        bool fire();
        bool attracting;
        void setInvincible(bool v);
        bool isInvincible();
        int getVelocity();
    protected:
    private:
        int coins, floorHeight, jumpTicks, armorLevel, shotTimer;
        bool jumping, invincible;
};

#endif // PLAYER_H
