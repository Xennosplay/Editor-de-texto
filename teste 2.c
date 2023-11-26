#include <stdio.h>
#include <conio.h>

void monitoramento_teclas(){
    char entrada[256];  // Array para armazenar a entrada do usuário
    int posicao = 0, tecla;    // Posição atual na entrada
    printf("(Pressione 'ESC' para sair):\n");
    do {
        if (_kbhit()) {
            tecla = _getch();

            //ESC
            if (tecla == 27) {
                printf("Tecla 'ESC' pressionada. Finalizando o programa.\n");
                break;
            }

            //Backspace
            if (tecla == 8 && posicao > 0) {
                printf("\b \b");  // Move o cursor uma posição para trás e apaga o caractere
                posicao--;
                entrada[posicao] = '\0';  // Remove o último caractere da entrada
            } else if(tecla != 224 || tecla != 0 || tecla != 134){
                printf("%c", tecla);
                entrada[posicao] = tecla;  // Armazena o caractere na entrada
                posicao++;
            }

            //Teclas especiais
            if (tecla == 224 || tecla == 0) {
                tecla = _getch();
                switch (tecla){
                    case 59:
                        printf("\nTecla F1 pressionada.\n");
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
    monitoramento_teclas();
}
