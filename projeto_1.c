/*Calculadora de números complexos
Disciplina: Algoritimos e técnicas de programação 2
Projeto 1
Professor: Aleardo Manacero Junior
Aluno: Ana Ligia Mendes */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//struct de complexos inseridos para as operações
struct opcomplex{
    float r;
    float im;
    char numplex[50];
}num[2];

//struct para armazenar
struct guardacomplex{
    float re;
    float ima;
    char numer[50];
}numg[2];

bool salvo=false;
char fnl[500]; //string final para concatenação



int main()
{
    int esclha, sn=1; //opção de entrada no menu e opção de seleção

    bool sair = false;

    //cabeçalho das funções
    void salvar();
    void imprimir(int a);
    void calculo();
    void calculosalv();



    while (sair==false)
    {
        esclha == 0;
        printf("\t\t\tCalculadora de complexos\n\n\n");
        printf("\t\tMenu\n\n");
        printf("<1>Armazenar os numeros em um vetor\n<2>Imprimir os numeros salvos no vetor\n<3>Realizar operações\n<4>Sair\n");
        scanf("%d",&esclha);

        if (esclha == 1)
        {
            salvar();
        }

        else if (esclha == 2)
        {
            imprimir(1);
        }
        else if (esclha == 3)
        {
            
            printf("Deseja utilizar os números salvos no vetor?\n");
            printf("<1>Sim\t<2>Não\n");
            scanf("%d",&sn);
            if (sn == 1 && salvo==false)
                printf("não existem numeros salvos\n");

            else if(sn == 1 && salvo==true)
                calculosalv();

            else if (sn == 2)
                calculo();

            else
                printf("erro! opção invalida\n");
            
                
        }

        else if (esclha == 4)
        {
            return 0;
        }
        else
            printf("\noperação invalida\n");
        
    }

    return 0;
}

void salvar()
{
    printf("digite o primeiro numero complexo em forma cartesiana (x+yi)\n");
    scanf("%s",numg[0].numer);
    setbuf(stdin, NULL);
    printf("digite o segundo numero complexo em forma cartesiana (x+yi)\n");
    scanf("%s",numg[1].numer);
    setbuf(stdin, NULL);
    salvo=true;
}

void imprimir(int det)
{
    if (det==1)
    {
        if(salvo==true)
        {
            printf("primeiro numero: %s\n",numg[0].numer);
            printf("segundo numeros: %s\n",numg[1].numer);
        }
        else
        {
            printf("não existem numeros salvos\n");
        }
    }

    else if (det==2)
    {
        printf("\nResultado:%s\n",fnl);
    }
        
}

