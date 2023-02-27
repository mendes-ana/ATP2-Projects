#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <pthread.h>
#define MAX 200000

int auxSort;

void calcula_tempo(struct timeval *start, struct timeval *end)
{
    double tempo_levado= (end->tv_sec - start->tv_sec) + ((end->tv_usec - start->tv_usec)/1000000.0);
    printf("tempo de ordenação: %lf segundos\n",tempo_levado);
}

void create(int *vet)
{
    int i, seed;

    puts("\nQual o valor da semente de geração aleatória (entre 0 e 1000)?\n");
    scanf("%d",&seed);
    srand(seed);

    for (i=0; i < MAX; i++)
       vet[i] = rand( )%100000;
}

void *insertion(void *vet) //realiza o insertion com os threads
{
    int *v = (int *)vet;
    int aux, j;

    for(int i = 0; i<auxSort; i++)
    {
        aux = v[i];
        j = i-1;
        while(j >= 0 && v[j] > aux)
        {
            v[j+1] = v[j];
            j--;   
        }

        v[j+1] = aux;
    }
}

void insertionNT(int *v) //faz o insertion sem os threads
{
    int aux, j;

    for(int i = 0; i<auxSort; i++)
    {
        aux = v[i];
        j = i-1;
        while(j >= 0 && v[j] > aux)
        {
            v[j+1] = v[j];
            j--;   
        }

        v[j+1] = aux;
    }
}

