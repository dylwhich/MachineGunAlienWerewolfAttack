#ifndef ENTITY_H
#define ENTITY_H

#include <allegro.h>
#include <vector>
#include <list>

struct Addon
{
    BITMAP* disp;
    int xOffset, yOffset;
};

class Entity
{
    public:
        static const int MAX_X;
        static const int MAX_Y;
        static int MAX_ID;
        static std::vector<Entity*> ALL_ENTITIES;
        enum { COIN, PLAYER, DYNAMITE, APPLE, ARMOR, TUTORIAL, AMBIENT, BULLET, ZOMBIE };

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
        void remove();
        bool cull();
        void attachSprite(BITMAP* b, int xOff, int yOff);
        bool hasNextAddon();
        Addon nextAddon();
        void resetAddons();
        static int numEntities();
        virtual void interact(Entity* e)=0;
    protected:
        void updateID(unsigned int newID);
        void init();
    private:
        std::list<Addon>::iterator addonIt;
        std::list<Addon> addons;
        unsigned int id;
        int x, y, health;
        BITMAP* display;
};

#endif // ENTITY_H
