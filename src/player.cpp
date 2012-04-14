#include "../include/player.h"

Player::Player()
{
    setFloorHeight(448);
    setHealth(getMaxHealth());
    armorLevel=0;
    shotTimer = 0;
}

Player::Player(int xPos, int yPos)// : Entity(xPos,yPos)
{
    setFloorHeight(448);
    coins = 0;
    setHealth(getMaxHealth());
    setX(xPos);
    setY(yPos); //not inherited from Entity constructor because I don't want it to init()
    shotTimer = 0;
}

Player::~Player()
{
    //dtor
}

void Player::onTouch(Entity* e)
{
    switch(e->getType())
    {
        case COIN:
            collectCoin();
        break;
        default:
        break;
    }
}

void Player::onTick()
{
    if (shotTimer>0) shotTimer--;
    if (jumping) setY(getY()-40);
    if (getY()<floorHeight) setY(getY()+4*jumpTicks++);
    if (getY()>floorHeight) setY(floorHeight);
    if (getY()==floorHeight) jumpTicks = 0;
}

int Player::getType()
{
    return Entity::PLAYER;
}

int Player::getMaxHealth()
{
    return 10 + getCoins()/50;
}

int Player::getCoins()
{
    return coins;
}

void Player::collectCoin()
{
    coins++;
    if ((getCoins()%50)==0) heal(2);
}

void Player::setFloorHeight(int height)
{
    floorHeight = height;
}

void Player::toggleJumping(bool val)
{
    //if (jumping != val) jumpTicks -= 2;   //makes un-jumping release smoother, but screws up other things
    jumping = val;
}

bool Player::isJumping()
{
    return jumping;
}

int Player::damage(int points)
{
    setHealth(getHealth()-(points-armorLevel));
    return getHealth();
}

bool Player::fire()
{
    if (shotTimer==0)
    {
        shotTimer = 19;
        return true;
        //new Bullet(getX()+getWidth(),getY()+10)->setDisplay(load_bitmap("../img/fireball.bmp"));
    }
    return false;
}
