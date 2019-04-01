#include "archer.h"
#include "flecha.h"

archer::archer(ALLEGRO_KEYBOARD_STATE * k_state, vector<golpe *> * golpe_vec, int px, int py)
{
    bmp = al_load_bitmap("graficos/Archer.png");

    if(!bmp)
        printf("ERRO:Nao carregou graficos \n");

    col = new colisor(px, py, px + 24, py + 39);
    estado = ARCHER_ESTADO_CAINDO;

    razao_flecha = 0;

    //Lado 1 = esquerda. Lado 2 = direita
    lado_virado = 2;

    //Parado olhar direita
    spr[0].tick = 10;
    spr[0].x0 = 28;
    spr[0].y0 = 17;
    spr[0].alt = 39;
    spr[0].lar = 24;

    //Andar p/ direita
    spr[1].tick = 10;
    spr[1].x0 = 85;
    spr[1].y0 = 17;
    spr[1].alt = 39;
    spr[1].lar = 22;
    spr[2].tick = 10;
    spr[2].x0 = 151;
    spr[2].y0 = 18;
    spr[2].alt = 39;
    spr[2].lar = 24;
    spr[3].tick = 10;
    spr[3].x0 = 213;
    spr[3].y0 = 18;
    spr[3].alt = 38;
    spr[3].lar = 28;

    //Parado olhar esquerda
    spr[4].tick = 10;
    spr[4].x0 = 268;
    spr[4].y0 = 17;
    spr[4].alt = 39;
    spr[4].lar = 24;

    //Andar p/ esquerda
    spr[5].tick = 10;
    spr[5].x0 = 341;
    spr[5].y0 = 17;
    spr[5].alt = 39;
    spr[5].lar = 22;
    spr[6].tick = 10;
    spr[6].x0 = 401;
    spr[6].y0 = 18;
    spr[6].alt = 39;
    spr[6].lar = 24;
    spr[7].tick = 10;
    spr[7].x0 = 463;
    spr[7].y0 = 18;
    spr[7].alt = 38;
    spr[7].lar = 28;

    //Atacando p/ direita
    spr[8].tick = 4;
    spr[8].x0 = 29;
    spr[8].y0 = 81;
    spr[8].alt = 39;
    spr[8].lar = 23;
    spr[9].tick = 3;
    spr[9].x0 = 93;
    spr[9].y0 = 81;
    spr[9].alt = 39;
    spr[9].lar = 35;
    spr[10].tick = 2;
    spr[10].x0 = 156;
    spr[10].y0 = 81;
    spr[10].alt = 39;
    spr[10].lar = 28;
    spr[11].tick = 3;
    spr[11].x0 = 220;
    spr[11].y0 = 81;
    spr[11].alt = 39;
    spr[11].lar = 24;

    //Atacando p/ esquerda
    spr[12].tick = 4;
    spr[12].x0 = 268;
    spr[12].y0 = 81;
    spr[12].alt = 39;
    spr[12].lar = 23;
    spr[13].tick = 3;
    spr[13].x0 = 320;
    spr[13].y0 = 81;
    spr[13].alt = 39;
    spr[13].lar = 35;
    spr[14].tick = 2;
    spr[14].x0 = 392;
    spr[14].y0 = 81;
    spr[14].alt = 39;
    spr[14].lar = 28;
    spr[15].tick = 3;
    spr[15].x0 = 460;
    spr[15].y0 = 81;
    spr[15].alt = 39;
    spr[15].lar = 24;

    spr_atual = 0;
    tec = k_state;
    tick = 0;
    golpes = golpe_vec;
};

archer::~archer()
{

};

