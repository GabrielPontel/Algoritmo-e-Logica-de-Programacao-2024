//função que ira validar o nr de acordo com o arquivo
int validar_nr_inexistente()
{
    int nr, validar;
    do
    {
        printf("DIGITE O NR..: ");
        scanf("%d", &nr);
        validar = validar_nr_binario(nr);
        if(nr < 0 || validar == 1)
        {
            printf("NR INVALIDO...\n");
        }
    }
    while(nr < 0 || validar == 1);
    return nr;
}

//a funcao remove o \n do final da string
void limpar_string(char string[])
{
    if(string[strlen(string)-1] == '\n')
        string[strlen(string)-1] = '\0';
}

//funcao para validar valor inicial de um produto
float validar_valor_inicial_de_um_produto()
{
    float valor;
    do
    {
        printf("DIGITE UM VALOR INICIAL..: ");
        scanf("%f", &valor);
        if(valor < 0 )
        {
            printf("DIGITE UM VALOR POSTIVO.. \n");
        }
    }
    while(valor < 0);
    return valor;
}

// a função preenche os dados de um produto
tp_leilao ler_dados_de_um_produto()
{
    tp_leilao produto;
    produto.nr = validar_nr_inexistente();
    fflush(stdin);
    printf("DIGITE O NOME DO PRODUTO..: ");
    fgets(produto.produto,29,stdin);
    limpar_string(produto.produto);
    produto.valor = validar_valor_inicial_de_um_produto();
    produto.lances = 0;
    produto.sit = 'A';
    produto.nome[0] = '\0';
    produto.telefone[0] = '\0';
    strcat(produto.nome," ");
    strcat(produto.telefone," ");
    produto.status = 1;
    return produto;
}

//funcao para validar se o usuario quer sim ou nao
char validar_S_ou_N()
{
    char op;
    do
    {
        scanf(" %c", &op);
        if(op != 'S' && op != 's' && op != 'N' && op != 'n')
            printf("DIGITE APENAS S OU N..\n");
    }
    while(op != 'S' && op != 's' && op != 'N' && op != 'n');
    return op;
}

//interface para o usuario continuar a incluir novos produtos
void incluir_novo_produto()
{
    char op='S';
    tp_leilao produto;
    printf("---FUNCAO DE INCLUSAO DE PRODUTOS---\n");
    do
    {
        if(op == 'S' || op == 's')
        {
            produto = ler_dados_de_um_produto();
            incluir_novo_produto_no_arquivo(produto);
        }
        printf("DIGITE S PARA INCLUIR OU N PARA ENCERRAR..: ");
        op = validar_S_ou_N();
    }
    while(op == 'S' || op == 's');
}

//funcao para apresentar uma linha com dados de uma struct
void apresentar_linha(tp_leilao produto)
{
    printf("%0.6d %-30s %-7.2f %0.6d %c   %-30s %-20s\n",
           produto.nr, produto.produto, produto.valor, produto.lances, produto.sit, produto.nome, produto.telefone);
}

//funcao para apresentar o cabecalho da tabela
void apresentar_cabecalho()
{
    printf("%-6s %-30s %-6s  %-6s %-3s %-30s %-20s\n", "NR", "PRODUTO", "VALOR", "LANCES", "SIT", "NOME", "TELEFONE");
}

//apresentar todos os dados de todos os produtos
void apresentar_todos_produtos()
{
    int i, tl;
    tp_leilao produto;
    tl = retornar_qtd_struct();
    apresentar_cabecalho();
    for(i=0; i<tl; i++)
    {
        produto = retornar_estrutura_apartir_pos(i);
        if(produto.status==1)
            apresentar_linha(produto);
    }
}

//Funcao para o usuario dgitar os novos dados de seu produto
tp_leilao ler_dados_de_um_alterado(tp_leilao produto)
{
    printf("DIGITE O NOVO NOME DO PRODUTO ...: ");
    fflush(stdin);
    fgets(produto.produto,39,stdin);
    limpar_string(produto.produto);
    produto.valor = validar_valor_inicial_de_um_produto();
    return produto;
}

