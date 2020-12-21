//
// Created by joao on 12/09/2020.
//

#include "jogo.h"
#include <ncurses.h>
#include <unistd.h>


#define MAXTIROS 1000
#define INIMIGOS 9

int direcao=0;

struct {
    int x;
    int y;
    char aparencia;
}loc_inimigo[INIMIGOS],tiro[MAXTIROS];

void iniciar_tiro (int xtiros, int max_y);

void continuar_tiro();

void zerar_tiro(int max_y);

void criar_inimigo();

void mostrar_inimigo(int max_x);

void detectar_colisao();

int detectar_termino();

int detectar_game_over(int max_y);

int jogoo() {
    int pontuacao = 1000;
    int max_y = 0, max_x= 0;
    int posicao = 0;
    int andar;
    int endgame = 0, gameover = 0;
    getmaxyx(stdscr, max_y, max_x);
    max_y--;
    zerar_tiro(max_y);

    initscr();
    noecho();
    curs_set(FALSE);

    criar_inimigo();

    while(gameover == 0 && endgame == 0) {
        getmaxyx(stdscr, max_y, max_x);
        max_y--;
        mvprintw(max_y,posicao,"/'\\");


        gameover = detectar_termino();
        endgame = detectar_game_over(max_y);
        detectar_colisao();
        mostrar_inimigo(max_x);
        continuar_tiro();
        timeout (17);
        andar = getch();



        refresh();
        if (andar==32){
            iniciar_tiro(posicao, max_y);
            pontuacao = pontuacao - 10;
        }

        if (andar == 68)
            if(posicao !=0)
                posicao=posicao - 1;

        if (andar == 67)
            if (posicao != max_x-3)
                posicao=posicao + 1;


        clear();
    }
    if (gameover==1)
        mvprintw(5,5,"Voce ganhou !!!!!");
    else {
        mvprintw(5, 5, "Voce perdeu");
        pontuacao = 0;
    }
    refresh();
    sleep (2);
    endwin();
    return pontuacao;
}

void criar_inimigo(){
    int j=0;
    for (int i=0; i<INIMIGOS; i++){
        loc_inimigo[i].x=j;
        loc_inimigo[i].aparencia='*';
        j=j+2;
    }
}

void mostrar_inimigo(int max_x){
    int j;
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

void iniciar_tiro (int xtiro, int max_y){
    int i=0;

    mvprintw(max_y-1,xtiro+1,"|");
    refresh();
    do{

        refresh();

        if (tiro[i].x==0) {
            tiro[i].x = xtiro+1;
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
            }
        }

    }
}

void zerar_tiro(int max_y){
    for (int i=0; i<MAXTIROS;i++){
        tiro[i].x=0;
    }
    for (int i=0; i<MAXTIROS;i++){
        tiro[i].y=max_y-1;
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
    int aux;
    aux=0;
    for (int i=0;i<INIMIGOS;i++){
        if (loc_inimigo[i].aparencia == ' ')
            aux++;
    }
    if (aux == INIMIGOS) {
        return 1;
    }
    else
        return 0;
}

int detectar_game_over(int max_y){
    if (loc_inimigo[0].y==max_y) {
        return 2;
    }
    else
        return 0;
}