void archer::animar()
{
#ifdef DEBUG_ON
    col->mostra(al_map_rgb(255,0,0));
#endif
    tick ++;

    switch(estado)
    {
        case ARCHER_ESTADO_NORMAL:
            if(al_key_down(tec, ALLEGRO_KEY_LEFT))
            {
                lado_virado = 1;
                //Se apertar pra andar pra esquerda e os sprites nao estiverem entre os andares da esquenda, ja coloca a base pra esquerda
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
                    spr_atual = 4;
            }
            if(al_key_down(tec, ALLEGRO_KEY_RIGHT))
            {
                lado_virado = 2;
                //Se apertar pra andar pra direita e os sprites nao estiverem entre os andares da direita, ja coloca a base pra direita
                if(spr_atual<0 || spr_atual>3)
                {
                    spr_atual = 0;
                }
                if(tick >= spr[spr_atual].tick)
                {
                    spr_atual ++;
                    tick = 0;
                }
                if(spr_atual == 4)
                    spr_atual = 0;
            }

            break;

        case ARCHER_ESTADO_PREPARA_FLECHA:
            if(lado_virado == 2)
            {
                if(spr_atual<8 || spr_atual>11)
                {
                    spr_atual = 8;
                }
                if(tick >= spr[spr_atual].tick)
                {
                    spr_atual ++;
                    tick = 0;
                }
                if(spr_atual == 11)
                {
                    spr_atual = 0;
                    tick = 0;
                    estado = ARCHER_ESTADO_SOLTA_FLECHA;
                }
            }
            if(lado_virado == 1)
            {
                if(spr_atual<12 || spr_atual>15)
                {
                    spr_atual = 12;
                }
                if(tick >= spr[spr_atual].tick)
                {
                    spr_atual ++;
                    tick = 0;
                }
                if(spr_atual == 15)
                {
                    spr_atual = 4;
                    tick = 0;
                    estado = ARCHER_ESTADO_SOLTA_FLECHA;
                }
            }
            break;
        case ARCHER_ESTADO_SOLTA_FLECHA:
            break;
        case ARCHER_ESTADO_FERIDO:
            break;
        case ARCHER_ESTADO_MORTO:
            break;
        case ARCHER_ESTADO_CAINDO:
            if(al_key_down(tec, ALLEGRO_KEY_RIGHT))
            {
                spr_atual = 0;
            }
            if(al_key_down(tec, ALLEGRO_KEY_LEFT))
            {
                spr_atual = 4;
            }
            break;
        case ARCHER_ESTADO_PULO:
            if(al_key_down(tec, ALLEGRO_KEY_RIGHT))
            {
                spr_atual = 0;
            }
            if(al_key_down(tec, ALLEGRO_KEY_LEFT))
            {
                spr_atual = 4;
            }
            break;
        case ARCHER_ESTADO_ESCADA:
            break;
    }

    //Se virado pra esquerda, começa sprites do sup direito
    if(lado_virado == 1)
    {
        if((col->get_sup_esquerdo().x + spr[spr_atual].lar) > (col->get_sup_esquerdo().x + col->get_largura()))
        {
            int x_diferenca = ((col->get_sup_esquerdo().x + spr[spr_atual].lar) - (col->get_sup_esquerdo().x + col->get_largura()));

            al_draw_bitmap_region(  bmp, spr[spr_atual].x0, spr[spr_atual].y0, spr[spr_atual].lar, spr[spr_atual].alt,
                            col->get_sup_esquerdo().x - x_diferenca, col->get_sup_esquerdo().y, 0);
        }
        else
        {
            al_draw_bitmap_region(  bmp, spr[spr_atual].x0, spr[spr_atual].y0, spr[spr_atual].lar, spr[spr_atual].alt,
                            col->get_sup_esquerdo().x, col->get_sup_esquerdo().y, 0);
        }
    }
    //Se virado para direita, começa sprites do sup esquerdo
    if(lado_virado == 2)
    {
        al_draw_bitmap_region(  bmp, spr[spr_atual].x0, spr[spr_atual].y0, spr[spr_atual].lar, spr[spr_atual].alt,
                            col->get_sup_esquerdo().x, col->get_sup_esquerdo().y, 0);
    }

    posicao pos = col->get_inf_direito();
};

