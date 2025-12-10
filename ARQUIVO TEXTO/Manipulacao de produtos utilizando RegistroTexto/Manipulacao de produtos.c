/*
Desenvolva um programa em linguagem C para gerenciar um estoque de produtos utilizando vetores de estruturas e leitura de arquivo texto.
O arquivo “BancodeDados.txt” contém os dados dos produtos no seguinte formato:
Primeira linha: quantidade total de produtos

Para cada produto:
    Código
    Nome
    Departamento
    Preço
    Quantidade em estoque

O programa deve:

-> Importar os dados do arquivo
    Ler o arquivo e carregar os produtos em um vetor de estruturas.
-> Oferecer ao usuário um menu com as seguintes opções:
    Apresentar todos os produtos (nome, código, departamento, preço e quantidade).
    Pesquisar um produto pelo código e apresentar seus dados; caso não exista, mostrar mensagem.
    Mostrar o total de itens no estoque, somando todas as quantidades.
    Calcular o valor total em estoque, multiplicando quantidade × preço de cada produto.
    Listar todos os produtos pertencentes a um determinado departamento.
    O programa deve repetir o menu até que o usuário escolha a opção 0 – Sair.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    int cod,quant;
    char nome[50],departamento[50];
    float preco;
}tp_produto;

///Funcao para retirar os \n desnecessarios de uma string
void retirar_espacos(char string[])
{
    if(string[strlen(string)-1]=='\n')
    string[strlen(string)-1]='\0';
}

///Essa funcao esta importando os dados do arquivo Banco de Dados
///E trazendo-os para dentro do struct
void importar_dados(tp_produto produtos[], int *tl)
{
    int i;
    char aux[30];
    FILE *arquivo;
    arquivo = fopen("BancodeDados.txt", "r");

    if(arquivo!= NULL)
    {
        fgets(aux,30,arquivo);
        *tl = atoi(aux);
        for(i=0;i<*tl;i++)
        {
            fgets(aux,30,arquivo);
            produtos[i].cod = atoi(aux);
            fgets(produtos[i].nome,50,arquivo);
            retirar_espacos(produtos[i].nome);
            fgets(produtos[i].departamento,50,arquivo);
            retirar_espacos(produtos[i].departamento);
            fgets(aux,30,arquivo);
            produtos[i].preco = atof(aux);
            fgets(aux,30,arquivo);
            produtos[i].quant = atoi(aux);
        }
    }
    else
    {
        printf("Arquivo vazio\n");
    }
    fclose(arquivo);
}

///Funcao para apresentar o registro
void apresentar_registro(tp_produto produtos[], int tl)
{
    int i;
    for(i=0;i<tl;i++)
    {
        printf("Nome do Produto .........: %s\n", produtos[i].nome);
        printf("Codigo do Produto .......: %6d\n", produtos[i].cod);
        printf("Departamento ............: %s\n", produtos[i].departamento);
        printf("Preco do Produto ........: %9.2f\n", produtos[i].preco);
        printf("Quantidade em Estoque ...: %6d\n\n", produtos[i].quant);

    }
}

///Funcao que o usuario impunhara o codigo e apartir dai achara os dados desse produto caso haver
void apresentar_dados_apartir_cod(tp_produto produtos[], int tl)
{
    int i,codigo,indice=-1;
    printf("\n\nDigite o codigo do produto que deseja:\n");
    scanf("%d", &codigo);
    for(i=0;i<tl;i++)
    {
        if(codigo==produtos[i].cod)
        {
            indice = i;
            i=tl;
        }
    }
    if(indice!=-1)
    {
        printf("Nome do Produto .........: %s\n", produtos[indice].nome);
        printf("Codigo do Produto .......: %6d\n", produtos[indice].cod);
        printf("Departamento ............: %s\n", produtos[indice].departamento);
        printf("Preco do Produto ........: %9.2f\n", produtos[indice].preco);
        printf("Quantidade em Estoque ...: %6d\n\n", produtos[indice].quant);
    }
    else
    {
        printf("O codigo nao esta presente nos dados\n");
    }

}

///Funcao para somar a quantidade total dos produtos em estoque
int somar_produtos(tp_produto produtos[], int tl)
{
    int i,somar=0;
    for(i=0;i<tl;i++)
    {
        somar += produtos[i].quant;
    }
    return somar;
}
///funcao ira calcular o valor total a partir da multiplicacao do preco pela quantidade de cada produto
int calcular_valor_total(tp_produto produtos[], int tl)
{
    int i,somar=0;
    for(i=0;i<tl;i++)
    {
        somar+=(produtos[i].quant*produtos[i].preco);
    }
    return somar;
}

///Funcao para encontrar determinado produto apartir do departamento
void apresentar_produtos_apartir_departamento(tp_produto produtos[], int tl)
{
    int i;
    char escolhido[50];
    printf("Qual o departamento desejado:\n");
    fflush(stdin);
    fgets(escolhido,50,stdin);
    retirar_espacos(escolhido);
    printf("Os produtos que esse departamento oferece:\n");
    for(i=0;i<tl;i++)
    {
      if(strcmp(escolhido,produtos[i].departamento)==0)
        printf("-> %s\n", produtos[i].nome);
    }
}

///Funcao para validar a escolha do usuario na opcao desejada
int escolher_opcao()
{
    int opc;
    do
    {
      printf("0 SAIR\n1 Apresentar todos os produtos\n2 Pesquisar um produto pelo codigo e apresentar seus dados, caso o codigo nao exista apresentar uma mensagem\n3 Apresentar a quantidade total de produtos em estoque\n4 Apresentar o valor total em estoque (quantidade do produto multiplicado pelo valor do produto)\n5 Apresentar todos os produtos de um determinado departamento\n");
    scanf("%d", &opc);
    }while(opc<0||opc>5);
    return opc;
}
void main()
{
    tp_produto produtos[50];
    int tl,soma_quant,soma_valor,escolha;
    escolha = escolher_opcao();
    importar_dados(produtos,&tl);
do{
    switch(escolha)
    {
    case 1:
        apresentar_registro(produtos,tl);
        break;
     case 2:
        apresentar_dados_apartir_cod(produtos,tl);
        break;
     case 3:
        soma_quant = somar_produtos(produtos,tl);
    printf("\nA quantidade dos produtos = %d\n\n", soma_quant);
        break;
     case 4:
        soma_valor = calcular_valor_total(produtos,tl);
    printf("O valor total em estoque = %d\n\n", soma_valor);
        break;
     case 5:
        apresentar_produtos_apartir_departamento(produtos,tl);
        break;
    }
    escolha = escolher_opcao();
}while(escolha!=0);
}
