#include "golpe.h"

golpe::golpe()
{
    alvo = NULL;
    bmp = NULL;
    col = NULL;
    dano = 0;
};

golpe::golpe(int x, int y, int largura, int altura)
{
    alvo = NULL;
    bmp = NULL;
    col = new colisor(x, y, x + largura, y + altura);
    dano = 0;
};

golpe::~golpe()
{
};

colisor * golpe::get_colisor()
{
    return col;
};

int golpe::get_dano()
{
    return dano;
};

GOLPE_ESTADO golpe::get_estado()
{
    return estado;
};

void golpe::set_alvo(inimigo *novo_alvo)
{
    alvo = novo_alvo;
};