void calculo()
{
    int op, volt=2; //escolha da operação e para voltar
    float vcr, vcc; //variavel de calculo real(vcr) e variavel de calculo complexo(vcc) para armazenar
    char spr[50]; //string para reais
    char spc[50]; //para complexos
    float vcd; //variavel de calculo do denominador
    char sd [50]; //string para o denominador

    while(volt==2)
    {
        strcpy(fnl, "");
        //armazenamento dos numeros que serão usados nos calculos
        printf("digite o primeiro numero complexo em forma cartesiana (x+yi)\n");
        scanf("%s",num[0].numplex);
        printf("digite o segundo numero complexo em forma cartesiana (x+yi)\n");
        scanf("%s",num[1].numplex);
        //transformar string em numeros
        sscanf(num[0].numplex, "%f %f", &num[0].r, &num[0].im);
        sscanf(num[1].numplex, "%f %f", &num[1].r, &num[1].im);
        //escolha de operações
        printf("\n\n\tEscolha a operação\n\n");
        printf("<1>Adição\n<2>Subtração\n<3>Multiplicação\n<4>Divisão\n");
        scanf("%d",&op);

        if(op==1)
        {
            //realiza o calculo
            vcr= num[0].r + num[1].r;
            vcc= num[0].im + num[1].im;
            //transforma de volta em string para exibção
            gcvt(vcr, 45, spr);
            gcvt(vcc, 45, spc);
            //concatenação
            if (vcr==0 && vcc==0)
                strcat(fnl, "0");
            
            else
            {
                strcat(fnl, spr);
                if(vcc > 0)
                {
                    strcat(fnl, "+");
                    strcat(fnl, spc);
                    strcat(fnl, "i");
                }

                else
                {
                    strcat(fnl, spc);
                    strcat(fnl, "i");
                }
            }
            imprimir(2);
        }

        else if(op==2)
        {
            vcr= num[0].r - num[1].r;
            vcc= num[0].im - num[1].im;

            gcvt(vcr, 45, spr);
            gcvt(vcc, 45, spc);

            if (vcr==0 && vcc==0)
                strcat(fnl, "0");
            
            else
            {
                strcat(fnl, spr);
                if(vcc > 0)
                {
                    strcat(fnl, "+");
                    strcat(fnl, spc);
                    strcat(fnl, "i");
                }

                else
                {
                    strcat(fnl, spc);
                    strcat(fnl, "i");
                }
        
            }
            imprimir(2);
        }

        else if(op==3)
        {
            vcr= (num[0].r*num[1].r)-(num[0].im*num[1].im);
            vcc= (num[0].r*num[1].im)+(num[0].im*num[1].r);

            gcvt(vcr, 45, spr);
            gcvt(vcc, 45, spc);

            if (vcr==0 && vcc==0)
                strcat(fnl, "0");
            
            else
            {
                strcat(fnl, spr);
                if(vcc > 0)
                {
                    strcat(fnl, "+");
                    strcat(fnl, spc);
                    strcat(fnl, "i");
                }

                else
                {
                    strcat(fnl, spc);
                    strcat(fnl, "i");
                }
            }
            imprimir(2);
        }
        
        else if(op==4)
        {
            vcd= (num[1].r*num[1].r)+((num[1].im * (num[1].im * -1))*-1);
            if (vcd==0)
                printf("denominador=0, nao é possivel realizar a divisão\n");

            else
            {
                vcr= (num[0].r*num[1].r)+((num[0].im*(num[1].im*-1))*-1);
                vcc= (num[0].r*(num[1].im*-1)) + (num[0].im*num[1].r);

                gcvt(vcd, 45, sd);
                gcvt(vcr, 45, spr);
                gcvt(vcc, 45, spc);

                if (vcr==0 && vcc==0)
                {
                    strcat(fnl, "0");
                    strcat(fnl, "/");
                    strcat(fnl, sd);
                }

                else
                {
                    strcat(fnl, spr);
                    if(vcc > 0)
                    {
                        strcat(fnl, "+");
                        strcat(fnl, spc);
                        strcat(fnl, "i");
                        strcat(fnl, "/");
                        strcat(fnl, sd);
                    }

                    else
                    {
                        strcat(fnl, spc);
                        strcat(fnl, "i");
                        strcat(fnl, "/");
                        strcat(fnl, sd);
                    }            
                }
            }
            imprimir(2);
        }
        else
            printf("opção invalida\n");

        printf("\n\n<1>voltar ao menu\n<2>fazer outra operação\n");
        scanf("%d",&volt);
    }

}

