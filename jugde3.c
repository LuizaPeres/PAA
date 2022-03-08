//Luiza Peres

#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#define DIMENSION 8
#define NCELL DIMENSION*DIMENSION
#define true 1
#define false 0

int qtd_p;
int teste = 0;

int** Cria_Tabuleiro()
{
    int i;
    int** tabuleiro;
    tabuleiro = calloc (DIMENSION,sizeof (int*));
    for(i = 0; i < DIMENSION; i++)
    {
        tabuleiro[i] = calloc (DIMENSION,sizeof (int));
    }
    return tabuleiro;
}


void preenche_tabuleiro(int **tabuleiro, int *visitado)
{
    int x, y;
    int cont = 1;
    for(x=0; x<8; x++)
    {
        for(y=0; y<8; y++)
        {
            tabuleiro[x][y] = 0;
            visitado[cont] = 0;
            cont++;
        }
    }
}

void encontra(int *peao, int H, int P)
{
// printf("\nENTROU EM ENCONTRA");
    int i = 0;
    int cont = 0;
    while(cont < P)
    {
        if(peao[i] == H)
        {
            peao[i] = 0;
            return;
        }
        else if(peao[i] == 0);
        else
            cont++;
        i++;
    }
}

void Move_Pawn(int P, int *peao, int **tabuleiro, int *excede)
{
    int i = 0, aux = 0;
    //printf("\nENTROU EM MOVE PAWN");
    for(i=0; i<qtd_p; i++)
    {
        if(peao[i] != 0)
        {
            //printf("\n DIFERENTE DE 0 -> PEAO -> %d",peao[i]);
            if(peao[i]+8 > 64)
            {
                *excede +=1;
                return;
            }
        }
        //se a posicao abaixo do peao atual estiver vazia, entao apenas atualizamos
        if(tabuleiro[((peao[i])/DIMENSION)+1][peao[i]%DIMENSION-1] == 0)
        {
            peao[i] += 8;
            //printf("\nCELULA A FRENTE EH VAZIA");
        }
        //entao há um peao na frente, entao devemos atualizar os dois
        else if(tabuleiro[((peao[i])/DIMENSION)+1][peao[i]%DIMENSION-1] == 1)
        {
            int cont = 1;
            //printf("\nCELULA A FRENTE JA ESTA OCUPADA");

            while(tabuleiro[((peao[i])/DIMENSION)+cont][peao[i]%DIMENSION-1] == 1)
            {
                cont++;
            }

            int k = 0;
            tabuleiro[((peao[i]-1)/DIMENSION)][peao[i]%DIMENSION-1] = 0;

            for(k=1; k < cont; k++)
            {
                tabuleiro[((peao[i])/DIMENSION)+k][peao[i]%DIMENSION-1] = 1;//atualizando o tabuleiro
            }
        }//entao o cavalo está a frente, portanto o jogo acabou
        else if(tabuleiro[((peao[i])/DIMENSION)+1][peao[i]%DIMENSION-1] == 2)
        {
            // printf("\nCAVALO A FRENTE");
            return;
        }
    }
}

bool procura(int **tabuleiro, int H, int CandidateX, int CandidateY, int *peao, int *coord, int P)
{
    //printf("\nENTROU EM PROCURA");
    //tabuleiro[(peao[i]-1)/DIMENSION][(peao[i]-1)%DIMENSION] = 1;
    int k=0, cont = 0;
    //verificar para todas as posições possiveis que o cavalo pode andar, se há algum peao
    while(cont < P)
    {
        //verifica a partir da posicao H no tabuleiro
        if(peao[k] == 0);
        else if(H == peao[k]) //entao encontramos uma solucao deste subconjunto
        {
            //printf("\nENCONTROU UM PEAO EM PROCURA\n");
            tabuleiro[((H-1)/DIMENSION)][((H-1)%DIMENSION)] = 0;
            peao[k] = 0;
            return true;
        }
        else
        {
            cont++;
        }
        k++;
    }
    return false;
}
//Função para verificar se o H somado em coord está no vetor peoes,verifica se contem solução na procura
bool Contem_solucao(int **tabuleiro, int H, int *CandidateX, int *CandidateY, int *peao,
                    int *coord, int P, int aux)
{
// printf("\nENTROU NO CONTEM SOLUCAO POSICAO -> %d | AUX -> %d | H+COORD -> %d",coord[aux],aux, H+coord[aux]);
    if(aux == 8)
        return false;
    //tabuleiro[(peao[i]-1)/DIMENSION][(peao[i]-1)%DIMENSION] = 1;
    int i=0;
    if((((H-1)/DIMENSION)+CandidateX[aux]) >= 0 &&
            (((H-1)/DIMENSION)+CandidateX[aux]) < DIMENSION &&
            ((H-1)%DIMENSION)+CandidateY[aux] >= 0 &&
            ((H-1)%DIMENSION)+CandidateY[aux] < DIMENSION)
    {
        for(i=0; i<qtd_p; i++) //verificando se está no peão
        {
            if(peao[i] == 0);
            else if(peao[i] == H+coord[aux])
            {
                //entao tamo bem
                // printf("\nENCONTROU UM PEAO EM CONTEM SOLUCAO\n");
                tabuleiro[((H+coord[aux])-1)/DIMENSION][((H+coord[aux])-1)%DIMENSION] = 0;
                peao[i] = 0;
                return true;
            }
        }
    }
    return Contem_solucao(tabuleiro, H, CandidateX, CandidateY, peao, coord, P, aux+1);
}

