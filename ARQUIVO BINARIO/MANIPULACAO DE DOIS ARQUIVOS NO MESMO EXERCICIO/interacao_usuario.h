//funcao para validar a opcao a ser escolhida pelo usuario
int escolher_funcao()
{
    int esc;
    do{
            printf("=====================================MENU======================================\n"
                   "DIGITE A OPCAO DESEJADA:\n0 - SAIR\n1 - INCLUIR PRODUTO\n2 - ALTERAR DADOS DO PRODUTO\n3 - EXCLUIR UM PRODUTO, QUE NAO TENHA SIDO VENDIDO\n"
                   "4 - PESQUISAR UM PRODUTO\n5 - COMPRAR MAIS QUANTIDADE DE PRODUTOS QUE JA SAO CADASTRADOS\n6 - APRESENTAR TODOS OS DADOS DE TODOS OS PRODUTOS\n"
                   "7 - APRESENTAR BALANCETE\n8 - APRESENTAR PRODUTOS COM POUCO NO ESTOQUE\n9 - INCLUSAO DE VENDAS\n"
                   "10 - APRESENTAR TODAS AS VENDAS DE UM DETERMINADO PRODUTO\n11 - APRESNETAR A RELACAO DE TODAS AS VENDAS RELIZADAS EM UMA DATA\n"
                   "12 - APRESENTAR A QUANTIDADE VENDIDA DE CADA UM DOS PRODUTOS\n13 - APRESENTAR O TOTAL ARRECADADO EM UM CERTO MES\n"
                   "===============================================================================\n");
        scanf("%d", &esc);
        if(esc<0 || esc>13)
            printf("ESCOLHA UMA OPCAO VALIDA\n");
    }while(esc<0 || esc>13);
    return esc;
}

//funcao que forca o usuario a colocar um codigo valido
int validar_codigo()
{
    int val,cod_desejado;
    do
    {
        printf("CODIGO DO PRODUTO .........: ");
        scanf("%d", &cod_desejado);
        val = verificar_cod_arquivo(cod_desejado);
        if(val == 1 || cod_desejado<0)
            printf("DIGITE UM CODIGO VALIDO!!\n");
    }
    while(val==1|| cod_desejado<0);
    return cod_desejado;
}

//funcao vai validar que a quantidade em estoque nao pode ser negativo
int validar_inteiro_positivo()
{
    int estoque;
    do
    {
        scanf("%d", &estoque);
        if(estoque<0)
            printf("DIGITE UMA QUANTIDADE VALIDA!!\n");
    }
    while(estoque<0);
    return estoque;
}

//funcao para validar o preco que nao pode ser negativo
float validar_preco_produto()
{
    float preco;
    do
    {
        printf("PRECO PRODUTO ............: ");
        scanf("%f", &preco);
        if(preco<0)
            printf("DIGITE UM PRECO VALIDO\n");
    }
    while(preco<0);
    return preco;
}

//funcao para retirar o \n no final da string
void limpar_string(char string[])
{
    if(string[strlen(string)-1]=='\n')
        string[strlen(string)-1]='\0';
}

//funcao para preencher uma estrutura de produto
tp_produto preencher_estrutura_produto()
{
    tp_produto item;
    printf("NOME DO PRODUTO .......: ");
    fflush(stdin);
    fgets(item.nome, 29, stdin);
    limpar_string(item.nome);
    item.cod = validar_codigo();
    printf("QUANTIDADE EM ESTOQUE .......: ");
    item.estoque = validar_inteiro_positivo();
    item.preco = validar_preco_produto();
    return item;
}

//funcao para incluir um novo produto no arquivo
void incluir_novo_produto()
{
    tp_produto item;
    item = preencher_estrutura_produto();
    adicionar_novo_produto_arquivo(item);
}

//funcao para alterar todos os dados de um produto
void alterar_dados_produto()
{
    tp_produto item;
    int pos,cod_desejado;
    printf("================ALTERAR DADOS DE UM PRODUTO================\n");
    printf("DIGITE O CODIGO DESEJADO: ");
    cod_desejado = validar_inteiro_positivo();
    pos = retornar_posicao_apartir_cod(cod_desejado);
    if(pos!=-1)
    {
        item = preencher_estrutura_produto();
               sobreescrever_arquivo_produto(item,pos);
    }
    else
        printf("ESSE PRODUTO NAO EXISTE NO ARQUIVO\n");
}

