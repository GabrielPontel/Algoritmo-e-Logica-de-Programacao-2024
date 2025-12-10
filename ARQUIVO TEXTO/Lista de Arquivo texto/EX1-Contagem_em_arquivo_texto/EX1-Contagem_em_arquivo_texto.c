/*
Desenvolva um programa em linguagem C que leia um arquivo texto chamado "arquivo.txt" e apresente estatísticas sobre seu conteúdo. O programa deve implementar funções específicas para:
    - Contar quantas vezes um caractere desejado aparece no arquivo (ex.: espaço, quebra de linha, etc.).
    - Contar todos os caracteres do arquivo (incluindo letras, números, símbolos e espaços).
    - Contar quantos dígitos numéricos (0–9) existem no arquivo.
    - Contar quantas letras (A–Z, desconsiderando acentuação) existem no arquivo.
    - Calcular o número de linhas, a partir da quantidade de quebras de linha ‘\n’.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///Funcao para contar os caracteres desejados em um arquivo
int contar_caracteres_desejados(char caracter_desejado)
{
    FILE*arquivo;
    char caracter_do_arquivo;
    int cont=0;
    arquivo = fopen("arquivo.txt", "r");
    if(arquivo != NULL)
    {
        while(!feof(arquivo))
        {
            caracter_do_arquivo = fgetc(arquivo);
            if(caracter_desejado==caracter_do_arquivo)
                cont++;
        }
        fclose(arquivo);
    }
    else
    {
        printf("O arquivo nao foi encontrado!!\n");
    }
    return cont;
}

///Funcao para contar todos os caracteres em um arquivo
int contar_todos_caracteres()
{
    FILE*arquivo;
    char caracter_do_arquivo;
    int cont=0;
    arquivo = fopen("arquivo.txt", "r");
    if(arquivo != NULL)
    {
        while(!feof(arquivo))
        {
            caracter_do_arquivo = fgetc(arquivo);
            cont++;
        }
        fclose(arquivo);
    }
    else
    {
        printf("O arquivo nao foi encontrado!!\n");
    }
    return cont;
}

///Funcao para contar todos os numeros em um arquivo
int contar_numeros_arquivo()
{
    FILE*arquivo;
    char caracter_do_arquivo;
    int cont=0;
    arquivo = fopen("arquivo.txt", "r");
    if(arquivo != NULL)
    {
        while(!feof(arquivo))
        {
            caracter_do_arquivo = fgetc(arquivo);
            if(caracter_do_arquivo>='0'&&caracter_do_arquivo<='9')
            cont++;
        }
        fclose(arquivo);
    }
    else
    {
        printf("O arquivo nao foi encontrado!!\n");
    }
    return cont;
}

///Funcao para contar todas os letras em um arquivo
int contar_letras_arquivo()
{
    FILE*arquivo;
    char caracter_do_arquivo;
    int cont=0;
    arquivo = fopen("arquivo.txt", "r");
    if(arquivo != NULL)
    {
        while(!feof(arquivo))
        {
            caracter_do_arquivo = fgetc(arquivo);
            caracter_do_arquivo = toupper(caracter_do_arquivo);
            if(caracter_do_arquivo>='A'&&caracter_do_arquivo<='Z')
            cont++;
        }
        fclose(arquivo);
    }
    else
    {
        printf("O arquivo nao foi encontrado!!\n");
    }
    return cont;
}

void main()
{
    int quantidade;

    quantidade = contar_caracteres_desejados('\n')+1;
    printf("A quantidade de linhas desse arquivo e: %d\n", quantidade);
    quantidade = contar_caracteres_desejados(' ');
    printf("A quantidade de espacos em branco desse arquivo e: %d\n", quantidade);
    quantidade = contar_letras_arquivo();
    printf("A quantidade de letras desse arquivo e: %d\n", quantidade);
    quantidade = contar_numeros_arquivo();
    printf("A quantidade de numeros desse arquivo e: %d\n", quantidade);
    quantidade = contar_todos_caracteres();
    printf("A quantidade de caracteres desse arquivo e: %d\n", quantidade);
}


