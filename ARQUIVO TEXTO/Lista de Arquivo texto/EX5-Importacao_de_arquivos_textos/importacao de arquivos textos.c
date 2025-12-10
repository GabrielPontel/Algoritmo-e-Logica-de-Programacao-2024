/*
Faça um programa em C que leia de um arquivo (dados_alunos.txt) os dados de vários alunos e suas disciplinas.

Para cada aluno, o arquivo contém:
    nome
    curso
    quantidade de disciplinas

Para cada disciplina:
    nome
    sigla
    nota1
    nota2
    frequência

O programa deve:
    - Importar todos os alunos do arquivo para um vetor de estruturas.
    - Armazenar também um vetor de disciplinas dentro de cada aluno.
    - Apresentar na tela todos os dados de todos os alunos e de cada disciplina cursada.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[50],sigla[15];
    float nota1,nota2,freq;
} tp_disciplina;

typedef struct
{
    char nome[50], curso[50];
    int disciplinas;
    tp_disciplina materias[10];
} tp_aluno;
///Funcao para retirar o \n de uma string
void limpar_string(char string[])
{
    if(string[strlen(string)-1]=='\n')
        string[strlen(string)-1]='\0';
}
///Funcao para importar os dados dos alunos;
int importar_dados_alunos(tp_aluno alunos[])
{
    int tl_alunos=0,i,j;
    char aux[11];
    FILE*arquivo;
    arquivo = fopen("dados_alunos.txt", "r");
    if(arquivo != NULL)
    {
        i=10;
        itoa(aux,i);
        printf("%s\n", i);
        fgets(aux,10,arquivo);
        tl_alunos = atoi(aux);
        for(i=0; i<tl_alunos; i++)
        {
            fgets(alunos[i].nome,49,arquivo);
            limpar_string(alunos[i].nome);
            fgets(alunos[i].curso,49,arquivo);
            limpar_string(alunos[i].curso);
            fscanf(arquivo,"%d\n", &alunos[i].disciplinas);
            for(j=0; j<alunos[i].disciplinas; j++)
            {
                fgets(alunos[i].materias[j].nome,49,arquivo);
                limpar_string(alunos[i].materias[j].nome);
                fscanf(arquivo,"%s %f %f %f\n", &alunos[i].materias[j].sigla,&alunos[i].materias[j].nota1,&alunos[i].materias[j].nota2,&alunos[i].materias[j].freq);
                limpar_string(alunos[i].materias[j].sigla);
            }
        }
        fclose(arquivo);
    }
    else
    {
        printf("Erro no sistema\n");
    }
    return tl_alunos;
}

///Funcao para apresentar todos os dados de um aluno
void apresentar_um_aluno(tp_aluno a)
{
    int i;
    printf("NOME ................................: %s\n", a.nome);
    printf("CURSO ...............................: %s\n", a.curso);
    printf("QUANTIDADE DE DISCIPLINAS ...........: %d\n", a.disciplinas);
    for(i=0; i<a.disciplinas; i++)
    {
        printf("\n");
        printf("DISCIPLINA ..........................: %s\n", a.materias[i].nome);
        printf("SIGLA ...............................: %s\n", a.materias[i].sigla);
        printf("NOTA 1 ..............................: %.2f\n", a.materias[i].nota1);
        printf("NOTA 2 ..............................: %.2f\n", a.materias[i].nota2);
        printf("FREQUENCIA ..........................: %.2f\n", a.materias[i].freq);

    }
}

///Funcao para apresentar os dados de todos os alunos
void apresentar_alunos(tp_aluno alunos[], int tl)
{
    int i;
    for(i=0; i<tl; i++)
    {
        apresentar_um_aluno(alunos[i]);
        printf("\n\n");
    }
}

void main()
{
    tp_aluno alunos[100];
    int tl;
    tl= importar_dados_alunos(alunos);
    apresentar_alunos(alunos, tl);
}
