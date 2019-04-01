#ifndef __FLECHA_INCLUIDO__
#define __FLECHA_INCLUIDO__

#include "golpe.h"

class flecha: public golpe
{
    private:
    sprite spr[7];
    int spr_atual;
    int distancia;
    int lado_virado;
    int tick;
    int x_inicial;
    int y_inicial;

    public:
    flecha();
    virtual ~flecha();
    flecha(int x, int y, int lado_v);
    void animar();
    void atualizar();
    void atualizar(vector<colisor *> * chao_col);
};

#endif
