#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


typedef struct data{
	int dia;
	int mes;
	int ano;
}d; //struct para guardar dia mês e ano
typedef struct carr{
    int id;
    char placa[9];
    char fab[64];
    char mod[64];
    char disp;
    char cat[64];
    int lug;
    char ar;
    int km;
    d data[2];
    char g_data;
    int next;

}carro; //struct usada para a lista onde next aponta para o próximo indice do vetor de structs
bool controle= false;




void ler_arq(FILE *p, int *h, carro *pc, int *cad) //struct responsavel por ler o aquivo
{
    char guard[300]; //string para guardar cada linha lida
    p= fopen("listacarros.dat", "r"); //abertura do arquivo para leitura
    while(!feof(p)) //laço de repetição para ler o arquivo até o fim
    {
    	fgets (guard, 200 , p);
    	sscanf(guard, "%d %s %s %s", &pc[(*cad)].id, pc[(*cad)].placa, pc[(*cad)].fab, pc[(*cad)].mod); //separa as partes de cada linha
    	strcpy(guard, " ");
    	
		fgets (guard, 200 , p);
    	sscanf(guard, "%c %s %d %c", &pc[(*cad)].disp, pc[(*cad)].cat, &pc[(*cad)].lug, &pc[(*cad)].ar); //separa as partes de cada linha
    	strcpy(guard, " ");
    	
    	fgets (guard, 200 , p);
    	sscanf(guard, "%d", &pc[(*cad)].km); //separa as partes de cada linha
    	strcpy(guard, " ");
    	


    	fgets (guard, 200 , p);
        sscanf(guard, "%d%*c%d%*c%d", &pc[(*cad)].data[0].dia, &pc[(*cad)].data[0].mes, &pc[(*cad)].data[0].ano); //armazena a primeira parte das datas
        sscanf(guard, "%*s%d%*c%d%*c%d", &pc[(*cad)].data[1].dia, &pc[(*cad)].data[1].mes, &pc[(*cad)].data[1].ano); //armazena a primeira parte das datas
        strcpy(guard, " ");	
    	
    	//adiciona -1 ao next de cada item lido
    	pc[(*cad)].next= -1;
    	
        //verifica se é de fato o final da lista e se não for ele substitui pelo indice de seu proximo
    	if((*cad) > 0)
    		pc[(*cad)-1].next= *cad;
    		
    	(*cad)++;	
		
    	
	}
	
    //retira a leitura a mais feita pelo feof
	(*cad)--;
	pc[(*cad)-1].next= -1;
    
    return;

}

int achar_ind(int n, carro *pc, int *cabeca, int *cont) //função que busca o indice
{
	int aux= *cabeca;
	int loop=0;
	bool achado= false;
	while(!achado)
	{
		if(n!= -1 && n==pc[pc[aux].next].next)
		{
			achado= true;
			return pc[aux].next;		
		}
		else if(n==-1 && pc[aux].next==-1)
		{
			achado= true;
			return aux;	
		}
		else if(*cont<loop)
			{
				achado= true;
				return -2;
			}
		
		aux= pc[aux].next;	
		loop++;
		
		
	}
}


void imprimir(int a, int *h, carro *p, int *cont) //função responsavel pela impressão
{
	bool tail= false;
	int guard_fim;
	int i=*h;
	
	guard_fim= achar_ind(a, p, h, cont); //chama a função achar_ind para encontrar onde o looping deve terminar baseado em uma variavel "a" enviada por quem chama a função de impressão
    
	while(!tail)
    {
    	printf("%d %s %s %s\n", p[i].id, p[i].placa, p[i].fab, p[i].mod);
    	printf("%c %s %d %c\n", p[i].disp, p[i].cat, p[i].lug, p[i].ar);
   		printf("%d\n", p[i].km);
		printf("%d/%d/%d  ", p[i].data[0].dia, p[i].data[0].mes, p[i].data[0].ano);
        printf("%d/%d/%d\n", p[i].data[1].dia, p[i].data[1].mes, p[i].data[1].ano);
    	printf("\n\n");
    	if(i == guard_fim || i>guard_fim)
    		tail= true;
    	i= p[i].next;
	}
	
}



