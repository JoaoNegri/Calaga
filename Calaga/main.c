#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include "jogo.h"
#include "usuarios.h"

void apagar_setas(int y,int x);

int main(int argc, char *argv[]){
    int max_x, max_y;
    int menu_x,menu_y;
    int opcao,n=1;
    int sair=0;
    //sistema_usuario();
    initscr();
    noecho();
    curs_set(FALSE);
    refresh();
    getmaxyx(stdscr,max_y,max_x);
    menu_x=max_x/2;
    menu_y=max_y/2;
    //jogoo(argc, *argv);
    while (sair ==0) {
        mvprintw(menu_y, menu_x, "menu");
        mvprintw(menu_y + 1, menu_x, "Jogar");
        mvprintw(menu_y + 2, menu_x, "Pontuacao");
        mvprintw(menu_y + 3, menu_x, "Sair");

        mvprintw(menu_y + n, menu_x - 3, "->");
        opcao = getch();
        //mvprintw(menu_y + n, menu_x - 3, "%d",opcao);
        while (opcao != 10) {

            if (opcao == 65) {
                n--;
                if (n < 1)
                    n = 3;
                else if (n > 3)
                    n = 1;
                apagar_setas(menu_y, menu_x);
                mvprintw(menu_y + n, menu_x - 3, "->");
            }
            if (opcao == 66) {
                n++;
                if (n < 1)
                    n = 3;
                else if (n > 3)
                    n = 1;
                apagar_setas(menu_y, menu_x);
                mvprintw(menu_y + n, menu_x - 3, "->");
            }

            opcao = getch();

        }
        switch (n) {
            case 1:
                jogoo(argc, argv);
                break;
            case 2:
                //verificar_pontuacao;
                break;
            case 3:
                sair =1;
                endwin();
        }
        clear();
    }
    refresh();
    sleep(5);
    endwin();

}

void apagar_setas(int y,int x){
    mvprintw(y + 1, x - 3, "  ");
    mvprintw(y + 2, x - 3, "  ");
    mvprintw(y + 3, x - 3, "  ");
}