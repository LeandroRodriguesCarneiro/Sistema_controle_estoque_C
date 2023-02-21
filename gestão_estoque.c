#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct tipo de variavel homogenica onde se armazena os dados do produto
typedef struct TProduto {
long int codigo;
int quantidade,grupo;
char descricao[41], unidade[3], fornecedor[41],nome_produto[41];
float pr_compra, pr_venda,lucro;
} Tproduto;

//definicao de constantes
const int MAX=50;
//variável para controlar a ordenação dos dados
int ordenado=0;

void leitura(Tproduto estoque[], int *tamanho);
void gravacao(Tproduto estoque[], int tamanho);
int pesquisabinaria(Tproduto estoque[], int chave, int tamanho);
int vazio(int tamanho);
void ordena(Tproduto estoque[], int tamanho);
void ordena_preco(Tproduto estoque[], int tamanho);
int pesquisa (Tproduto estoque[],int chave,int tamanho);
void apresentar(Tproduto estoque[],int chave);

void cadastrar(Tproduto estoque[],int *tamanho);
void alterar(Tproduto estoque[],int *tamanho);
void consultar(Tproduto estoque[],int*tamanho);
void consulta_nome(Tproduto estoque[],int *tamanho);
void delete(Tproduto estoque[],int*tamanho);
void comprar(Tproduto estoque[],int*tamanho);
void relatorio_ficha(Tproduto estoque[],int chave);
void relatorio_lista(Tproduto estoque[],int chave);
void relatorio_geral(Tproduto estoque[],int tamanho);
void relatorio_lista_preco(Tproduto estoque[],int tamanho);
void relatorio_produto_unidade(Tproduto estoque[],int tamanho);

int main (){
    Tproduto estoque[MAX];
    int tamanho=0, opcao, opc,opc1;
    leitura(estoque, &tamanho);// abre o arquivo da base de dados
    do{
        printf(" -----------------------------------------\n");
        printf("|             Sistema da Loja             |\n");
        printf(" -----------------------------------------");
        printf("\n\t 1 - CADASTRAR\n");
        printf("\t 2 - ATUALIZAR\n");
        printf("\t 3 - EXCLUIR\n");
    	printf("\t 4 - CONSULTAR\n");
        printf("\t 5 - RELATORIO\n");
        printf("\t 6 - COMPRA DE PRODUTOS\n");
        printf("\t 0 - SAIR\n");
        printf("\nESCOLHA A OPCAO DESEJADA:\n");
        scanf("%d",&opcao);
        fflush(stdin);
        system("cls");
        switch (opcao){
            case 1:{
                cadastrar(estoque,&tamanho);
                gravacao(estoque,tamanho);
				break;
			}        	
            case 2:{
                alterar(estoque,&tamanho);
                gravacao(estoque,tamanho);
				break;
			}
			case 3:{
                delete(estoque,&tamanho);
                gravacao(estoque,tamanho);
				break;
			}
			case 4:{
                printf("qual a forma de pesquisa:");
                printf("\n1 - pesquisa por codigo\n2 - pesquisa por texto\n0 - voltar ao menu principal\n");
                scanf("%i",&opc1);
                fflush(stdin);
                switch (opc1){
                case 0:{
                    system("cls");
                    break;
                }
                case 1:{
                    consultar(estoque,&tamanho);
                    break;
                    }
                case 2 :{
                    consulta_nome(estoque,&tamanho);
                    break;
                    }
                default:{
                    printf("digite uma opcao valida");
                    break;
                    }
                }
				break;
			}
			case 5:{
				printf("qual o relatorio desejado:");
                printf("\n1 - relatorio geral\n2 - relatorio de precos\n3 - relatorio por unidade de venda\n0 - voltar ao menu principal\n");
                scanf("%i",&opc);
                fflush(stdin);
                switch (opc){
                case 0:{
                    system("cls");
                    break;
                }
                case 1:{
                    relatorio_geral(estoque,tamanho);
                    break;
                    }
                case 2 :{
                    relatorio_lista_preco(estoque,tamanho);
                    break;
                    }
                case 3:{
                    relatorio_produto_unidade(estoque,tamanho);
                    break;
                }
                default:{
                    printf("digite uma opcao valida");
                    break;
                    }
                }
				break;
			}
			case 6:{
                comprar(estoque,&tamanho);
                gravacao(estoque,tamanho);
				break;
			}	
            case 0: 
				printf("Obrigado por usar nosso sistema.\n");
				system("pause");
				exit(0);
				break;
            default: printf("OPCAO INVALIDA!");
        }
    }while (opcao!=0);
            gravacao(estoque, tamanho);// grava após realizada as operações
	return 0;
}

