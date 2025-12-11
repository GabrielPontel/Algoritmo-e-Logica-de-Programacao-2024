//Gabriel Pontel de Mori e Tobias Rafael

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "estrutura_leilao.h"
#include "arquivo_binario.h"
#include "interagindo_usu_leilao.h"
void main()
{
    int op, validar;
    do
    {
        op = validar_escolha_do_principal();
        if(validar_se_tem_algo_arquivo() == 1 || op == 1)
        {
            switch(op)
            {
            case 1:
                incluir_novo_produto();
                break;
            case 2:
                alterar_dados_de_um_produto();
                break;
            case 3:
                excluir_produtos_logicamente();
                break;
            case 4:
                recuperar_produtos_logicamente();
                break;
            case 5:
                pesquisar_produto_apartir_nr();
                break;
            case 6:
                excluir_fisicamente_todos_produtos_excluidos_logicamente();
                break;
            case 7:
                apresentar_todos_produtos();
                break;
            case 8:
                incluir_novo_lance_produto();
                break;
            case 9:
                finalizar_produto();
                break;
            case 10:
                relatorio_leiloes_abertos();
                break;
            case 11:
                relatorio_leiloes_finalizados();
                break;
            }
        }
        else
            {
                printf("O ARQUIVO ESTA VAZIO.. (ESCOLHA A OPCAO 1)..\n");
            }
            pausa_limpar();
    }
    while(op != 0);
}
