#ifndef AMBIENT_H
#define AMBIENT_H

#include "../include/entity.h"


class Ambient : public Entity
{
    public:
        Ambient(BITMAP* disp);
        virtual ~Ambient();
        void onTick();
        void onTouch(Entity* e);
        int getType();
        int getMaxHealth();
        void interact(Entity* e);
    protected:
    private:
        int waitTime;
};

#endif // AMBIENT_H