int achar_ID(int n, carro *pc, int *cabeca, int *cont) //função responsavel por encontrar o ID caminhando pela lista
{
	int aux= *cabeca;
	int loop=0;
	bool achado= false;
	while(!achado)
	{
		if(n==pc[aux].id)
		{
			achado= true;
			return aux; //a função retorna o indice do id
				
		}
		if(*cont==loop)
		{
			achado= true;
			return -2; //caso não encontrado
		}
		
		aux= pc[aux].next;	
		loop++;
		
		
	}
}

int compara_data(carro *p, int j, int dia, int mes, int ano) //função que realiza a comparação de datas
{
		if(ano>p[j].data[1].ano)
			return 1;
		else if((ano == p[j].data[1].ano) && (mes>p[j].data[1].mes))
			return 1;
		else if((ano == p[j].data[1].ano) && (mes == p[j].data[1].mes) && (dia>p[j].data[1].dia))
			return 1; //retorna 1 onde uma data adicionada precisa ser maior que a presente
        else if((ano == p[j].data[1].ano) && (mes == p[j].data[1].mes) && (dia==p[j].data[1].dia))
            return 2; //retorna 2 em casos onde é necessario que as datas sejam iguais
		else
			return -2;
	
}

void achar_cat(char *p_busq, carro *pc, int *cabeca, int *cont, int d, int m, int a) //função responsavem por buscar uma categoria baseada em uma data
{
	bool achei_tds= false;
	int loop=0;
	int i= *cabeca;
	int n_achei=0;
    controle= false;
	while(!achei_tds)
	{

		if(strcmp(pc[i].cat, p_busq)==0 && compara_data(pc, i, d, m, a)==1 && pc[i].disp=='S') //verifica se a categoria é igual, a data compativel e a siponibilidade
		{
            loop++;
			imprimir(i, &i, pc, cont);
			
        
		}
        else if(strcmp(pc[i].cat, p_busq)==0 && compara_data(pc, i, d, m, a)==2 && pc[i].disp=='S')
		{
			loop++;
            imprimir(i, &i, pc, cont);
			
		}
			
		else if(loop>=(*cont)) //condição de saida
		{
			achei_tds= true;
		}
		
		else
		{
			n_achei++;
			loop++;	
		}
		i= pc[i].next;
	}

	if(n_achei==loop)
    {
    
		printf("Nenhum correspondente encontrado\n");
        controle= true;
    }
}

int pega_cat(carro *p, int *con, int *cab) //função resposavel por pegar as categorias para a função Listar carros de uma determinada categoria em uma determinada data
{
	char busq_cat[64];
	char dat[11];
	char *p_busq_cat= busq_cat;
	char *p_dat= dat;
	int op_busq_cat;
	int d_c, m_c, a_c;
	printf("Qual categoria deseja buscar?:\n<1>Compacto\n<2>Médio\n<3>Grande\n<4>SUV\n<5>Minivan\n");
	scanf("%d",&op_busq_cat);
	printf("Indique a data que deseja buscar:");
	scanf("%s",dat);
	sscanf(dat, "%d%*c%d%*c%d", &d_c, &m_c, &a_c);
	setbuf(stdin, NULL);
	switch(op_busq_cat)
	{
		case 1:
			strcpy(busq_cat, "Compacto");
		break;
		
		case 2:
			strcpy(busq_cat, "Médio");
		break;
		
		case 3:
			strcpy(busq_cat, "Grande");
		break;
		
		case 4:
			strcpy(busq_cat, "SUV");
		break;
		
		case 5:
			strcpy(busq_cat, "Minivan");
		break;
	}
	achar_cat(p_busq_cat, p, cab, con, d_c, m_c, a_c); //chama a função para verificar a categoria, data e disponibilidade
}