//Funcao para alterar o nome e o valor de um produto
void alterar_dados_de_um_produto()
{
    int pos,nr_desejado;
    tp_leilao produto;

    printf("---FUNCAO DE ALTERACAO DE DADOS---\n");
    printf("DIGITE O NR DESEJADO: \n");
    scanf("%d", &nr_desejado);
    pos = retornar_posicao_apartir_nr(nr_desejado);
    if(pos!=-1)
    {
        produto = retornar_estrutura_apartir_pos(pos);
        if(produto.status==1)
        {
            if(produto.sit == 'A')
            {
                apresentar_produto_unicamente(produto);
                produto = ler_dados_de_um_alterado(produto);
                sobreescrever_arquivo_apartir_pos(produto,pos);
            }
            else
                printf("PRODUTO JA FINALIZADO..\n");
        }
        else
            printf("PRODUTO EXCLUIDO, RECUPERE ELE PARA MODIFICAR DADOS\n");
    }
    else
        printf("NAO CONTEM O PRODUTO NO BANCO DE DADOS\n");
}

//Funcao na qual vai excluir os produtos logicamente
void excluir_produtos_logicamente()
{
    int nr_desejado,pos;
    tp_leilao produto;

    printf("---FUNCAO DE EXCLUSAO DE PRODUTO---\n");
    printf("DIGITE O NR DESEJADO: \n");
    scanf("%d", &nr_desejado);
    pos = retornar_posicao_apartir_nr(nr_desejado);
    if(pos!=-1)
    {
        produto = retornar_estrutura_apartir_pos(pos);
        if(produto.status==1)
        {
            produto.status=0;
            sobreescrever_arquivo_apartir_pos(produto,pos);
        }
        else
            printf("ESSE PRODUTO JA FOI EXCLUIDO\n");
    }

    else
        printf("NAO CONTEM O PRODUTO NO BANCO DE DADOS\n");
}

//Funcao na qual vai recuperar os produtos logicamente
void recuperar_produtos_logicamente()
{
    int nr_desejado,pos;
    tp_leilao produto;

    printf("---FUNCAO DE RECUPERACAO DE PRODUTO---\n");
    printf("DIGITE O NR DESEJADO: \n");
    scanf("%d", &nr_desejado);
    pos = retornar_posicao_apartir_nr(nr_desejado);
    if(pos!=-1)
    {
        produto = retornar_estrutura_apartir_pos(pos);
        if(produto.status==0)
        {
            produto.status=1;
            sobreescrever_arquivo_apartir_pos(produto,pos);
        }
        else
            printf("PRODUTO JA ERA ATIVO\n");
    }
    else
        printf("NAO CONTEM O PRODUTO NO BANCO DE DADOS\n");
}

//Funcao que vai apresentar um produto em especifico
void apresentar_produto_unicamente(tp_leilao produto)
{
    printf("NUMERO : %0.6d\n", produto.nr);
    printf("PRODUTO : %-50s\n", produto.produto);
    printf("VALOR : %6.2f\n", produto.valor);
    printf("LANCES : %0.6d\n", produto.lances);
    printf("SITUACAO : %c\n", produto.sit);
    printf("NOME: %-50s\n", produto.nome);
    printf("TELEFONE: %-50s\n\n", produto.telefone);

}

//Funcao vai basicamente apresentaum produto apartir do seu nr
void pesquisar_produto_apartir_nr()
{
    int nr_desejado,pos;
    tp_leilao produto;

    printf("---FUNCAO APRESENTAR PRODUTO---\n");
    printf("DIGITE O NR DESEJADO: \n");
    scanf("%d", &nr_desejado);
    pos = retornar_posicao_apartir_nr(nr_desejado);
    if(pos!=-1)
    {
        produto = retornar_estrutura_apartir_pos(pos);
        if(produto.status==1)
        {
            apresentar_produto_unicamente(produto);
        }
        else
            printf("PRODUTO EXCLUIDO LOGICAMENTE, RECUPERE ELE PARA APRESENTA-LO\n");
    }
    else
        printf("NAO CONTEM O PRODUTO NO BANCO DE DADOS\n");
}

//verifica se o telefone for valido possui 11 numeros
void validar_numero_telefone(char telefone[])
{
    int val;
    tp_leilao produto;
    do
    {
        printf("DIGITE O NUMERO DE TELEFONE..: \n");
        fflush(stdin);
        fgets(telefone,19,stdin);
        limpar_string(telefone);
        val = validar_quantidade_digitos(telefone);
        if(val!=1)
            printf("NUMERO INVALIDO DIGITE NOVAMENTE.. \n");
    }
    while(val != 1);
    quebrar_numero_telefone(telefone);
}

