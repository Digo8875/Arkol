#include "colisor.h"

colisor::colisor()
{
    X0 = 0.0f;
    X1 = 0.0f;
    Y0 = 0.0f;
    X1 = 0.0f;
};

colisor::colisor(int x0, int y0, int x1, int y1)
{
    X0 = x0;
    X1 = x1;
    Y0 = y0;
    Y1 = y1;
};

colisor::~colisor()
{
};

bool colisor::colide(colisor * outro)
{
    return (outro->get_sup_esquerdo().x <= X1 && outro->get_inf_direito().x >= X0 &&
            outro->get_sup_esquerdo().y <= Y1 && outro->get_inf_direito().y >= Y0);
};

int colisor::get_altura()
{
    return Y1 - Y0;
};

posicao colisor::get_inf_direito()
{
    posicao pos;
    pos.x = X1;
    pos.y = Y1;
    return pos;
};

posicao colisor::get_inf_esquerdo()
{
    posicao pos;
    pos.x = X0;
    pos.y = Y1;
    return pos;
};

int colisor::get_largura()
{
    return X1 - X0;
};

posicao colisor::get_sup_esquerdo()
{
    posicao pos;
    pos.x = X0;
    pos.y = Y0;
    return pos;
};

posicao colisor::get_sup_direito()
{
    posicao pos;
    pos.x = X1;
    pos.y = Y0;
    return pos;
};

void colisor::mostra(ALLEGRO_COLOR cor)
{
    al_draw_rectangle(X0, Y0, X1, Y1, cor, 1);
};

void colisor::set_posicao(int x, int y)
{
    int alt = get_altura();
    int lar = get_largura();
    X0 = x;
    Y0 = y;
    X1 = x + lar;
    Y1 = y + alt;
};

void colisor::set_tamanho(int altura, int largura)
{
    X1 = X0 + largura;
    Y1 = Y0 + altura;
};
