#ifndef __COLISOR_INCLUSO__
#define __COLISOR_INCLUSO__

#include "config.h"

class colisor
{
    private:
    float X0;
    float X1;
    float Y0;
    float Y1;

    public:
    colisor();
    virtual ~colisor();
    colisor(int x0, int y0, int x1, int y1);
    bool colide(colisor * outro);
    int get_altura();
    posicao get_inf_direito();
    posicao get_inf_esquerdo();
    int get_largura();
    posicao get_sup_esquerdo();
    posicao get_sup_direito();
    void mostra(ALLEGRO_COLOR cor);
    void set_posicao(int x, int y);
    void set_tamanho(int altura, int largura);
};

#endif
