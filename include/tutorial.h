#ifndef TUTORIAL_H
#define TUTORIAL_H

#include "../include/entity.h"


class Tutorial : public Entity
{
    public:
        Tutorial(BITMAP* disp, int minX, int yPos);
        virtual ~Tutorial();
        void onTick();
        void onTouch(Entity* e);
        int getType();
        int getMaxHealth();
        bool isDone();
    protected:
    private:
        int lifetime;
        bool done;
        int leftBound;
        int yFloat;
};

#endif // TUTORIAL_H