//funcao para excluir um produto caso ele nao tenha sido vendido nenhuma vez
void excluir_produto_sem_venda()
{
    int val,pos,cod_desejado;
    printf("===============EXCLUSAO DE UM PRODUTO SEM VENDA===============\n");
    printf("DIGITE O CODIGO DESEJADO: ");
    cod_desejado = validar_inteiro_positivo();
    pos = retornar_posicao_apartir_cod(cod_desejado);
    if(pos!=-1)
    {
        val = somar_produto_vendido(cod_desejado);
        if(val == 0)
        {
            excluir_produto_do_arquivo(pos);
        }
        else
            printf("ESSE PRODUTO JA CONTEVE VENDAS ENTAO NAO PODE SER EXCLUIDO\n");
    }
    else
        printf("ESSE PRODUTO NAO EXISTE NO ARQUIVO\n");
}

//funcao para apresentar os dados de um produto especifico
void apresentar_produto_unico(tp_produto item)
{
    printf("CODIGO ............: %6.0d\n", item.cod);
    printf("NOME ..............: %-30s\n", item.nome);
    printf("PRECO .............: %6.2f\n", item.preco);
    printf("ESTOQUE ...........: %6.0d\n\n", item.estoque);
}

//funcao para apresentar um produto apartir de seu codigo
void pesquisar_produto()
{
    tp_produto item;
    int cod_desejado,pos;
    printf("==============PESQUISAR PRODUTO=================\n");
    printf("DIGITE O CODIGO DESEJADO: ");
    cod_desejado = validar_inteiro_positivo();
    pos = retornar_posicao_apartir_cod(cod_desejado);
    if(pos != -1)
    {
        item = retornar_estrutura_apartir_posicao(pos);
        apresentar_produto_unico(item);
    }
    else
        printf("ESSE PRODUTO NAO EXISTE NO ARQUIVO\n");
}

//funcao para comprar mais quantidade de um produto ja cadastrado
void comprar_mais_quantidade()
{
    tp_produto item;
    int cod_desejado,pos,quant;
    printf("==============COMPRAR MAIS ITENS DE UM PRODUTO=================\n");
    printf("DIGITE O CODIGO DESEJADO: ");
    cod_desejado = validar_inteiro_positivo();
    pos = retornar_posicao_apartir_cod(cod_desejado);
    if(pos != -1)
    {
        printf("DIGITE A QUANTIDADE COMPRADA: ");
        quant = validar_inteiro_positivo();
        item = retornar_estrutura_apartir_posicao(pos);
        item.estoque += quant;
        sobreescrever_arquivo_produto(item, pos);
    }
    else
        printf("ESSE PRODUTO NAO EXISTE NO ARQUIVO\n");
}

//funcao para apresentar todos os dados de todos os produtos
void apresentar_todos_produtos()
{
    tp_produto item;
    int tl,i;
    tl = retornar_tl_arquivo_produto();
    for(i=0;i<tl;i++)
    {
        item = retornar_estrutura_apartir_posicao(i);
        apresentar_produto_unico(item);
    }
}

//funcao para apresentar o cabecario com balancete
void apresentar_cabecario_balancete()
{
    printf("%-6s %-29s %-6s %-7s %-10s\n", "CODIGO", "NOME", "PRECO", "ESTOQUE", "BALANCETE");
}

//funcao para apresentar uma linha com o balancete
void apresentar_produto_unico_com_balancete(tp_produto item, float balancete)
{
    printf("%6.0d %-29s %6.2f %6.0d   %6.2f\n", item.cod, item.nome, item.preco, item.estoque, balancete);
}

//funcao para apresentar todos os dados e o balancete de todos os produtos
void apresentar_balancete_todos_produtos()
{
    tp_produto item;
    int tl,i;
    float balancete, estoque=0;
    tl = retornar_tl_arquivo_produto();
    apresentar_cabecario_balancete();
    for(i=0;i<tl;i++)
    {
        item = retornar_estrutura_apartir_posicao(i);
        balancete = item.estoque * item.preco;
        apresentar_produto_unico_com_balancete(item,balancete);
        estoque += balancete;
    }
    printf("PORTANTO NO ESTOQUE CONTEM: %6.2f\n", estoque);
}

