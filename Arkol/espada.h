#ifndef __ESPADA_INCLUIDO__
#define __ESPADA_INCLUIDO__

#include "golpe.h"

class espada: public golpe
{
    private:
    sprite spr[8];
    int spr_atual;
    int lado_virado;
    int tick;
    int x_inicial;
    int y_inicial;

    public:
    espada();
    ~espada();
    espada(int x, int y, int lado_v);
    void animar();
    void atualizar();
    void atualizar(vector<colisor *> * chao_col);
};

#endif
