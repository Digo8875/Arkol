#include "cenario.h"

cenario::cenario(ALLEGRO_MIXER * mixer)
{
    mix = mixer;
    bmp = al_load_bitmap("graficos/cenario2.png");
};

void cenario::animar()
{
    al_draw_bitmap_region(bmp, 0, 0, 800, 600, 0, 0, 0);
};