void Busca_solucao(int **tabuleiro, int *peao, int P, int H, int *visitado, int n_jogadas, int *menor_jogada, int excede)
{
    //printf("\nENTROU EM BUSCA | H -> %d | P -> %d | N JOGADAS -> %d",H, P, n_jogadas);

    int CandidateX[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int CandidateY[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
    int coord[8] = {17, 10, -6, -15, -17, -10, 6, 15};
    int candidatos = 0;

    if(P == 0)//Cavalo venceu
    {
        //printf("\nVENCEU! N JOGADAS -> %d", n_jogadas);
        if(n_jogadas < *menor_jogada)
        {
            *menor_jogada = n_jogadas ;
        }
        return;
    }

    else if(n_jogadas == 8) //entao peao virou rei ou eh impossivel
    {
        return;
    }

    else if(visitado[H] == 1) //verifica se essa posicao no tabuleiro ja foi visitada
    {
        return;
    }
// printf("\nINICIANDO O FOR...");
    if(Contem_solucao(tabuleiro, H, CandidateX, CandidateY, peao, coord, P, 0))
    {
        visitado[H] = 1;//informando que este subconjunto já foi verificado

        /*int T;
        for(T=0;T < qtd_p; T++) {
          printf("\npiao -> %d",peao[T]);
        }*/
        //printf("\nENCONTROU UMA SOLUCAO PARA O SUBCONJUNTO DE H -> %d", H);
        //printf("\nATUALIZANDO PEOES...");
        Move_Pawn(P, peao, tabuleiro, &excede);//atualizando os peoes
        if(excede > 1)
        {
            return;
        }
        //printf("\nPEOES ATUALIZADOS");
        for(candidatos = 0; candidatos < DIMENSION; candidatos++)
        {
            if( (((H-1)/DIMENSION)+CandidateX[candidatos]) >= 0 &&
                    (((H-1)/DIMENSION)+CandidateX[candidatos]) < DIMENSION &&
                    ((H-1)%DIMENSION)+CandidateY[candidatos] >= 0 &&
                    ((H-1)%DIMENSION)+CandidateY[candidatos] < DIMENSION)
            {
                Busca_solucao(tabuleiro, peao, P-1, H+coord[candidatos],visitado,n_jogadas+1, menor_jogada, excede);
            }
        }
    }
    else
    {
        visitado[H] = 1;//informando que este subconjunto já foi verificado

        Move_Pawn(P, peao, tabuleiro, &excede);//atualizando os peoes
        if(excede > 1)
            return;
        for(candidatos = 0; candidatos < DIMENSION; candidatos++)
        {
            //printf("\nNAO ENCONTROU UMA SOLUCAO PARA O SUBCONJUNTO DE H -> %d", H);
            if( (((H-1)/DIMENSION)+CandidateX[candidatos]) >= 0 &&
                    (((H-1)/DIMENSION)+CandidateX[candidatos]) < DIMENSION &&
                    ((H-1)%DIMENSION)+CandidateY[candidatos] >= 0 &&
                    ((H-1)%DIMENSION)+CandidateY[candidatos] < DIMENSION)
            {
                //precisamos verificar se X e Y sao validos para este subconjunto
                /*if((((H-1)/DIMENSION)+CandidateX[candidatos]) >= 0 &&
                  (((H-1)/DIMENSION)+CandidateX[candidatos]) < DIMENSION &&
                  (H%DIMENSION-1)+CandidateY[candidatos] >= 0 &&
                  (H%DIMENSION-1)+CandidateY[candidatos] < DIMENSION)*/
                Busca_solucao(tabuleiro, peao, P, H+coord[candidatos],visitado, n_jogadas+1, menor_jogada,excede);
            }
        }
    }
    //printf("\nFINALIZOU O FOR.");
}

void Imprime_Tabuleiro(int **Tab)
{
    int i, j;
    for(i =0; i < DIMENSION; i++)
    {
        for(j=0; j < DIMENSION; j++)
        {
            printf("%d", Tab[i][j]);
        }
        printf("\n");
    }
}

int main(void)
{
    int **tabuleiro;
    int P, H,i;
    int *peao;
    int *visitado, num_jogada = 0, min_Step, excede = 0;

    tabuleiro = Cria_Tabuleiro();

    //primeiro ler num peoes
    //printf("\nDigite a quantidade de peoes -> ");
    scanf("%d",&P);
    qtd_p = P;
    peao = (int *)calloc (P,sizeof(int));
    visitado = (int*)malloc(sizeof(int)*65); // Vetor auxiliar para guardar as posições já vistadas

    //preencher o tabuleiro
    preenche_tabuleiro(tabuleiro, visitado);

    //printf("Digite as posicoes dos peoes:");
    for(i=0; i < P; i++)
    {
        //printf("\nDigite a posicao do peao %d -> ",i+1);
        scanf("%d",&peao[i]);
    }
    /*for(i=0;i < P; i++) {
      printf("\npiao -> %d",peao[i]);
    }*/
// printf("\nDigite a posicao do cavalo -> ");
    //ler posicao do cavalo
    scanf("%d", &H);
// printf("\nINICIANDO A BUSCA...");
    min_Step =10;
    Busca_solucao(tabuleiro,peao,  P,  H, visitado, num_jogada, &min_Step, excede);
// printf("\nBUSCA FINALIZADA");
    if (min_Step < 10)
    {
        printf ("%d", min_Step);
    }
    else
    {
        printf("\nimpossible");
    }
    //imprimindo tabuleiro
    //Imprime_Tabuleiro(tabuleiro);

    return 0;
}
