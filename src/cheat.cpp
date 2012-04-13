#include "../include/cheat.h"

Cheat::Cheat()
{
    progress = 0;
    activated = false;
}

Cheat::Cheat(int* keyCodes)
{
    progress = 0;
    keys = keyCodes;
    activated = false;
}

void Cheat::deactivate()
{
    activated = false;
}

bool Cheat::isActivated()
{
    return activated;
}

void Cheat::queueKey(int key)
{
    if (key==keys[progress])
        progress++;
    else progress=0;
    if (progress==sizeof(keys)/sizeof(keys[0])) activated = true;
}
