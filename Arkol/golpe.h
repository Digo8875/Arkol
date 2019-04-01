#ifndef __GOLPE_INCLUIDO__
#define __GOLPE_INCLUIDO__

#include "colisor.h"
#include "config.h"

class inimigo;

class golpe
{
protected:
    inimigo *alvo;
    ALLEGRO_BITMAP * bmp;
    colisor * col;
    int dano;
    GOLPE_ESTADO estado;

public:
    golpe();
    virtual ~golpe();
    golpe(int x, int y, int largura, int altura);
    virtual void animar() = 0;
    virtual void atualizar() = 0;
    virtual void atualizar(vector<colisor *> * chao_col) = 0;
    colisor * get_colisor();
    int get_dano();
    GOLPE_ESTADO get_estado();
    virtual void set_alvo(inimigo *novo_alvo);
};

#endif
