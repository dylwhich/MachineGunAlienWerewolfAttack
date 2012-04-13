#ifndef ENTITY_H
#define ENTITY_H

#include <allegro.h>

class Entity
{
    public:
        static const int MAX_X;
        static const int MAX_Y;
        enum { COIN, PLAYER, DYNAMITE, APPLE, ARMOR, TUTORIAL, AMBIENT, BULLET };
        /*static const int COIN;
        static const int PLAYER;
        static const int DYNAMITE;
        static const int APPLE;
        static const int ARMOR;
        static const int TUTORIAL;
        static const int AMBIENT;*/

        Entity();
        Entity(int xPos, int yPos);
        virtual ~Entity();
        virtual void onTouch(Entity* e)=0;
        virtual void onTick()=0;
        virtual int getType()=0;
        virtual int getMaxHealth()=0;
        int getX();
        void setX(int newX);
        int getY();
        void setY(int newY);
        int getWidth();
        int getHeight();
        int getHealth();
        void setHealth(int newHealth);
        int damage(int points);
        int heal(int points);
        Entity* setDisplay(BITMAP* newDisplay);
        BITMAP* getDisplay();
        bool collides(Entity* e);
    protected:
    private:
        int x, y, health;
        BITMAP* display;
};

#endif // ENTITY_H
