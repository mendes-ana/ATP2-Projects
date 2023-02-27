/* Busca sequencial com vetor B desordenado.
Busca sequencial com vetor B ordenado pelo bubble sort.
Busca binária com vetor B ordenado pelo bubble sort.
Busca ponderada com vetor B ordenado pelo bubble sort.
Busca sequencial com vetor B ordenado pelo insertion sort.
Busca binária com vetor B ordenado pelo insertion sort.
Busca ponderada com vetor B ordenado pelo insertion sort.
Busca sequencial com vetor B ordenado pelo selection sort.
Busca binária com vetor B ordenado pelo selection sort.
Busca ponderada com vetor B ordenado pelo selection sort. */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h> 

/*void escreve_arquivo(double tp, int n)
{
    FILE *fp;
    fp= fopen("dados.txt", "a+");
    if(n == 1)
        fprintf(fp, "tempo total: %lf segundos\n",tp);
    else if(n == 2)
        fprintf(fp, "tempo de ordenação: %lf segundos\n",tp);
    else
        fprintf(fp, "tempo de busca: %lf segundos\n",tp);
    
    fclose(fp);
} */ //Função feita para armazenar os resultados em um arquivo no intuito de facilitar a coleta de dados

void calcula_tempo(struct timeval *start, struct timeval *end, int n)
{
    double tempo_levado= (end->tv_sec - start->tv_sec) + ((end->tv_usec - start->tv_usec)/1000000.0);
    
    if(n==2)
        printf("tempo de ordenação: %lf segundos\n",tempo_levado);
    
    else if(n==4)
        printf("tempo de busca: %lf segundos\n",tempo_levado);
        
    else
        printf("tempo total: %lf segundos\n",tempo_levado);

    //escreve_arquivo(tempo_levado, n);
}

void cria_vet(int *vetA, int *vetB)
{   
    int i, seed;
    puts("\nQual o valor da semente de geração aleatória (entre 0 e 1000)?");
    scanf("%d",&seed);
    srand(seed);
    for (i=0; i < 2000; i++)
       vetA[i] = rand( )%100000;

    for (i=0; i < 200000; i++)
       vetB[i] = rand( )%100000;
}

int ponderada(int *a, int *v, int tam, int n)
{
    int ini;
    int meio;
    int fim;
    int contador=0;
    int i=0;
    bool achado;

    for(int i=0; i<tam; i++)
    {
        ini = 0;
        fim = n-1;
        achado= false;
        while(ini <= fim && a[i]>= v[ini] && a[i]  <= v[fim] && !achado) //condições para saida do loop de forma que ele para quando encontra um elemento
        {
            meio = ini + (((double)(fim - ini) / (v[fim] - v[ini])) * (a[i] -v[ini]));
            
            if(a[i] < v[meio])
            {
                fim = meio - 1;
            
            }
            else if(a[i] > v[meio])
            {
                ini = meio + 1;
            }
            else
            {
                contador++;
                achado= true;
            }
        }
    }
    return contador;

}

int binaria (int *a, int *v, int tam, int n)
{
    
    int contador = 0;
    bool achado;
    int inf;
    int sup;
    int meio;

    for(int i=0; i<tam; i++)
    {
        achado = false;
        inf = 0;
        sup = n-1;
        meio= (inf + sup) / 2;

        while (inf<=sup && !achado) //condição de parada para quando a busca encontra um elemento que pertence então segue para o proximo
        {
            
            if (a[i]==v[meio])
            {
                contador ++;
                achado = true;
            }
            else if (a[i]<v[meio])
            {
                sup= meio-1;
                
            }
            else
            {
                inf= meio+1;
                
            }
            meio = (inf + sup) / 2;
        }
    }
    return contador;  
}

//percorre o vetor todo em busca do elemento
int sequencial(int *a, int *v, int tam, int n)
{
    int contador = 0;
    int j=0;
    bool achado;
    while(j<tam)
    {
        achado = false;
        for (int i=0; i<n && !achado; i++) //para no momento em que encontra um elemento e segue para o próximo
        {
            if(v[i]==a[j])
            {
                contador++;
                achado = true;
            }
        }
        j++;
    }
    return contador;
}

