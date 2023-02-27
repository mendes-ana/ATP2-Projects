#include <stdio.h>
#include <stdlib.h>
#define tam 100000
#define bi 1000000000

typedef struct biggo{ 
    int high; 
    int low; 
    }BigInt;



void create_array(BigInt *v)
{
    int i, seed;

    puts("Qual o valor da semente de geração aleatória (entre 0 e 1000)?");
    scanf("%d",&seed);
    srand(seed);
    for (i=0; i < tam; i++)
    {
       v[i].high = rand()%bi;
       v[i].low = rand()%bi;
    }
}

int pivo(int inicio, int fim, BigInt v[])
{
    BigInt pivo = v[fim];
    int i = inicio -1, j;
    BigInt aux;
    int a;
    
    for(j = inicio; j <= fim -1; j++)
    {
        if(pivo.high > v[j].high)
            a = v[j].high - pivo.high; 
        
        else if(pivo.high < v[j].high) 
            a = v[j].high - pivo.high;

        else if(pivo.high == v[j].high) 
            a = v[j].low - pivo.low;
        //printf("%d\t%d\n",v[0].high,v[0].low);
        if(a < 0)
        { 
            i++; // soma um ao i para realizar a troca corretamente entre a posição salva e a posição em que J parou
            aux = v[i];
            v[i] = v[j];
            v[j] = aux;
        }
    }

    aux = v[i+1]; // ao chegar aqui, teremos o indice de um valor que é menor do que o pivo, e o próximo dele, um valor que é maior do que o pivo, 
    v[i+1] = v[fim];                    //então realizamos a troca entre o valor do pivo que está em high e o valor do elemento que é maior que ele
    v[fim] = aux;
    
return(i+1); // retorna a posição onde o pivo se encontra
}

void quick(BigInt v[], int inicio, int fim){
    
    if(inicio < fim) // caso sejam iguais, realizamos todas as trocas possiveis, ou caso fim seja menor que inicio, não tem sentido lógico.
    {
        int pos = pivo(inicio,fim,v);
        quick(v,inicio,pos - 1); // ordena agora a partir do elemento anterior ao pivo
        quick(v,pos + 1,fim); // começa a ordenar a partir o elemento posterior ao pivo

    }

return;
}


int main()
{
    BigInt v[tam];
    create_array(v);
    quick(v, 0, tam-1);
    FILE *fp;
    fp = fopen("vetor.txt","w");
    for(int i=0; i<tam; i++)
    {   
        fprintf (fp,"%d%09d\n",v[i].high,v[i].low);
    }
    fclose(fp);
    return 0;
}