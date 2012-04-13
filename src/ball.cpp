#include "../include/ball.h"

Ball::Ball()
{
    //ctor
}

Ball::Ball(BITMAP* disp, int xPos, int yPos, int moveSpeed, int bounceVelocity, int floorHeight)
{
    //Sprite(disp,xPos,yPos,moveSpeed);
    ticks = 0;
    /*x = xPos;
    y = yPos;
    speed = moveSpeed;*/
    speedY = bounceVelocity;
    bottom = floorHeight;
}

void Ball::tick()
{
    if (y <= bottom) ticks = 0;
    y -= -4*ticks++ + speedY;
}
