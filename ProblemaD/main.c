#include <stdio.h>
/**
 * Problema D - O Cliente é um chato
 * Alexandre Monteiro, 44149
 * Bruno Monteiro, 43994
 * Manuel Carvalho, 43760
 * 
 * 4    
 * 1
 * 2
 * 3
 * 4
 * 
 * 4 - Quantidade de números a ler
 * 1,2,3,4 - Números a ler; 
 * 
 */

/*
* Protótipos das funções
*/
int myrand ();
int checkInArray(int carro, int * montra);
int LRU(int * carros,int qtdCarros,int cap);
int RAND(int *carros, int qtdCarros);
int FIFO(int * carros,int qtdCarros);
int IDEAL(int * carros,int qtdCarros,int cap);

int main(void)
{
    int qtdCarros;
    scanf("%d",&qtdCarros);
    int carros[qtdCarros];
    for(int i=0;i<qtdCarros;i++)
    {
        scanf("%d",&carros[i]);
    }
    printf("LRU : %d\n",LRU(carros,qtdCarros,4));
    printf("Rand : %d\n",RAND(carros,qtdCarros));
    printf("FIFO : %d\n",FIFO(carros,qtdCarros));
    printf("IDEAL : %d\n",IDEAL(carros,qtdCarros,4));
    return 0;
}

/**
 * Função disponibilizada pelo professor
 * @return um número random
 */
int myrand () 
{
    static int valor = 45;
    valor = 73 * valor + 2713;
    valor = (valor % 101);
    return (valor%4);
}

/**
 * Verifica se um determinado carro está na montra
 * @param carro inteiro que representa um carro
 * @param montra vetor com os carros que estão na montra
 * @return -1 caso não esteja na montra ou a sua posição caso esteja na montra
 */
int checkInArray(int carro, int * montra)
{
    for(int i = 0 ; i < 4;i++)
    {
        if(carro == montra[i])
            return i;
    }
    return -1;
}

/**
 * Least Recently Used- Verifica se o carro existe na montra caso não exista retira o que se encontra na primeira
 * posição da montra e avança os restantes uma posição e, por fim adiciona esse carro na última posição da montra.
 * @param carros vetor com os numeros lidos do input
 * @param qtdCarros quantidade existente de carros(quantidade de números lidos no input)
 * @param cap numero máximo de carros que a montra pode ter
 * @return número de trocas feito
 */
int LRU(int * carros,int qtdCarros,int cap)
{
    int montra[] = {1,2,3,4};
    int troca=0;
    int exist=-1;
    for(int i = 0 ;i < qtdCarros ; i++)
    {
        if((exist=checkInArray(carros[i],montra))==-1)
        {
            montra[0] = montra[1];
            montra[1] = montra[2];
            montra[2] = montra[3];
            montra[3] = carros[i];
            troca++;
        }else
        {
            for(int x = exist; x < cap;x++)
            {
                if(x == 3)
                {
                    montra[3] = carros[i];
                }else
                {
                    montra[x] = montra[x+1];
                }
            }
        }
    }
    return troca;
}

/**
 * Random - Verifica se um carro existe na montra. Caso não exista escolhe uma posição aleatória para o colocar e
 * coloca-o nessa posição
 * @param carros vetor com os numeros lidos do input
 * @param qtdCarros quantidade existente de carros(quantidade de números lidos no input)
 * @return número de trocas feito
 */
int RAND(int *carros, int qtdCarros)
{
    int montra[] = {1,2,3,4};
    int troca=0;
    int exist=-1;
    for(int i=0;i<qtdCarros;i++)
    {
        if((exist=checkInArray(carros[i],montra))==-1)
        {
            montra[myrand()] = carros[i];
            troca++;
        }
    }
    return troca;
}
/**
 * FIFO (First In First Out) - Verifica se um carro existe na montra. Caso não exista remove o que se encontra na primeira
 * posição e coloca o carro na ultima posição da montra
 * @param carros vetor com os numeros lidos do input
 * @param qtdCarros quantidade existente de carros(quantidade de números lidos no input)
 * @return número de trocas feito
 */
int FIFO(int * carros,int qtdCarros)
{
    int montra[] = {1,2,3,4};
    int troca=0;
    int exist=-1;
    for(int i=0;i<qtdCarros;i++)
    {
        if((exist=checkInArray(carros[i],montra))==-1)
        {
            montra[0] = montra[1];
            montra[1] = montra[2];
            montra[2] = montra[3];
            montra[3] = carros[i];
            troca++;
        }
    }

    return troca;
}

/**
 * IDEAL - Verifica se o carro existe na montra. Caso não esteja determina qual dos quatro carros da montra está mais afastado e
 * coloca o que está a ser comparado na posição do carro mais afastado.
 * @param carros vetor com os numeros lidos do input
 * @param qtdCarros quantidade existente de carros(quantidade de números lidos no input)
 * @return número de trocas feito
 */
int IDEAL(int * carros,int qtdCarros,int cap)
{
    int montra[] = {1,2,3,4},temp[4];
    int troca=0;
    int exist1=0, exist2=0,pos,max;
    
    for(int i = 0;i< qtdCarros;i++)
    {
        exist1=0;
        for(int j =0;j<cap;j++)
        {
            if(montra[j]==carros[i])
            {
                exist1 = 1;
                break;
            }
        }

        if(exist1==0)
        {
            exist2=0;

            for(int j =0;j<cap;j++)
            {
                temp[j]=-1;
                for(int k=i+1;k<qtdCarros;k++)
                {
                    if(montra[j]==carros[k])
                    {
                        temp[j]=k;
                        break;
                    }
                }
            }
            for(int j =0;j< cap;j++)
            {
                if(temp[j]==-1)
                {
                    pos=j;
                    exist2=1;
                    break;
                }
            }
            if(exist2==0)
            {
                max=temp[0];
                pos=0;
                for(int j =1;j< cap;j++)
                {
                    if(temp[j]> max)
                    {
                        max=temp[j];
                        pos=j;
                    }
                }
            }
            montra[pos]=carros[i];
            troca++;
        }
    }
    
    return troca;
}
