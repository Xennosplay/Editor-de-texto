#include <stdio.h>
#include <conio.h>
#include "BrennoMurakamiEstrutura.h"

int x = 1, y = 1;

// Função para posicionar o cursor na tela
void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

void atualizar_cursor(int nx, int ny) {
    gotoxy(nx, ny);
}

void limpar_tela(){
    system("cls");
}

void aumentar_x(){
    if(x < 90){
        x++;
    }
    else{
        y++;
        x = 1;
    }
    atualizar_cursor(x, y);
}

void diminuir_x(){
    if(x > 1){
        x--;
    }
    else if(y > 1){
        y--;
        x = 90;
    }
    atualizar_cursor(x, y);
}

void aumentar_y(){
    y++;
    atualizar_cursor(x, y);
}

void monitoramento_teclas(LISTA **lista){
    int tecla;
    LISTA *q, *aux;
    q = *lista;
    do {
        if (_kbhit()) {
            tecla = _getch();

            //Teclas especiais
            if (tecla == 224 || tecla == 0) {
                tecla = _getch();
                switch (tecla){
                    //F1
                    case 59:
                        break;
                    //F2
                    case 60:
                        break;
                    //F10
                    case 68:
                        break;
                    //F12
                    case 134:
                        break;
                    //SETA DIREITA
                    case 77:
                        q = retornar_no_atual(*lista, y-1);
                        if(x < q->tam+2 && q->linha[x-1] != '\n'){
                            aumentar_x();
                        }
                        else{
                            if(q->next != NULL){
                                q = q->next;
                                y++;
                                x = 1;
                                atualizar_cursor(x, y);
                            }
                        }
                        break;
                    //SETA BAIXO
                    case 80:
                        q = retornar_no_atual(*lista, y-1);
                        if(q->next != NULL){
                            q = q->next;
                            if(x-2 > q->tam){
                                if(q->linha[q->tam] == '\n'){
                                    x = q->tam+1;
                                }
                                else{
                                    x = q->tam+2;
                                }
                            }
                            y++;
                            atualizar_cursor(x, y);
                        }
                        break;
                    //SETA ESQUERDA
                    case 75:
                        if(y > 1){
                            q = retornar_no_anterior(*lista, y-1);
                            if(x > 1){
                            x--;
                            }
                            else{
                                if(q->linha[q->tam] == '\n'){
                                    x = q->tam+1;
                                }
                                else{
                                    x = q->tam+2;
                                }
                                y--;
                            }
                        }
                        else{
                            if(x > 1){
                                x--;
                            }
                        }
                        atualizar_cursor(x, y);
                        break;
                    //SETA CIMA
                    case 72:
                        if(y > 1){
                            q = retornar_no_anterior(*lista, y-1);
                            if(x > q->tam+1){
                                x = q->tam+1;
                            }
                            y--;
                            atualizar_cursor(x, y);
                        }
                        break;
                    //INSERT
                    case 82:
                        break;
                    //DELETE
                    case 83:
                        remover_caractere_posicao(lista, y-1, x-1);
                        limpar_tela();
                        exibir(*lista);
                        atualizar_cursor(x, y);
                        break;
                    //END
                    case 79:
                        q = retornar_no_atual(*lista, y-1);
                        if(q->linha[q->tam] == '\n'){
                            x = q->tam+1;
                        }
                        else{
                            x = q->tam+2;
                        }

                        limpar_tela();
                        exibir(*lista);
                        atualizar_cursor(x, y);
                        break;
                    //HOME
                    case 71:
                        x = 1;
                        atualizar_cursor(x, y);
                        break;
                    //PAGEUP
                    case 73:
                        break;
                    //PAGEDOWN
                    case 81:
                        break;
                }
            } else{

                //BACKSPACE
                if (tecla == 8) {
                    if(x == 1){
                        if(y > 1){
                            q = retornar_no_anterior(*lista, y-1);
                            aux = retornar_no_atual(*lista, y-1);

                            if(aux->tam > -1){

                                int i = 0;
                                while( i <= aux->tam){
                                    if(aux->linha[i] != '\n' && q->tam < 89){
                                        inserir_caractere_posicao(lista, aux->linha[i], y-2, q->tam);
                                    }
                                    i++;
                                }

                                while( i >= 0){
                                    if(aux->linha[i] != '\n'){
                                        remover_caractere_posicao(lista, y-1, i);
                                    }
                                    i--;
                                }
                            }
                            if(aux->tam == -1 || aux->linha[0] == '\n'){
                                remover_linha_posicao(lista,y-1);
                            }
                            limpar_tela();
                            exibir(*lista);

                            if(q->linha[q->tam] != '\n'){
                                x = q->tam+2;
                            }
                            else{
                                x = q->tam+1;
                            }
                            y--;
                            atualizar_cursor(x, y);
                        }
                    }
                    else{
                        remover_caractere_posicao(lista,y-1, x-2);
                        limpar_tela();
                        exibir(*lista);
                        diminuir_x();
                    }

                }
                //ESC
                else if(tecla == 27){
                    break;
                }
                //ENTER
                else if(tecla == 13){
                    inserir_caractere_posicao(lista,'\n', y-1, x-1);
                    y++;
                    x = 1;
                    criar_linha_posicao(lista, y-2);
                    atualizar_cursor(x, y);
                }
                else{
                    if(x >= 90){
                        q = retornar_no_atual(*lista, y-1);

                        if(q->linha[q->tam] != '\n'){
                            inserir_caractere_posicao(lista,'\n', y-1, x-1);
                        }else{
                            criar_linha_posicao(lista, y-1);
                            inserir_caractere_posicao(lista, '\n', y, 0);
                        }

                        if(q->next == NULL){
                            criar_linha_final(lista);
                        }
                    }
                    inserir_caractere_posicao(lista, tecla, y-1, x-1);
                    limpar_tela();
                    exibir(*lista);
                    aumentar_x();
                }
            }
        }
    } while (1);
}

void main() {
    LISTA *lista;

    gotoxy(x, y);

    inicializar(&lista);
    criar_linha_comeco(&lista);
    monitoramento_teclas(&lista);
}
