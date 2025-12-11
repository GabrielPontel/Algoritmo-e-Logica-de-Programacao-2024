/*
Faça um programa em C que leia um arquivo contendo seletores CSS e identifique
cada seletor como classe, identificador ou elemento HTML.
Verificar:
    começa com . → classe
    começa com # → identificador
    caso contrário → elemento
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void separar_elementos_html()
{
    FILE*origem,*destino;
    int i;
    char texto[101],tipo[110],novo[101];
    origem = fopen("arquivo.txt","r");
    destino = fopen("novo.txt", "w");
    if(origem!=NULL && destino!=NULL)
    {
        while(!feof(origem))
        {
            fgets(texto,100,origem);
            if(texto[0]!=' ' && texto[0]!='}')
            {
                tipo[0]='\0';
                i=0;
                while(texto[i]!=' ')
                {
                    novo[i]=texto[i];
                    i++;
                }
                novo[i]='\0';
                if(novo[0]=='.')
                {
                    strcat(tipo,"classe --> ");
                    strcat(tipo,novo);
                }
                else if(novo[0]=='#')
                {
                    strcat(tipo,"identificador --> ");
                    strcat(tipo,novo);
                }
                else
                {
                    strcat(tipo,"elemento --> ");
                    strcat(tipo,novo);
                }
                fprintf(destino,"%s\n",tipo);
            }
        }
        fclose(origem);
        fclose(destino);
    }
    else
    {
        printf("Erro no sistema\n");
    }
}

void main()
{
    separar_elementos_html();
}
