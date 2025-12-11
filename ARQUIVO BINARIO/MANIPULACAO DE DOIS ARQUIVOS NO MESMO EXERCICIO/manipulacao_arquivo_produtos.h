//Funcao para verificar se existe o codigo no arquivo produto, se retornar 1 existe e 0 nao existe
int verificar_cod_arquivo(int cod_desejado)
{
    tp_produto item;
    int val=0;
    FILE *arquivo;
    arquivo = fopen("tabela_de_produtos.dat", "rb");
    if(arquivo!=NULL)
    {
        fread(&item,sizeof(tp_produto),1,arquivo);
        while(!feof(arquivo) && val==0)
        {
            if(item.cod==cod_desejado)
                val=1;
            fread(&item,sizeof(tp_produto),1,arquivo);
        }
          fclose(arquivo);
    }
    else
        printf("ERRO NO SISTEMA\n");
    return val;
}

//funcao que adiciona um novo produto no final do arquivo
void adicionar_novo_produto_arquivo(tp_produto item)
{
    FILE *arquivo;
    arquivo = fopen("tabela_de_produtos.dat", "ab");
    if(arquivo == NULL)
        arquivo = fopen("tabela_de_produtos.dat", "wb");
    if(arquivo != NULL)
    {
        fwrite(&item,sizeof(tp_produto),1,arquivo);
        fclose(arquivo);
    }
    else
        printf("ERRO NO SISTEMA\n");
}

//funcao que retorna a posicao apartir do codigo do produto
int retornar_posicao_apartir_cod(int cod_desejado)
{
    int pos=-1,i=0;
    tp_produto item;
    FILE*arquivo;
    arquivo = fopen("tabela_de_produtos.dat", "rb");
    if(arquivo != NULL)
    {
        fread(&item, sizeof(tp_produto), 1, arquivo);
        while(!feof(arquivo))
        {
            if(item.cod==cod_desejado)
                pos = i;
            fread(&item, sizeof(tp_produto), 1, arquivo);
            i++;
        }
        fclose(arquivo);
    }
    else
        printf("ERRO NO SISTEMA123\n");
    return pos;
}

//funcao para retornar uma estrutura apartir da posicao
tp_produto retornar_estrutura_apartir_posicao(int pos)
{
    tp_produto item;
    FILE*arquivo;
    arquivo = fopen("tabela_de_produtos.dat", "rb");
    if(arquivo != NULL)
    {
        fseek(arquivo, pos*sizeof(tp_produto), SEEK_SET);
        fread(&item, sizeof(tp_produto), 1, arquivo);
        fclose(arquivo);
    }
    else
        printf("ERRO NO SISTEMA\n");
    return item;
}

//funcao para soobrescrever o arquivo de produto com a nova estrutura e na posicao que se deseja
void sobreescrever_arquivo_produto(tp_produto item, int pos)
{
    FILE*arquivo;
    arquivo = fopen("tabela_de_produtos.dat", "rb+");
    if(arquivo != NULL)
    {
        fseek(arquivo, pos*sizeof(tp_produto), SEEK_SET);
        fwrite(&item, sizeof(tp_produto), 1, arquivo);
        fclose(arquivo);
    }
    else
        printf("ERRO NO SISTEMA\n");
}

//funcao para excluir fisicamente um produto apartir de sua posicao
void excluir_produto_do_arquivo(int pos)
{
    int i=0;
    tp_produto item;
    FILE *origem, *destino;
    origem = fopen("tabela_de_produtos.dat", "rb");
    destino = fopen("auxiliar.dat", "wb");
    if(origem != NULL && destino != NULL)
    {
        fread(&item, sizeof(tp_produto), 1, origem);
        while(!feof(origem))
        {
            if(pos != i)
                fwrite(&item, sizeof(tp_produto), 1, destino);
            i++;
            fread(&item, sizeof(tp_produto), 1, origem);
        }
        fclose(origem);
        fclose(destino);
        remove("tabela_de_produtos.dat");
        rename("auxiliar.dat", "tabela_de_produtos.dat");
    }
    else
        printf("ERRO NO SISTEMA\n");
}

//funcao para retornar o tl do arquivo ou seja a quantidade de estruturas no arquivo
int retornar_tl_arquivo_produto()
{
    int tl;
    long int bytes;
    FILE*arquivo;
    arquivo = fopen("tabela_de_produtos.dat", "rb");
    if(arquivo != NULL)
    {
        fseek(arquivo, 0, SEEK_END);
        bytes = ftell(arquivo);
        tl = bytes/sizeof(tp_produto);
        fclose(arquivo);
    }
    else
        printf("ERRO NO SISTEMA\n");
    return tl;
}

//funcao para validar se o arquivo tem ao menos uma estrutura retorna 1, se nao conter retorna 0
int validar_arquivo_produto()
{
    int val=0;
    tp_produto item;
    FILE *arquivo;
    arquivo = fopen("tabela_de_produtos.dat", "rb");
    if(arquivo == NULL)
    {
        arquivo = fopen("tabela_de_produtos.dat", "wb");
    }
    if(arquivo != NULL)
    {
        fread(&item, sizeof(tp_produto), 1, arquivo);
        while(!feof(arquivo)&&val==0)
            val=1;
        fclose(arquivo);
    }
    else
        printf("ERRO NO SISTEMA\n");
    return val;
}
