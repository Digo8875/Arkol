#include "inimigo.h"

inimigo::inimigo()
{
    alvo = NULL;
    bmp = NULL;
    col = 0;
    estado = INIMIGO_ESTADO_NORMAL;
    golpes = NULL;
};

inimigo::inimigo(int x, int y, int alt, int lar, vector<golpe *> * golpe_vec, archer * player)
{
    alvo = player;
    bmp = NULL;
    col = new colisor(x, y, x + lar, y + alt);
    golpes = golpe_vec;
};
inimigo::~inimigo()
{
};

colisor * inimigo::get_colisor()
{
    return col;
};

INIMIGO_ESTADO inimigo::get_estado()
{
    return estado;
};
