#ifndef __INIMIGO_INCLUSO__
#define __INIMIGO_INCLUSO__

#include "colisor.h"
#include "archer.h"
#include "golpe.h"

class inimigo
{
    protected:
    archer * alvo;
    ALLEGRO_BITMAP * bmp;
    colisor * col;
    INIMIGO_ESTADO estado;
    vector<golpe *> * golpes;
    int lado_virado;
    bool mover;

    public:
    inimigo();
    inimigo(int x, int y, int alt, int lar, vector<golpe *> * golpe_vec, archer * player);
    virtual ~inimigo();
    virtual void animar() = 0;
    virtual void atacar(int tipo_ataque) = 0;
    virtual bool atualizar(vector<colisor *> * chao_col, vector<colisor *> * escada_col) = 0;
    colisor * get_colisor();
    INIMIGO_ESTADO get_estado();
};

#endif
