#include "config.h"
#include "archer.h"
#include "cenario.h"
#include "knight.h"

int main()
{
    srand(time(0));
    al_init();

    float tempo = 0.03;
    ALLEGRO_TIMER * timer = NULL;
    timer = al_create_timer(tempo);
    al_start_timer(timer);

    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    //AUDIO
    al_install_audio();
    al_init_acodec_addon();
    ALLEGRO_MIXER * mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_1);
    ALLEGRO_VOICE * voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_1);
    //al_attach_mixer_to_voice(mixer, voice);
    al_set_default_mixer(mixer);

    //CRIAR O DISPLAY
    ALLEGRO_DISPLAY * display = NULL;
    display = al_create_display(800, 600); //CRIA A TELA
    al_set_window_title(display, "Arkol");

    //LISTA DE EVENTOS
    ALLEGRO_EVENT_QUEUE * event_queue = NULL;
    event_queue = al_create_event_queue();

    //TECLADO
    al_install_keyboard();
    ALLEGRO_KEYBOARD_STATE kb;

    //MOUSE
    al_install_mouse();
    al_register_event_source(event_queue, al_get_display_event_source(display)); //EVENTO DE DISPLAY (fechar janela);
    al_register_event_source(event_queue, al_get_timer_event_source(timer)); //EVENTO DE TIMER (framerate);
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_set_target_bitmap(al_get_backbuffer(display));
    ALLEGRO_EVENT ev;

    bool run = true;
    bool redraw = true;

    al_start_timer(timer);

    vector <golpe *> golpeP1;
    vector <golpe *> golpe_inimigo;

    vector <inimigo *> inimigos;
    int inimigos_qtd = QTD_INIMIGOS;
    archer * player1 = new archer(&kb, &golpeP1, 380, 450);
    cenario * cen = new cenario(mixer);

    //COLISORES DE CHAO ----------------------
    vector <colisor *> chao_col;
    chao_col.push_back(new colisor(0,522,800,600));
    chao_col.push_back(new colisor(233,212,797,230));

    //----------------------------------------

    //COLISORES DE ESCADAS ----------------------
    vector <colisor *> escada_col;
    escada_col.push_back(new colisor(355,205,385,515));

    //----------------------------------------

    ALLEGRO_FONT * fonte = al_load_ttf_font("graficos/FreeSansBoldOblique.ttf", 12, 0);
    while(run)
    {
        al_wait_for_event(event_queue, &ev);
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
        if(ev.type == ALLEGRO_EVENT_TIMER)
            redraw = true;
        if(redraw && al_is_event_queue_empty(event_queue))
        {
            al_clear_to_color(al_map_rgb(200,200,200));
            al_get_keyboard_state(&kb);

            //se não tem inimigo, sorteia
            if(inimigos.size() == 0)
            {
                colisor * p_col = player1->get_colisor();

                int onda = rand() % MAX_ONDA + 1;
                if(inimigos_qtd <= 3)
                    onda = 3;

                for(int i = 0; i < onda; i++)
                {
                    int x_enemy = 0;
                    int y_enemy = 0;

                    //Gera no chao superior ou chao inferior
                    if(rand()%100 > 50)
                    {
                        //chao inferior
                        do
                        {
                            x_enemy = 10 + (rand() % 700);
                        }
                        while((x_enemy > (p_col->get_sup_esquerdo().x - 50)) && (x_enemy < (p_col->get_sup_esquerdo().x + p_col->get_largura() + 50)));

                        y_enemy = 515;
                    }
                    else
                    {
                        //chao superior
                        do
                        {
                            x_enemy = 300 + (rand() % 400);
                        }
                        while((x_enemy > (p_col->get_sup_esquerdo().x - 50)) && (x_enemy < (p_col->get_sup_esquerdo().x + p_col->get_largura() + 50)));

                        y_enemy = 150;
                    }

                    inimigos.push_back(new knight(x_enemy, y_enemy, &golpe_inimigo, player1));
                }
            }

            //ATUALIZAR -----------------------------------------------------------
            player1->atualizar(&chao_col, &escada_col);

            for(unsigned int i = 0; i < inimigos.size(); i++)
                inimigos[i]->atualizar(&chao_col, &escada_col);



            //Atualiza golpes PLAYER
            for(unsigned int i = 0; i < golpeP1.size(); i++)
            {
                golpeP1[i]->atualizar(&chao_col);
                colisor * col = golpeP1[i]->get_colisor();

                //golpe saiu da tela sem atingir ninguem ou está no estado 'fim' é para destuí-lo
                if((col->get_inf_esquerdo().x < 0) || (col->get_inf_direito().x > 800) || (golpeP1[i]->get_estado() == GOLPE_ESTADO_FIM))
                {
                    delete golpeP1[i];
                    golpeP1.erase(golpeP1.begin() + i);
                    i--;
                }

                //golpe colidiu com inimigo
                for(unsigned int j = 0; j < inimigos.size(); j++)
                {
                    if(col->colide(inimigos[j]->get_colisor()))
                    {
                        delete golpeP1[i];
                        golpeP1.erase(golpeP1.begin() + i);
                        i--;
                        delete inimigos[j];
                        inimigos.erase(inimigos.begin() + j);
                        j--;

                    }
                }

            }

            //Atualiza golpes INIMIGO
            for(unsigned int i = 0; i < golpe_inimigo.size(); i++)
            {
                printf("golpe enemy %d \n", i);
                golpe_inimigo[i]->atualizar(&chao_col);
                colisor * col = golpe_inimigo[i]->get_colisor();

                //golpe saiu da tela sem atingir ninguem ou está no estado 'fim' é para destuí-lo
                if((col->get_inf_esquerdo().x < 0) || (col->get_inf_direito().x > 800) || (golpe_inimigo[i]->get_estado() == GOLPE_ESTADO_FIM))
                {
                    delete golpe_inimigo[i];
                    golpe_inimigo.erase(golpe_inimigo.begin() + i);
                    i--;
                }

                //golpe colidiu com player
                if(col->colide(player1->get_colisor()))
                {
                    printf("socou player! %d\n", i);
                    delete golpe_inimigo[i];
                    golpe_inimigo.erase(golpe_inimigo.begin() + i);
                    i--;
                }

            }

            //---------------------------------------------------------------------

            //ANIMAR --------------------------------------------------------------
            cen->animar();
            player1->animar();

            for(unsigned int i = 0; i < inimigos.size(); i++)
                inimigos[i]->animar();

            //desenhar colisor do chao
            for(unsigned int i = 0; i < chao_col.size(); i++)
            {
                chao_col.at(i)->mostra(al_map_rgb(255,0,0));
            }

            //desenhar colisor de escada
            for(unsigned int i = 0; i < escada_col.size(); i++)
            {
                escada_col.at(i)->mostra(al_map_rgb(255,0,0));
            }

            for(unsigned int i = 0; i < golpeP1.size(); i++)
                golpeP1[i]->animar();

            for(unsigned int i = 0; i < golpe_inimigo.size(); i++)
                golpe_inimigo[i]->animar();

            //----------------------------------------------------------------------

            redraw = false;
            al_flip_display();
        }
    }

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
