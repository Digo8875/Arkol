#include "flecha.h"

flecha::flecha(): golpe()
{
};

flecha::flecha(int x, int y, int lado_v):golpe(x + 23, y + 2, 3, 5)
{
    bmp = al_load_bitmap("graficos/Archer.png");
    dano = 100;
    estado = GOLPE_ESTADO_VOANDO;
    lado_virado = lado_v;
    distancia = 300;
    x_inicial = x + 23;
    y_inicial = y + 2;

    //Flecha caida no chão
    spr[0].tick = 30;
    spr[0].x0 = 515;
    spr[0].y0 = 33;
    spr[0].alt = 25;
    spr[0].lar = 9;
    spr[1].tick = 30;
    spr[1].x0 = 525;
    spr[1].y0 = 33;
    spr[1].alt = 25;
    spr[1].lar = 9;
    spr[2].tick = 30;
    spr[2].x0 = 535;
    spr[2].y0 = 33;
    spr[2].alt = 25;
    spr[2].lar = 9;

    //Flecha voando p/ direita
    spr[3].tick = 0;
    spr[3].x0 = 513;
    spr[3].y0 = 5;
    spr[3].alt = 9;
    spr[3].lar = 26;
    spr[4].tick = 0;
    spr[4].x0 = 514;
    spr[4].y0 = 15;
    spr[4].alt = 14;
    spr[4].lar = 22;

    //Flecha voando p/ esquerda
    spr[5].tick = 0;
    spr[5].x0 = 549;
    spr[5].y0 = 5;
    spr[5].alt = 9;
    spr[5].lar = 26;
    spr[6].tick = 0;
    spr[6].x0 = 552;
    spr[6].y0 = 15;
    spr[6].alt = 14;
    spr[6].lar = 22;

    spr_atual = 0;
    tick = 0;
};

flecha::~flecha()
{

};

void flecha::animar()
{
#ifdef DEBUG_ON
    col->mostra(al_map_rgb(255,0,0));
#endif

    tick ++;

    switch(estado)
    {
        case GOLPE_ESTADO_VOANDO:
            //Voando pra Direita
            if(lado_virado == 2)
            {
                tick = 0;
                spr_atual = 3;

                al_draw_bitmap_region(  bmp, spr[spr_atual].x0, spr[spr_atual].y0, spr[spr_atual].lar, spr[spr_atual].alt,
                            col->get_sup_esquerdo().x - 23, col->get_sup_esquerdo().y - 2, 0);
            }
            //Voando pra Esquerda
            if(lado_virado == 1)
            {
                tick = 0;
                spr_atual = 5;

                al_draw_bitmap_region(  bmp, spr[spr_atual].x0, spr[spr_atual].y0, spr[spr_atual].lar, spr[spr_atual].alt,
                        col->get_sup_esquerdo().x, col->get_sup_esquerdo().y - 2, 0);
            }
            break;

        case GOLPE_ESTADO_CAINDO:
            //Voando pra Direita
            if(lado_virado == 2)
            {
                tick = 0;
                spr_atual = 4;

                al_draw_bitmap_region(  bmp, spr[spr_atual].x0, spr[spr_atual].y0, spr[spr_atual].lar, spr[spr_atual].alt,
                            col->get_sup_esquerdo().x - 19, col->get_sup_esquerdo().y - 11, 0);
            }
            //Voando pra Esquerda
            if(lado_virado == 1)
            {
                tick = 0;
                spr_atual = 6;

                al_draw_bitmap_region(  bmp, spr[spr_atual].x0, spr[spr_atual].y0, spr[spr_atual].lar, spr[spr_atual].alt,
                            col->get_sup_esquerdo().x, col->get_sup_esquerdo().y - 11, 0);
            }
            break;

        case GOLPE_ESTADO_CHAO:
            if(spr_atual<0 || spr_atual>2)
            {
                spr_atual = 0;
            }
            if(tick >= spr[spr_atual].tick)
            {
                spr_atual ++;
                tick = 0;
            }
            if(spr_atual == 3)
            {
                spr_atual = 2;
                estado = GOLPE_ESTADO_FIM;
            }

            al_draw_bitmap_region(  bmp, spr[spr_atual].x0, spr[spr_atual].y0, spr[spr_atual].lar, spr[spr_atual].alt,
                            col->get_sup_esquerdo().x - 2, col->get_sup_esquerdo().y - 22, 0);
            break;

        case GOLPE_ESTADO_FIM:
            break;
    }

};

void flecha::atualizar()
{
};

void flecha::atualizar(vector<colisor *> * chao_col)
{
    switch(estado)
    {
        case GOLPE_ESTADO_VOANDO:
        {
            posicao pos = col->get_sup_esquerdo();
            //Se estiver voando pra Direnta
            if(lado_virado == 2)
            {
                if((pos.x - x_inicial) < (distancia * 0.4))
                    pos.x += 10;
                else if((pos.x - x_inicial) < (distancia * 0.6))
                    pos.x += 7;
                else
                    pos.x += 5;

                if((pos.x - x_inicial) > (distancia * 0.7))
                {
                    estado = GOLPE_ESTADO_CAINDO;
                }
            }
            //Se estiver voando pra Esquerda
            if(lado_virado == 1)
            {
                if((x_inicial - pos.x) < (distancia * 0.4))
                    pos.x -= 10;
                else if((x_inicial - pos.x) < (distancia * 0.6))
                    pos.x -= 7;
                else
                    pos.x -= 5;

                if((x_inicial - pos.x) > (distancia * 0.7))
                {
                    estado = GOLPE_ESTADO_CAINDO;
                }
            }

            col->set_posicao(pos.x, pos.y);
            break;
        }

        case GOLPE_ESTADO_CAINDO:
        {
            posicao pos = col->get_sup_esquerdo();
            //Se estiver caindo pra Direnta
            if(lado_virado == 2)
            {
                pos.x += 4;
                if((pos.x - x_inicial) > (distancia * 0.7))
                {
                    pos.y += 1;
                }
            }
            //Se estiver caindo pra Esquerda
            if(lado_virado == 1)
            {
                pos.x -= 4;
                if((x_inicial - pos.x) > (distancia * 0.7))
                {
                    pos.y += 1;
                }
            }

            for(unsigned int i = 0; i < chao_col->size(); i++)
            {
                if(col->colide(chao_col->at(i)))
                {
                    pos.y = chao_col->at(i)->get_sup_esquerdo().y - col->get_altura();
                    estado = GOLPE_ESTADO_CHAO;
                    tick = 0;
                }

            }

            col->set_posicao(pos.x, pos.y);
            break;
        }
        case GOLPE_ESTADO_CHAO:
            break;
        case GOLPE_ESTADO_FIM:
            break;
    }
};
