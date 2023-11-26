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

void diminuir_y(){
    if(y > 1){
        y--;
    }
    atualizar_cursor(x, y);
}

void monitoramento_teclas(LISTA **lista){
    int tecla;
    LISTA *q;
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
                        aumentar_x();
                        break;
                    //SETA BAIXO
                    case 80:
                        aumentar_y();
                        break;
                    //SETA ESQUERDA
                    case 75:
                        diminuir_x();
                        break;
                    //SETA CIMA
                    case 72:
                        diminuir_y();
                        break;
                    //INSERT
                    case 82:
                        break;
                    //DELETE
                    case 83:
                        break;
                    //END
                    case 79:
                        break;
                    //HOME
                    case 71:
                        x = 0;
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
//                    printf("\b \b");
                    diminuir_x();
                }
                //ESC
                else if(tecla == 27){
                    break;
                }
                //ENTER
                else if(tecla == 13){
                    y++;
                    x = 1;
                    atualizar_cursor(x, y);
                }
                else{
                    if(x == 90){
                        if(q->next == NULL){
                            criar_linha_final(lista);
                            q = q->next;
                        }
                    }
                    inserir_caractere_posicao(lista, tecla, y-1, x-1);
                    system("cls");
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
