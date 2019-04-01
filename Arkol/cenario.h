#ifndef __CENARIO_INCLUSO__
#define __CENARIO_INCLUSO__

#include "config.h"

class cenario
{
    private:
    ALLEGRO_BITMAP * bmp;
    ALLEGRO_SAMPLE_INSTANCE * bgm;
    ALLEGRO_MIXER * mix;
    int y;

    public:
    cenario(ALLEGRO_MIXER * mixer);
    void animar();
};

#endif
