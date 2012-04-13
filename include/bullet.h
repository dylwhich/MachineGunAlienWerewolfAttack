#ifndef BULLET_H
#define BULLET_H

#include "../include/entity.h"


class Bullet : public Entity
{
    public:
        Bullet();
        Bullet(int xPos, int yPos);
        virtual ~Bullet();
        void onTick();
        void onTouch(Entity* e);
        int getMaxHealth();
        int getType();
    protected:
    private:
};

#endif // BULLET_H
