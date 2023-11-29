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

#endif // BrennoMurakamiFuncoes
