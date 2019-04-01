#include "knight.h"
#include "espada.h"

knight::knight():inimigo()
{
};

knight::knight(int x, int y, vector<golpe *> * golpe_vec, archer * player):inimigo(x, y, x + 19, y + 31, golpe_vec, player)
{
    bmp = al_load_bitmap("graficos/Mobs.png");

    if(!bmp)
        printf("ERRO:Nao carregou graficos \n");

    col = new colisor(x, y, x + 19, y + 31);
    estado = INIMIGO_ESTADO_CAINDO;

    razao_espada = 0;

    //Lado 1 = esquerda. Lado 2 = direita
    lado_virado = 2;
    mover = 0;

    //Parado olhar direita
    spr[0].tick = 10;
    spr[0].x0 = 24;
    spr[0].y0 = 18;
    spr[0].alt = 31;
    spr[0].lar = 27;

    //Andar p/ direita
    spr[1].tick = 10;
    spr[1].x0 = 87;
    spr[1].y0 = 18;
    spr[1].alt = 31;
    spr[1].lar = 27;
    spr[2].tick = 10;
    spr[2].x0 = 146;
    spr[2].y0 = 18;
    spr[2].alt = 32;
    spr[2].lar = 29;
    spr[3].tick = 10;
    spr[3].x0 = 206;
    spr[3].y0 = 19;
    spr[3].alt = 31;
    spr[3].lar = 30;

    //Parado olhar esquerda
    spr[4].tick = 10;
    spr[4].x0 = 274;
    spr[4].y0 = 18;
    spr[4].alt = 31;
    spr[4].lar = 27;

    //Andar p/ esquerda
    spr[5].tick = 10;
    spr[5].x0 = 333;
    spr[5].y0 = 18;
    spr[5].alt = 31;
    spr[5].lar = 27;
    spr[6].tick = 10;
    spr[6].x0 = 399;
    spr[6].y0 = 18;
    spr[6].alt = 32;
    spr[6].lar = 29;
    spr[7].tick = 10;
    spr[7].x0 = 461;
    spr[7].y0 = 19;
    spr[7].alt = 31;
    spr[7].lar = 30;

    //Atacando p/ direita
    spr[8].tick = 5;
    spr[8].x0 = 22;
    spr[8].y0 = 75;
    spr[8].alt = 38;
    spr[8].lar = 24;
    spr[9].tick = 3;
    spr[9].x0 = 71;
    spr[9].y0 = 77;
    spr[9].alt = 36;
    spr[9].lar = 46;
    spr[10].tick = 2;
    spr[10].x0 = 143;
    spr[10].y0 = 82;
    spr[10].alt = 31;
    spr[10].lar = 29;
    spr[11].tick = 3;
    spr[11].x0 = 207;
    spr[11].y0 = 83;
    spr[11].alt = 31;
    spr[11].lar = 30;

    //Atacando p/ esquerda
    spr[12].tick = 5;
    spr[12].x0 = 274;
    spr[12].y0 = 77;
    spr[12].alt = 38;
    spr[12].lar = 24;
    spr[13].tick = 3;
    spr[13].x0 = 324;
    spr[13].y0 = 79;
    spr[13].alt = 36;
    spr[13].lar = 46;
    spr[14].tick = 2;
    spr[14].x0 = 403;
    spr[14].y0 = 85;
    spr[14].alt = 31;
    spr[14].lar = 29;
    spr[15].tick = 3;
    spr[15].x0 = 465;
    spr[15].y0 = 85;
    spr[15].alt = 31;
    spr[15].lar = 30;

    spr_atual = 0;
    tick = 0;
    golpes = golpe_vec;
};

knight::~knight()
{

};

