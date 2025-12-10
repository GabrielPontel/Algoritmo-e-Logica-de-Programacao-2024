/*
Faça um programa em C que leia um arquivo no formato do arquivo /etc/passwd do Linux (no caso, passwd-exerc3.txt).

Cada linha contém informações separadas por : sobre um usuário, na seguinte ordem:
    nome do usuário
    senha criptografada
    UID
    GID
    nome completo
    diretório inicial
    shell

O programa deve:
    Ler cada linha do arquivo e separar os campos usando :
    Armazenar os valores em uma estrutura (tp_linux)
    Guardar cada registro em um vetor
No final, apresentar os dados de todos os usuários lidos.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char nome_usu[100], senha[100], nome_completo[100], diretorio[100], shell[100];
    char num_usu[100], num_grupo[100];
} tp_linux;

/// Funcao para importar os dados
int importar_dados(tp_linux sistemas[])
{
    int tl = 0, i;
    char car;
    FILE *arquivo;
    arquivo = fopen("passwd-exerc3.txt", "r");
    if (arquivo != NULL)
    {
        car = fgetc(arquivo);
        while (car != EOF)
        {
            printf("a");
            car = fgetc(arquivo);

            sistemas[tl].senha[0] = '\0';
            sistemas[tl].nome_completo[0] = '\0';
            sistemas[tl].diretorio[0] = '\0';
            sistemas[tl].shell[0] = '\0';
            sistemas[tl].num_usu[0] = '\0';
            sistemas[tl].num_grupo[0] = '\0';

            while (car != ':')
            {
               strcat(sistemas[tl].nome_usu,car);
                car = fgetc(arquivo);
            }
            strcat(sistemas[tl].nome_usu,"\0");
            for(i=0;i<5;i++)
                printf("%c", sistemas[tl].nome_usu);
            car = fgetc(arquivo);
            while (car != ':')
            {
                strcat(sistemas[tl].senha,car);
                car = fgetc(arquivo);
            }
            strcat(sistemas[tl].senha,"\0");
            car = fgetc(arquivo);
            while (car != ':')
            {
                strcat(sistemas[tl].num_usu,car);
                car = fgetc(arquivo);
            }
            strcat(sistemas[tl].num_usu,"\0");
            car = fgetc(arquivo);
            while (car != ':')
            {
                strcat(sistemas[tl].num_grupo,car);
                car = fgetc(arquivo);
            }
            strcat(sistemas[tl].num_grupo,"\0");
            car = fgetc(arquivo);
            while (car != ':')
            {
                strcat(sistemas[tl].nome_completo,car);
                car = fgetc(arquivo);
            }
            strcat(sistemas[tl].nome_completo,"\0");
            car = fgetc(arquivo);
            while (car != ':')
            {
                strcat(sistemas[tl].diretorio,car);
                car = fgetc(arquivo);
            }
            strcat(sistemas[tl].diretorio,car);
            car = fgetc(arquivo);
            while (car != '\n')
            {
                strcat(sistemas[tl].shell,car);
                car = fgetc(arquivo);
            }
            strcat(sistemas[tl].shell,"\0");
            fscanf(arquivo,"\0%c", &car);
            tl++;
            }
            fclose(arquivo);
        }
        else
        {
            printf("Erro no sistema\n");
        }
        return tl;
    }

    void apresentar_dados(tp_linux sistemas[], int tl)
    {
        int i;
        for(i=0; i<tl; i++)
        {
            printf("NOME DO USUARIO .........................: %s", sistemas[i].nome_usu);
            printf("SENHA CRIPTOGRAFADA .....................: %s", sistemas[i].senha);
            printf("NUMERO DO ID DO USUARIO (UID) ...........: %s", sistemas[i].num_usu);
            printf("NUMERO DO ID DO GRUPO DO USUARIO (GID)...: %s", sistemas[i].num_grupo);
            printf("DIRETORIO INICIAL DO USUARIO ............: %s", sistemas[i].diretorio);
            printf("SHELL DO LOGIN ..........................: %s", sistemas[i].shell);
        }
    }

    int main()
    {
        tp_linux sistemas[100];
        int tl;
        tl = importar_dados(sistemas);
        apresentar_dados(sistemas,tl);
        return 0;
    }
