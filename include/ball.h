#ifndef BALL_H
#define BALL_H

#include "sprite.h"


class Ball : public Sprite
{
    public:
        Ball();
        Ball(BITMAP* disp, int xPos, int yPos, int moveSpeed, int bounceVelocity, int floorHeight);
        int speedY;
        int bottom;
        void tick();
    protected:
    private:
        int ticks;
};

#endif // BALL_H
