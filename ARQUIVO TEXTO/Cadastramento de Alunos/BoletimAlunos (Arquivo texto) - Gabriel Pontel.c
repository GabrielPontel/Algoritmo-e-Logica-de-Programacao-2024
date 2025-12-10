/*
Implemente um sistema em linguagem C para gerenciar informações de alunos utilizando arquivos e vetores de estruturas.
O programa deve permitir:
 - Cadastrar alunos em um arquivo texto, registrando nome, prontuário, duas notas e frequência.
 - Importar os dados do arquivo para um vetor de estruturas.
 - Apresentar todos os alunos, mostrando nome, prontuário, notas, média e frequência.
 - Ordenar os alunos por nome (ordem alfabética) e apresentar o resultado.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

///� uma estrutura que contara com os dados de um aluno
typedef struct
{
    char nome[70];
    float nota1,nota2,freq;
    char prontuario[50];
} tp_aluno;

///Funcao para tirar o \n no final da string
void limpar_string(char string[])
{
    if(string[strlen(string)-1]=='\n')
        string[strlen(string)-1]='\0';
}

///Funcao para validar dados
float validar_dados(int tl)
{
    float nota;
    do
    {
        scanf("%f", &nota);
        if(nota>tl||nota<0)
            printf("RESPOSTA INVALIDA, DIGITE NOVAMENTE, DENTRE O INTERVALO DE 0 A %d\n", tl);
    }
    while(nota>tl||nota<0);
    return nota;
}

///Funcao na qual guardara os dados de um aluno
void gravar_arquivos()
{
    FILE*arquivo;
    tp_aluno aluno;
    char aux[10];
    arquivo = fopen("alunos.txt","a");
    printf("NOME ........................: ");
    fflush(stdin);
    fgets(aluno.nome,69,stdin);
    limpar_string(aluno.nome);
    while(strcmp(aluno.nome,"")!=0)
    {
        printf("PRONTUARIO ..................: ");
        fgets(aluno.prontuario,49,stdin);
        printf("NOTA 1 ......................: ");
        aluno.nota1=validar_dados(10);
        printf("NOTA 2 ......................: ");
        aluno.nota2=validar_dados(10);
        printf("FREQUENCIA ..................: ");
        aluno.freq = validar_dados(100);
        fputs(aluno.nome, arquivo);
        fprintf(arquivo,"\n%s", aluno.prontuario);
        fprintf(arquivo,"%6.2f %6.2f %7.2f\n",aluno.nota1,aluno.nota2,aluno.freq);

        printf("\nNOME ........................: ");
        fflush(stdin);
        fgets(aluno.nome,69,stdin);
        limpar_string(aluno.nome);
    }
    fclose(arquivo);
}

///Funcao para importar os dados dos arquivos
int importar_dados(tp_aluno alunos[])
{
    int tl=0;
    FILE*arquivo;
    arquivo = fopen("alunos.txt","r");
    if(arquivo!=NULL)
    {
        while(!feof(arquivo))
        {
            fgets(alunos[tl].nome,69,arquivo);
            limpar_string(alunos[tl].nome);
            fgets(alunos[tl].prontuario,49,arquivo);
            limpar_string(alunos[tl].prontuario);
            fscanf(arquivo,"%f %f %f\n",&alunos[tl].nota1,&alunos[tl].nota2,&alunos[tl].freq);
            tl++;
        }

    }
    else
    {
        printf("O arquivo desejado n�o foi encontrado\n");
    }
    fclose(arquivo);
    return tl;
}

///Funcao para apresentar os dados de um aluno
void apresentar_aluno(tp_aluno aluno)
{
    float media;
    media = (float)(aluno.nota1+aluno.nota2)/2;
    printf("NOME ........................: %s\n", aluno.nome);
    printf("PRONTUARIO ..................: %s\n", aluno.prontuario);
    printf("NOTA 1 ......................: %6.2f\n",aluno.nota1);
    printf("NOTA 2 ......................: %6.2f\n",aluno.nota2);
    printf("MEDIA .......................: %6.2f\n",media);
    printf("FREQUENCIA ..................: %6.2f\n\n", aluno.freq);
}

///Funcao para apresentar os dados de todos os alunos
void apresentar_todos_alunos(tp_aluno alunos[], int tl)
{
    int i;
    for(i=0; i<tl; i++)
    {
        apresentar_aluno(alunos[i]);
    }
}

///Funcao para validar a op��o de escolha do switch
char validar_opcao()
{
    char esc;
    do
    {
        printf("DIGITE SUA ESCOLHA:\nA - Apresentar os dados dos alunos\nB - Cadastrar mais alunos\nC - Ordenar por ordem alfabetica e apresenta-lo\n");
        scanf(" %c", &esc);
    }
    while(esc!='A'&&esc!='B'&&esc!='C');
    return esc;
}

///Funcao para ordenar o registro de acordo com o nome dos alunos
void ordenar_vetor(tp_aluno alunos[], int tl, tp_aluno ordenado[])
{
    char menor[70];
int pos_menor,j,i,aux,a=0;
    for(i=0; i<tl-1; i++)
    {
        strcpy(menor,alunos[i].nome);
        pos_menor=i;
        for(j=i;j<tl;j++)
        {
            if(strcmp(alunos[j].nome,menor)<0)
            {
                strcpy(menor,alunos[j].nome);
                pos_menor=j;
            }
        }
        for(j=pos_menor;j<tl;j++)
        {

        }
        strcpy(ordenado[a].nome,alunos[pos_menor].nome);
        strcpy(ordenado[a].prontuario,alunos[pos_menor].prontuario);
        ordenado[a].nota1 = alunos[pos_menor].nota1;
        ordenado[a].nota2 = alunos[pos_menor].nota2;
        ordenado[a].freq = alunos[pos_menor].freq;
         aux=i;
        i=pos_menor;
        pos_menor=aux;
        a++;
    }
}
void main()
{
    int tl;
    tp_aluno alunos[50],ordenado[50];

    switch(validar_opcao())
    {
    case 'A':
        tl = importar_dados(alunos);
        apresentar_todos_alunos(alunos,tl);
        break;
    case 'B':
        gravar_arquivos();
        break;
    case 'C':
        tl = importar_dados(alunos);
        ordenar_vetor(alunos,tl,ordenado);
        apresentar_todos_alunos(ordenado,tl);
        break;
    }
}
