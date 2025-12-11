//uma funcao que retorna 1 se ele existir no arquivo e -1 caso nao
int validar_nr_binario(int nr_desejado)
{
    int val = -1;
    tp_leilao produto;
    FILE *arquivo;
    arquivo = fopen("dadosleilao.dat", "rb");
    if(arquivo == NULL)
    {
        printf("ERRO NO ARQUIVO..\n");
    }
    else
    {
        fread(&produto, sizeof(tp_leilao), 1, arquivo);
        while(!feof(arquivo) && val == -1)
        {
            if(nr_desejado == produto.nr)
            {
                val = 1;
            }
            fread(&produto, sizeof(tp_leilao), 1, arquivo);
        }
        fclose(arquivo);
    }
    return val;
}

//uma funcao para incluir um novo produto no final do arquivo
void incluir_novo_produto_no_arquivo(tp_leilao produto)
{
    FILE *arquivo;
    arquivo = fopen("dadosleilao.dat", "ab");
    if(arquivo == NULL)
        arquivo = fopen("dadosleilao.dat", "wb");
    if(arquivo == NULL)
    {
        printf("ERRO NO ARQUIVO..\n");
    }
    else
    {
        fwrite(&produto, sizeof(tp_leilao), 1, arquivo);
        fclose(arquivo);
    }
}

//uma funcao que retorna a quantidade de struct ate o final do arquivo
int retornar_qtd_struct()
{
    FILE *arquivo;
    int quantidade = 0;
    long qtd_bits;
    arquivo = fopen("dadosleilao.dat", "rb");
    if(arquivo == NULL)
        printf("ERRO NO ARQUIVO..\n");
    else
    {
        fseek(arquivo,0,SEEK_END);
        qtd_bits = ftell(arquivo);
        quantidade = qtd_bits/sizeof(tp_leilao);
        fclose(arquivo);
    }
    return quantidade;
}

//Funcao que apartir do nr retornara a posicao do produto
int retornar_posicao_apartir_nr(int nr)
{
    int pos=-1,i=0;
    tp_leilao produto;
    FILE *arquivo;
    arquivo = fopen("dadosleilao.dat", "rb");
    if(arquivo!=NULL)
    {
        fread(&produto,sizeof(tp_leilao), 1, arquivo);
        while(!feof(arquivo)&&pos==-1)
        {
            if(nr == produto.nr)
                pos=i;
            i++;
            fread(&produto,sizeof(tp_leilao), 1, arquivo);
        }
        fclose(arquivo);
    }
    else
        printf("ERRO NO SISTEMA\n");
    return pos;
}

//Funcao de sobreescrever uma struct apartir de posicao
void sobreescrever_arquivo_apartir_pos(tp_leilao leilao, int pos)
{
    FILE *arquivo;
    arquivo = fopen("dadosleilao.dat", "rb+");
    if(arquivo!=NULL)
    {
        fseek(arquivo,pos*sizeof(tp_leilao),SEEK_SET);
        fwrite(&leilao,sizeof(tp_leilao), 1,arquivo);
        fclose(arquivo);
    }
    else
    {
        printf("ERRO NO SISTEMA\n");
    }
}

//Funcao que apartir da posicao retornara a estrutura do produto
tp_leilao retornar_estrutura_apartir_pos(int pos)
{
    tp_leilao produto;
    FILE *arquivo;
    arquivo = fopen("dadosleilao.dat", "rb");
    if(arquivo!=NULL)
    {
        fseek(arquivo,sizeof(tp_leilao)*pos, SEEK_SET);
        fread(&produto,sizeof(tp_leilao),1,arquivo);
        fclose(arquivo);
    }
    else
        printf("ERRO NO SISTEMA\n");
    return produto;
}

//Funcao para realizar a excusao fisica de todos os produtos excluidos logicamente
void excluir_fisicamente_todos_produtos_excluidos_logicamente()
{
    tp_leilao produto;
    FILE *origem,*destino;
    origem = fopen("dadosleilao.dat", "rb");
    destino = fopen("novo.dat", "wb");
    if(origem!=NULL && destino!=NULL)
    {
        fread(&produto,sizeof(tp_leilao),1,origem);
        while(!feof(origem))
        {
            if(produto.status==1)
            {
                fwrite(&produto,sizeof(tp_leilao),1,destino);
            }
            fread(&produto,sizeof(tp_leilao),1,origem);
        }
        fclose(origem);
        fclose(destino);
        remove("dadosleilao.dat");
        rename("novo.dat","dadosleilao.dat");
    }
    else
    {
        printf("ERRO NO SISTEMA\n");
    }
}

//Funcao para validar se a algo no arquivo
int validar_se_tem_algo_arquivo()
{
    int val=0;
    tp_leilao produto;
    FILE*arquivo;
    arquivo = fopen("dadosleilao.dat", "rb");
    if(arquivo==NULL)
        arquivo = fopen("dadosleilao.dat", "wb");
    if(arquivo!=NULL)
    {
        fread(&produto,sizeof(tp_leilao),1,arquivo);
        while(!feof(arquivo)&&val==0)
        {
            val=1;
        }
        fclose(arquivo);
    }
    else
        printf("ERRO NO SISTEMA\n");
    return val;
}