void inserir(carro *p, int *con, int *cab) //função que insere novo elemento na lista
{                                          //*con é um contador de espaços usados no vetor +1 para verificar onde sera adicionado o proximo
	int op_cat;
	int op_disp;
	int op_ar;
	int scr;
	
	printf("ID do carro a ser adicionado: ");
	scanf("%d",&p[(*con)].id); 
	printf("\n");
	printf("Placa do carro a ser adicionado: ");
	scanf("%s",p[(*con)].placa);
	setbuf(stdin, NULL);
	printf("\n");
	printf("Fabricante do carro a ser adicionado: ");
	scanf("%s",p[(*con)].fab);
	setbuf(stdin, NULL);
	printf("\n");
	printf("Modelo do carro a ser adicionado: ");
	scanf("%s",p[(*con)].mod);
	setbuf(stdin, NULL);
	printf("\n");
	printf("O carro esta disponivel para aluguel?:\n<1>Sim\n<2>Não\n ");
	scanf("%d",&op_disp);
	switch(op_disp)
	{
		case 1:
			p[(*con)].disp= 'S';
		break;
		
		case 2:
			p[(*con)].disp= 'N';
		break;
	}
	printf("\n");
	printf("Categoria do carro a ser adicionado:\n<1>Compacto\n<2>Médio\n<3>Grande\n<4>SUV\n<5>Minivan\n"); //para evitar erros, disponibilizei as opção para o usuario selecionar
	scanf("%d",&op_cat);
	switch(op_cat)
	{
		case 1:
			strcpy(p[(*con)].cat, "Compacto");
		break;
		
		case 2:
			strcpy(p[(*con)].cat, "Médio");
		break;
		
		case 3:
			strcpy(p[(*con)].cat, "Grande");
		break;
		
		case 4:
			strcpy(p[(*con)].cat, "SUV");
		break;
		
		case 5:
			strcpy(p[(*con)].cat, "Minivan");
		break;
	}
	printf("\n");
	printf("Quantidade de lugares que o carro possui: ");
	scanf("%d",&p[(*con)].lug);
	printf("\n");
	printf("O carro possui ar condicionado?:\n<1>Sim\n<2>Não\n");
	scanf("%d",&op_ar);
	switch(op_ar)
	{
		case 1:
			p[(*con)].ar= 'S';
		break;
		
		case 2:
			p[(*con)].ar= 'N';
		break;
	}
	printf("\n");
	printf("Quantidade de quilometros rodados pelo carro: ");
	scanf("%d",&p[(*con)].km);
	printf("\n");
	for(int s=0; s<2; s++) //o novo elemento inicia com a reserva zerada
	{
		p[(*con)].data[s].dia=0; p[(*con)].data[s].mes=0; p[(*con)].data[s].ano=0;
	}
	
	scr= achar_ind(-1, p, cab, con); //adiciona -1 ao final do novo elemento e muda o "next" do que era -1 anteriormente
	p[scr].next = *con;
	p[(*con)].next= -1;
	
	(*con)++;
	
	
	return;
	
}

void remocao(carro *p, int *cab, int *con)
{
	int hlp= *cab;
	int id_remov;
	int b, auxiliar, loop=0;
	bool removido=false;
	printf("Digite o ID do carro que deseja remover: ");
	scanf("%d",&id_remov);
	b= achar_ID(id_remov, p, cab, con);
	while(!removido)
	{
		if(p[b].next == p[*cab].next)
		{
			//remoção da cabeça
			*cab= p[b].next;
			(*con)--;
			removido= true;
		}
		else if(p[b].next == -1)
		{
            //remoção do final
			p[achar_ind(b, p, cab, con)].next=-1;
			(*con)--;
			removido= true;
		}
		
		else if(achar_ID(id_remov, p, cab, con)==-2)
		{
            //verifica se existe o ID que esta tentando remover
			printf("nenhum correspondente encontrado");
			removido= true;
		}
		else
		{
            //remoção no meio
			p[achar_ind(b, p, cab, con)].next = p[b].next;
			(*con)--;
			removido= true;
		}
		
		hlp=p[hlp].next;
		loop++;
	}
	
}

void pega_data_hoje(carro *pc, int *cont, int *h) //função que pega data do sistema com time.h
{
	int d_atual, m_atual, a_atual;
    bool todos= false;
    int loop=0;
    int n_achei=0;
    int control= *h;
	time_t data_hoje;
	struct tm * timeinfo;
	time(&data_hoje);
	timeinfo = localtime(&data_hoje);
	d_atual = timeinfo->tm_mday;
    m_atual = (timeinfo->tm_mon)+1;
    a_atual = (timeinfo->tm_year)+1900;
    printf("Data de hoje identificada: %d/%d/%d \n",d_atual, m_atual, a_atual);
    //verifica se está disponivel para alugar e mostra os que estão
    while(!todos)
    {

    	if(compara_data(pc, control, d_atual, m_atual, a_atual)==1 && pc[control].disp=='S')
    	{
            imprimir(control, &control, pc, cont);
            loop++;

		}
        else if(loop>=(*cont))
            todos= true;

        else
        {
            n_achei++;
            loop++;
        }
        control= pc[control].next;
        
        
    }
    if(n_achei==loop)
        printf("Nenhum correspondente encontrado\n");
}

