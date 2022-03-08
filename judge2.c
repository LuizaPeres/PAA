//Luiza Peres

#include <stdio.h>

#include <stdlib.h>

#define REMOVIDO -1







typedef struct

{



    int lin;

    int col;

    int valor;

    int tamMax;



} CHAVE;



CHAVE calculaMenorValor(int K, CHAVE *coluna)

{



    CHAVE menorValor;

    int i;



    if(coluna[0].valor != REMOVIDO)

    {



        menorValor.valor = coluna[0].valor;

        menorValor.lin = coluna[0].lin;



    }

    else

    {

        int valor = coluna[0].valor;

        int lin = coluna[0].lin;

        i = 1;



        while(valor == REMOVIDO)

        {

            valor = coluna[i].valor;

            lin = coluna[i].lin;

            i++;



        }

        menorValor.valor = valor;

        menorValor.lin = lin;



    }



    i=0;

    do

    {

        if(coluna[i].valor != REMOVIDO)

        {

            if( menorValor.valor > coluna[i].valor)

            {

                menorValor.valor = coluna[i].valor;

                menorValor.lin = i;

            }

        }

        i++;



    }

    while ( i < K);



    return menorValor;



}



void iniciaColuna(CHAVE* coluna, int **vetores,int i)

{



    coluna[i].col = 0;

    coluna[i].lin = i;

    coluna[i].valor = vetores[i][0];



}



void imprimeColuna(CHAVE* coluna, int tam)

{



    int i;



    for(i = 0; i < tam; i++)

        printf("[%d][%d] = %d\n", coluna[i].lin, coluna[i].col, coluna[i].valor);



}







int main(void)

{



    int **vetores;

    CHAVE *coluna;

    CHAVE menorValor;



    int houveRemocao;

    int K, I, tamVetor, i, j,soma=0,remove;

    int lin, col;

    int novoValor;



    //printf("Digite o valor de K, sendo um conjunto de K vetores ordenados de números inteiros não-negativos.");

    scanf("%d", &K);



    vetores = malloc(K * sizeof(int*));

    coluna = malloc(K * sizeof(CHAVE));



    //printf("Digite o valor de i");

    scanf("%d", &I);



    for(i = 0; i < K; i++)

    {

        //printf(Digite o valor do tamanho do vetor);

        scanf("%d", &tamVetor);



        if(tamVetor > 0)

        {

            vetores[i] = malloc(tamVetor * sizeof(int));



        }

        if(tamVetor == 0)

        {

            vetores[i] = malloc(1 * sizeof(int));

            vetores[i][0] = REMOVIDO;



            iniciaColuna(coluna, vetores, i);

            coluna[i].tamMax = tamVetor;



        }

        else

        {

            for(j = 0; j < tamVetor; j++)

            {

                scanf("%d", &vetores[i][j]);

            }

            iniciaColuna(coluna, vetores, i);

            coluna[i].tamMax = tamVetor;



            if(vetores[i][0] > 0)

                soma+=vetores[i][0];



        }

    }

    if(I == 1 && tamVetor >0)

    {

        printf("%d\n",soma);



    }

    else

    {

        for(i = 1; i < I; i++)

        {

            //Busca menor valor e guarda sua posicao na matrix de vetores

            menorValor = calculaMenorValor(K, coluna);

            lin = menorValor.lin;

            col = menorValor.col;



            //Retira menor valor do somatorio e atualiza posicao

            soma -= menorValor.valor;

            coluna[lin].col++;



            if(coluna[lin].col > coluna[lin].tamMax - 1)

            {

                coluna[lin].valor = REMOVIDO;

                houveRemocao = 1;



            }

            else

            {

                coluna[lin].valor = vetores[lin][coluna[lin].col];

                //printf("lin = %d col = %d val = %d\n",coluna[lin].lin, coluna[lin].col, coluna[lin].valor);

            }

            if(houveRemocao == 1 )

            {

                soma += coluna[lin].valor + 1;

            }

            else

            {

                soma += coluna[lin].valor;



            }

            houveRemocao = 0;

        }

        printf("%d\n",soma);

    }



    return 0;

}
