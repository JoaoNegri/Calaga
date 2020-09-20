//
// Created by joao on 14/09/2020.
//

#include "usuarios.h"
#include "pontuacao.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int entrar_jogo=0;

char userID[20];

char NewUserID[20];

typedef struct {

    char UserID[20];
    char Senha[20];
    int contador;
    float pontuacao;

} User_Template;

User_Template tabela_usuarios[7] ={

};

void mostrar_pontuacao();

static void cria_users1();

void validar_user(){

    char pwd[20];
    int  UserIDFind=1;
    int i;

    for(i=0;i<7&& UserIDFind;i++){

        if(strcmp(userID,tabela_usuarios[i].UserID)==0){

            UserIDFind=0;

        }

    }

    if(UserIDFind==0){

        i--;

        if(tabela_usuarios[i].contador<5){

            printf("Entre com a sua senha,%s\n",userID);
            scanf("%s",pwd);

            if(strcmp(pwd, tabela_usuarios[i].Senha)==0){

                printf("Senha correta\n");

                entrar_jogo=1;

            } else{

                printf("Senha Digitada incorretamente\n");

                tabela_usuarios[i].contador++;

            }


        } else{

            printf("Usuário bloqueado, entre em contato com um admin\n");

        }

    } else{

        char resposta;

        printf("Usuário não existe! Deseja criar um novo usuário?[s/n]\n");
        scanf("%s",&resposta);

        if(resposta=='s'){

            printf("Você será direcionado para página de criação de contas\n");

            system("clear");

            cria_users1();


        }else{

            printf("Obrigado por instalar o Calaga\n");

        }

    }

};


int sistema_usuario(){

    while(1){

        printf("--Bem vindo ao Calaga!!--\n");

        printf("Entre com seu nome de usuário\n");
        scanf("%s",userID);

        validar_user();
        if (entrar_jogo == 1)
            break;
    }

};

void cria_users1(){

    char Newpwd[20];
    int i;
    char j[20];
    int k;
    int tam;
    int x=0;

    for(i=0;i<9;i++){

        tam= strlen(tabela_usuarios[i].UserID);

        if(tam!=0){

            x=x+1;

        }



    };

    printf("--Criação de usuário--\n");

    printf("Entre com o nome do usuário que deseja criar\n");
    scanf("%s",tabela_usuarios[x].UserID);

    printf("Entre com a senha para, %s\n",tabela_usuarios[x].UserID);
    scanf("%s",tabela_usuarios[x].Senha);

    tabela_usuarios[x].pontuacao=0;
    tabela_usuarios[x].contador=0;

    printf("Você será direcionado para página inicial do game\n");

    system("clear");

    sistema_usuario();

};

void mostrar_pontuacao();
