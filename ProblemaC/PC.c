#include<stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Problema C - Escalonamento por EDF
 * Alexandre Monteiro, 44149
 * Bruno Monteiro, 43994
 * Manuel Carvalho, 43760
 * 
 * 3    
 * A 1 4
 * B 2 6
 * c 3 8
 * 25
 * 
 * 3 - Numero Processos
 * A - Nome Processo;
 * 1 - Tempo de Execução;
 * 4 - Período 
 * 
 */
/*
* Struct com a informação de cada bloco a ser processado
*/
typedef struct{
    int PID;
    char NomeProcesso;//A
    int numeroInstancia;
    int tempoExecucao; //2
    int periodo;//5
    int tempoExecucaoRestante;
    int periodoRestante;
    int instanciado;
}BLOCO;

/*
* Struct com todas o PID e a respetiva instância 
*/
typedef struct
{
    int PID;
    char instancia[5];
}INSTANCIAS;

int numInstancias;
int numProcessos;
int processoAnterior;


/**
 * Atribui as várias instâncias ao respetivo processo. 
 * @param I Struct com todas as PID e respetiva Instãncia
 * @param processos Conjunto de todos os processos
 */
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

/**
 * Cria uma nova instância
 * @param I struct com todas as PID e respetiva Instância
 * @param processos Conjunto de todos os processos
 * @param instanciaAtual Instância atual
 */
void criarInstancias(INSTANCIAS I[][200],char instanciaAtual[5])
{
    int existe=0,i;
    for(i=0;i<numInstancias;i++)
    {
        if(strcmp((*I)[i].instancia,instanciaAtual)==0)
        {
            existe=1;
        }
    }
    if(existe==0)
    {
        numInstancias++;
        strcpy((*I)[numInstancias-1].instancia,instanciaAtual);
        (*I)[numInstancias-1].PID = (*I)[numInstancias-2].PID + 1; 
    }
}

/**
 * Vai verificar se o PID existe e devolve o valor em relação a isso
 * @param I struct com todas as PID e respetiva Instância
 * @param instanciaAtual Instância atual
 * @return O indice de uma instância ou -1 caso não exista
 */
int devolverPID(INSTANCIAS I[200],char instanciaAtual[5])
{
    int i;
    for(i=0;i<numInstancias;i++)
    {
        if(strcmp(I[i].instancia,instanciaAtual)==0)
            return i;
    }
    return -1;
}

/**
 * Quando o seu periodo chega a zero, ou seja precisamos de usar um processo novo.
 * Desta forma, criamos uma nova instância para um processo
 * @param processos Conjunto de todos os processos
 * @param tempoAtual tempo em que nos encontramos (e.g T=0)
 * @param I struct com todas as PID e respetiva Instância
 */
void resetar(BLOCO processos[][numProcessos],int tempoAtual, INSTANCIAS I[][200])
{
    int i;
    char instancia[5];
    for(i=0;i<numProcessos;i++)
    {
        if((*processos)[i].periodoRestante==0 && (*processos)[i].tempoExecucaoRestante==0 && (tempoAtual) !=0)
        {
            (*processos)[i].numeroInstancia++;
            (*processos)[i].tempoExecucaoRestante = (*processos)[i].tempoExecucao;
            (*processos)[i].periodoRestante = (*processos)[i].periodo;
            if((*processos)[i].instanciado==0)
            {
                sprintf(instancia,"%c-%d",(*processos)[i].NomeProcesso,(*processos)[i].numeroInstancia);
                criarInstancias(I,instancia);
            }
            (*processos)[i].instanciado=0;
        }else if((*processos)[i].periodoRestante==0 && (*processos)[i].tempoExecucaoRestante > 0 && (tempoAtual) !=0)
        {
            (*processos)[i].instanciado=1;
            sprintf(instancia,"%c-%d",(*processos)[i].NomeProcesso,(*processos)[i].numeroInstancia+1);
            criarInstancias(I,instancia);
        }
    }
}

