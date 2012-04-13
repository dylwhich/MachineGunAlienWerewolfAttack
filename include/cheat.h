#ifndef CHEAT_H
#define CHEAT_H
#include <string>

class Cheat
{
    public:
        Cheat();
        Cheat(int keyCodes[]);
        void deactivate();
        bool isActivated();
        void queueKey(int key);
    protected:
    private:
        int* keys;
        int progress;
        bool activated;
};

#endif // CHEAT_H
