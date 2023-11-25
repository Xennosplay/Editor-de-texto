#include <stdio.h>
#include <conio.h>

int main() {
    printf("Digite algo (Pressione 'q' para sair):\n");

    char entrada[256];  // Array para armazenar a entrada do usu�rio
    int posicao = 0;    // Posi��o atual na entrada

    do {
        if (_kbhit()) {
            char tecla = _getch();

            // Verifica se a tecla 'q' foi pressionada para sair do programa
            if (tecla == 27) {
                printf("Tecla 'ESC' pressionada. Finalizando o programa.\n");
                break;
            }

            // Verifica se a tecla Backspace foi pressionada para apagar o �ltimo caractere
            if (tecla == 8 && posicao > 0) {
                printf("\b \b");  // Move o cursor uma posi��o para tr�s e apaga o caractere
                posicao--;
                entrada[posicao] = '\0';  // Remove o �ltimo caractere da entrada
            } else {
                printf("%c", tecla);
                entrada[posicao] = tecla;  // Armazena o caractere na entrada
                posicao++;
            }

            if (tecla == 0 || tecla == 224) {
                printf("\nTecla F1 pressionada.\n");
            }
        }

    } while (1);  // Loop infinito

    return 0;
}
