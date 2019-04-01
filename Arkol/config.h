#ifndef __CONFIG_INCLUSO__
#define __CONFIG_INCLUSO__

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

#define DEBUG_ON
#define QTD_INIMIGOS 10
#define MAX_ONDA 3

using namespace std;

struct sprite
{
    int alt;
    int lar;
    int tick;
    int x0;
    int y0;
};

struct posicao
{
    int x;
    int y;
};

enum ARCHER_ESTADO
{
    ARCHER_ESTADO_NORMAL = 0,
    ARCHER_ESTADO_PREPARA_FLECHA = 1,
    ARCHER_ESTADO_SOLTA_FLECHA = 2,
    ARCHER_ESTADO_FERIDO = 3,
    ARCHER_ESTADO_MORTO = 4,
    ARCHER_ESTADO_CAINDO = 5,
    ARCHER_ESTADO_PULO = 6,
    ARCHER_ESTADO_ESCADA = 7
};

enum GOLPE_ESTADO
{
    GOLPE_ESTADO_VOANDO = 0,
    GOLPE_ESTADO_CAINDO = 1,
    GOLPE_ESTADO_CHAO = 2,
    GOLPE_ESTADO_FIM = 3,
    GOLPE_ESTADO_ATACANDO = 4
};

enum INIMIGO_ESTADO
{
    INIMIGO_ESTADO_NORMAL = 0,
    INIMIGO_ESTADO_MORTO = 1,
    INIMIGO_ESTADO_FERIDO = 2,
    INIMIGO_ESTADO_CAINDO = 3,
    INIMIGO_ESTADO_ATACA_ESPADA = 4
};

enum RAZAO_ATAQUE
{
    RAZAO_FLECHA = 20,
    RAZAO_ESPADA = 30
};

#endif