//funcao para apresentar todos os dados de todos os produtos com menos de 5 itens
void apresentar_todos_produtos_com_max_5()
{
    tp_produto item;
    int tl,i;
    tl = retornar_tl_arquivo_produto();
    for(i=0;i<tl;i++)
    {
        item = retornar_estrutura_apartir_posicao(i);
        if(item.estoque<5)
            apresentar_produto_unico(item);
    }
}

//funcao para validar o dia
int validar_dia_venda(int maximo)
{
    int dia;
    do{
        printf("DIGITE O DIA (ENTRE 0 a %d): ", maximo);
        scanf("%d", &dia);
        if(dia<0 || dia>maximo)
            printf("DIA INVALIDO!!\n");
    }while(dia<0 || dia>maximo);
    return dia;
}

//funcao para validar o mes
int validar_mes_venda()
{
    int mes;
    do{
        printf("DIGITE O MES: ");
        scanf("%d", &mes);
        if(mes<1 || mes>12)
            printf("MES INVALIDO!!\n");
    }while(mes<1 || mes>12);
    return mes;
}

//funcao para preencher a data
tp_venda preencher_data_de_venda()
{
    int maximo=30;
    tp_venda nota;
    printf("DIGITE O ANO: ");
    nota.ano = validar_inteiro_positivo();
    nota.mes = validar_mes_venda();
    if(nota.mes == 1 || nota.mes == 3 ||nota.mes == 5 ||nota.mes == 7 ||nota.mes == 8 ||nota.mes == 10 ||nota.mes == 12)
        maximo =31;
    if(nota.mes == 2)
    {
        if(nota.ano%4==0)
            maximo = 29;
        else
            maximo = 28;
    }
    nota.dia = validar_dia_venda(maximo);
    return nota;
}

//funcao que forca o usuario a colocar um codigo valido
int forcar_colocar_codigo_existente()
{
    int val,cod_desejado;
    do
    {
        printf("CODIGO DO PRODUTO .........: ");
        scanf("%d", &cod_desejado);
        val = verificar_cod_arquivo(cod_desejado);
        if(val == 0 || cod_desejado<0)
            printf("DIGITE UM CODIGO VALIDO!!\n");
    }
    while(val==0|| cod_desejado<0);
    return cod_desejado;
}

//funcao para validar a quantidade de unidades em estoque e a demanda
int validar_quantidades_estoque_compra(int maximo)
{
    int quant;
    do{
        printf("DIGITE A QUANTIDADE A SER COMPRADA(ENTRE 0 A %d): ", maximo);
        scanf("%d", &quant);
        if(quant>maximo || quant<0)
            printf("QUANTIDADE INVALIDA\n");
    }while(quant>maximo || quant<0);
    return quant;
}

//funcao que realiza a inclusao de vendas
void inclusao_de_vendas()
{
    tp_venda nota;
    tp_produto item;
    int pos,cod_desejado;
    float gasto;
    nota = preencher_data_de_venda();
    cod_desejado = forcar_colocar_codigo_existente();
    pos = retornar_posicao_apartir_cod(cod_desejado);
    item = retornar_estrutura_apartir_posicao(pos);
    nota.cod = cod_desejado;
    nota.quant = validar_quantidades_estoque_compra(item.estoque);
    item.estoque-=nota.quant;
    gasto = nota.quant * item.preco;
    printf("\nO VALOR GASTO FOI DE %.2f\n\n", gasto);
    sobreescrever_arquivo_produto(item, pos);
    incluir_no_final_vendas(nota);
}

//funcao para apresentar unicamente uma estrutura de venda
void apresentar_unicamente_vendas(tp_venda nota, float preco)
{
    printf("CODIGO DO PRODUTO ...: %d\n", nota.cod);
    printf("DIA .................: %d\n", nota.dia);
    printf("MES .................: %d\n", nota.mes);
    printf("ANO .................: %d\n", nota.ano);
    printf("QUANTIDADE ..........: %d\n", nota.quant);
    printf("PRECO ...............: %.2f\n\n", preco);
}

