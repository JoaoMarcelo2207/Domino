#ifndef LISTADE_H
#define LISTADE_H
#include "PILHA.H"
#include <stdio.h>
#include <stdlib.h>




typedef tp_pedra tp_item2;
// dados estruturados que representam o descritor
typedef struct tp_no_aux{
	struct tp_no_aux *ant;
	tp_item2 info;
	struct tp_no_aux *prox;
} tp_no;

//dados estruturados que representam o nó da lista
typedef struct{
	tp_no *ini;
	tp_no *fim;
	int tamanho;
}tp_listad;

//aloca-se memória para o descritor (explicado no início deste arquivo) e faz os seus ponteiros apontarem para o nulo

tp_listad *inicializa_listad (){
	tp_listad *lista=(tp_listad*) malloc(sizeof(tp_listad));
	lista->ini = NULL;
	lista->fim = NULL;
	lista->tamanho = 0;
	return lista;
}

//Aloca um nó na lista
tp_no *aloca(){
	tp_no* pt;
	pt=(tp_no*) malloc(sizeof(tp_no));
	return pt;
}

int lista_vazia(tp_listad *lista){
	if(lista->ini==NULL)return 1;//verdade
	return 0;//falso
}

//insere um novo nó na lista
int insere_listad_no_fim(tp_listad *lista, tp_item2 e){
	tp_no *novo;
	novo=aloca();
	if(!novo)	return 0;
	novo->info = e;
	
	if (lista_vazia(lista)){//Se for o primeiro elemento da lista
		novo->prox = NULL;
		novo->ant = NULL;
		lista->ini = lista->fim = novo;
	}
	else{
		novo->prox = NULL;
		novo->ant = lista->fim;
		lista->fim->prox = novo;
		lista->fim = novo;
		lista->tamanho++;
		return 1;
	}
}

//Imprime os conteúdos da lista (de frente para trás ou de trás para frente)
void imprime_listad(tp_listad *lista, int ordem){
	tp_no *atu;
	int x = 1;
	
	switch (ordem){
		case 1: atu=lista->ini;
			while (atu!=NULL){
				printf("|%d|%d| ",atu->info.lado1,atu->info.lado2);
				  printf("%d\n", x);
				  atu=atu->prox;
				  x++;
			}
			break;
		case 2: atu=lista->fim;
				while(atu!=NULL){
					printf("|%d|%d| \n",atu->info.lado1,atu->info.lado2);
					printf("%d\n", x);
					atu=atu->ant;
					x++;
				}
				break;
		default: printf("Código inválido");
	}
	printf("\n");
}

// remove um elemento da lista

int remove_listad(tp_listad *lista, tp_item2 e){
	tp_no *atu;
	atu = lista->ini;
	
	//printf("peca que eu quero enontarar: %d/%d\n", e.lado1, e.lado2);
	
	while( atu->info.lado1 != e.lado1 || atu->info.lado2 != e.lado2){
		//printf("peca atual: %d/%d\n", atu->info.lado1, atu->info.lado2);
		atu = atu->prox;
	}
	
	//printf("peca encontradaaaaaaaaaaaaaaaaa %d/%d \n", atu->info.lado1, atu->info.lado2);
	
	if(atu==NULL) return 0;
	
	if(lista->ini==lista->fim){// Se for o único elemento da lista
		lista->ini = lista->fim = NULL;
	}
	else{
		if (lista->ini==atu){//Se for o primeiro elemento da lista
			lista->ini=atu->prox;
			atu->prox->ant=NULL;	}
		else{
			if(lista->fim==atu){//Se for o último nó da lista
				lista->fim=atu->ant;
				atu->ant->prox = NULL;	}
				
			else{
				atu->prox->ant = atu->ant;
				atu->ant->prox = atu->prox;
			}	
		}	
	}
	free(atu); lista->tamanho--;
	return 1;

}


tp_pedra remove_listad_no_fim(tp_listad *lista){
	
	tp_no *atu = lista->ini;
	tp_pedra elemento;
	
	while( atu->prox != NULL ){
		atu = atu->prox;
	}
	
	
	if(lista->ini==lista->fim){// Se for o único elemento da lista
		lista->ini = lista->fim = NULL;
	}
	else{
		if (lista->ini==atu){//Se for o primeiro elemento da lista
			lista->ini=atu->prox;
			atu->prox->ant=NULL;	}
		else{
			if(lista->fim==atu){//Se for o último nó da lista
				lista->fim=atu->ant;
				atu->ant->prox = NULL;	}
				
			else{
				atu->prox->ant = atu->ant;
				atu->ant->prox = atu->prox;
			}	
		}	
	}
	elemento = atu->info;
	free(atu); 
	
	lista->tamanho--;
	return elemento;
}






//Com base em um conteúdo, retorna-se o endereço do nó que contém o conteúdo
tp_no* busca_listad(tp_listad *lista, tp_item2 e){
	tp_no *atu;
	atu=lista->ini;
	while ((atu!=NULL) && (atu->info.lado1!=e.lado1) && (atu->info.lado2!=e.lado2)){
		atu=atu->prox;}
		return atu;
}
// Retira da memória todos os nós da lista e também o desritor
tp_listad *destroi_listad(tp_listad *lista){
	tp_no *atu;
	atu=lista->ini;
	while (atu!=NULL){
		lista->ini=atu->prox;
		free(atu);
		atu=lista->ini;
	}
	free(lista);
	return NULL;
}

int tamanho_listad(tp_listad *lista){
    return lista->tamanho;
}

void insere_inicio(tp_listad *mesa, tp_item2 e) {
	tp_no *atu;
	atu=aloca();
	atu->info= e;  //criar novo elemento
	//verificar se o inicio for nulo, se sim, inicio recebe novo e o fim vai ser novo também, pois se os dois são nulos o inico e fim recebe o novo.
	if(mesa->ini==NULL){
		mesa->ini=atu;
		mesa->fim=atu;

	//Se a lista já tiver dado se cria outro elemento e aponta o ant para o dado 2 e prox do dado 2 para o 1.
	}else{
		tp_no *atual; //criar novo elemento caso tenha dado no inicio da lista.
		atual = mesa->ini;
		atu->prox = atual;
		atual->ant = atu;
		mesa->ini = atu;
	}
	mesa->tamanho++;
}
#endif
