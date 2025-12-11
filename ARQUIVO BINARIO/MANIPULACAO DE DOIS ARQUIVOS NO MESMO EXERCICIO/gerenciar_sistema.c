#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "estruturas.h"
#include "manipulacao_arquivo_produtos.h"
#include "manipulacao_arquivo_vendas.h"
#include "interacao_usuario.h"

void main()
{
    int esc;
    float valor;
    do
    {
        esc = escolher_funcao();
        if(validar_arquivo_produto()==1|| esc == 1 || esc == 0)
        {
            if(validar_arquivo_vendas()==1 || (esc>=0 && esc<=9))
            {
                switch(esc)
                {
                case 1:
                    incluir_novo_produto();
                    break;
                case 2:
                    alterar_dados_produto();
                    break;
                case 3:
                    excluir_produto_sem_venda();
                    break;
                case 4:
                    pesquisar_produto();
                    break;
                case 5:
                    comprar_mais_quantidade();
                    break;
                case 6:
                    apresentar_todos_produtos();
                    break;
                case 7:
                    apresentar_balancete_todos_produtos();
                    break;
                case 8:
                    apresentar_todos_produtos_com_max_5();
                    break;
                case 9:
                    inclusao_de_vendas();
                    break;
                case 10:
                    apresentar_todas_estrutura_vendas();
                    break;
                case 11:
                    apresentar_todas_estrutura_vendas_de_dia_especifico();
                    break;
                case 12:
                    apresentar_quantidade_por_cada_produto();
                    break;
                case 13:
                    valor = retornar_total_arrecadado_mes();
                    printf("O TOTAL ARRECADADO = %.2f\n", valor);
                    break;
                }
            }
            else
                printf("O ARQUIVO DE VENDAS ESTA VAZIO, ESCOLHA A OPCAO 10 PARA INCLUIR UMA VENDA\n");
        }
        else
            printf("O ARQUIVO DE PRODUTOS ESTA VAZIO, ESCOLHA A OPCAO 1 PARA INCLUIR ALGO\n");
    }
    while(esc!=0);
}
