//estrutura de um produto
typedef struct{
    int cod,estoque;
    char nome[30];
    float preco;
}tp_produto;

//estrura de venda de um produto
typedef struct{
    int dia,mes,ano,cod,quant;
}tp_venda;
