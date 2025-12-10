/*
Faça um programa em C que leia um arquivo contendo código HTML e gere outro arquivo contendo apenas o texto, removendo todas as tags HTML.
O programa deve copiar somente os caracteres que estão fora de < >, ignorando tudo que estiver dentro das tags.
*/
#include <stdio.h>
#include <stdlib.h>

//Funcao para passar de um arquivo para o outro sem as tags HTML
void retirar_tags_html()
{
    FILE*origem,*destino;
    char caracter;
    int pegar=0;
    origem = fopen("arquivo.txt", "r");
    destino = fopen("novo_.txt", "w");
    if(origem!=NULL&&destino!=NULL)
    {
        caracter = fgetc(origem);
        while(caracter!=EOF)
        {
            if(caracter=='<')
            {
                pegar=1;
            }
            if(pegar==0&&caracter!='\0')
            {
                fputc(caracter,destino);
            }
            if(caracter=='>')
            {
                pegar=0;
            }
            caracter = fgetc(origem);
        }
        fclose(origem);
        fclose(destino);
    }
    else
    {
        printf("Erro no sistema");
    }
}

void main()
{
    retirar_tags_html();
}