void preenche_Merge(int *vet, int **pArray, int n, int t, int elements) //preenche e faz o merge 
{
    int *v1, *v2, *v3, *v4, *v5, *v6, *v7, *v8, *vAux; 
    int j = 0; 
    pthread_t trd1, trd2, trd3, trd4, trd5, trd6, trd7, trd8;

    //Caso sejam 2 divisões
    if(n == 2)
    {
        auxSort = elements;
        v1 = pArray[0];
        v2 = pArray[1];
        
        for(int i = 0; i < elements; i++)
        {
            v1[i] = vet[j];
            j++;
        }

        for(int i = 0; i < elements; i++)
        {
            v2[i] = vet[j];
            j++;
        }

        if(t == 0) // 0 Threads
        {
            insertionNT(v1);
            insertionNT(v2);
        }
        
        else // 2 Threads
        {
            //Cria os threads que vão ser usados
            pthread_create(&trd1, NULL, insertion, v1);
            pthread_create(&trd2, NULL, insertion, v2);

            //Chama os threads
            pthread_join(trd1, NULL);
            pthread_join(trd2, NULL);
        }
    }

    //4 Divisões
    else if(n == 4)
    {
        auxSort = elements;
        v1 = pArray[0];
        v2 = pArray[1];
        v3 = pArray[2];
        v4 = pArray[3];

        for(int i = 0; i < elements; i++)
        {
            v1[i] = vet[j];
            j++;
        }

        for(int i = 0; i < elements; i++)
        {
            v2[i] = vet[j];
            j++;
        }

        for(int i = 0; i < elements; i++)
        {
            v3[i] = vet[j];
            j++;
        }

        for(int i = 0; i < elements; i++)
        {
            v4[i] = vet[j];
            j++;
        }

        if(t == 0) // 0 Threads
        {
            insertionNT(v1);
            insertionNT(v2);
            insertionNT(v3);
            insertionNT(v4);
        }

        else if(t == 2) // 2 Threads
        {
            pthread_create(&trd1, NULL, insertion, v1);
            pthread_create(&trd2, NULL, insertion, v2);
            pthread_join(trd1, NULL);
            pthread_join(trd2, NULL);
            pthread_create(&trd1, NULL, insertion, v3);
            pthread_create(&trd2, NULL, insertion, v4);
            pthread_join(trd1, NULL);
            pthread_join(trd2, NULL);
        }

        else // 4 Threads
        {
            pthread_create(&trd1, NULL, insertion, v1);
            pthread_create(&trd2, NULL, insertion, v2);
            pthread_create(&trd3, NULL, insertion, v3);
            pthread_create(&trd4, NULL, insertion, v4);
            pthread_join(trd1, NULL);
            pthread_join(trd2, NULL);
            pthread_join(trd3, NULL);
            pthread_join(trd4, NULL);
        }
    }

    //8 Divisões
    else
    {
        auxSort = elements;
        v1 = pArray[0];
        v2 = pArray[1];
        v3 = pArray[2];
        v4 = pArray[3];
        v5 = pArray[4];
        v6 = pArray[5];
        v7 = pArray[6];
        v8 = pArray[7];

        for(int i = 0; i < elements; i++)
        {
            v1[i] = vet[j];
            j++;
        }

        for(int i = 0; i < elements; i++)
        {
            v2[i] = vet[j];
            j++;
        }

        for(int i = 0; i < elements; i++)
        {
            v3[i] = vet[j];
            j++;
        }

        for(int i = 0; i < elements; i++)
        {
            v4[i] = vet[j];
            j++;
        }

        for(int i = 0; i < elements; i++)
        {
            v5[i] = vet[j];
            j++;
        }

        for(int i = 0; i < elements; i++)
        {
            v6[i] = vet[j];
            j++;
        }

        for(int i = 0; i < elements; i++)
        {
            v7[i] = vet[j];
            j++;
        }

        for(int i = 0; i < elements; i++)
        {
            v8[i] = vet[j];
            j++;
        }

        if(t == 0) // 0 Threads
        {
            insertionNT(v1);
            insertionNT(v2);
            insertionNT(v3);
            insertionNT(v4);
            insertionNT(v5);
            insertionNT(v6);
            insertionNT(v7);
            insertionNT(v8);
        }

        else if(t == 2) // 2 Threads
        {
            pthread_create(&trd1, NULL, insertion, v1);
            pthread_create(&trd2, NULL, insertion, v2);
            pthread_join(trd1, NULL);
            pthread_join(trd2, NULL);
            pthread_create(&trd1, NULL, insertion, v3);
            pthread_create(&trd2, NULL, insertion, v4);
            pthread_join(trd1, NULL);
            pthread_join(trd2, NULL);
            pthread_create(&trd1, NULL, insertion, v5);
            pthread_create(&trd2, NULL, insertion, v6);
            pthread_join(trd1, NULL);
            pthread_join(trd2, NULL);
            pthread_create(&trd1, NULL, insertion, v7);
            pthread_create(&trd2, NULL, insertion, v8);
            pthread_join(trd1, NULL);
            pthread_join(trd2, NULL);
        }

        else if(t == 4) // 4 Threads
        {
            pthread_create(&trd1, NULL, insertion, v1);
            pthread_create(&trd2, NULL, insertion, v2);
            pthread_create(&trd3, NULL, insertion, v3);
            pthread_create(&trd4, NULL, insertion, v4);
            pthread_join(trd1, NULL);
            pthread_join(trd2, NULL);
            pthread_join(trd3, NULL);
            pthread_join(trd4, NULL);
            pthread_create(&trd1, NULL, insertion, v5);
            pthread_create(&trd2, NULL, insertion, v6);
            pthread_create(&trd3, NULL, insertion, v7);
            pthread_create(&trd4, NULL, insertion, v8);
            pthread_join(trd1, NULL);
            pthread_join(trd2, NULL);
            pthread_join(trd3, NULL);
            pthread_join(trd4, NULL);
        }

        else // 8 Threads
        {
            pthread_create(&trd1, NULL, insertion, v1);
            pthread_create(&trd2, NULL, insertion, v2);
            pthread_create(&trd3, NULL, insertion, v3);
            pthread_create(&trd4, NULL, insertion, v4);
            pthread_create(&trd5, NULL, insertion, v5);
            pthread_create(&trd6, NULL, insertion, v6);
            pthread_create(&trd7, NULL, insertion, v7);
            pthread_create(&trd8, NULL, insertion, v8);
            pthread_join(trd1, NULL);
            pthread_join(trd2, NULL);
            pthread_join(trd3, NULL);
            pthread_join(trd4, NULL);
            pthread_join(trd5, NULL);
            pthread_join(trd6, NULL);
            pthread_join(trd7, NULL);
            pthread_join(trd8, NULL);   
        }
    }

    vAux = (int*)malloc(sizeof(int)*MAX);
    j = 0; //Reinicializa o valor de j para poder adicionar os valores no vAux

    if(n == 2)
    {
        for(int i = 0; i < elements; i++)
        {
            vAux[j] = v1[i];
            j++;
        }

        for(int i = 0; i < elements; i++)
        {
            vAux[j] = v2[i];
            j++;
        }
    }

    else if(n == 4)
    {
       for(int i = 0; i < elements; i++)
        {
            vAux[j] = v1[i];
            j++;
        }

        for(int i = 0; i < elements; i++)
        {
            vAux[j] = v2[i];
            j++;
        }

        for(int i = 0; i < elements; i++)
        {
            vAux[j] = v3[i];
            j++;
        }

        for(int i = 0; i < elements; i++)
        {
            vAux[j] = v4[i];
            j++;
        } 
    }

    else
    {
       for(int i = 0; i < elements; i++)
        {
            vAux[j] = v1[i];
            j++;
        }

        for(int i = 0; i < elements; i++)
        {
            vAux[j] = v2[i];
            j++;
        }

        for(int i = 0; i < elements; i++)
        {
            vAux[j] = v3[i];
            j++;
        }

        for(int i = 0; i < elements; i++)
        {
            vAux[j] = v4[i];
            j++;
        }

        for(int i = 0; i < elements; i++)
        {
            vAux[j] = v5[i];
            j++;
        }

        for(int i = 0; i < elements; i++)
        {
            vAux[j] = v6[i];
            j++;
        }

        for(int i = 0; i < elements; i++)
        {
            vAux[j] = v7[i];
            j++;
        }

        for(int i = 0; i < elements; i++)
        {
            vAux[j] = v8[i];
            j++;
        } 
    }

    //Faz o insertion no novo vetor auxiliar criado a partir da junção dos anteriores
    auxSort = MAX;
    insertion(vAux);

    //Preenche o vetor original com os dados do novo pós ordenação
    for(int i = 0; i < MAX; i++)
    {
        vet[i] = vAux[i];
    }

    //free dos vetores auxiliares referente 
    if(n == 2)
    {
        free(vAux);
        free(v1);
        free(v2);
    }

    else if(n == 4)
    {
        free(vAux);
        free(v1);
        free(v2);
        free(v3);
        free(v4);
    }

    else
    {
        free(vAux);
        free(v1);
        free(v2);
        free(v3);
        free(v4);
        free(v5);
        free(v6);
        free(v7);
        free(v8);
    }

    printf("\nOrdenação concluida!\n");
}

