#ifndef BrennoMurakamiFuncoes_H
#define BrennoMurakamiFuncoes_H
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Função para posicionar o cursor na tela
void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

//Função para atualizar o cursor na tela
void atualizar_cursor(int nx, int ny) {
    gotoxy(nx, ny);
}

//Função para aumentar o x para a movimentação do cursor, neste caso, se x for ultrapassar o limite da tela, ele vai pra linha debaixo reiniciando a contagem
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

//Função para limpar a tela
void limpar_tela(){
    system("cls");
}

//inverso da função de aumentar o x
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


//Função para aumentar y, ou seja, incrementar y significa passar para a linha de baixo
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
