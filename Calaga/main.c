#include <ncurses.h>
#include <unistd.h>

#include "jogo.h"
#include "usuarios.h"

void apagar_setas(int y,int x);
void menu_usuario(int menu_x,int menu_y);
void menu_admin(int menu_x,int menu_y);

int main(){
    int max_x, max_y;
    int menu_x,menu_y;


    int qual_menu;
    qual_menu = sistema_usuario();
    sleep (1);
    initscr();
    noecho();
    curs_set(FALSE);
    refresh();
    getmaxyx(stdscr,max_y,max_x);
    menu_x=max_x/2;
    menu_y=max_y/2;

    refresh();

    if (qual_menu == 0)
        menu_admin(menu_x,menu_y);
    else
        menu_usuario(menu_x,menu_y);
    refresh();

    endwin();

}

void apagar_setas(int y,int x){
    mvprintw(y + 1, x - 3, "  ");
    mvprintw(y + 2, x - 3, "  ");
    mvprintw(y + 3, x - 3, "  ");
    mvprintw(y + 4, x - 3, "  ");
}
void menu_usuario(int menu_x,int menu_y) {
    int opcao, n = 1;
    int ponto_atual;
    int sair = 0;
    int pontos;
    while (sair == 0) {
        mvprintw(menu_y, menu_x, "MENU_USUARIO");
        mvprintw(menu_y + 1, menu_x, "Jogar");
        mvprintw(menu_y + 2, menu_x, "Pontuacao");
        mvprintw(menu_y + 3, menu_x, "Alterar sua Senha");
        mvprintw(menu_y + 4, menu_x, "Sair");

        mvprintw(menu_y + n, menu_x - 3, "->");
        opcao = getch();

        while (opcao != 10) {

            if (opcao == 65) {
                n--;
                if (n < 1)
                    n = 4;
                else if (n > 4)
                    n = 1;
                apagar_setas(menu_y, menu_x);
                mvprintw(menu_y + n, menu_x - 3, "->");
            }
            if (opcao == 66) {
                n++;
                if (n < 1)
                    n = 4;
                else if (n > 4)
                    n = 1;
                apagar_setas(menu_y, menu_x);
                mvprintw(menu_y + n, menu_x - 3, "->");
            }

            opcao = getch();

        }
        switch (n) {
            case 1:
                pontos = jogoo();
                salvar_pontuacao(pontos);
                break;
            case 2:
                ponto_atual = mostrar_pontuacao();
                clear();
                mvprintw(menu_y, menu_x-15, "Sua pontuacao maxia e de %d pontos", ponto_atual);
                refresh();
                sleep(2);
                break;
            case 3:
                //mvprintw(5, 5, "trocando senha");
                endwin();
                alterar_senha();
                initscr();
                noecho();
                curs_set(FALSE);
                refresh();
                sleep(1);
                break;
            case 4:
                sair = 1;
                endwin();
        }
        clear();
    }
}
void menu_admin(int menu_x, int menu_y) {
    int opcao, n = 1;
    int sair = 0;

    while (sair == 0) {
        mvprintw(menu_y, menu_x, "MENU_ADMIN");
        mvprintw(menu_y + 1, menu_x, "Desbloquear Usuario");
        mvprintw(menu_y + 2, menu_x, "Alterar Senha do Usuario");
        mvprintw(menu_y + 3, menu_x, "Alterar sua Senha");
        mvprintw(menu_y + 4, menu_x, "Sair");

        mvprintw(menu_y + n, menu_x - 3, "->");
        opcao = getch();

        while (opcao != 10) {
            if (opcao == 65) {
                n--;
                if (n < 1)
                    n = 4;
                else if (n > 4)
                    n = 1;
                apagar_setas(menu_y, menu_x);
                mvprintw(menu_y + n, menu_x - 3, "->");
            }
            if (opcao == 66) {
                n++;
                if (n < 1)
                    n = 4;
                else if (n > 4)
                    n = 1;
                apagar_setas(menu_y, menu_x);
                mvprintw(menu_y + n, menu_x - 3, "->");
            }
            opcao = getch();

        }
        switch (n) {
            case 1:
                mvprintw(1, 1, "Desbloqueando Usuario...");
                endwin();
                desbloquear_usuario();
                initscr();
                noecho();
                curs_set(FALSE);
                refresh();
                sleep(1);
                break;
            case 2:

                endwin();
                alterar_senha();
                initscr();
                noecho();
                curs_set(FALSE);
                refresh();
                sleep(1);
                break;
            case 3:
                mvprintw(5, 5, "trocando senha");
                //alterar_senha();
                refresh();
                sleep(1);
                break;
            case 4:
                sair = 1;
                endwin();
        }
        clear();
    }
}