/**
 *Compara processos para saber qual irá processar.
 * @param processos Conjunto de todos os processos
 * @return -1 se ficar em IDLE ou >=0 para ser usado como indice na estrutura de processos
*/
int compararProcessos(BLOCO processos[numProcessos])
{
    int i;
    int indiceMenor=0;
    int menor=processos[0].tempoExecucaoRestante;
    for(i=1;i<numProcessos;i++)
    {
        if(menor==0)
        {
            menor = processos[i].tempoExecucaoRestante;
            indiceMenor = i;
        }else
        if(processos[indiceMenor].periodoRestante >= processos[i].periodoRestante && processos[i].tempoExecucaoRestante >0)
        {
            if(processos[indiceMenor].periodoRestante == processos[i].periodoRestante)
            {
                if(processoAnterior == -1)
                {
                    if(processos[indiceMenor].periodo - processos[indiceMenor].periodoRestante > processos[i].periodo - processos[i].periodoRestante )
                    {
                        menor = processos[indiceMenor].tempoExecucaoRestante;
                        indiceMenor = indiceMenor;
                    }else
                    {
                        menor = processos[i].tempoExecucaoRestante;
                        indiceMenor = i;
                    }
                }else
                {
                    if(indiceMenor == processoAnterior)
                    {
                        menor = processos[indiceMenor].tempoExecucaoRestante;
                        indiceMenor = indiceMenor;
                    }else if (i == processoAnterior)
                    {
                        menor = processos[i].tempoExecucaoRestante;
                        indiceMenor = i;
                    }else
                    {
                       if(processos[indiceMenor].periodo - processos[indiceMenor].periodoRestante > processos[i].periodo - processos[i].periodoRestante )
                        {
                            menor = processos[indiceMenor].tempoExecucaoRestante;
                            indiceMenor = indiceMenor;
                        }else
                        {
                            menor = processos[i].tempoExecucaoRestante;
                            indiceMenor = i;
                        } 
                    }
                }
            }else{
                menor = processos[i].tempoExecucaoRestante;
                indiceMenor = i;
            }
        }
    }
    if(menor == 0)
        return -1;
    return indiceMenor;
}

int main(){

    int i,tempoTotal,u;
    float Carga=0;
    processoAnterior = -1;
    scanf("%d\n", &numProcessos);
    BLOCO processos[numProcessos];
    INSTANCIAS I[200];
    int falha=0;

    //Inicia primeiramente os processos
    for(i=0;i<numProcessos;i++){
        scanf("%c %d %d\n", &processos[i].NomeProcesso, &processos[i].tempoExecucao, &processos[i].periodo);
        processos[i].numeroInstancia = 1;
        processos[i].tempoExecucaoRestante = processos[i].tempoExecucao;
        processos[i].periodoRestante = processos[i].periodo;
        processos[i].PID=i;
        processos[i].instanciado=0;

        //Cálculo da Carga
        Carga += ((float)processos[i].tempoExecucao/(float)processos[i].periodo);
    }
    //Mostra a Carga
    printf("CARGA=%4.3f\n", Carga);

    //Lê o tempo total de execução
    scanf("%d\n",&tempoTotal); 

    comecarInstancias(&I,processos);
    
    int indiceAtual;
    //Vai percorrer o tempo total
    for(i=0;i<tempoTotal;i++)
    {
        char instancia[5];

        //Resetar os tempos
        resetar(&processos,i,&I);

        //Comparar qual dos processos deve fazer
        indiceAtual = compararProcessos(processos);
        if(indiceAtual ==-1)
        {
            printf("T=%d IDLE\n",i);
        }else
        {
            processoAnterior = indiceAtual;
            //Tira o tempo de execução quando se usa um dado processo
            if(processos[indiceAtual].tempoExecucaoRestante>0)
                processos[indiceAtual].tempoExecucaoRestante--;
            //Fazer a String da instância
            sprintf(instancia,"%c-%d",processos[indiceAtual].NomeProcesso,processos[indiceAtual].numeroInstancia);
            printf("T=%d PID=%d CPU=%s\n",i,I[devolverPID(I,instancia)].PID,instancia);
        }
        
        //Reduz a todos os processos um segundo no periodo restante
        for(u=0;u<numProcessos;u++)
        {
            if(processos[u].periodoRestante > 0)
                processos[u].periodoRestante--;    
        }

        //Verifica-se se existe alguma falha
        for(u=0;u<numProcessos;u++)
        {
            if(processos[u].periodoRestante == 0 && processos[u].tempoExecucaoRestante >0)
            {
                falha=1;
            }
        }
    }


    if(falha==0)
        printf("COMPETENTE\n");
    else
        printf("FALHA\n");
}