void bubble_srt(int *v, int n)
{

    int aux;
    for(int i=0; i<n; i++)
    {  
      bool rusbeh = false;
       for(int j=0; j<n-i-1; j++)
       {
          if(v[j]>v[j+1])
          {
            rusbeh = true;
             aux = v[j+1];
             v[j+1] = v[j];
             v[j] = aux;
          }
       }
      // se nenhuma troca aconteceu em uma execução então o vetor esta organizado
      if(!rusbeh){ 
         return; 
      } 
   }
}

void insertion_srt(int *v, int n)
{
    int aux;
    int j;
    for (int i = 1; i < n; i++) { 
        aux = v[i]; 
        j = i - 1; 
  
        /* move os elementos do vetor maior que o aux para uma posição a frente da sua atual */
        while (j >= 0 && v[j] > aux) { 
            v[j + 1] = v[j]; 
            j = j - 1; 
        } 
        v[j + 1] = aux; 
    } 
} 

void selection_srt(int *v, int n)
{
    for (int i = 0; i < n - 1; i++)  
    { 
  
        // loop variavel : Elementos até  
        // a[i - 1] estar organizado. 
  
        // acha o menor elemento do  
        // v[i] para v[n - 1]. 
        int min = i; 
        for (int j = i + 1; j < n; j++) 
            if (v[min] > v[j]) 
            min = j; 
  
        // Move menor elemento para atual i. 
        int key = v[min]; 
        while (min > i)  
        { 
            v[min] = v[min - 1]; 
            min--; 
        } 
              
        v[i] = key; 
    } 
} 

