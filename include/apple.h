#ifndef APPLE_H
#define APPLE_H

#include "../include/entity.h"


class Apple : public Entity
{
    public:
        Apple();
        Apple(int xPos, int yPos);
        virtual ~Apple();
        void onTick();
        void onTouch(Entity* e);
        int getMaxHealth();
        int getType();
    protected:
    private:
        int speed;
};

#endif // APPLE_H