void leitura(Tproduto estoque[], int *tamanho){
    FILE *arquivo;
  	arquivo= fopen("estoque.dat", "a+b");	   /* abrimos para anexar, binário */ 
  	if (!arquivo){
  		printf("Erro ao abrir arquivo!");
  		return;
  	}
//le os dados do arquivo
    while(!feof(arquivo)){
       fread (&estoque[*tamanho], sizeof (Tproduto) , 1, arquivo);
       (*tamanho)++;
    }
	(*tamanho)--;
//fecha o arquivo
	fclose(arquivo);
	return;
}

void gravacao(Tproduto estoque[], int tamanho){
    FILE *arquivo;
    int i;
    arquivo= fopen("estoque.dat", "wb+");	   /* abre e apaga o conteúdo do arquivo,binário */ 
  	if (!arquivo){
  		printf("Erro ao abrir arquivo!");
  		return;
  	}
// grava a estrutura no arquivo
    for(i=0;i<tamanho;i++)  
       fwrite(&estoque[i], sizeof(Tproduto), 1, arquivo);
// Fecha o arquivo de dados
	fclose(arquivo);
	return;
}

int pesquisabinaria(Tproduto estoque[], int chave, int tamanho){
    if(vazio(tamanho))
       return -1;   //vetor vazio    
    if (! ordenado){
        ordena(estoque,tamanho);
        ordenado=1; 
    }
    int inicio=0,final=tamanho, meio;
    while (inicio<=final){
        meio=(int)(inicio+final)/2;
        if (estoque[meio].codigo==chave)
           return meio; // encontrou
        if (estoque[meio].codigo<chave)
           inicio=meio+1;
        else
           final=meio-1;
    }
    return -1; // não encontrou
}

int vazio(int tamanho){
     if(tamanho==0){
        printf("\nREGISTRO VAZIO!\n");
        return 1;
     }
     return 0;
}

void ordena(Tproduto estoque[], int tamanho){
	int i,j;
    Tproduto aux;
    for(i=0;i<tamanho-1;i++)
        for(j=i+1;j<tamanho;j++)
          	if (estoque[i].codigo>estoque[j].codigo){
              	aux=estoque[i];
              	estoque[i]=estoque[j];
              	estoque[j]=aux;
            }
}

void ordena_preco(Tproduto estoque[], int tamanho){
	int i,j;
    Tproduto aux;
    for(i=0;i<tamanho-1;i++)
        for(j=i+1;j<tamanho;j++)
          	if (estoque[i].pr_venda>estoque[j].pr_venda){
              	aux=estoque[i];
              	estoque[i]=estoque[j];
              	estoque[j]=aux;
            }
}

int pesquisa (Tproduto estoque[],int chave,int tamanho){ 
    if (tamanho==0)
    return -2; // registro vazio
    int i;
    for (i=0;i<tamanho;i++){
     	if  (estoque[i].codigo==chave)
     		return i; // encontrou e retorna o local
    }
	return -1;// nao encontrou
}

void apresentar(Tproduto estoque[],int chave){
    printf("\ncodigo = %ld\n", estoque[chave].codigo);
    printf("nome = %s\n", estoque[chave].nome_produto);
    printf("forncedor = %s\n", estoque[chave].fornecedor);
    printf("descricao = %s\n",estoque[chave].descricao);
    printf("grupo = %d\n",estoque[chave].grupo);
    printf("quantidade = %d\n",estoque[chave].quantidade);
    printf("unidade de medida de venda: %s\n",estoque[chave].unidade);
    printf("valor de compra = %.2f\n",estoque[chave].pr_compra);
    printf("valor de lucro = %.2f\n",estoque[chave].lucro); 
    printf("valor de venda = %.2f\n",estoque[chave].pr_venda);
    return;
}

