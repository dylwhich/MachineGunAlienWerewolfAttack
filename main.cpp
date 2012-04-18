    #include <allegro.h>
#include "./include/player.h"
#include "./include/dynamite.h"
#include "./include/apple.h"
#include "./include/coin.h"
#include "./include/armor.h"
#include "./include/tutorial.h"
#include "./include/ambient.h"
#include "./include/bullet.h"
#include "./include/zombie.h"
#include <vector>
#include <iostream>

/*BITMAP *load_sprite(const char* filename) {
   BITMAP *tmp, *ret;

   // convert the sprite to current format, unless it would lose alpha information
   set_color_conversion(COLORCONV_KEEP_ALPHA);
   tmp = load_bitmap(filename, NULL);

   // create a video bitmap of the same size and same color depth as the sprite
   //allegro_gl_set_video_bitmap_color_depth(bitmap_color_depth(tmp));
   ret = create_video_bitmap(tmp->w, tmp->h);
   //allegro_gl_set_video_bitmap_color_depth(-1);

   // blit a memory sprite to a video bitmap
   blit(tmp, ret, 0, 0, 0, 0, tmp->w, tmp->h);

   destroy_bitmap(tmp);
   return ret;
}*/

BITMAP* load_sprite(const char* filename)
{
    return load_bitmap(filename, NULL);
}