void verificar_dev(carro *p, int *con, int *h) //verifica a data de devolução a partir de um ID digitado pelo usuario
{
    int id_busca;
    int guard;
    printf("Digite o ID do carro:");
    scanf("%d",&id_busca);
    guard= achar_ID(id_busca, p, h, con);
    printf("\n\n\n%d\n\n\n", guard);
    printf("O carro deverá ser devolvido em %d/%d/%d\n",p[guard].data[1].dia, p[guard].data[1].mes, p[guard].data[1].ano);
}

void fazer_reserv(carro *pc, int *cont, int *h)  //efetua a reserva alterando os valores da data na struct
{
    int op_reserv;
    char aux[64];
    char *p_aux= aux;
    char dat_aux[64];
    int d_i[2], m_i[2], a_i[2];
    int aux_id, aqui;
    printf("Qual categoria deseja reservar?:\n<1>Compacto\n<2>Médio\n<3>Grande\n<4>SUV\n<5>Minivan\n");
    scanf("%d",&op_reserv);
	switch(op_reserv)
	{
		case 1:
			strcpy(aux, "Compacto");
		break;
		
		case 2:
			strcpy(aux, "Médio");
		break;
		
		case 3:
			strcpy(aux, "Grande");
		break;
		
		case 4:
			strcpy(aux, "SUV");
		break;
		
		case 5:
			strcpy(aux, "Minivan");
		break;
	}
    printf("Opções disponiveis para reserva:\n");
    achar_cat(p_aux, pc, h, cont, 0, 0, 0); //busca os carros da categoria que possuem a reserva zerada
    if(controle) //controle é mudado caso não encontre um carro compativel de reserva zerada
    {
        printf("Não foi possivel realizar a reserva\n");
    }
    else
    {
        printf("Insira o ID do carro que deseja reservar: ");
        scanf("%d",&aux_id);
        printf("\n");
        aqui= achar_ID(aux_id, pc, h, cont);
        if(aqui==-2)
            printf("ID não reconhecido");
        else
        {
            printf("Digite a data inicial para a reserva: ");
            scanf("%s",dat_aux);
            sscanf(dat_aux, "%d%*c%d%*c%d", &d_i[0], &m_i[0], &a_i[0]); 
            strcpy(dat_aux, " ");
            printf("\n");
            printf("Digite a data final para a reserva: ");
            scanf("%s",dat_aux);
            sscanf(dat_aux, "%d%*c%d%*c%d", &d_i[1], &m_i[1], &a_i[1]); 
            strcpy(dat_aux, " ");

            for(int k=0; k<2; k++)
            {
                pc[aqui].data[k].dia= d_i[k];
                pc[aqui].data[k].mes= m_i[k];
                pc[aqui].data[k].ano= a_i[k];
            }

            printf("Reserva efetuada com sucesso");

        }
        

    }
    
    
}

void remov_reser(carro *pc, int *h, int *cont) //remove a reserva deixando as datas zeradas
{
    int id, aqui;
    printf("Insira o ID do carro que deseja remover a reserva: ");
    scanf("%d",&id);
    aqui= achar_ID(id, pc, h, cont);
    if(aqui==-2)
        printf("ID não encontrado");
    else
    {
        for(int k=0; k<2; k++)
            {
                pc[aqui].data[k].dia= 0;
                pc[aqui].data[k].mes= 0;
                pc[aqui].data[k].ano= 0;
            }
    }
}

void atualizar(carro *pc, int *h, int *cont) //a função de atualização muda a partir do ID se o carro continua disponivel, o funcionamento do ar condicionado
{                                           //a nova quilometragem e automaticamente retira a reserva o deixando disponivel
    int id, aqui;
    int op_disp, op_ar;
    printf("insira o ID do carro a ser atualizado: ");
    scanf("%d",&id);
    aqui= achar_ID(id, pc, h, cont); //busca o indice do ID que o usuario inseriu
    if(aqui==-2)
        printf("ID não encontrado");
    else
    {
        printf("O carro está disponivel para aluguel?:\n<1>Sim\n<2>Não\n ");
	    scanf("%d",&op_disp);
	    switch(op_disp)
        {
            case 1:
                pc[aqui].disp= 'S';
            break;
            
            case 2:
                pc[aqui].disp= 'N';
            break;
        }
        printf("O carro possui com ar condicionado?:\n<1>Sim\n<2>Não\n");
	    scanf("%d",&op_ar);
	    switch(op_ar)
        {
            case 1:
                pc[aqui].ar= 'S';
            break;
            
            case 2:
                pc[aqui].ar= 'N';
            break;
        }
        printf("Quantidade de quilometros rodados pelo carro: ");
	    scanf("%d",&pc[aqui].km);
        for(int k=0; k<2; k++)
            {
                pc[aqui].data[k].dia= 0;
                pc[aqui].data[k].mes= 0;
                pc[aqui].data[k].ano= 0;
            }

    }
}


