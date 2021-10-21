//Luiza Peres  RA: 140491

#include <stdio.h>

#include <math.h>



int AtingiuaMeta(int atual, int meta)

{

    if(atual >= meta)
    {
        return 1;
    }

    return 0;

}

int Ceil(double num)
{

    int num_aux;

    num_aux = num;

    if(num - num_aux > 0.0)
    {
        return num_aux +1;

    }
    return num;
}


int main()
{

    int N,M,i, resultado, dias, Meta_atingida = 0, soma;
    int D[30],verifica,count=0,novaMeta;
    double media,nova_media;



    //printf( "Digite a quantidade inicial de usuários e a quantidade de usuários a ser alcançada");
    scanf("%d %d", &N, &M);

    novaMeta = M - N;
    soma = 0;



    for(i = 0; i < 30; i++)
    {

        //printf("Digite são apresentados em ordem cronológica, representando as quantidades de novos usuários registrados nos últimos 30 dias");

        scanf("%d", &D[i]);
        soma += D[i];// total do vetor

        /*	if(AtingiuaMeta(soma + N, M) && !Meta_atingida) {

        		resultado = i + 1;

        		Meta_atingida = 1;

        	}*/
    }

    i = 0;
    dias = 0;

    while(!AtingiuaMeta(N, M))
    {

        media = Ceil( soma/ 30.0);
        //printf("MEDIA %.0f\n", media);

        N += media;
        nova_media = AtingiuaMeta(N, M);
        soma += media; // atualizando a soma;
        soma -= D[i]; //mantendo os 30 elementos atualizando o valor total
        D[i] = media; // atualizando posição



        if(i < 29)
        {
            i++;

        }
        else if( i>=29)
        {
            i=0;
        }
        else
        {
            i++;
        }

        dias++;

    }
    printf("%d", dias);

    return 0;

}

