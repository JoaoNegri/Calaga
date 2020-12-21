
//
// Created by Kelvin on 14/09/2020.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int entrar_jogo=0;

char userID[20];

char ADUser[20];

char NewUserID[20];

int tipo_usuario;

typedef struct {

    char UserID[20];
    char Senha[20];
    int contador;
    float pontuacao;

} User_Template;

User_Template tabela_usuarios[7] ={

};

void restaurar_tabela();

void salvar_arquivo();

static void cria_users1();

//static void alterar_senha();

//static void desbloquear_usuario();

int validar_user(){

    char pwd[20];
    int  UserIDFind=1;
    int i;

    restaurar_tabela();
    for(i=0;i<7&& UserIDFind;i++){

        if(strcmp(userID,tabela_usuarios[i].UserID)==0){

            UserIDFind=0;

        }

    }

    if(UserIDFind==0){

        i--;

        while(tabela_usuarios[i].contador<3){

            printf("Entre com a sua senha,%s\n",userID);
            scanf("%s",pwd);

            if(strcmp(pwd, tabela_usuarios[i].Senha)==0){

                printf("Senha correta\n");

                entrar_jogo=1;

                if (strstr(userID, "admin") != NULL) {

                    system("clear");

                    printf("Admin logado\n");
                    tipo_usuario=0;
                    return 0;

                }else{
                    system("clear");

                    printf("Usuário logado\n");
                    tipo_usuario=1;
                    return 0;

                }
            } else{

                printf("Senha Digitada incorretamente\n");

                tabela_usuarios[i].contador++;

            }


        } if (tabela_usuarios[i].contador ==3){

            printf("Usuário bloqueado, entre em contato com um admin\n");
            salvar_arquivo();
            return 0;

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

}

int sistema_usuario(){

    while(1){

        printf("--Bem vindo ao Calaga!!--\n");

        printf("Entre com seu nome de usuário\n");
        scanf("%s",userID);

        validar_user();

        if (entrar_jogo == 1)
            break;
    }
    return tipo_usuario;
}

void cria_users1(){

    int i;
    int tam;
    int x=0;
    int codigo_user;


    for(i=0;i<7;i++){

        tam= strlen(tabela_usuarios[i].UserID);

        if(tam!=1){

            x=x+1;

        }



    }

    printf("--Criação de usuário--\n");

    printf("Entre com o nome do usuário que deseja criar\n");
    scanf("%s",tabela_usuarios[x].UserID);


    printf("Entre com a senha para, %s\n",tabela_usuarios[x].UserID);
    scanf("%s",tabela_usuarios[x].Senha);

    if (strstr(userID, "admin") != NULL) {

        printf("Insira o código de validação de criação de admins:\n");
        scanf("%d",&codigo_user);

        if( codigo_user == 5){

            printf("Código aceito , usuário criado\n");
            tabela_usuarios[x].pontuacao=0;
            tabela_usuarios[x].contador=0;


        }else {
            //printf("aaaaaa\n");
            printf("Código incorreto, voltando para o menu\n");
            strcpy(tabela_usuarios[x].UserID, "A");
            strcpy(tabela_usuarios[x].Senha, "A" );
        }

    }else{

        tabela_usuarios[x].pontuacao=0;
        tabela_usuarios[x].contador=0;

    }


    printf("Você será direcionado para página inicial do game\n");


    salvar_arquivo();
    sistema_usuario();

}

void alterar_senha(){

    int  UserIDFind=1;
    int k;

    if (strstr(userID, "admin") != NULL) {

        printf("Entre com o nome do usuário que deseja mudar a senha:\n");
        scanf("%s",ADUser);


        for(k=0;k<7&& UserIDFind;k++){

            if(strcmp(ADUser,tabela_usuarios[k].UserID)==0){

                UserIDFind=0;

            }

            if(UserIDFind==0){

                printf("Entre com a nova senha do usuário:\n");
                scanf("%s",tabela_usuarios[k].Senha);
                salvar_arquivo();
                system("clear");

            }

        }

    }else{

        printf("Alterando senha de %s\n",userID);

        for(k=0;k<7&& UserIDFind;k++){

            if(strcmp(userID,tabela_usuarios[k].UserID)==0){

                UserIDFind=0;

            }

            if(UserIDFind==0){

                printf("Entre com sua nova senha,%s\n",userID);
                scanf("%s",tabela_usuarios[k].Senha);
                salvar_arquivo();
                system("clear");

            }

        }

    }

}

void desbloquear_usuario(){

    int  UserIDFind=1;
    int k;

    printf("Entre com o nome do usuário que deseja desbloquear:\n");
    scanf("%s",ADUser);


    for(k=0;k<7&& UserIDFind;k++){

        if(strcmp(ADUser,tabela_usuarios[k].UserID)==0){

            UserIDFind=0;

        }

        if(UserIDFind==0){

            tabela_usuarios[k].contador=0;
            salvar_arquivo();
            printf("Usuário desbloquado\n");

            system("clear");

        }

    }

}

void salvar_pontuacao(int pontos) {
    int UserIDFind = 1;
    for(int k=0;k<7&& UserIDFind;k++){

        if(strcmp(userID,tabela_usuarios[k].UserID)==0){

            UserIDFind=0;

        }

        if (UserIDFind == 0) {
            if (tabela_usuarios[k].pontuacao<pontos) {
                tabela_usuarios[k].pontuacao = pontos;
                salvar_arquivo();
            }
        }
    }
}

int mostrar_pontuacao() {

    for (int k = 0; k < 7 ; k++) {

        if (strcmp(userID, tabela_usuarios[k].UserID) == 0) {

            return tabela_usuarios[k].pontuacao;

        }

    }
}
void salvar_arquivo(){
    FILE *ptr;
    int i;

    if ((ptr = fopen("Usuarios.dat", "w+"))== NULL) {
        printf("Erro na abertura de arquivo\n");
        exit(-1);
    }
    for (i=0;i<7;i++)
        fprintf (ptr, "%s:%s:%d:%f\n", tabela_usuarios[i].UserID, tabela_usuarios[i].Senha, tabela_usuarios[i].contador, tabela_usuarios[i].pontuacao);
    fclose(ptr);
}

void restaurar_tabela(){

    FILE *ptr;
    int ret=0,i=0;

    if ((ptr = fopen("Usuarios.dat", "r"))== NULL) {
        printf("Erro na abertura de arquivo\n");
        exit(-1);
    }
    while  (ret != EOF) {
        ret = fscanf (ptr, " %[^:]:%[^:]:%d:%f", tabela_usuarios[i].UserID, tabela_usuarios[i].Senha, &tabela_usuarios[i].contador, &tabela_usuarios[i].pontuacao);
        i++;
    }
    fclose(ptr);
}