void salvar(FILE *p, int *h, carro *pc, int *cont) //o salvamento do arquivo é feito conforme o molde enviado
{
    p=fopen("listacarros.dat", "w");
    bool tail= false;
	int guard_fim;
	int i=*h;
	
	guard_fim= achar_ind(-1, pc, h, cont); //busca o fim da lista para determinar a condição de parada
    
	while(!tail)
    {
    	fprintf(p,"%d %s %s %s\n", pc[i].id, pc[i].placa, pc[i].fab, pc[i].mod);
        fprintf(p,"%c %s %d %c\n",pc[i].disp, pc[i].cat, pc[i].lug, pc[i].ar);
        fprintf(p,"%d\n", pc[i].km);
        fprintf(p,"%d/%d/%d %d/%d/%d\n", pc[i].data[0].dia, pc[i].data[0].mes, pc[i].data[0].ano, pc[i].data[1].dia, pc[i].data[1].mes, pc[i].data[1].ano);
    	if(i == guard_fim || i>guard_fim) //condição de saida
    		tail= true;
    	i= pc[i].next;
	}
}

int main()
{
    carro car[1000];
    int head= 0;
    carro *p_car= car;
    int op;
    bool sair=false;
    int contador=0;

    FILE *fp;
    /* Chamar a função que lê o arquivo */
    ler_arq(fp, &head, p_car, &contador);
    
    while(!sair && contador>=0) //só é possivel acessar o menu caso existam elementos cadastrados
    {
		printf("\n<1> imprimir\n<2> inserir\n<3> remover\n<4> Listar carros de uma determinada categoria em uma determinada data\n<5>Data hoje\n<6>Verificar devolução do carro\n<7>Fazer reserva\n<8>Remover reserva\n<9>Atualizar dados do veiculo retornado\n<10>Sair e Atualizar\n");
	    scanf("%d",&op);
	    switch(op)
	    {
	    	case 1: imprimir(-1, &head, p_car, &contador); //chamada da função de impressão da lista toda
	    	break;
	    	
			case 2: inserir(p_car, &contador, &head); //chamada da função para inserir
	    	break;
	    	
	    	case 3: remocao(p_car, &head, &contador); //chamada da função de remover
	    	break;
	    	
	    	case 4: pega_cat(p_car, &contador, &head); //função para iniciar a busca busca de uma determinada categoria em uma data
	    	break;
	    	
	    	case 5: pega_data_hoje(p_car, &contador, &head); //função responsavel por pegar a data do sistema do usuario
	    	break; 

            case 6: verificar_dev(p_car, &contador, &head); //função para verificar quando um carro deve ser devolvido
	    	break;

            case 7: fazer_reserv(p_car, &contador, &head); //função para efetuar a reserva
	    	break;

            case 8: remov_reser(p_car, &head, &contador); //função para remover a reserva
	    	break;
	    	
	    	case 9: atualizar(p_car, &head, &contador); //função para atualizar a volta de um carro
	    	break;

            case 10: salvar(fp, &head, p_car, &contador); //função para salvar o arquivo e sair do programa
                sair= true;
            break;
		}
	}
	sair= false; //reset da variavel sair para o caso de contador<=0
	if(contador<=0){
            printf("Não existem elementos cadastrados\n\n<1>Inserir um novo cadastro\n<2>Sair sem salvar\n"); //não é possivel salvar o arquivo sem elementos
            scanf("%d",&op);
            switch(op)
            {
                case 1: 
                    inserir(p_car, &contador, &head);
                    contador++;
                break;

                case 2: 
                    sair=true;
                break;
            }
        }
    
    
    return 0;

}