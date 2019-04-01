#include "espada.h"

espada::espada(): golpe()
{
};

espada::espada(int x, int y, int lado_v):golpe(x +6 , y - 7, 15, 12)
{
    bmp = al_load_bitmap("graficos/Mobs.png");
    dano = 100;
    estado = GOLPE_ESTADO_ATACANDO;
    lado_virado = lado_v;
    x_inicial = x;
    y_inicial = y;

    //Atacando Espada p/ direita
    spr[0].tick = 5;
    spr[0].x0 = 22;
    spr[0].y0 = 75;
    spr[0].alt = 38;
    spr[0].lar = 24;
    spr[1].tick = 3;
    spr[1].x0 = 71;
    spr[1].y0 = 77;
    spr[1].alt = 36;
    spr[1].lar = 46;
    spr[2].tick = 2;
    spr[2].x0 = 143;
    spr[2].y0 = 82;
    spr[2].alt = 31;
    spr[2].lar = 29;
    spr[3].tick = 3;
    spr[3].x0 = 207;
    spr[3].y0 = 83;
    spr[3].alt = 31;
    spr[3].lar = 30;

    //Atacando Espada p/ esquerda
    spr[4].tick = 5;
    spr[4].x0 = 274;
    spr[4].y0 = 77;
    spr[4].alt = 38;
    spr[4].lar = 24;
    spr[5].tick = 3;
    spr[5].x0 = 324;
    spr[5].y0 = 79;
    spr[5].alt = 36;
    spr[5].lar = 46;
    spr[6].tick = 2;
    spr[6].x0 = 403;
    spr[6].y0 = 85;
    spr[6].alt = 31;
    spr[6].lar = 29;
    spr[7].tick = 3;
    spr[7].x0 = 465;
    spr[7].y0 = 85;
    spr[7].alt = 31;
    spr[7].lar = 30;

    spr_atual = 0;
    tick = 0;
};

espada::~espada()
{
    printf("espada bagaçou!\n");
};

void espada::animar()
{
#ifdef DEBUG_ON
    col->mostra(al_map_rgb(255,0,0));
#endif

    tick ++;

    switch(estado)
    {
        printf("??? \n");
        case GOLPE_ESTADO_ATACANDO:
            //Atacando Espada pra Direita
            if(lado_virado == 2)
            {
                if(spr_atual<0 || spr_atual>3)
                {
                    printf(" apr 0\n");
                    spr_atual = 0;
                }
                if(tick >= spr[spr_atual].tick)
                {
                    spr_atual ++;
                    tick = 0;
                }
                if(spr_atual == 4)
                {
                    spr_atual = 3;
                    estado = GOLPE_ESTADO_FIM;
                }
            }
            //Atacando Espada pra Esquerda
            if(lado_virado == 1)
            {
                if(spr_atual<4 || spr_atual>7)
                {
                    spr_atual = 4;
                }
                if(tick >= spr[spr_atual].tick)
                {
                    spr_atual ++;
                    tick = 0;
                }
                if(spr_atual == 8)
                {
                    spr_atual = 7;
                    estado = GOLPE_ESTADO_FIM;
                }
            }
            break;

        case GOLPE_ESTADO_FIM:
        {
            break;
        }
    }

};

void espada::atualizar()
{
};

void espada::atualizar(vector<colisor *> * chao_col)
{
    switch(estado)
    {
        case GOLPE_ESTADO_ATACANDO:
        {
            //Se estiver atacando pra Direita
            if(lado_virado == 2)
            {
                if(spr_atual == 0)
                {
                    printf(" COL 0\n");
                    col->set_posicao(x_inicial + 6, y_inicial - 7);
                    col->set_tamanho(12, 15);
                }
                if(spr_atual == 1)
                {
                    col->set_posicao(x_inicial + 21, y_inicial - 7);
                    col->set_tamanho(43, 27);
                }
            }
            //Se estiver atacando pra Esquerda
            if(lado_virado == 1)
            {
                if(spr_atual == 4)
                {
                    col->set_posicao(x_inicial - 6, y_inicial - 7);
                    col->set_tamanho(12, 15);
                }
                if(spr_atual == 5)
                {
                    col->set_posicao(x_inicial - 17, y_inicial - 7);
                    col->set_tamanho(43, 27);
                }
            }

            break;
        }

        case GOLPE_ESTADO_FIM:
        {
            break;
        }
    }
};