bool archer::atualizar(vector<colisor *> * chao_col, vector<colisor *> * escada_col)
{
    razao_flecha ++;
    int flag_col_escada = false;

    for(unsigned int i = 0; i < escada_col->size(); i++)
    {
        //Se o player está 'dentro' da escada
        if((col->get_sup_esquerdo().x > escada_col->at(i)->get_sup_esquerdo().x) && (col->get_inf_direito().x < escada_col->at(i)->get_inf_direito().x))
        {
            flag_col_escada = true;
        }

    }

    for(unsigned int i = 0; i < chao_col->size(); i++)
    {
        colisor * c_col = chao_col->at(i);
        //Se o player for pra 'fora' do chao, andando para as beiras, começa estado caindo...
        if(((col->get_inf_direito().x < c_col->get_sup_esquerdo().x) || (col->get_sup_esquerdo().x > c_col->get_inf_direito().x)) && (col->get_inf_direito().y > c_col->get_sup_esquerdo().y - 2))
        {
            estado = ARCHER_ESTADO_CAINDO;
        }

    }

    switch(estado)
    {
        case ARCHER_ESTADO_NORMAL:
        {
            posicao pos = col->get_sup_esquerdo();

            if(al_key_down(tec, ALLEGRO_KEY_LEFT) && (col->get_sup_esquerdo().x > 0))
                pos.x -= 3;
            if(al_key_down(tec, ALLEGRO_KEY_RIGHT) && ((col->get_sup_esquerdo().x + col->get_largura()) < 800))
                pos.x += 3;
            if(al_key_down(tec, ALLEGRO_KEY_Z))
            {
                tick = 0;
                if(razao_flecha > RAZAO_FLECHA)
                {
                    estado = ARCHER_ESTADO_PREPARA_FLECHA;
                }
            }
            if(al_key_down(tec, ALLEGRO_KEY_SPACE))
            {
                forca_pulo = 40;
                estado = ARCHER_ESTADO_PULO;
            }
            if(al_key_down(tec, ALLEGRO_KEY_UP))
            {
                if(flag_col_escada)
                {
                    estado = ARCHER_ESTADO_ESCADA;
                }
            }
            if(al_key_down(tec, ALLEGRO_KEY_DOWN))
            {
                if(flag_col_escada)
                {
                    estado = ARCHER_ESTADO_ESCADA;
                }
            }

            col->set_posicao(pos.x, pos.y);
            break;
        }

        case ARCHER_ESTADO_PREPARA_FLECHA:
            break;

        case ARCHER_ESTADO_SOLTA_FLECHA:
                if(razao_flecha > RAZAO_FLECHA)
                    atira_flecha();
                razao_flecha = 0;
                estado = ARCHER_ESTADO_NORMAL;
            break;

        case ARCHER_ESTADO_FERIDO:
            break;

        case ARCHER_ESTADO_MORTO:
            break;

        case ARCHER_ESTADO_CAINDO:
        {
            posicao pos = col->get_sup_esquerdo();
            pos.y += 3;

            for(unsigned int i = 0; i < chao_col->size(); i++)
            {
                if(col->colide(chao_col->at(i)))
                {
                    pos.y = chao_col->at(i)->get_sup_esquerdo().y - col->get_altura();
                    estado = ARCHER_ESTADO_NORMAL;
                }

            }

            if(al_key_down(tec, ALLEGRO_KEY_LEFT) && (col->get_sup_esquerdo().x > 0))
            {
                pos.x -= 3;
                lado_virado = 1;
            }
            if(al_key_down(tec, ALLEGRO_KEY_RIGHT) && ((col->get_sup_esquerdo().x + col->get_largura()) < 800))
            {
                pos.x += 3;
                lado_virado = 2;
            }
            if(al_key_down(tec, ALLEGRO_KEY_Z))
            {
                tick = 0;
                if(razao_flecha > RAZAO_FLECHA)
                {
                    atira_flecha();
                    razao_flecha = 0;
                }
            }
            if(al_key_down(tec, ALLEGRO_KEY_UP))
            {
                if(flag_col_escada)
                {
                    estado = ARCHER_ESTADO_ESCADA;
                }
            }
            if(al_key_down(tec, ALLEGRO_KEY_DOWN))
            {
                if(flag_col_escada)
                {
                    estado = ARCHER_ESTADO_ESCADA;
                }
            }

            col->set_posicao(pos.x, pos.y);
            break;
        }

        case ARCHER_ESTADO_PULO:
            {
            posicao pos = col->get_sup_esquerdo();
            if(forca_pulo > 0)
            {
                forca_pulo -= 2;
                pos.y -= 4;
            }
            else
                estado = ARCHER_ESTADO_CAINDO;

            if(al_key_down(tec, ALLEGRO_KEY_LEFT) && (col->get_sup_esquerdo().x > 0))
            {
                pos.x -= 3;
                lado_virado = 1;
            }
            if(al_key_down(tec, ALLEGRO_KEY_RIGHT) && ((col->get_sup_esquerdo().x + col->get_largura()) < 800))
            {
                pos.x += 3;
                lado_virado = 2;
            }
            if(al_key_down(tec, ALLEGRO_KEY_Z))
            {
                tick = 0;
                if(razao_flecha > RAZAO_FLECHA)
                {
                    atira_flecha();
                    razao_flecha = 0;
                }
            }
            if(al_key_down(tec, ALLEGRO_KEY_UP))
            {
                if(flag_col_escada)
                {
                    estado = ARCHER_ESTADO_ESCADA;
                }
            }
            if(al_key_down(tec, ALLEGRO_KEY_DOWN))
            {
                if(flag_col_escada)
                {
                    estado = ARCHER_ESTADO_ESCADA;
                }
            }

            col->set_posicao(pos.x, pos.y);
            break;
            }
        case ARCHER_ESTADO_ESCADA:
            posicao pos = col->get_sup_esquerdo();
            colisor * esc_col;

            for(unsigned int i = 0; i < escada_col->size(); i++)
            {
                if(col->colide(escada_col->at(i)))
                {
                    esc_col = new colisor(escada_col->at(i)->get_sup_esquerdo().x, escada_col->at(i)->get_sup_esquerdo().y,
                                          escada_col->at(i)->get_inf_direito().x, escada_col->at(i)->get_inf_direito().y);

                    break;
                }

            }

            if(al_key_down(tec, ALLEGRO_KEY_UP))
            {
                pos.y -= 6;
                if((col->get_sup_esquerdo().y) < esc_col->get_sup_esquerdo().y)
                {
                    pos.y = esc_col->get_sup_esquerdo().y - col->get_altura();
                    estado = ARCHER_ESTADO_CAINDO;
                }
            }
            if(al_key_down(tec, ALLEGRO_KEY_DOWN))
            {
                pos.y += 4;
                if(col->get_inf_direito().y > esc_col->get_inf_direito().y)
                {
                    pos.y = esc_col->get_inf_direito().y - col->get_altura();
                    estado = ARCHER_ESTADO_CAINDO;
                }
            }

            col->set_posicao(pos.x, pos.y);
            break;
    }

    return true;
};

void archer::atira_flecha()
{
    printf("flechou\n");
    posicao pos2 = col->get_sup_esquerdo();

    if(lado_virado == 2)
        golpes->push_back(new flecha(pos2.x + 15, pos2.y + 15, lado_virado));

    if(lado_virado == 1)
        golpes->push_back(new flecha(pos2.x - 11, pos2.y + 15, lado_virado));

};

colisor * archer::get_colisor()
{
    return col;
};

ARCHER_ESTADO archer::get_estado()
{
    return estado;
};