// essa função formata o numero
void quebrar_numero_telefone(char telefone[])
{
    int i=0,j=0;
    char auxiliar[20];
    while(telefone[i]!='\0')
    {
        if(telefone[i]>='0'&&telefone[i]<='9')
        {
            auxiliar[j]=telefone[i];
            j++;
        }
        i++;
    }

    i=12;
    while(i > 2)
    {
        auxiliar[i] = auxiliar[i-1];
        i--;
    }
    auxiliar[2] = ' ';
    i=13;
    while(i > 8)
    {
        auxiliar[i] = auxiliar[i-1];
        i--;
    }
    auxiliar[8] = '-';
    auxiliar[14] = '\0';
    strcpy(telefone,auxiliar);
}

//Funcao para validar as opcoes que o usuario contem
int validar_escolha_do_principal()
{
    int opcao;
    do
    {
        printf("==========================MENU DE ESCOLHAS==========================\n");
        printf("DIGITE A OPCAO DESEJADA\n");
        printf("0 - SAIR\n");
        printf("1 - INCLUIR NOVOS PRODUTOS\n");
        printf("2 - ALTERAR DADOS DE UM PRODUTO\n");
        printf("3 - EXCLUIR LOGICAMENTE UM PRODUTO\n");
        printf("4 - RECUPERAR UM PRODUTO\n");
        printf("5 - PESQUISAR UM PRODUTO\n");
        printf("6 - EXCLUSAO FISICA DE TODOS PRODUTOS EXCLUIDOS LOGICAMENTE\n");
        printf("7 - APRESENTAR TODOS OS PRODUTOS DO LEILAO\n");
        printf("8 - INCLUIR NOVO LANCE\n");
        printf("9 - FINALIZAR LEILAO\n");
        printf("10 - APRESENTAR LISTAGEM DE LEILOES EM ABERTO\n");
        printf("11 - APRESENTAR LISTAGEM DE LEILOES FECHADOS E VALORES\n");
        printf("====================================================================\n");
        scanf("%d", &opcao);
        if(opcao<0||opcao>11)
            printf("DIGITE UMA OPCAO VALIDA\n");
    }
    while(opcao<0||opcao>11);
    return opcao;
}

//Funcao que finalizara um produto do leilao
void finalizar_produto()
{
    int pos,nr_desejado;
    char op;
    tp_leilao produto;
    printf("-----FINALIZACAO DE UM PRODUTO DO LEILAO-----\n");
    printf("DIGITE O NR DESEJADO: \n");
    scanf("%d", &nr_desejado);
    pos = retornar_posicao_apartir_nr(nr_desejado);
    if(pos!=-1)
    {
        produto = retornar_estrutura_apartir_pos(pos);
        if(produto.status==1)
        {
            if(produto.sit == 'A')
            {
                apresentar_produto_unicamente(produto);
                printf("DIGITE S PARA CONFIRMAR EXCLUSAO E N PARA DESISTIR\n");
                op = validar_S_ou_N();
                if(op=='S'|| op=='s')
                {
                    produto.sit='F';
                    sobreescrever_arquivo_apartir_pos(produto,pos);
                }
            }
            else
                printf("O PRODUTO JA ESTAVA FINALIZADO\n");
        }
        else
        {
            printf("PRODUTO EXCLUIDO LOGICAMENTE, NAO PODE SER FECHADO\n");
        }
    }
    else
        printf("NAO CONTEM ESSE PRODUTO NO BANCO DE DADOS\n");

}

//Funcao para validar se o telefone apresentar 11 digitos
//retornando 1 caso ele tiver 11 digitos
int validar_quantidade_digitos(char telefone[])
{
    int val=0,cont=0,i=0;
    while(telefone[i]!='\0')
    {
        if(telefone[i]>='0'&&telefone[i]<='9')
            cont++;
        i++;
    }
    if(cont == 11)
    {
        val=1;
    }
    return val;
}

//funcao para apresentar a listagem de leiloes que estao abertos
void apresentar_produtos_sit(char aux)
{
    int tl, i;
    tp_leilao produto;
    tl = retornar_qtd_struct();
    for(i=0; i<tl; i++)
    {
        produto = retornar_estrutura_apartir_pos(i);
        if(produto.status == 1 && produto.sit == aux)
        {
            apresentar_linha(produto);
        }
    }
}

