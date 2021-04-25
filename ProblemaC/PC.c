#include<stdio.h>

typedef struct{
    int PID;
    char NomeProcesso;
    int numeroInstancia;
    int tempoExecucao;
    int periodo;
    int tempoInicio;
    int tempoChegada;
    int tempoDuracaoInicial;
    int tempoCPURestante;
}BLOCO;

int main(){
    int numProcessos;
    float Carga=0;
    scanf("%d\n", &numProcessos);
    BLOCO processos[numProcessos];

    for(int i=0;i<numProcessos;i++){
        
        scanf("%c %d %d\n", &processos[i].NomeProcesso, &processos[i].tempoExecucao, &processos[i].periodo);
       
        Carga += ((float)processos[i].tempoExecucao/(float)processos[i].periodo);
    }

    

    printf("CARGA=%4.3f\n", Carga);

    

}