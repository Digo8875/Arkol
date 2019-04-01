#ifndef __KNIGHT_INCLUSO__
#define __KNIGHT_INCLUSO__

#include "inimigo.h"

class knight: public inimigo
{
    private:
    sprite spr[16];
    int spr_atual;
    int tick;
    int razao_espada;
    float veloc;

    public:
    knight();
    virtual ~knight();
    knight(int x, int y, vector<golpe *> * golpe_vec, archer * player);
    void animar();
    void atacar(int tipo_ataque);
    void ataca_espada();
    bool atualizar(vector<colisor *> * chao_col, vector<colisor *> * escada_col);
};

#endif
