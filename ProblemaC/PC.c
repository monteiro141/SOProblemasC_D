#include<stdio.h>
#include <string.h>
#include <stdlib.h>

//20segundos
//A 2 5
//B 5 8
typedef struct{
    int PID;
    char NomeProcesso;//A
    int numeroInstancia;
    int tempoExecucao; //2
    int periodo;//5
    int tempoExecucaoRestante;
    int periodoRestante;
}BLOCO;

typedef struct
{
    int PID;
    char instancia[200];
}INSTANCIAS;
int numInstancias;
int numProcessos;

void comecarInstancias(INSTANCIAS I[][200],BLOCO processos[numProcessos])
{
    int i;
    numInstancias=numProcessos;
    for(i=0;i<numProcessos;i++)
    {
        sprintf((*I)[i].instancia,"%c-%d",processos[i].NomeProcesso,1);
        (*I)[i].PID=i;
    }
}

int verificarInstancias(INSTANCIAS I[][200],char instanciaAtual[5])
{
    int existe=0,i;
    for(i=0; i < numInstancias;i++)
    {
        if(strcmp((*I)[i].instancia,instanciaAtual)==0)
        {
            return i;
        }
    }
    if(existe==0 && numInstancias !=0)
    {
        (*I)[numInstancias].PID = (*I)[numInstancias-1].PID +1;
        strcpy((*I)[numInstancias].instancia,instanciaAtual);
        numInstancias++;
    }else if (existe==0 && numInstancias ==0)
    {
        (*I)[numInstancias].PID = 0;
        strcpy((*I)[numInstancias].instancia,instanciaAtual);
        numInstancias++;
    }
    return numInstancias-1;
}

void resetar(BLOCO processos[][numProcessos],int tempoAtual)
{
    int i;
    for(i=0;i<numProcessos;i++)
    {
        if((*processos)[i].periodoRestante==0 && (*processos)[i].tempoExecucaoRestante==0 && (tempoAtual) !=0)
        {
            (*processos)[i].numeroInstancia++;
            (*processos)[i].tempoExecucaoRestante = (*processos)[i].tempoExecucao;
            (*processos)[i].periodoRestante = (*processos)[i].periodo;
        }
    }
}
//-1 se for idle e >= 0 se tiver processos para fazer
int compararProcessos(BLOCO processos[numProcessos])
{
    int i;
    int indiceMenor=0;
    int menor=processos[0].tempoExecucaoRestante;
    for(i=1;i<numProcessos;i++)
    {
        //printf("menor: %d vs %d pR\n",menor,processos[i].periodoRestante);
        /*if((menor==0 && processos[i].tempoExecucaoRestante!=0) || (processos[indiceMenor].periodoRestante >= processos[i].periodoRestante && processos[i].tempoExecucaoRestante !=0))
        {
            //printf("Entrou\n");
            menor = processos[i].tempoExecucaoRestante;
            indiceMenor = i;
        }*/
        if(menor==0 || (processos[indiceMenor].periodoRestante >= processos[i].periodoRestante && processos[i].tempoExecucaoRestante >0))
        {
            menor = processos[i].tempoExecucaoRestante;
            indiceMenor = i;
        }
    }
    if(menor == 0)
        return -1;
    return indiceMenor;
}

int main(){
    int i,tempoTotal,u;
    float Carga=0;
    scanf("%d\n", &numProcessos);
    BLOCO processos[numProcessos];
    INSTANCIAS I[200];
    int falha=0;

    for(i=0;i<numProcessos;i++){
        
        scanf("%c %d %d\n", &processos[i].NomeProcesso, &processos[i].tempoExecucao, &processos[i].periodo);
        processos[i].numeroInstancia = 1;
        processos[i].tempoExecucaoRestante = processos[i].tempoExecucao;
        processos[i].periodoRestante = processos[i].periodo;
        processos[i].PID=i;
        Carga += ((float)processos[i].tempoExecucao/(float)processos[i].periodo);
    }
    printf("CARGA=%4.3f\n", Carga);
    scanf("%d\n",&tempoTotal); //20

    comecarInstancias(&I,processos);
    //char processoAnterior;
    int indiceAtual;
    for(i=0;i<tempoTotal;i++)
    {
        /*if(i>=0)
        {
            printf("Antes\n");
            printf("i: %d vs processo %c vs tempR %d vs perR %d\n",i,processos[0].NomeProcesso,processos[0].tempoExecucaoRestante,processos[0].periodoRestante);
            printf("i: %d vs processo %c vs tempR %d vs perR %d\n",i,processos[1].NomeProcesso,processos[1].tempoExecucaoRestante,processos[1].periodoRestante);
            printf("i: %d vs processo %c vs tempR %d vs perR %d\n",i,processos[2].NomeProcesso,processos[2].tempoExecucaoRestante,processos[2].periodoRestante);

        }*/
        char instancia[5];
        //Resetar os tempos
        resetar(&processos,i);
        //Comparar qual dos processos deve fazer
        indiceAtual = compararProcessos(processos);
        //printf("IND a: %d\n",indiceAtual);
        for(u=0;u<numProcessos;u++)
        {
            if(processos[u].periodoRestante > 0)
                processos[u].periodoRestante--;    
        }
        if(indiceAtual ==-1)
        {
            printf("T=%d IDLE\n",i);
        }else
        {
            //verificarInstancias(&I,processos[indiceAtual].NomeProcesso);
            if(processos[indiceAtual].tempoExecucaoRestante>0)
                processos[indiceAtual].tempoExecucaoRestante--;
            sprintf(instancia,"%c-%d",processos[indiceAtual].NomeProcesso,processos[indiceAtual].numeroInstancia);
            printf("T=%d PID=%d CPU=%s\n",i,I[verificarInstancias(&I,instancia)].PID,instancia);
        }
        /*if(i>=0)
        {
            printf("Depois\n");
            printf("i: %d vs processo %c vs tempR %d vs perR %d\n",i,processos[0].NomeProcesso,processos[0].tempoExecucaoRestante,processos[0].periodoRestante);
            printf("i: %d vs processo %c vs tempR %d vs perR %d\n",i,processos[1].NomeProcesso,processos[1].tempoExecucaoRestante,processos[1].periodoRestante);
            printf("i: %d vs processo %c vs tempR %d vs perR %d\n",i,processos[2].NomeProcesso,processos[2].tempoExecucaoRestante,processos[2].periodoRestante);

        }*/
        for(u=0;u<numProcessos;u++)
        {
            if(processos[u].periodoRestante == 0 && processos[u].tempoExecucaoRestante >0)
            {
                //printf("Teste falha: pR %d vs %d tR\n",processos[u].periodoRestante,processos[u].tempoExecucaoRestante);
                falha=1;
            }
        }
    }
    if(falha==0)
        printf("COMPETENTE\n");
    else
        printf("FALHA\n");
}