void calculosalv()
{

    int ops, volts=2; //escolha da operação e para voltar
    float vcrs, vccs; //variavel de calculo real(vcr) e variavel de calculo complexo(vcc) para armazenar
    char sprs[50]; //string para reais
    char spcs[50]; //para complexos
    float vcds; //variavel de calculo do denominador
    char sds [50]; //string para o denominador

    while(volts==2)
    {
        strcpy(fnl, "");
        //transformar string em numeros
        sscanf(numg[0].numer, "%f %f", &numg[0].re, &numg[0].ima);
        sscanf(numg[1].numer, "%f %f", &numg[1].re, &numg[1].ima);
        //escolha de operações
        printf("\n\n\tEscolha a operação\n\n");
        printf("<1>Adição\n<2>Subtração\n<3>Multiplicação\n<4>Divisão\n");
        scanf("%d",&ops);

        if(ops==1)
        {
            //realiza o calculo
            vcrs= numg[0].re + numg[1].re;
            vccs= numg[0].ima + numg[1].ima;
            //transforma de volta em string para exibção
            gcvt(vcrs, 45, sprs);
            gcvt(vccs, 45, spcs);
            //concatenação
            if (vcrs==0 && vccs==0)
            {
                strcat(fnl, "0");
            }

            else
            {
                strcat(fnl, sprs);
                if(vccs > 0)
                {
                    strcat(fnl, "+");
                    strcat(fnl, spcs);
                    strcat(fnl, "i");
                }

                else
                {
                    strcat(fnl, spcs);
                    strcat(fnl, "i");
                }
            }
            imprimir(2);
        }

        else if(ops==2)
        {
            vcrs= numg[0].re - numg[1].re;
            vccs= numg[0].ima - numg[1].ima;

            gcvt(vcrs, 45, sprs);
            gcvt(vccs, 45, spcs);

            if(vcrs==0 && vccs==0)
            {
                strcat(fnl, "0");
            }
            else
            {
                strcat(fnl, sprs);
                if(vccs > 0)
                {
                    strcat(fnl, "+");
                    strcat(fnl, spcs);
                    strcat(fnl, "i");
                }

                else
                {
                    strcat(fnl, spcs);
                    strcat(fnl, "i");
                }
            }
            imprimir(2);
        }

        else if(ops==3)
        {
            vcrs= (numg[0].re*numg[1].re)-(numg[0].ima*numg[1].ima);
            vccs= (numg[0].re*numg[1].ima)+(numg[0].ima*numg[1].re);

            gcvt(vcrs, 45, sprs);
            gcvt(vccs, 45, spcs);

            if(vcrs==0 && vccs==0)
            {
                strcat(fnl, "0");
            }

            else
            {
                strcat(fnl, sprs);
                if(vccs > 0)
                {
                    strcat(fnl, "+");
                    strcat(fnl, spcs);
                    strcat(fnl, "i");
                }

                else
                {
                    strcat(fnl, spcs);
                    strcat(fnl, "i");
                }
            }
            imprimir(2);
        }
        
        else if(ops==4)
        {
            vcds= (numg[1].re*numg[1].re)+((numg[1].ima * (numg[1].ima * -1))*-1);;
            if (vcds==0)
                printf("denominador=0, nao é possivel realizar a divisão\n");

            else
            {
                vcrs= (numg[0].re*numg[1].re)+((numg[0].ima*(numg[1].ima*-1))*-1);
                vccs= (numg[0].re*(numg[1].ima*-1)) + (numg[0].ima*numg[1].re);

                gcvt(vcds, 45, sds);
                gcvt(vcrs, 45, sprs);
                gcvt(vccs, 45, spcs);

                if(vcrs==0 && vccs==0)
                {
                    strcat(fnl, "0");
                    strcat(fnl, "/");
                    strcat(fnl, sds);
                }

                else
                {
                    strcat(fnl, sprs);
                    if(vccs > 0)
                    {
                        strcat(fnl, "+");
                        strcat(fnl, spcs);
                        strcat(fnl, "i");
                        strcat(fnl, "/");
                        strcat(fnl, sds);
                    }

                    else
                    {
                        strcat(fnl, spcs);
                        strcat(fnl, "i");
                        strcat(fnl, "/");
                        strcat(fnl, sds);
                    }            
                }
                imprimir(2);
            }
        }
        else
            printf("opção invalida");

        printf("\n\n<1>voltar ao menu\n<2>fazer outra operação\n");
        scanf("%d",&volts);
    }

    
}