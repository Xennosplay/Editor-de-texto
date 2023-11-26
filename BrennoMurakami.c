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

void monitoramento_teclas(LISTA **lista){
    int tecla;    // Posição atual na entrada
    printf("(Pressione 'ESC' para sair):\n");
    do {
        if (_kbhit()) {
            tecla = _getch();

            //ESC
            if (tecla == 27) {
                printf("Tecla 'ESC' pressionada. Finalizando o programa.\n");
                break;
            }

            if(tecla == 13){
                y++;
                atualizar_cursor(x, y);
            }

            //Backspace
            if (tecla == 8) {

            } else if(tecla != 224 || tecla != 0 || tecla != 134){

            }

            //Teclas especiais
            if (tecla == 224 || tecla == 0) {
                tecla = _getch();
                switch (tecla){
                    case 59:
                        printf("\nTecla F1 pressionada.\n");
                        atualizar_cursor(15, 15);
                        break;
                    case 60:
                        printf("\nTecla F2 pressionada.\n");
                        break;
                    case 61:
                        printf("\nTecla F3 pressionada.\n");
                        break;
                    case 62:
                        printf("\nTecla F4 pressionada.\n");
                        break;
                    case 63:
                        printf("\nTecla F5 pressionada.\n");
                        break;
                    case 64:
                        printf("\nTecla F6 pressionada.\n");
                        break;
                    case 65:
                        printf("\nTecla F7 pressionada.\n");
                        break;
                    case 66:
                        printf("\nTecla F8 pressionada.\n");
                        break;
                    case 67:
                        printf("\nTecla F9 pressionada.\n");
                        break;
                    case 68:
                        printf("\nTecla F10 pressionada.\n");
                        break;
                    case 134:
                        printf("\nTecla F12 pressionada.\n");
                        break;
                    case 77:
                        printf("\nSeta Direita");
                        break;
                    case 80:
                        printf("\nSeta Baixo");
                        break;
                    case 75:
                        printf("\nSeta Esquerda");
                        break;
                    case 72:
                        printf("\nSeta Cima");
                        break;
                    case 82:
                        printf("\nInsert");
                        break;
                    case 83:
                        printf("\nDelete");
                        break;
                    case 79:
                        printf("\nEnd");
                        break;
                    case 71:
                        printf("\nHome");
                        break;
                    case 73:
                        printf("\nPageUP");
                        break;
                    case 81:
                        printf("\nPageDown");
                        break;
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