void cadastrar(Tproduto estoque[],int *tamanho){
    if (*tamanho == MAX){
        printf("Arquivo cheio");
        return;
    }
    Tproduto aux;
    char correto = 'n';
    do{
        printf("insira o codigo do produto: \n");
        scanf("%ld",&aux.codigo);
        fflush(stdin);
        if(aux.codigo <= 0){
            printf("Codigo invalido\n");
            system("pause");
            system("cls");
        }
    }while (aux.codigo<=0);
    if (pesquisa(estoque, aux.codigo, *tamanho) <0){
        printf("insira o nome do produto: \n");
        gets(aux.nome_produto);
        fflush(stdin);
        printf("insira a descricao do produto: \n");
        gets(aux.descricao);
        fflush(stdin);
        printf("insira ofornecedor do produto: \n");
        gets(aux.fornecedor);
        fflush(stdin);
        do{
            printf ("1 - comprimido\n2 - gotas\n3 - granel\n4 - pacote\n5 - capsula\n");
            printf("insira o grupo do produto: \n");
            scanf("%d",&aux.grupo);
            fflush(stdin);
            if (aux.grupo <= 0 || aux.grupo >5){
                printf("Grupo invalido");
                system("pause");
                system("cls");
            }
        }while (aux.grupo <= 0 || aux.grupo >5);
        int opc;
        do{
            printf("selecione a unidade de medida do produto");
            printf ("\n1 - litros\n2 - kilogramas\n3 - unidade\n");
            scanf("%d",&opc);
            fflush(stdin);
            switch (opc){
            case 1:{
                strcpy (aux.unidade, "LT");
                break;
            }
            case 2:{
                strcpy (aux.unidade, "KG");
                break;
            }
            case 3:{
                strcpy (aux.unidade, "UN");
                break;
            }
            default:
                printf("Digite um codigo valido\n");
                system("pause");
                system("cls");
                break;
            }
        }while (opc <= 0 || opc >3);
        do{
            printf("insira o quantidade do produto: \n");
            scanf("%d",&aux.quantidade);
            fflush(stdin);
            if(aux.quantidade<0){
                printf("Quantidade deve ser maior que 0");
                system("pause");
                system("cls");
            }
        }while (aux.quantidade<0);
        do{
            printf("insira o preco de compra do produto: \n");
            scanf("%f",&aux.pr_compra);
            fflush(stdin);
            
        } while (aux.pr_compra<0);
        do{
            printf("insira a margem de lucro: \n");
            scanf("%f",&aux.lucro);
            fflush(stdin);
            if(aux.lucro<0){
                printf("Quantidade deve ser maior que 0");
                system("pause");
                system("cls");
            }
        } while (aux.lucro<0);
        aux.pr_venda = ((aux.pr_compra*(aux.lucro + 100)))/100;
        system("cls");
        printf("\ncodigo = %ld\n", aux.codigo);
        printf("nome = %s\n", aux.nome_produto);
        printf("forndecedor = %s\n",aux.fornecedor);
        printf("descricao = %s\n",aux.descricao);
        printf("grupo = %d\n",aux.grupo);
        printf("quantidade = %d\n",aux.quantidade);
        printf("unidade de medida de venda: %s\n",aux.unidade);
        printf("valor de compra = %.2f\n",aux.pr_compra);
        printf("margem de lucro = %.2f%%\n",aux.lucro); 
        printf("valor de venda = %.2f\n",aux.pr_venda);
        printf ("Os dados estao corretos?(S/N)\n");
        correto=getchar();
        fflush(stdin);
        system("cls");
        if (correto=='s'||correto=='S'){
            estoque [*tamanho] = aux;// faz a transferência
            (*tamanho) ++;
            ordenado=0;
            printf ("\tO produto foi incluido!\n");
            fflush(stdin);
        }

    }else 
    	printf ("\tCODIGO JA CADASTRADO!!\n");
    printf("\tAPERTE ENTER PARA VOLTAR AO MENU");
    fflush(stdin);
    getchar();
    fflush(stdin);
    system("cls");
    return;
}