int main()
{
    int a[2000];
    int b[200000];
    int op;
    int result;
    bool sair = false;
    struct timeval start, end, stotal, etotal;
    double tempo_levado;
    


    while(!sair)
    {
        int a[2000];
        int b[200000];
        cria_vet(a,b);

        printf("\n<1>Busca sequencial com vetor B desordenado.\n<2>Busca sequencial com vetor B ordenado pelo bubble sort.\n");
        printf("<3>Busca binária com vetor B ordenado pelo bubble sort.\n");
        printf("<4>Busca ponderada com vetor B ordenado pelo bubble sort.\n<5>Busca sequencial com vetor B ordenado pelo insertion sort.\n");
        printf("<6>Busca binária com vetor B ordenado pelo insertion sort.\n<7>Busca ponderada com vetor B ordenado pelo insertion sort.\n");
        printf("<8>Busca sequencial com vetor B ordenado pelo selection sort.\n<9>Busca binária com vetor B ordenado pelo selection sort.\n");
        printf("<10>Busca ponderada com vetor B ordenado pelo selection sort.\n<11>Sair\n");
        scanf("%d",&op);
        switch (op)
        {
            case 1:
                gettimeofday(&start, NULL); //começa a contar o tempo 
                result = sequencial(a, b, 2000, 200000); 
                gettimeofday(&end, NULL); //termina de contar o tempo
                calcula_tempo(&start, &end, 4); //calcula o tempo
                printf("Foram encontrados: %d elementos",result);
                break;
            
            case 2:
                gettimeofday(&stotal, NULL); //começa a contar o tempo total
                gettimeofday(&start, NULL); //começa a contar o tempo para a ordenação
                bubble_srt(b, 200000); 
                gettimeofday(&end, NULL);  //termina de contar o tempo para a ordenação
                calcula_tempo(&start, &end, 2); //calcula o tempo da ordenação
                gettimeofday(&start, NULL); //começa a contar o tempo da busca
                result = sequencial(a, b, 2000, 200000); 
                gettimeofday(&end, NULL); //termina de contar o tempo da busca
                calcula_tempo(&start, &end, 4); //calcula o tempo da busca
                gettimeofday(&etotal, NULL); //termina de contar o tempo total
                calcula_tempo(&stotal, &etotal, 1); //calcula o tempo total
                printf("Foram encontrados: %d elementos",result);
                break;

            case 3:
                gettimeofday(&stotal, NULL);
                gettimeofday(&start, NULL);
                bubble_srt(b, 200000);
                gettimeofday(&end, NULL); 
                calcula_tempo(&start, &end, 2);
                gettimeofday(&start, NULL);
                result = binaria(a, b, 2000, 200000); 
                gettimeofday(&end, NULL); 
                calcula_tempo(&start, &end, 4);
                gettimeofday(&etotal, NULL);
                calcula_tempo(&stotal, &etotal, 1);
                printf("Foram encontrados: %d elementos",result);
                break;

            case 4:
                gettimeofday(&stotal, NULL);
                gettimeofday(&start, NULL);
                bubble_srt(b, 200000);
                gettimeofday(&end, NULL); 
                calcula_tempo(&start, &end, 2);
                gettimeofday(&start, NULL);
                result = ponderada(a, b, 2000, 200000);
                gettimeofday(&end, NULL); 
                calcula_tempo(&start, &end, 4);
                gettimeofday(&etotal, NULL);
                calcula_tempo(&stotal, &etotal, 1);
                printf("Foram encontrados: %d elementos",result);
                break;

            case 5:
                gettimeofday(&stotal, NULL);
                gettimeofday(&start, NULL);
                insertion_srt(b, 200000);
                gettimeofday(&end, NULL); 
                calcula_tempo(&start, &end, 2);
                gettimeofday(&start, NULL);
                result = sequencial(a, b, 2000, 200000);
                gettimeofday(&end, NULL); 
                calcula_tempo(&start, &end, 4);
                gettimeofday(&etotal, NULL);
                calcula_tempo(&stotal, &etotal, 1);
                printf("Foram encontrados: %d elementos",result);
                break;

            case 6:
                gettimeofday(&stotal, NULL);
                gettimeofday(&start, NULL);
                insertion_srt(b, 200000); 
                gettimeofday(&end, NULL); 
                calcula_tempo(&start, &end, 2);
                gettimeofday(&start, NULL);
                result = binaria(a, b, 2000, 200000);
                gettimeofday(&end, NULL); 
                calcula_tempo(&start, &end, 4);
                gettimeofday(&etotal, NULL);
                calcula_tempo(&stotal, &etotal, 1);
                printf("Foram encontrados: %d elementos",result);
                break;

            case 7:
                gettimeofday(&stotal, NULL);
                gettimeofday(&start, NULL);
                insertion_srt(b, 200000); 
                gettimeofday(&end, NULL); 
                calcula_tempo(&start, &end, 2);
                gettimeofday(&start, NULL);
                result = ponderada(a, b, 2000, 200000); 
                gettimeofday(&end, NULL); 
                calcula_tempo(&start, &end, 4);
                gettimeofday(&etotal, NULL);
                calcula_tempo(&stotal, &etotal, 1);
                printf("Foram encontrados: %d elementos",result);
                break;

            case 8:
                gettimeofday(&stotal, NULL);
                gettimeofday(&start, NULL);
                selection_srt(b, 200000); 
                gettimeofday(&end, NULL); 
                calcula_tempo(&start, &end, 2);
                gettimeofday(&start, NULL);
                result = sequencial(a, b, 2000, 200000);
                gettimeofday(&end, NULL); 
                calcula_tempo(&start, &end, 4);
                gettimeofday(&etotal, NULL);
                calcula_tempo(&stotal, &etotal, 1);
                printf("Foram encontrados: %d elementos",result);
                break;

            case 9:
                gettimeofday(&stotal, NULL);
                gettimeofday(&start, NULL);
                selection_srt(b, 200000); 
                gettimeofday(&end, NULL); 
                calcula_tempo(&start, &end, 2);
                gettimeofday(&start, NULL);
                result = binaria(a, b, 2000, 200000); 
                gettimeofday(&end, NULL); 
                calcula_tempo(&start, &end, 4);
                gettimeofday(&etotal, NULL);
                calcula_tempo(&stotal, &etotal, 1);
                printf("Foram encontrados: %d elementos",result);
                break;

            case 10:
                gettimeofday(&stotal, NULL);
                gettimeofday(&start, NULL);
                selection_srt(b, 200000); 
                gettimeofday(&end, NULL); 
                calcula_tempo(&start, &end, 2);
                gettimeofday(&start, NULL);
                result = ponderada(a, b, 2000, 200000); 
                gettimeofday(&end, NULL); 
                calcula_tempo(&start, &end, 4);
                gettimeofday(&etotal, NULL);
                calcula_tempo(&stotal, &etotal, 1);
                printf("Foram encontrados: %d elementos",result);
                break;
            
            case 11:
                sair = true;
        }
    }
    
}