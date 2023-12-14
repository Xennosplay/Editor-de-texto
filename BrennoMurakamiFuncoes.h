#ifndef BrennoMurakamiFuncoes_H
#define BrennoMurakamiFuncoes_H
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Fun��o para posicionar o cursor na tela
void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

//Fun��o para atualizar o cursor na tela
void atualizar_cursor(int nx, int ny) {
    gotoxy(nx, ny);
}

//Fun��o para aumentar o x para a movimenta��o do cursor, neste caso, se x for ultrapassar o limite da tela, ele vai pra linha debaixo reiniciando a contagem
void aumentar_x(int *x, int *y){
    if(*x < 90){
        (*x)++;
    }
    else{
        (*y)++;
        *x = 1;
    }
    atualizar_cursor(*x, *y);
}

//Fun��o para limpar a tela
void limpar_tela(){
    system("cls");
}

//inverso da fun��o de aumentar o x
void diminuir_x(int *x, int *y){
    if(*x > 1){
        (*x)--;
    }
    else if(*y > 1){
        (*y)--;
        *x = 90;
    }
    atualizar_cursor(*x, *y);
}


//Fun��o para aumentar y, ou seja, incrementar y significa passar para a linha de baixo
void aumentar_y(int *x, int *y){
    (*y)++;
    atualizar_cursor(*x, *y);
}

void printarArquivo(){
    FILE *arquivo;
    char c;
    int tecla;
    int j = 0;

    limpar_tela();
    arquivo = fopen("BrennoMurakami_ajuda.txt", "r");

    while((c = fgetc(arquivo)) != EOF){
        printf("%c", c);
    }

    do{
        tecla = _getch();
        if(tecla == 27){
            j = 1;
        }
    }while(j != 1);
    limpar_tela();
}

void salvar_arquivo(LISTA *q){
    FILE *arquivo;
    int i;
    arquivo = fopen("BrennoMurakami.txt", "w");

    while(q != NULL){
        for(i = 0; i <= q->tam; i++){
            fprintf(arquivo, "%c", q->linha[i]);
        }
        q = q->next;
    }
    fclose(arquivo);
}

void limpar_estrutura(LISTA **lista){
    while(!empty(lista)){
        remover_linha_comeco(lista);
    }
}

void descer_caracteres(LISTA **lista, int no, char caractere, int pos){
    LISTA *q, *aux, *anterior;
    int i=0,j=0, k = 0;
    q = *lista;
    aux = *lista;
    anterior = *lista;
    while(i < no){
        q = q->next;
        aux = aux->next;
        i++;
    }
    while(aux->tam > 89 && aux->next != NULL)
    {
        aux = aux->next;
        i++;
    }

    if(aux->next == NULL && aux->tam == 90)
    {
        if(aux->linha[90] != '\n'){
            aux->linha[90] = '\n';
        }
        criar_linha_final(lista);
        aux = aux->next;
        aux->linha[0] = '\n';
        aux->tam++;
        i++;
    }
    while(i > no){
       anterior = *lista;
       while(j < i-1)
       {
         anterior = anterior->next;
         j++;
       }
       inserir_caractere_comeco(lista,anterior->linha[anterior->tam-1],i);
       remover_caractere_posicao(lista, i-1, q->tam-1);
       i--;
       j = 0;
    }
    inserir_caractere_posicao(lista, caractere, no, pos);
}

void dados_aluno(){
    int j = 0, tecla;
    limpar_tela();
    printf("[ESC] - Voltar");
    printf("\n\nNome: Brenno Murakami");
    printf("\nProntuario: PE3008983");
    printf("\nCurso: Bacharelado em Ciencia da Computacao - IFSP P. Epitacio");
    printf("\nAno de Ingresso: 2020");
    do{
        tecla = _getch();
        if(tecla == 27){
            j = 1;
        }
    }while(j != 1);
    limpar_tela();
}

#endif // BrennoMurakamiFuncoes