int main()
{
 //set up all the allegro thingies
    allegro_init();
    set_window_title("Machine Gun Alien Werewolf Attack");
    install_keyboard();

    set_gfx_mode( GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
    set_color_depth(16);
    //std::cout << ALLEGRO_VERSION_STR << std::endl;
    //set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);

    /*PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "img");
    al_change_directory(al_path_cstr(path, '/'));  // change the working directory
    al_destroy_path(path);*/

    BITMAP* buffer;
    buffer = create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP* playerSprite = load_sprite("img/player.bmp");
    BITMAP* cart = load_sprite("img/minecart.bmp");
    BITMAP* apple = load_sprite("img/apple.bmp");
    BITMAP* coin = load_sprite("img/coin.bmp");
    BITMAP* dynamite = load_sprite("img/dynamite.bmp");
    BITMAP* heart = load_sprite("img/heart.bmp");
    BITMAP* emptyheart = load_sprite("img/emptyheart.bmp");
    BITMAP* gameover = load_sprite("img/gameover.bmp");
    BITMAP* tutorial1 = load_sprite("img/tutorial1.bmp");
    //BITMAP* hook = load_sprite("img/grapplinghook.bmp");
    //BITMAP* shaft = load_sprite("img/grapplingshaft.bmp");
    //BITMAP* head = load_sprite("img/grapplinghead.bmp");
    BITMAP* helmet = load_sprite("img/helmet.bmp");
    BITMAP* chestplate = load_sprite("img/chestplate.bmp");
    BITMAP* lamp = load_sprite("img/lamp.bmp");
    BITMAP* fireball = load_sprite("img/fireball.bmp");
    BITMAP* zombie = load_sprite("img/grapplinghook.bmp");

    int cartOffset = (SCREEN_W-cart->w)/2;
    int bottomHeight = SCREEN_H-playerSprite->h;
    int tutorialProgress = 0;
    bool paused = false;
    int pauseTimer = 0;
    int floorTickTimer = 10;
    //srand(time(0));

    Player* player = new Player((SCREEN_W-playerSprite->w)/2,bottomHeight-playerSprite->h);
    player->setDisplay(playerSprite);
    player->attachSprite(helmet, (player->getWidth()-helmet->w)/2, -5);
    player->attachSprite(cart, (player->getWidth()-cart->w)/2,player->getHeight()-cart->h/2);

    new Tutorial(tutorial1,(SCREEN_W-tutorial1->w)/2,SCREEN_H-180-tutorial1->h/2);
    new Ambient(lamp);

    while (!key[KEY_ESC] && player->getHealth() > 0)
    {
        //acquire_screen();
        if (paused)
        {
            if (pauseTimer<20) pauseTimer++;
            if (key[KEY_P] && pauseTimer==20) paused = false;
            clear_keybuf();
            rest(80);
        } else
        {
            if (pauseTimer>0) pauseTimer--;
            /*if (floorTickTimer>0) floorTickTimer--;
            else
            {
                floorTickTimer=20;
                player->setFloorHeight(bottomHeight--);
            }*/
            //if (key[KEY_W] || key[KEY_UP]) player->setY(player->getY()-5);
            //else if (key[KEY_S] || key[KEY_DOWN]) player->setY(player->getY()+5);

            if (key[KEY_SPACE] xor player->isJumping()) player->toggleJumping(key[KEY_SPACE]);
            #ifdef DEBUG
            if (key[KEY_LCONTROL] xor player->attracting) player->attracting=key[KEY_LCONTROL];
            if (key[KEY_V]) player->setInvincible(true);
            if (key[KEY_U]) player->setInvincible(false);
            #endif

            clear_to_color(buffer, 0x000000);
            if (key[KEY_P] && pauseTimer==0)
            {
                paused = true;
                textout_ex(buffer, font, "GAME PAUSED", 0, 80, 0xFFFFFF, -1);
            }
                //begin sprite calculation block
            for (unsigned int i=0; i<Entity::ALL_ENTITIES.size();i++)
            {
                Entity* curr = Entity::ALL_ENTITIES.at(i);
                curr->onTick();
                if (!curr->cull())
                {
                        //calculate this entity with reference to *every* other entity in the list
                    for (unsigned int j=0;j<Entity::ALL_ENTITIES.size();j++) //I'm completely amazed that this doesn't slow down the program excessively
                    {
                        if (j==i) continue;
                        Entity* target = Entity::ALL_ENTITIES.at(j);
                        if (target->collides(curr))
                        {
                            curr->onTouch(target);
                            target->onTouch(curr);
                        }
                        curr->interact(target);
                        target->interact(curr);
                    }

                        //if the current tutorial is done and it is the first one, spawn the second
                    if (curr->getType()==Entity::TUTORIAL && ((Tutorial*)curr)->isDone() && ++tutorialProgress==1)
                    {
                        new Tutorial(load_bitmap("img/tutorial2.bmp", NULL),3*SCREEN_W/4,SCREEN_H-80);
                    }
                    draw_sprite(buffer, curr->getDisplay(), curr->getX(), curr->getY());
                }
            }   //end sprite calculation block

                //draw all the player's hearts and wrap if needed
            for (int i=0;i<player->getMaxHealth();i++)
            {
                draw_sprite(buffer, (player->getHealth()>i)?heart:emptyheart, (i%40)*(heart->w+1), 20+(heart->h+1)*(i/40));
            }
            //player->onTick();

                //once the first tutorial is complete, the player is allowed to shoot things
            if (tutorialProgress>0)
            {
                if ((key[KEY_UP] || key[KEY_DOWN] || key[KEY_LEFT] || key[KEY_RIGHT]) && (player->fire()
                    #ifdef DEBUG
                    || key[KEY_LSHIFT]
                    #endif
                    )) (new Bullet(player->getX()-fireball->w/2/*player->getX()+player->getWidth()-(key[KEY_LEFT]?(player->getWidth()+fireball->w+2):0)*/,    //X
                                   player->getY()+3,    //Y
                                   key[KEY_LEFT]-key[KEY_RIGHT],
                                   key[KEY_UP]-key[KEY_DOWN],
                                   0,
                                   ((key[KEY_UP] || key[KEY_DOWN]) && (player->getVelocity()>0 xor key[KEY_UP]) && (player->getVelocity()<0 xor key[KEY_DOWN]))?player->getVelocity():0))->setDisplay(fireball);
                    //cheaty cheats
                #ifdef DEBUG
                if (key[KEY_C] || key[KEY_Y] || key[KEY_L])
                {
                    if (key[KEY_C]) (new Coin(player->getX()+2*player->getWidth(),player->getY()))->setDisplay(coin);
                    else if (key[KEY_Y]) (new Dynamite(player->getX()+2*player->getWidth(), player->getY()))->setDisplay(dynamite);
                    else if (key[KEY_L]) (new Apple(player->getX()+2*player->getWidth(), player->getY()))->setDisplay(apple);
                } else if (tutorialProgress>2)  //once both tutorials are done entities will start spawning on their own
                #endif
                {
                    int makeSprite = rand()%500;
                    if (makeSprite<20) (new Coin(SCREEN_W,bottomHeight-rand()%180))->setDisplay(coin);
                    else if (makeSprite<23) (new Dynamite(SCREEN_W, bottomHeight-rand()%180))->setDisplay(dynamite);
                    else if (makeSprite<24) (new Apple(SCREEN_W, bottomHeight-rand()%180))->setDisplay(apple);
                    else if (makeSprite<28
                    #ifdef DEBUG
                    || key[KEY_Z]
                    #endif
                    )
                    {
                        /*
                         *      0
                         *   --------
                         * 1 |      | 3
                         *   |      |
                         *   --------
                         *      2
                         */
                        int side = rand()%3;
                        if (side==2) side = 3;
;
                        //TODO replace zeroes with negative sprite dimensions
                        //and also make sprite
                        int tmpX[4] = {rand()%Entity::MAX_X,-zombie->w,rand()%Entity::MAX_X,Entity::MAX_X};
                        int tmpY[4] = {-zombie->h,rand()%Entity::MAX_Y,Entity::MAX_Y,rand()%Entity::MAX_Y};
                        (new Zombie(tmpX[side],tmpY[side]))->setDisplay(zombie);
                    }
                }
            }

            while (player->hasNextAddon())
            {
                Addon it = player->nextAddon();
                draw_sprite(buffer, it.disp, player->getX()+it.xOffset, player->getY()+it.yOffset);
            }
            /*std::list<Addon>::iterator it;
            for (it = player->addons.begin(); it != player->addons.end(); it++)
            {
                draw_sprite(buffer, it->disp, player->getX()+it->xOffset, player->getY()+it->yOffset);
            }*/
            /*draw_sprite(buffer, helmet, player->getX()+player->getWidth()/2-helmet->w/2, player->getY()-5);
            draw_sprite(buffer, chestplate, player->getX()+player->getWidth()/2-chestplate->w/2, player->getY()+8);
            draw_sprite(buffer, cart, player->getX()+player->getWidth()/2-cart->w/2, bottomHeight+16);*/
            textprintf_ex(buffer, font, 5, 5, 0xFFFFFF, -1, "Coins: %d", player->getCoins());
            #ifdef DEBUG
            textprintf_ex(buffer, font, 5, 40, 0xFFFFFF, -1, "%d (%d calcs/tick)", Entity::numEntities(),Entity::numEntities()*Entity::numEntities());
            #endif
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
END_OF_MAIN()