void knight::animar()
{
    #ifdef DEBUG_ON
        col->mostra(al_map_rgb(255,0,0));
    #endif
    tick ++;

    switch(estado)
    {
        case INIMIGO_ESTADO_NORMAL:
        {
            if(mover)
            {
                if(lado_virado == 1)
                {
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
                if(lado_virado == 2)
                {
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
            }

            break;
        }
        case INIMIGO_ESTADO_FERIDO:
        {
            break;
        }
        case INIMIGO_ESTADO_MORTO:
        {
            break;
        }
        case INIMIGO_ESTADO_CAINDO:
        {
            if(lado_virado == 2)
            {
                spr_atual = 0;
            }
            if(lado_virado == 1)
            {
                spr_atual = 4;
            }
            break;
        }
        case INIMIGO_ESTADO_ATACA_ESPADA:
        {
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
                    estado = INIMIGO_ESTADO_NORMAL;
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
                    estado = INIMIGO_ESTADO_NORMAL;
                }

            }

            break;
        }
    }

    int x_desenha = col->get_sup_esquerdo().x;
    int y_desenha = col->get_sup_esquerdo().y;

    if(spr_atual == 8)
        y_desenha = col->get_sup_esquerdo().y -7;
    if(spr_atual == 9)
        y_desenha = col->get_sup_esquerdo().y -5;
    if(spr_atual == 12)
        y_desenha = col->get_sup_esquerdo().y -7;
    if(spr_atual == 13)
        y_desenha = col->get_sup_esquerdo().y -5;



    //Se virado pra esquerda, começa sprites do sup direito
    if(lado_virado == 1)
    {
        if((col->get_sup_esquerdo().x + spr[spr_atual].lar) > (col->get_sup_esquerdo().x + col->get_largura()))
        {
            int x_diferenca = ((col->get_sup_esquerdo().x + spr[spr_atual].lar) - (col->get_sup_esquerdo().x + col->get_largura()));

            al_draw_bitmap_region(  bmp, spr[spr_atual].x0, spr[spr_atual].y0, spr[spr_atual].lar, spr[spr_atual].alt,
                            x_desenha - x_diferenca, y_desenha, 0);
        }
        else
        {
            al_draw_bitmap_region(  bmp, spr[spr_atual].x0, spr[spr_atual].y0, spr[spr_atual].lar, spr[spr_atual].alt,
                            x_desenha, y_desenha, 0);
        }
    }
    //Se virado para direita, começa sprites do sup esquerdo
    if(lado_virado == 2)
    {
        al_draw_bitmap_region(  bmp, spr[spr_atual].x0, spr[spr_atual].y0, spr[spr_atual].lar, spr[spr_atual].alt,
                            x_desenha, y_desenha, 0);
    }

    posicao pos = col->get_inf_direito();
};

void knight::atacar(int tipo_ataque)
{
    switch(tipo_ataque)
    {
        case 1:
        {
            ataca_espada();
            break;
        }

    }
};

void knight::ataca_espada()
{
    posicao pos2 = col->get_sup_esquerdo();

    if(lado_virado == 2)
        golpes->push_back(new espada(pos2.x + 6, pos2.y -7 , lado_virado));

    if(lado_virado == 1)
        golpes->push_back(new espada(pos2.x - 6, pos2.y - 7, lado_virado));

};

bool knight::atualizar(vector<colisor *> * chao_col, vector<colisor *> * escada_col)
{
    razao_espada ++;

    posicao pos_player = alvo->get_colisor()->get_sup_esquerdo();
    posicao pos = col->get_sup_esquerdo();

    for(unsigned int i = 0; i < chao_col->size(); i++)
    {
        colisor * c_col = chao_col->at(i);
        //Se o knight for pra 'fora' do chao, andando para as beiras, começa estado caindo...
        if(((col->get_inf_direito().x < c_col->get_sup_esquerdo().x) || (col->get_sup_esquerdo().x > c_col->get_inf_direito().x)) && (col->get_inf_direito().y > c_col->get_sup_esquerdo().y - 1))
        {
            estado = INIMIGO_ESTADO_CAINDO;
        }

    }

    //Seta o lado que tem que andar pra pegar o player
    if(pos_player.x < pos.x)
    {
        lado_virado = 1;
    }
    else
    {
        lado_virado = 2;
    }

    switch(estado)
    {
        case INIMIGO_ESTADO_NORMAL:
        {
            mover = false;
            if((rand() % 100) > 50)
            {
                if(lado_virado == 2)
                {
                    pos.x += 2;
                    mover = true;
                }
                if(lado_virado == 1)
                {
                    pos.x -= 2;
                    mover = true;
                }
            }

            //Se player na zona de ataque de espada, ataca espada
            if(((alvo->get_colisor()->get_inf_direito().x + 5 >= col->get_sup_esquerdo().x) && (pos_player.x - 5 <= col->get_inf_direito().x)) &&
                ((alvo->get_colisor()->get_inf_direito().y >= col->get_sup_esquerdo().y) && (pos_player.y <= col->get_inf_direito().y)))
            {
                tick = 0;
                if(razao_espada > RAZAO_ESPADA)
                {
                    atacar(1);
                    razao_espada = 0;
                    estado = INIMIGO_ESTADO_ATACA_ESPADA;
                }
            }

            break;
        }
        case INIMIGO_ESTADO_FERIDO:
        {
            break;
        }
        case INIMIGO_ESTADO_MORTO:
        {
            break;
        }
        case INIMIGO_ESTADO_CAINDO:
        {
            pos.y += 3;
            for(unsigned int i = 0; i < chao_col->size(); i++)
            {
                if(col->colide(chao_col->at(i)))
                {
                    pos.y = chao_col->at(i)->get_sup_esquerdo().y - col->get_altura();
                    estado = INIMIGO_ESTADO_NORMAL;
                }

            }

            col->set_posicao(pos.x, pos.y);
            break;
        }
        case INIMIGO_ESTADO_ATACA_ESPADA:
        {
            break;
        }
    }

    col->set_posicao(pos.x, pos.y);
    return true;
};
