#include <stdio.h>
#include <conio.h>  // Para _kbhit() e _getch()

int main() {
    printf("Digite algo (Pressione 'q' para sair):\n");

    do {
        // Verifica se alguma tecla foi pressionada
        if (_kbhit()) {
            // L� a tecla pressionada
            char tecla = _getch();

            // Verifica se a tecla 'q' foi pressionada para sair do programa
            if (tecla == 'q' || tecla == 'Q') {
                printf("Tecla 'q' pressionada. Finalizando o programa.\n");
                break;
            }

            // Imprime a tecla digitada pelo usu�rio
            printf("Tecla digitada: %c\n", tecla);
        }

        // Adicione outras verifica��es de teclas conforme necess�rio

    } while (1);  // Loop infinito

    return 0;
}
