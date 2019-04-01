#ifndef __ARCHER_INCLUSO__
#define __ARCHER_INCLUSO__

#include "config.h"
#include "colisor.h"
#include "golpe.h"

class archer
{
    private:
    ALLEGRO_BITMAP * bmp;
    colisor * col;
    ARCHER_ESTADO estado;
    int forca_pulo;
    int razao_flecha;
    vector<golpe *> * golpes;
    int lado_virado;
    sprite spr[16];
    int spr_atual;
    ALLEGRO_KEYBOARD_STATE * tec;
    int tick;
    void atira_flecha();

    public:
    archer(ALLEGRO_KEYBOARD_STATE * k_state, vector<golpe *> * golpe_vec, int px, int py);
    ~archer();
    void animar();
    bool atualizar(vector<colisor *> * chao_col, vector<colisor *> * escada_col);
    colisor * get_colisor();
    ARCHER_ESTADO get_estado();
};

#endif