void alterar(Tproduto estoque[],int *tamanho){
    if (*tamanho == 0){
        printf("registro vazio");
        return;
    }
    Tproduto aux;
    int posicao,codigo;
    char correto = 'N';
    int opc;
    printf("insira o codigo do produto: \n");
    scanf("%d",&codigo);
    fflush(stdin); 
    posicao = pesquisabinaria(estoque,codigo,*tamanho);
    if (posicao>=0){
        aux = estoque[posicao];
        apresentar(estoque,posicao);
        printf("\nO que deseja alterar:");
        printf("\n\t1 - nome do produto\n\t2 - descricao\n\t3 - fornecedor\n\t4 - grupo\n\t5 - unidade\n\t6 - quantidade\n\t7 - preco de compra\n\t8 - margem de lucro\n");
        scanf("%d",&opc);
        fflush(stdin);
        switch (opc){
        case 1:{
            printf("digite o nome do produto:\n");
            gets(aux.nome_produto);
            fflush(stdin);
            break;
        }
        case 2:{
            printf("insira a descricao do produto: \n");
            gets(aux.descricao);
            fflush(stdin);
            break;
        }
        case 3:{
            printf("insira ofornecedor do produto: \n");
            gets(aux.fornecedor);
            fflush(stdin);
            break;
        }
        case 4:{
            do{
            printf ("1 - comprimido\n2 - gotas\n3 - granel\n4 - pacote\n5 - capsula\n");
            printf("insira o grupo do produto: \n");
            scanf("%d",&aux.grupo);
            fflush(stdin);
            if (aux.grupo <= 0 || aux.grupo >5){
                printf("Grupo invalido");
                system("pause");
                system("cls");
            }
            }while (aux.grupo <= 0 || aux.grupo >5);
            break;
        }
        case 5:{
            int unidade = 0;
            do{
                int opc;
                printf("selecione a unidade de medida do produto");
                printf ("\n1 - litros\n2 - kilogramas\n3 - unidade\n");
                scanf("%d",&opc);
                fflush(stdin);
                switch (opc){
                case 1:{
                    strcpy (aux.unidade, "LT");
                    unidade = 1;
                    break;
                }
                case 2:{
                    strcpy (aux.unidade, "KG");
                    unidade = 1;
                    break;
                }
                case 3:{
                    strcpy (aux.unidade, "UN");
                    unidade = 1;
                    break;
                }
                default:
                    printf("Digite um codigo valido\n");
                    system("pause");
                    system("cls");
                    break;
                }
            }while (unidade == 0);
            break;
        }
        case 6:{
            do{
                printf("insira o quantidade do produto: \n");
                scanf("%d",&aux.quantidade);
                fflush(stdin);
                if(aux.quantidade<0){
                    printf("Quantidade deve ser maior que 0");
                    system("pause");
                    system("cls");
                }
            }while (aux.quantidade<0);
            break;
        }
        case 7:{
            do{
                printf("insira o preco de compra do produto: \n");
                scanf("%f",&aux.pr_compra);
                fflush(stdin);
                
            } while (aux.pr_compra<0);
            break;
        }
        case 8:{
            do{
                printf("insira a margem de lucro: \n");
                scanf("%f",&aux.lucro);
                fflush(stdin);
                if(aux.lucro<0){
                    printf("Quantidade deve ser maior que 0");
                    system("pause");
                    system("cls");
                }
            } while (aux.lucro<0);
            aux.pr_venda = ((aux.pr_compra*(aux.lucro + 100)))/100;
            break;
        }
        default:
            printf("digite uma opcao valida");
            break;
        }
        system("cls");
        printf("\ncodigo = %ld\n", aux.codigo);
        printf("nome = %s\n", aux.nome_produto);
        printf("descricao = %s\n",aux.descricao);
        printf("grupo = %d\n",aux.grupo);
        printf("quantidade = %d\n",aux.quantidade);
        printf("unidade de medida de venda: %s\n",aux.unidade);
        printf("valor de compra = %.2f\n",aux.pr_compra);
        printf("margem de lucro = %.2f%%\n",aux.lucro); 
        printf("valor de venda = %.2f\n",aux.pr_venda);
        printf ("Os dados estao corretos?(S/N)");
        correto=getchar();
        fflush(stdin);
        system("cls");
        if (correto=='s'||correto=='S'){
            estoque[posicao] = aux;// faz a transferência
            ordenado=0;
            printf ("\tO produto foi incluido!\n");
            fflush(stdin);
        }
    }else{
        printf ("\tCODIGO NAO ENCONTRADO!!\n");
    }
    printf("\tAPERTE ENTER PARA VOLTAR AO MENU");
    fflush(stdin);
    getchar();
    fflush(stdin);
    system("cls");
    return;
}

void consultar(Tproduto estoque[],int*tamanho){
    if (*tamanho == 0){
        printf("registro vazio");
        return;
    }
    int posicao,codigo;
    printf("insira o codigo do produto: \n");
    scanf("%d",&codigo);
    fflush(stdin); 
    system("cls");
    posicao = pesquisabinaria(estoque,codigo,*tamanho);
    if (posicao>=0){
        relatorio_ficha(estoque,posicao);
    }else{
        printf("O codigo nao foi encontrado");
    }
    printf("\tAPERTE ENTER PARA VOLTAR AO MENU");
    fflush(stdin);
    getchar();
    fflush(stdin);
    system("cls");
    return;
}

