#include <stdio.h>
#include <windows.h>

void main() {
    printf("Pressione uma tecla (Pressione 'q' para sair):\n");

    int estadoAnterior[12] = {0}; // Inicializa todos os estados como não pressionados

    do {
        for (int tecla = 1; tecla <= 12; ++tecla) {

            int estadoAtual = GetAsyncKeyState(VK_F1 + tecla - 1) & 0x8001;

            if (estadoAtual && !estadoAnterior[tecla - 1]) {
                printf("Tecla de funcao pressionada: F%d\n", tecla);
            }

            estadoAnterior[tecla - 1] = estadoAtual;
        }

        if (GetAsyncKeyState(VK_ESCAPE) & 0x8001) {
                return;
        }


    } while (1);
    printf("Ate mais.");
}
