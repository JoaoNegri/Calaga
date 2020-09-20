//
// Created by joao on 12/09/2020.
//

#include "jogo.h"
#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#define MAXTIROS 1000
#define INIMIGOS 5

int direcao=0;

struct {
    int x;
    int y;
    char aparencia;
}loc_inimigo[INIMIGOS],tiro[MAXTIROS];

void iniciar_tiro (int xtiros);

void continuar_tiro();

void zerar_tiro();

void criar_inimigo();

void mostrar_inimigo(int max_x, int x);

void detectar_colisao();

int detectar_termino();

int jogoo(int argc, char *argv[]) {
    int xatual=0;
    int max_y = 0, max_x = 0;
    int posicao = 0;
    int andar=0;
    int endgame = 0;
    zerar_tiro();

    initscr();
    noecho();
    curs_set(FALSE);

    criar_inimigo();

    while(endgame == 0) {
        getmaxyx(stdscr, max_y, max_x);
        //clear();
        mvprintw(20,posicao,"/'\\");
        //mvprintw(5,5,"%d",posicao);
        //mvprintw(8,6,"andar=%d",andar);



        endgame = detectar_termino();
        detectar_colisao();
        mostrar_inimigo(max_x,xatual);
        continuar_tiro();
        timeout (17);
        andar = getch();



        refresh();
        if (andar==32){
            iniciar_tiro(posicao);
        }

        if (andar == 68)
            if(posicao !=0)
                posicao=posicao - 1;

        if (andar == 67)
            if (posicao != max_x-3)
                posicao=posicao + 1;


        clear();
    }
    if (endgame==1)
        mvprintw(5,5,"Voce ganhou !!!!!");
    refresh();
    sleep (2);
    endwin();
}

void criar_inimigo(){
    int j=0;
    for (int i=0; i<INIMIGOS; i++){
        loc_inimigo[i].x=j;
        loc_inimigo[i].aparencia='*';
        j=j+2;
    }
}

void mostrar_inimigo(int max_x,int x){
    int j=0;
    for (int i=0; i<INIMIGOS; i++){
        if (direcao==0) {
            mvprintw(loc_inimigo[i].y,loc_inimigo[i].x, "%c",loc_inimigo[i].aparencia);
            loc_inimigo[i].x++;
            if (loc_inimigo[i].x==max_x) {
                direcao = 1;
                for (j=0;j<INIMIGOS;j++)
                    loc_inimigo[j].y++;
            }
        }
        else {
            mvprintw(loc_inimigo[i].y,loc_inimigo[i].x, "%c",loc_inimigo[i].aparencia);
            loc_inimigo[i].x--;
            if (loc_inimigo[i].x==0) {
                direcao = 0;
                for (j=0;j<INIMIGOS;j++)
                    loc_inimigo[j].y++;
                loc_inimigo[i].x=loc_inimigo[i].x+2; //quando ele troca a direcao o x que e igual a 0 fica deslocado 2 para a esquerda
            }
        }
    }
}

void iniciar_tiro (int xtiro){
    int i=0;

    mvprintw(19,xtiro,"|");
    refresh();
    do{
        mvprintw(2,2,"X=%d ",i);
        refresh();

        if (tiro[i].x==0) {
            tiro[i].x = xtiro;
            break;
        }
        i++;
    }while (tiro[i-1].x!=0);

}

void continuar_tiro(){
    for(int i=0; i<MAXTIROS;i++){
        if (tiro[i].x!=0) {
            if (tiro[i].y!=0) {
                tiro[i].y--;
                mvprintw(tiro[i].y, tiro[i].x, "|");
                mvprintw(8, 8, "X=%d  y=%d", tiro[i].x, tiro[i].y);
                //refresh();
                //sleep(1);
            }
        }

    }
};

void zerar_tiro(){
    for (int i=0; i<MAXTIROS;i++){
        tiro[i].x=0;
    }
    for (int i=0; i<MAXTIROS;i++){
        tiro[i].y=20;
    }
    for (int i=0; i<INIMIGOS;i++){
        loc_inimigo[i].x=0;
    }
    for (int i=0; i<INIMIGOS;i++){
        loc_inimigo[i].y=0;
    }
}

void detectar_colisao(){
    for (int i=0;i<INIMIGOS;i++){
        for (int j=0;j<MAXTIROS;j++){
            if (loc_inimigo[i].x == tiro[j].x && loc_inimigo[i].y == tiro[j].y)
                loc_inimigo[i].aparencia=' ';
        }
    }
}

int detectar_termino(){
   int aux=0;
    for (int i=0;i<INIMIGOS;i++){
        if (loc_inimigo[i].aparencia == ' ')
            aux++;
    }
    if (aux == INIMIGOS)
        return 1;
    else
        return 0;
}