//funcao que retorna a quantidade total de lances do leilao
int retornar_quantidade_total_de_lances()
{
    int cont = 0, tl, i;
    tp_leilao produto;
    tl = retornar_qtd_struct();
    for(i=0; i<tl; i++)
    {
        produto = retornar_estrutura_apartir_pos(i);
        if(produto.status == 1 && produto.sit == 'A')
        {
            cont += produto.lances;
        }
    }
    return cont;
}

//funcao que retorna a quantidade de leiloes ativos
int retornar_quantidade_de_leiloes_sit(char aux)
{
    int cont = 0, tl, i;
    tp_leilao produto;
    tl= retornar_qtd_struct();
    for(i=0; i<tl; i++)
    {
        produto = retornar_estrutura_apartir_pos(i);
        if(produto.status == 1)
        {
            if(produto.sit == aux)
            {
                cont ++;
            }
        }
    }
    return cont;
}

//apresenta o relatorio total de leiloes ativos
void relatorio_leiloes_abertos()
{
    int lances, ativos;
    apresentar_cabecalho();
    apresentar_produtos_sit('A');
    lances = retornar_quantidade_total_de_lances();
    ativos = retornar_quantidade_de_leiloes_sit('A');
    printf("A QUANTIDADE TOTAL DE LEILOES ATIVOS SAO %d E A QUANTIDADE TOTAL DE LANCES E DE %d\n", ativos, lances);
}

//funcao para somar o total de dinheiro arrecado
float somar_total_arreacado()
{
    float cont = 0;
    int tl, i;
    tp_leilao produto;
    tl = retornar_qtd_struct();
    for(i=0; i<tl; i++)
    {
        produto = retornar_estrutura_apartir_pos(i);
        if(produto.status == 1 && produto.sit == 'F')
        {
            cont += produto.valor;
        }
    }
    return cont;
}

//funcao para relatorio sobre produtos finalizados
void relatorio_leiloes_finalizados()
{
    float valor_arrecadado;
    int total;
    apresentar_cabecalho();
    apresentar_produtos_sit('F');
    valor_arrecadado = somar_total_arreacado();
    total = retornar_quantidade_de_leiloes_sit('F');
    printf("O TOTAL ARRECADO NOS LEILOES E DE..: %.2f E O TOTAL DE LEILOES FECHADOS E DE..: %d\n\n", valor_arrecadado, total);
}

//Funcao para validar atual do produto e o do lance
float validar_lance(float valor_atual)
{
    float lance;
    do
    {
        printf("DIGITE O VALOR DO SEU LANCE, QUE DEVE SER MAIOR QUE %.2f\n", valor_atual);
        scanf("%f", &lance);
        if(lance<=valor_atual)
            printf("DIGITE UM VALOR MAIOR QUE O ATUAL!!\n");
    }
    while(lance<=valor_atual);
    return lance;
}

//Funcao para incluir um novo lance
void incluir_novo_lance_produto()
{
    int nr_desejado,pos;
    tp_leilao produto;
    printf("DIGITE O NR DESEJADO: \n");
    scanf("%d", &nr_desejado);
    pos = retornar_posicao_apartir_nr(nr_desejado);
    if(pos!=-1)
    {
        produto = retornar_estrutura_apartir_pos(pos);
        if(produto.status==1)
        {
            if(produto.sit=='A')
            {
                apresentar_produto_unicamente(produto);
                produto.valor = validar_lance(produto.valor);
                printf("DIGITE O NOME DO COMPRADOR..: ");
                fflush(stdin);
                fgets(produto.nome,29,stdin);
                limpar_string(produto.nome);
                validar_numero_telefone(produto.telefone);
                produto.lances++;
                sobreescrever_arquivo_apartir_pos(produto,pos);
            }
            else
                printf("NAO TEM COMO DAR LANCE O PRODUTO JA FOI FINALIZADO\n");
        }
        else
            printf("NAO TEM COMO DAR O LANCE POIS O PRODUTO FOI EXCLUIDO LOGICAMENTE\n");
    }
    else
        printf("NAO CONTEM ESSE PRODUTO NO BANCO DE DADOS\n");
}

//Funcao para limpar o terminal
void pausa_limpar()
{
    system("pause");
    system("cls");
}
