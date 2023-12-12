#ifndef BrennoMurakamiEstrutura_H
#define BrennoMurakamiEstrutura_H
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct lista{
    char linha[91];
    int tam;
    struct lista *next;
}LISTA;

void inicializar(LISTA **lista){
    *lista = NULL;
}

LISTA* getnode(){
    return (LISTA*)malloc(sizeof(LISTA));
}

void freenode(LISTA *q){
    free(q);
}

int empty(LISTA **lista){
    if(*lista == NULL){
        return 1;
    }else{
        return 0;
    }
}

void exibir(LISTA *lista){
    setlocale(LC_ALL, "Portuguese");
    while(lista != NULL){
        for(int i = 0; i <= lista->tam; i++){
            printf("%c", lista->linha[i]);
        }
        lista = lista->next;
    }
}

void inserir_caractere_final(LISTA **lista, char caractere, int no){
    LISTA *q;
    q = *lista;
    int i = 0;

    while(i != no){
        q = q->next;
        i++;
    }
    q->linha[q->tam+1] = caractere;
    q->tam++;
}

void inserir_caractere_comeco(LISTA **lista, char caractere, int no){
    LISTA *q;
    q = *lista;
    int i = 0;
    while(i != no){
        q = q->next;
        i++;
    }
    if(q->tam == -1){
        q->linha[0] = caractere;
    }else{
        int j = q->tam+1;
        while(j > 0){
            q->linha[j] = q->linha[j-1];
            j--;
        }
        q->linha[j] = caractere;
    }
    q->tam++;
}

void inserir_caractere_posicao(LISTA **lista, char caractere, int no, int pos){
    LISTA *q;
    q = *lista;
    int i = 0;
    while(i != no){
        q = q->next;
        i++;
    }
    int j = q->tam+1;
    while(j > pos){
        j--;
        q->linha[j+1] = q->linha[j];
    }
    q->linha[j] = caractere;
    q->tam++;
}

void remover_caractere_posicao(LISTA **lista, int no, int pos){
    LISTA *q;
    q = *lista;
    int i = 0;
    while(i != no){
        q = q->next;
        i++;
    }
    if(q->tam >= 0){
        for(int j = pos; j < q->tam; j++){
            q->linha[j] = q->linha[j+1];
        }
        q->tam--;
    }
}

void remover_caractere_comeco(LISTA **lista, int no){
    LISTA *q;
    q = *lista;
    int i = 0;
    while(i != no){
        q = q->next;
    }
    if(q->tam >= 0){
        for(int j = 0; j < q->tam; j++){
            q->linha[j] = q->linha[j+1];
        }
        q->tam--;
    }

}

void remover_caractere_final(LISTA **lista, int no){
    LISTA *q;
    q = *lista;
    int i = 0;
    while(i != no){
        q = q->next;
    }
    if(q->tam >= 0){
        q->tam--;
    }
}

void criar_linha_comeco(LISTA **lista){
    LISTA *q;
    q = getnode();
    if(q == NULL){
        printf("\nHouve um erro.");
        return;
    }else{
        q->tam = -1;
        if(empty(lista)){
            q->next = NULL;
            *lista = q;
        }
        else{
            q->next = *lista;
            *lista = q;
        }
    }
}

//insere um no após a posição
void criar_linha_posicao(LISTA **lista, int pos){
    LISTA *q, *aux;
    q = getnode();
    aux = *lista;
    int i = 0;
    if(q != NULL){
        q->tam = -1;
        if(aux->next == NULL){
            q->next = NULL;
            aux->next = q;
        }
        else{
            while(i != pos){
                aux = aux->next;
                i++;
            }
            q->next = aux->next;
            aux->next = q;
        }
    }
    else{
        printf("\nHouve um erro.");
    }
}

void criar_linha_final(LISTA **lista){
    LISTA *q;
    q = getnode();
    if(q == NULL){
        printf("\nHouve um erro");
        return;
    }else{
        q->tam = -1;
        q->next = NULL;
        if(empty(lista)){
            *lista = q;
        }else{
            LISTA *aux;
            aux = *lista;
            while(aux->next != NULL){
                aux = aux->next;
            }
            aux->next = q;
        }
    }
}

void remover_linha_comeco(LISTA **lista){
    if(empty(lista)){
        printf("\nLista vazia.");
    }else{
        LISTA *aux;
        aux = *lista;
        *lista = (*lista)->next;
        free(aux);
    }
}

void remover_linha_final(LISTA **lista){
    if(empty(lista)){
        printf("\nLista vazia.");
    }else{
        LISTA *aux, *q;
        aux = *lista;
        if((*lista)->next == NULL){
            *lista = NULL;
            freenode(aux);
        }
        else{
            q = (*lista)->next;
            while(q->next != NULL){
                q = q->next;
                aux = aux->next;
            }
            aux->next = NULL;
            freenode(q);
        }
    }
}

void remover_linha_posicao(LISTA **lista, int pos){
    if(empty(lista)){
        printf("\nLista vazia.");
    }
    else{
        LISTA *aux, *q;
        aux = *lista;
        if((*lista)->next == NULL){
            *lista = NULL;
            freenode(aux);
        }
        else{
            q = (*lista)->next;
            int i = 1;
            while(i != pos){
                q = q->next;
                aux = aux->next;
                i++;
            }
            aux->next = q->next;
            free(q);
        }
    }
}

LISTA *retornar_no_anterior(LISTA *lista, int no){
    LISTA *q;
    q = lista;
    int i = 0;
    while(i != no-1){
        q = q->next;
        i++;
    }
    return q;
}

LISTA *retornar_no_atual(LISTA *lista, int no){
    LISTA *q;
    q = lista;
    int i = 0;
    while(i != no){
        q = q->next;
        i++;
    }
    return q;
}

void caracter_abaixo(LISTA **lista, int no, int pos){
    LISTA *q = *lista;
    LISTA *aux = *lista;
    int i = 0, j;
    while(i != no){
        q = q->next;
        aux = aux->next;
    }
    aux = aux->next;
    j = q->tam;
    while(q->linha[j] != '\n'){
        inserir_caractere_posicao(lista, q->linha[j], no+1, 0);
        remover_linha_posicao(lista, j);
        j--;
    }
}

void caracter_abaixoo(LISTA **lista, char caracter, int no, int pos){
    LISTA *q = *lista;

}

void caracter_acima(LISTA **lista, char caracter, int no, int pos){
    LISTA *q = *lista;
    int i = 0, j;
    while(i != no - 1){
        q = q->next;
        i++;
    }
    q = q->next;


}

#endif // BrennoMurakamiEstrutura