void consulta_nome(Tproduto estoque[],int *tamanho){
    if (*tamanho == 0){
        printf("registro vazio");
        return;
    }
    char pesquisa[256];
    int encontrou = 0;
    printf("Insira a palavra que deseja procurar:\n");
    gets(pesquisa);
    fflush(stdin);
    system("cls");
    printf("O que pesquisou foi: %s",pesquisa);
    for (int i = 0; i < *tamanho; i++){
        if(strcmp(estoque[i].nome_produto,pesquisa) == 0){
            relatorio_ficha(estoque,i);
            encontrou = 1;
        }
    }
    if(encontrou == 0){
        printf("\nNenhum produto encontrado\n");
    }
    system("pause");
    printf("\tAPERTE ENTER PARA VOLTAR AO MENU");
    fflush(stdin);
    getchar();
    fflush(stdin);
    system("cls");
    return;
}

void delete(Tproduto estoque[],int*tamanho){
    if (*tamanho == 0){
        printf("registro vazio");
        return;
    }
    int posicao,codigo;
    char correto = 'N';
    printf("insira o codigo do produto: \n");
    scanf("%d",&codigo);
    fflush(stdin); 
    posicao = pesquisabinaria(estoque,codigo,*tamanho);
    if (posicao>=0){
        apresentar(estoque,posicao);
        printf("realmente deseja excluir esse produto:(S/N)\n");
        fflush(stdin);
        scanf("%c",&correto);
        
        if (correto == 'S'||correto=='s'){
            for(int i = posicao; i<(*tamanho)-1;i++){
                estoque[i] = estoque[i+1];
                
            }
            (*tamanho)--;
            printf("item excluido\n");
        }else{
            printf("item nao excluido\n");
        }
    }
    system("cls");
    system("pause");
    printf("\tAPERTE ENTER PARA VOLTAR AO MENU");
    fflush(stdin);
    getchar();
    fflush(stdin);
    system("cls");
    return;
}

void comprar(Tproduto estoque[],int*tamanho){
    if (*tamanho == 0){
        printf("registro vazio");
        return;
    }
    Tproduto aux;
    int posicao,codigo,quantidade;
    char correto = 'N';
    printf("insira o codigo do produto: \n");
    scanf("%d",&codigo);
    fflush(stdin); 
    system("cls");
    posicao = pesquisabinaria(estoque,codigo,*tamanho);
    if (posicao>=0){
        aux = estoque[posicao];
        printf("descricao = %s\n",estoque[posicao].nome_produto);
        printf("unidade de medida de venda: %s\n",estoque[posicao].unidade);
        printf("forncedor = %s\n", estoque[posicao].fornecedor);
        printf("insira ofornecedor do produto: \n");
        gets(aux.fornecedor);
        fflush(stdin);
        do{
            printf("insira o quantidade do produto: \n");
            scanf("%d",&quantidade);
            fflush(stdin);
            if(quantidade<0){
                printf("Quantidade deve ser maior que 0");
                system("pause");
                system("cls");
            }
        }while (quantidade<0);
        aux.quantidade = aux.quantidade+quantidade;
        do{
            printf("insira o preco de compra do produto: \n");
            scanf("%f",&aux.pr_compra);
            fflush(stdin);
        } while (aux.pr_compra<0);
        system("cls");
        printf("\ncodigo = %ld\n", aux.codigo);
        printf("nome = %s\n", aux.nome_produto);
        printf("forndecedor = %s\n",aux.fornecedor);
        printf("descricao = %s\n",aux.descricao);
        printf("grupo = %d\n",aux.grupo);
        printf("quantidade = %d\n",aux.quantidade);
        printf("unidade de medida de venda: %s\n",aux.unidade);
        printf("valor de compra = %.2f\n",aux.pr_compra);
        printf("margem de lucro = %.2f%%\n",aux.lucro); 
        printf("valor de venda = %.2f\n",aux.pr_venda);
        printf("Os dados estao corretos(S/N):\n");
        scanf("%c",&correto);
        fflush(stdin);
        if(correto == 's'||correto =='S'){
            estoque[posicao]=aux;
        }
        
    }else{
        printf("O codigo nao foi encontrado");
    }
    system("pause");
    system("cls");
    printf("APERTE ENTER PARA VOLTAR AO MENU");
    getchar();
    fflush(stdin);
    system("cls");
    return;
}

