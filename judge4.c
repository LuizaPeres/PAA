//Luiza Peres

#include <stdio.h>

#include <stdlib.h>





typedef struct

{

    int valor;

    int tamMax;



} CHAVE;





//Função para achar a maior taxa disponível

int max_taxa(int taxa1, int taxa2)

{

    if(taxa1 > taxa2)
    {
        return taxa1;



    }
    else
    {

        return taxa2;

    }

}

//C = CAPACIDADE N NUM TRANSAÇOES

//Funçao baseada na ideia do exercicio 2 da lista de exercícios 3

int Calcula(CHAVE *vet,int C, int N)
{



    int i, b,m;

    int M[N+1][C+1];





    // construindo a tabela  M[][] utilizando bottom up

    for (i = 0; i <= N; i++)
    {

        for (b = 0; b <= C; b++)
        {

            if (i==0 || b==0)// Inicializando a primeira linha e a primeira coluna da matriz com "0"

            {

                M[i][b] = 0;

            }

            else if(vet[i-1].tamMax > b)   // faz a validação da seguinte condição:  se a transação atual possui um tamanho de bytes maior que a parte do bloco analisada, chamado  mempool
            {

                M[i][b] = M[i-1][b];

            }
            else    // se vet[i-1].tamMax <= b

            {

                int m = vet[i-1].tamMax;

                // chamando a função max apara achar as maiores taxas, temos :

                M[i][b] = max_taxa(vet[i-1].valor + M[i-1][b-m],M[i-1][b]);

            }

        }

    }



    return M[N][C];

}



int main(void)
{



    int N, C;

    int i, j;

    int sol;



//printf("Digite o número de transações existentes no mempool N");

    scanf("%d", &N);



    CHAVE *vetor;

    vetor = (CHAVE*) malloc(sizeof(CHAVE)*N);



//printf("Digite a capacidade em bytes de um bloco,C");

    scanf("%d", &C);



    for (i =0; i <= N; i++)
    {

        //printf("\nDigite o valor da taxa e o tamanho em bytes:");

        scanf("%d %d",&vetor[i].valor, &vetor[i].tamMax );

    }



// A soma a  das taxas em CBL a serem obtidas caso o bloco seja inserido no blockchain é :

    sol = Calcula(vetor,C, N);

    printf ("%d", sol);



    return 0;



}