void mergeSort(int *vet, int n, int t) //n = numero de divisões, t = numero de threads
{
    int *arrays[n]; //vetor de ponteiros para armazenar o vetor em pedações distintos

    for(int i = 0; i < n; i++)
        arrays[i] = (int*)malloc(sizeof(int)*(MAX/n)); //Aloca a quantidade de memória para cada novo array

    preenche_Merge(vet ,arrays, n, t, (MAX/n)); //Chama a função de preenchimento do array
}


void escreveVet(int *vet) //escreve o vetor ordenado em um arquivo
{
    FILE *fp;

        fp = fopen("vetor_ordenado.txt", "w+");
        for(int i = 0; i < MAX; i++)
            fprintf(fp, "%d\n", vet[i]);
        
        fclose(fp);
}

int main()
{
    int vet[MAX]; //Vetor a ser ordenado

    struct timeval comeco, fim; //Structs que armazenam o tempo de execução
    
    int op=1; //Entrada do usuario

    while (op != 0)
    {
        printf("1 - Vetor dividido em 2 partes, sem usar threads\n");
        printf("2 - Vetor dividido em 2 partes, usando 2 threads\n");
        printf("3 - Vetor dividido em 4 partes, sem usar threads\n");
        printf("4 - Vetor dividido em 4 partes, usando 2 threads\n");
        printf("5 - Vetor dividido em 4 partes, usando 4 threads\n");
        printf("6 - Vetor dividido em 8 partes, sem usar threads\n");
        printf("7 - Vetor dividido em 8 partes, usando 2 threads\n");
        printf("8 - Vetor dividido em 8 partes, usando 4 threads\n");
        printf("9 - Vetor dividido em 8 partes, usando 8 threads\n");
        printf("0 - Sair\n");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            create(vet);
            gettimeofday(&comeco, NULL); //Inicio da contagem de tempo
            mergeSort(vet, 2, 0);
            gettimeofday(&fim, NULL); //Fim da contagem de tempo
            calcula_tempo(&comeco, &fim);
            break;
        
        case 2:
            create(vet);
            gettimeofday(&comeco, NULL); //Inicio da contagem de tempo
            mergeSort(vet, 2, 2);
            gettimeofday(&fim, NULL); //Fim da contagem de tempo
            calcula_tempo(&comeco, &fim);
            break;

        case 3:
            create(vet);
            gettimeofday(&comeco, NULL); //Inicio da contagem de tempo
            mergeSort(vet, 4, 0);
            gettimeofday(&fim, NULL); //Fim da contagem de tempo
            calcula_tempo(&comeco, &fim);
            break;

        case 4:
            create(vet);
            gettimeofday(&comeco, NULL); //Inicio da contagem de tempo
            mergeSort(vet, 4, 2);
            gettimeofday(&fim, NULL); //Fim da contagem de tempo
            calcula_tempo(&comeco, &fim);
            break;

        case 5:
            create(vet);
            gettimeofday(&comeco, NULL); //Inicio da contagem de tempo
            mergeSort(vet, 4, 4);
            gettimeofday(&fim, NULL); //Fim da contagem de tempo
            calcula_tempo(&comeco, &fim);
            break;

        case 6:
            create(vet);
            gettimeofday(&comeco, NULL); //Inicio da contagem de tempo
            mergeSort(vet, 8, 0);
            gettimeofday(&fim, NULL); //Fim da contagem de tempo
            calcula_tempo(&comeco, &fim);
            break;

        case 7:
            create(vet);
            gettimeofday(&comeco, NULL); //Inicio da contagem de tempo
            mergeSort(vet, 8, 2);
            gettimeofday(&fim, NULL); //Fim da contagem de tempo
            calcula_tempo(&comeco, &fim);
            break;

        case 8:
            create(vet);
            gettimeofday(&comeco, NULL); //Inicio da contagem de tempo
            mergeSort(vet, 8, 4);
            gettimeofday(&fim, NULL); //Fim da contagem de tempo
            calcula_tempo(&comeco, &fim);
            break;

        case 9:
            create(vet);
            gettimeofday(&comeco, NULL); //Inicio da contagem de tempo
            mergeSort(vet, 8, 8);
            gettimeofday(&fim, NULL); //Fim da contagem de tempo
            calcula_tempo(&comeco, &fim);
            break;

        }
        escreveVet(vet);
        
    }

    return 0;
}
