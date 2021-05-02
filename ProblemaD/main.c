#include <stdio.h>
int myrand ();
int checkInArray(int carro, int * montra);
int LRU(int * carros,int qtdCarros,int cap);
int RAND(int *carros, int qtdCarros,int cap);
int FIFO(int * carros,int qtdCarros, int cap);
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
    printf("Rand : %d\n",RAND(carros,qtdCarros,4));
    printf("FIFO : %d\n",FIFO(carros,qtdCarros,4));
    printf("IDEAL : %d\n",IDEAL(carros,qtdCarros,4));
    return 0;
}


int myrand () 
{
    static int valor = 45;
    valor = 73 * valor + 2713;
    valor = (valor % 101);
    return (valor%4);
}

int checkInArray(int carro, int * montra)
{
    for(int i = 0 ; i < 4;i++)
    {
        if(carro == montra[i])
            return i;
    }
    return -1;
}

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
            for(int x = exist; x < 4;x++)
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
int RAND(int *carros, int qtdCarros,int cap)
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
int FIFO(int * carros,int qtdCarros, int cap)
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

int IDEAL(int * carros,int qtdCarros,int cap)
{
    int montra[] = {1,2,3,4},temp[4];
    int troca=0;
    int exist=-1,flag1=0,flag2=0,flag3=0,pos,max;
    
    for(int i = 0;i< qtdCarros;i++)
    {
        flag1 = flag2 = 0;
        for(int j =0;j<4;j++)
        {
            if(montra[j]==carros[i])
            {
                flag1 = flag2 = 1;
                break;
            }
        }

        if(flag2==0)
        {
            flag3=0;

            for(int j =0;j<4;j++)
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
            for(int j =0;j< 4;j++)
            {
                if(temp[j]==-1)
                {
                    pos=j;
                    flag3=1;
                    break;
                }
            }
            if(flag3==0)
            {
                max=temp[0];
                pos=0;
                for(int j =1;j< 4;j++)
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