void relatorio_ficha(Tproduto estoque[],int chave){
    printf("===========================================================================\n");
    printf("Codigo: %-59li",estoque[chave].codigo);
    printf("Grupo: %i\n",estoque[chave].grupo);
    printf("Descricao: %-53s",estoque[chave].nome_produto);
    printf("Unidade: %-3s\n",estoque[chave].unidade);
    printf("Fornecedor: %-69s\n",estoque[chave].fornecedor);
    printf("Preco de Compra: R$%-9.2f",estoque[chave].pr_compra);
    printf("Preco de Venda: R$%-9.2f",estoque[chave].pr_venda);
    printf("Lucro Minimo: %-5.1f%%\n",estoque[chave].lucro);
    printf("Quantidade em Estoque: %-28i",estoque[chave].quantidade);
    printf("Quantidade Minima: %-11i\n",estoque[chave].quantidade);
    printf("\n");
    printf("---------------------------------------------------------------------------\n");
}

void relatorio_lista(Tproduto estoque[],int chave){
    printf("==========================================================================\n");
    printf("Codigo: %-16li",estoque[chave].codigo);
    printf("Descricao: %-21s",estoque[chave].nome_produto);
    printf("preco: %-10.2f",estoque[chave].pr_venda);
    printf("\n");
    printf("--------------------------------------------------------------------------\n");
}

void relatorio_geral(Tproduto estoque[],int tamanho){
    ordena(estoque, tamanho);
    int cont = 1;
    for(int codigo=0; codigo<tamanho; codigo++){
    	relatorio_ficha(estoque,codigo);
        if (cont == 2){
            system("pause");
            system("cls");
            cont = 0;
        }
        cont++; 
    }
    printf("APERTE ENTER PARA VOLTAR AO MENU");
    getchar();
    fflush(stdin);
    system("cls");
}

void relatorio_lista_preco(Tproduto estoque[],int tamanho){
    ordena_preco(estoque, tamanho);
    int cont = 1;
    for(int codigo=0; codigo<tamanho; codigo++){
    	relatorio_lista(estoque,codigo); 
        if (cont == 15){
            system("pause");
            system("cls");
            cont = 0;
        }  
        cont++;
    }
    printf("APERTE ENTER PARA VOLTAR AO MENU");
    getchar();
    fflush(stdin);
    system("cls");
}

void relatorio_produto_unidade(Tproduto estoque[],int tamanho){
    ordena(estoque, tamanho);
    int opc;
    do{
        printf("selecione a unidade de medida do produto que deseja buscar");
        printf ("\n1 - litros\n2 - kilogramas\n3 - unidade\n");
        scanf("%d",&opc);
        fflush(stdin);
        int cont = 1;
        switch (opc){
            case 1:{
                printf("\tLitro\n");
                for(int codigo=0; codigo<tamanho; codigo++){
                    if(strcmp(estoque[codigo].unidade,"LT")==0){
                        relatorio_ficha(estoque,codigo);
                        if (cont == 2){
                            system("pause");
                            system("cls");
                            cont = 0;
                        }
                        cont++; 
                    }
                }
                system("pause");
                system("cls");
            break;
            }
            case 2:{
                printf("\tKilograma\n");
                for(int codigo=0; codigo<tamanho; codigo++){
                    if(strcmp(estoque[codigo].unidade,"KG")==0){
                        relatorio_ficha(estoque,codigo);
                        if (cont == 2){
                            system("pause");
                            system("cls");
                            cont = 0;
                        }
                        cont++; 
                    }
                }
                system("pause");
                system("cls");
                break;
            }
            case 3:{
                printf("\tUnidade\n");
                for(int codigo=0; codigo<tamanho; codigo++){
                    if(strcmp(estoque[codigo].unidade,"UN")==0){
                        relatorio_ficha(estoque,codigo);
                        if (cont == 2){
                            system("pause");
                            system("cls");
                            cont = 0;
                        }
                        cont++; 
                    }
                }
                system("pause");
                system("cls");
                break;
            }
            default:{
                printf("Codigo Invalido\n");
                system("pause");
                system("cls");
                break;
            }
        }
    } while (opc <= 0 || opc >3);
    printf("APERTE ENTER PARA VOLTAR AO MENU");
    getchar();
    fflush(stdin);
    system("cls");
    return;
}