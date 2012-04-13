#ifndef SPRITE_H
#define SPRITE_H
#include <allegro.h>

class Sprite
{
    public:
        Sprite();
        Sprite(BITMAP* disp, int xPos, int yPos, int moveSpeed);
        Sprite(BITMAP* disp, int xPos, int yPos, int moveSpeed, bool isSolid);
        ~Sprite();
        int x, y, speed;
        bool solid;
        BITMAP* display;
        virtual void tick();
    protected:
    private:
};

#endif // SPRITE_H
