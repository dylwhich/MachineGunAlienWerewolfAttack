#include "../include/sprite.h"

Sprite::Sprite()
{

}

Sprite::Sprite(BITMAP* disp, int xPos, int yPos, int moveSpeed)
{
    x = xPos;
    y = yPos;
    display = disp;
    speed = moveSpeed;
    solid=true;
}

Sprite::Sprite(BITMAP* disp, int xPos, int yPos, int moveSpeed, bool isSolid)
{

    x = xPos;
    y = yPos;
    display = disp;
    speed = moveSpeed;
    solid=isSolid;
}

Sprite::~Sprite()
{
    delete display;
}

void Sprite::tick()
{
    x-=speed;
}