//funcao apresentar todas as vendas de um determinado produto, com data, quantidade e valor total, ao final apresentar o valor total dessas vendas
void apresentar_todas_estrutura_vendas()
{
    tp_produto item;
    tp_venda nota;
    float total=0, preco_parcial;
    int tl,i,pos,cod_desejado;
    printf("DIGITE O CODIGO DESEJADO: ");
    cod_desejado = validar_inteiro_positivo();
    pos = retornar_posicao_apartir_cod(cod_desejado);
    if(pos!=-1)
    {
        tl = retornar_tl_arquivo_vendas();
        item = retornar_estrutura_apartir_posicao(pos);
        for(i=0;i<tl;i++)
        {
            nota = retornar_estrutura_de_vendas(i);
            if(nota.cod == cod_desejado)
            {
                preco_parcial = nota.quant*item.preco;
                apresentar_unicamente_vendas(nota,preco_parcial);
                total+=preco_parcial;
            }
        }
        printf("O TOTAL FOI DE %.2f\n", total);
    }
    else
        printf("ESSE PRODUTO NAO ESTA NO ARQUIVO\n");
}

//funcao apresentar todas as vendas em um dia especifico, com data, quantidade e valor total, ao final apresentar o valor total dessas vendas
void apresentar_todas_estrutura_vendas_de_dia_especifico()
{
    tp_produto item;
    tp_venda nota,dia_especifico;
    float total=0, preco_parcial;
    int tl,i,pos,cod_desejado;
    dia_especifico = preencher_data_de_venda();
        tl = retornar_tl_arquivo_vendas();
        for(i=0;i<tl;i++)
        {
            nota = retornar_estrutura_de_vendas(i);
            if(nota.dia==dia_especifico.dia && nota.mes==dia_especifico.mes && nota.ano==dia_especifico.ano)
            {
                pos = retornar_posicao_apartir_cod(nota.cod);
                item = retornar_estrutura_apartir_posicao(pos);
                preco_parcial = nota.quant*item.preco;
                apresentar_unicamente_vendas(nota,preco_parcial);
                total+=preco_parcial;
            }
        }
        printf("\nO TOTAL FOI DE %.2f\n", total);
}

//funcao que apresenta a quantidade vendida de cada um dos produtos
void apresentar_quantidade_por_cada_produto()
{
    tp_venda nota;
    int quantidade[50], codigos[50], contem, guardar_pos,j,i,tam_vet=0,tl;
    tl = retornar_tl_arquivo_vendas();
    for(i=0;i<50;i++)
    {
        quantidade[i]=0;
    }
    for(i=0;i<tl;i++)
    {
        nota = retornar_estrutura_de_vendas(i);
        contem=0;
        for(j=0;j<tam_vet;j++)
        {
            if(nota.cod==codigos[j])
            {
                contem=1;
                guardar_pos = j;
                j=tam_vet;
            }
        }
        if(contem==0)
        {
            codigos[tam_vet]=nota.cod;
            guardar_pos = tam_vet;
            tam_vet++;
        }
        quantidade[guardar_pos]+=nota.quant;
    }
    for(i=0;i<tam_vet;i++)
    {
        printf("A QUANTIDADE VENDIDA DO PRODUTO %d = %d\n",codigos[i] ,quantidade[i]);
    }
}

//funcao que o usuario digitara um mes e ela retornara o total arrecadado no mes
float retornar_total_arrecadado_mes()
{
    tp_venda nota;
    tp_produto item;
    int mes_especifico,ano_especifico,pos,tl,i;
    float total=0;
    mes_especifico = validar_mes_venda();
    printf("DIGITE O ANO : ");
    ano_especifico = validar_inteiro_positivo();
    tl = retornar_tl_arquivo_vendas();
    for(i=0;i<tl;i++)
    {
        nota = retornar_estrutura_de_vendas(i);
        if(nota.mes == mes_especifico && nota.ano == ano_especifico)
        {
            pos = retornar_posicao_apartir_cod(nota.cod);
            item = retornar_estrutura_apartir_posicao(pos);
            total += item.preco * nota.quant;
        }
    }
    return total;
}
