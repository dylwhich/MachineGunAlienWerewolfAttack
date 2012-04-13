#include "../include/player.h"

Player::Player()
{
    setFloorHeight(448);
    setHealth(getMaxHealth());
    armorLevel=0;
}

Player::Player(int xPos, int yPos) : Entity(xPos,yPos)
{
    setFloorHeight(448);
    coins = 0;
    setHealth(getMaxHealth());
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
            coins++;
            if ((getCoins()%50)==0) heal(2);
        break;
        case APPLE:
            heal(1);
        break;
        default:
        break;
    }
}

void Player::onTick()
{
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
