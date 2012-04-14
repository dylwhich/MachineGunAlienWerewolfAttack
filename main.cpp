#include <allegro.h>
#include "./include/sprite.h"
#include "./include/cheat.h"
#include "./include/ball.h"
#include "./include/player.h"
#include "./include/dynamite.h"
#include "./include/apple.h"
#include "./include/coin.h"
#include "./include/armor.h"
#include "./include/tutorial.h"
#include "./include/ambient.h"
#include "./include/bullet.h"
#include <vector>
#include <iostream>

    //copied from http://wiki.allegro.cc/index.php?title=Bounding_Box
int bounding_box_collision(int b1_x, int b1_y, int b1_w, int b1_h, int b2_x, int b2_y, int b2_w, int b2_h)
{
    if ((b1_x > b2_x + b2_w - 1) || // is b1 on the right side of b2?
        (b1_y > b2_y + b2_h - 1) || // is b1 under b2?
        (b2_x > b1_x + b1_w - 1) || // is b2 on the right side of b1?
        (b2_y > b1_y + b1_h - 1))   // is b2 under b1?
    {
        // no collision
        return 0;
    }

    // collision
    return 1;
}


int main()
{
 //set up all the allegro thingies
    allegro_init();
    set_window_title("Machine Gun Alien Werewolf Attack");
    install_keyboard();

    set_gfx_mode( GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
    set_color_depth(16);

    BITMAP* buffer;
    buffer = create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP* playerSprite = load_bitmap("img/player.bmp", NULL);
    BITMAP* cart = load_bitmap("img/minecart.bmp", NULL);
    BITMAP* apple = load_bitmap("img/apple.bmp", NULL);
    BITMAP* coin = load_bitmap("img/coin.bmp", NULL);
    BITMAP* dynamite = load_bitmap("img/dynamite.bmp", NULL);
    BITMAP* heart = load_bitmap("img/heart.bmp", NULL);
    BITMAP* emptyheart = load_bitmap("img/emptyheart.bmp", NULL);
    BITMAP* gameover = load_bitmap("img/gameover.bmp", NULL);
    BITMAP* tutorial1 = load_bitmap("img/tutorial1.bmp", NULL);
    BITMAP* hook = load_bitmap("img/grapplinghook.bmp", NULL);
    BITMAP* shaft = load_bitmap("img/grapplingshaft.bmp", NULL);
    BITMAP* head = load_bitmap("img/grapplinghead.bmp", NULL);
    BITMAP* helmet = load_bitmap("img/helmet.bmp", NULL);
    BITMAP* chestplate = load_bitmap("img/chestplate.bmp", NULL);
    BITMAP* lamp = load_bitmap("img/lamp.bmp", NULL);
    BITMAP* fireball = load_bitmap("img/fireball.bmp", NULL);

    int playerOffset = (SCREEN_W-playerSprite->w)/2;
    int cartOffset = (SCREEN_W-cart->w)/2;
    int bottomHeight = SCREEN_H-playerSprite->h;
    int lastAmbient = 0, shotTimer = 0;
    int tutorialProgress = 0;
    bool paused = false;
    int pauseTimer = 0;

    Player* player = new Player((SCREEN_W-playerSprite->w)/2,bottomHeight-playerSprite->h);
    player->setDisplay(playerSprite);

    std::vector<Entity*> sprites;
    srand(time(0));

    Tutorial* tutorialOne = new Tutorial(tutorial1,(SCREEN_W-tutorial1->w)/2,SCREEN_H-180-tutorial1->h/2);
    Tutorial* tutorialTwo = new Tutorial(load_bitmap("img/tutorial2.bmp", NULL),3*SCREEN_W/4,SCREEN_H-80);
    sprites.push_back(tutorialOne);

    while (!key[KEY_ESC] && player->getHealth() > 0)
    {
        //acquire_screen();
        if (paused)
        {
            //BITMAP* pauseBuffer;
            //blit(buffer, pauseBuffer, 0, 0, 0, 0, SCREEN_H, SCREEN_W);
            if (pauseTimer<20) pauseTimer++;
            if (key[KEY_P] && pauseTimer==20) paused = false;
            clear_keybuf();
            rest(80);
        } else
        {
            if (pauseTimer>0) pauseTimer--;
            if (key[KEY_W] || key[KEY_UP]) player->setY(player->getY()-5);

            else if (key[KEY_S] || key[KEY_DOWN]) player->setY(player->getY()+5);

            if (key[KEY_SPACE] xor player->isJumping()) player->toggleJumping(key[KEY_SPACE]);

            clear_to_color(buffer, 0x000000);
            textprintf_ex(buffer, font, 0, 40, 0xFFFFFF, -1, "%d",pauseTimer);
            if (key[KEY_P] && pauseTimer==0)
            {
                paused = true;
                //blit(buffer, pauseBuffer, 0, 0, 0, 0, SCREEN_H, SCREEN_W);
                textout_ex(buffer, font, "GAME PAUSED", 0, 80, 0xFF0000, -1);
            }
                //begin sprite calculation block
            for (unsigned int i=0; i<sprites.size();i++)
            {
                Entity* curr = sprites.at(i);

                if (player->collides(curr))
                {
                    curr->onTouch(player);
                    player->onTouch(curr);
                }
                    //calculate this entity with reference to *every* other entity in the list
                for (unsigned int j=0;j<sprites.size();j++) //I'm completely amazed that this doesn't slow down the program excessively
                {
                    if (j==i) continue;
                    if (sprites.at(j)->collides(curr))
                    {
                        curr->onTouch(sprites.at(j));
                        sprites.at(j)->onTouch(curr);
                    }
                }

                    //if the current tutorial is done and it is the first one, spawn the second
                if (curr->getType()==Entity::TUTORIAL && ((Tutorial*)curr)->isDone() && ++tutorialProgress==1) sprites.push_back(tutorialTwo);

                    //erase sprites off the screen to the left and bottom, and with no health
                if (curr->getHealth()==0 || (curr->getX()+curr->getWidth())<0 || curr->getY()>SCREEN_H)
                {
                    sprites.erase(sprites.begin()+i);
                } else  //only draw the sprite if it is not being moved
                draw_sprite(buffer, curr->getDisplay(), curr->getX(), curr->getY());

                curr->onTick();
            }   //end sprite calculation block

                //draw all the player's hearts and wrap if needed
            for (int i=0;i<player->getMaxHealth();i++)
            {
                draw_sprite(buffer, (player->getHealth()>i)?heart:emptyheart, (i%40)*(heart->w+1), 20+(heart->h+1)*(i/40));
            }
            player->onTick();

                //once the first tutorial is complete, the player is allowed to shoot things
            if (tutorialProgress>0)
            {
                if (key[KEY_F] && shotTimer==0)
                {
                    sprites.push_back((new Bullet(player->getX()+player->getWidth()+fireball->w,player->getY()-10))->setDisplay(fireball));
                    lastShot = 19;
                }
                    //cheaty cheats
                if (key[KEY_C] || key[KEY_Y] || key[KEY_L])
                {
                    if (key[KEY_C]) sprites.push_back((new Coin(player->getX()+2*player->getWidth(),player->getY()))->setDisplay(coin));
                    else if (key[KEY_Y]) sprites.push_back((new Dynamite(player->getX()+2*player->getWidth(), player->getY()))->setDisplay(dynamite));
                    else if (key[KEY_L]) sprites.push_back((new Apple(player->getX()+2*player->getWidth(), player->getY()))->setDisplay(apple));
                } else if (tutorialProgress>1)  //once both tutorials are done entities will start spawning on their own
                {
                    int makeSprite = rand()%500;
                    if (makeSprite<20) sprites.push_back((new Coin(SCREEN_W+1,bottomHeight-rand()%180))->setDisplay(coin));
                    else if (makeSprite<23) sprites.push_back((new Dynamite(SCREEN_W+1, bottomHeight-rand()%180))->setDisplay(dynamite));
                    else if (makeSprite<24) sprites.push_back((new Apple(SCREEN_W+1, bottomHeight-rand()%180))->setDisplay(apple));
                }
            }
            lastAmbient++;
            if (shotTimer>0) shotTimer--;
            if (lastAmbient==200)
            {
                sprites.push_back(new Ambient(lamp));
                lastAmbient=0;
            }
            draw_sprite(buffer, player->getDisplay(), player->getX(), player->getY());
            draw_sprite(buffer, helmet, player->getX()+player->getWidth()/2-helmet->w/2, player->getY()-5);
            draw_sprite(buffer, chestplate, player->getX()+player->getWidth()/2-chestplate->w/2, player->getY()+8);
            draw_sprite(buffer, cart, cartOffset, bottomHeight+16);
            textprintf_ex(buffer, font, 5, 5, 0xFFFFFF, -1, "Coins: %d", player->getCoins());
            acquire_screen();
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            release_screen();
            clear_keybuf();
            rest(5);
        }
    }
    if (player->getHealth() <= 0)
    {
        BITMAP* newBuffer = create_bitmap(SCREEN_W,SCREEN_H);
        COLOR_MAP global_light_table;
        create_light_table(&global_light_table, default_palette, 10, 10, 60, NULL);
        if (get_color_depth()==8)
            color_map = &global_light_table;
        else
            set_trans_blender(128, 128, 128, 255);
        for (int t=0;t<16;t++)
        {
            draw_lit_sprite(newBuffer, buffer, 0, 0, t*8);
            acquire_screen();
            blit(newBuffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            release_screen();
            rest(1);
        }
        blit(newBuffer, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        for (int h=-(gameover->h);h<(SCREEN_H-gameover->h)/2;h+=6)
        {
            if (key[KEY_ENTER]) h=(SCREEN_H-gameover->h)/2;
            blit(buffer, newBuffer, (SCREEN_W-gameover->w)/2, h-6, (SCREEN_W-gameover->w)/2, h-6, gameover->w, gameover->h+6);
            draw_sprite(newBuffer, gameover, (SCREEN_W-(gameover->w))/2, h);
            acquire_screen();
            blit(newBuffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            release_screen();
            rest(2);
        }
        while (!key[KEY_ESC])
        {
            rest(20);
            clear_keybuf();
        }
    }
    return 0;
}
END_OF_MAIN();
