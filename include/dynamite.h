#ifndef DYNAMITE_H
#define DYNAMITE_H

#include "../include/entity.h"


class Dynamite : public Entity
{
    public:
        Dynamite();
        Dynamite(int xPos, int yPos);
        virtual ~Dynamite();
        void onTick();
        void onTouch(Entity* e);
        int getType();
        int getMaxHealth();
    protected:
    private:
        int speed;
};

#endif // DYNAMITE_H
