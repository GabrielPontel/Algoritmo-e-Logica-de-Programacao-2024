//funcao para verificar se um produto ja foi vendido
int somar_produto_vendido(int cod_desejado)
{
    tp_venda nota;
    int somar=0;
    FILE *arquivo;
    arquivo = fopen("tabela_de_vendas.dat", "rb");
    if(arquivo != NULL)
    {
        fread(&nota, sizeof(tp_venda), 1, arquivo);
        while(!feof(arquivo))
        {
            if(nota.cod == cod_desejado)
                somar+=nota.quant;
            fread(&nota, sizeof(tp_venda), 1, arquivo);
        }
        fclose(arquivo);
    }
    else
        printf("ERRO NO SISTEMA\n");
    return somar;
}

//funcao que acrecenta uma nova venda no final do arquivo
void incluir_no_final_vendas(tp_venda nota)
{
    FILE *arquivo;
    arquivo = fopen("tabela_de_vendas.dat", "ab");
    if(arquivo == NULL)
        arquivo = fopen("tabela_de_vendas.dat", "wb");
    if(arquivo != NULL)
    {
        fwrite(&nota, sizeof(tp_venda), 1, arquivo);
        fclose(arquivo);
    }
    else
        printf("ERRO NO SISTEMA\n");
}

//funcao que retornara a estrutura de venda a partir de sua posicao
tp_venda retornar_estrutura_de_vendas(int pos)
{
    tp_venda nota;
    FILE *arquivo;
    arquivo = fopen("tabela_de_vendas.dat", "rb");
    if(arquivo != NULL)
    {
        fseek(arquivo, pos * sizeof(tp_venda),SEEK_SET);
        fread(&nota, sizeof(tp_venda), 1, arquivo);
        fclose(arquivo);
    }
    else
        printf("ERRO NO SISTEMA\n");
    return nota;
}

//funcao para achar a quantidade de estruturas contem no arquivo venda
int retornar_tl_arquivo_vendas()
{
    long int bytes;
    int tl;
    FILE *arquivo;
    arquivo = fopen("tabela_de_vendas.dat", "rb");
    if(arquivo != NULL)
    {
        fseek(arquivo, 0, SEEK_END);
        bytes = ftell(arquivo);
        tl = bytes/sizeof(tp_venda);
        fclose(arquivo);
    }
    else
        printf("ERRO NO SISTEMA\n");
    return tl;
}

//funcao para validar se o arquivo tem ao menos uma estrutura retorna 1, se nao conter retorna 0
int validar_arquivo_vendas()
{
    int val=0;
    tp_venda nota;
    FILE *arquivo;
    arquivo = fopen("tabela_de_vendas.dat", "rb");
    if(arquivo == NULL)
    {
        arquivo = fopen("tabela_de_vendas.dat", "wb");
    }
    if(arquivo != NULL)
    {
        fread(&nota, sizeof(tp_venda), 1, arquivo);
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
