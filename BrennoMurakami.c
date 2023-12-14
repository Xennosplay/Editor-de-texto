#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include "BrennoMurakamiEstrutura.h"
#include "BrennoMurakamiFuncoes.h"


//Função para monitorar as teclas a todo momento, presos em um laço de repetição para capturar entradas a todo tempo
void monitoramento_teclas(LISTA **lista, int *x, int *y){
    setlocale(LC_ALL, "Portuguese");
    int tecla, backspace = 0;
    int linha_criada = 0;
    LISTA *q, *aux;
    FILE *arquivo;
    char nomeArquivo[40];
    int i, j;
    int ins = 0;
    char c;
    do {
        if (_kbhit()) {
            tecla = _getch();
            //Teclas especiais
            if (tecla == 224 || tecla == 0) {
                tecla = _getch();
                switch (tecla){
                    //F1
                    //Função para imprimir o arquivo de ajuda, e após imprimir entra num looping que só sai quando o usuário pressiona ESC
                    case 59:
                        printarArquivo();
                        exibir(*lista);
                        atualizar_cursor(*x, *y);
                        break;
                    //F2
                    case 60:
                        q = retornar_no_atual(*lista, 0);
                        salvar_arquivo(q);
                        limpar_tela();
                        printf("Arquivo Salvo\n");
                        system("pause");
                        limpar_tela();
                        exibir(*lista);
                        atualizar_cursor(*x, *y);
                        break;
                    //F10
                    case 68:
                        setlocale(LC_ALL, "Portuguese");
                        limpar_tela();

                        printf("Digite o nome do arquivo a ser lido: ");
                        fflush(stdin);
                        scanf("%[^\n]s", nomeArquivo);
                        arquivo = fopen(nomeArquivo, "r");

                        if(arquivo != NULL){
                            limpar_estrutura(lista);
                            inicializar(lista);
                            criar_linha_comeco(lista);
                            linha_criada = 1;
                            q = *lista;
                            i = 0;
                            while((c = fgetc(arquivo)) != EOF){

                                if(i == 90 && c != '\n'){
                                    q->linha[90] = '\n';
                                    q->tam++;
                                    criar_linha_final(lista);
                                    linha_criada++;
                                    q = q->next;
                                    i = 0;
                                }
                                else if(c == '\n'){
                                    q->linha[i] = c;
                                    q->tam++;
                                    criar_linha_final(lista);
                                    linha_criada++;
                                    q = q->next;
                                    i = 0;
                                }
                                else{
                                    q->linha[i] = c;
                                    q->tam++;
                                    i++;
                                }
                            }
                            *x = q->tam+2;
                            *y = linha_criada;
                        }
                        else{
                            limpar_tela();
                            printf("Arquivo inexistente.\n");
                            system("pause");
                        }
                        limpar_tela();
                        exibir(*lista);
                        atualizar_cursor(*x,*y);
                        break;
                    //F12
                    //Função para aparecer as informações do aluno na tela, entrando em um looping que só finaliza quando o aluno aperta ESC
                    case 134:
                        dados_aluno();
                        exibir(*lista);
                        atualizar_cursor(*x, *y);
                        break;
                    //SETA DIREITA
                    //Função para mover o cursor para frente, caso o cursor exceda o ultimo caracter, ele vai pro começo da linha de baixo(caso houver)
                    case 77:
                        q = retornar_no_atual(*lista, (*y)-1);
                        if(*x < q->tam+2 && q->linha[(*x)-1] != '\n'){
                            aumentar_x(x,y);
                        }
                        else{
                            if(q->next != NULL){
                                q = q->next;
                                (*y)++;
                                *x = 1;
                                atualizar_cursor(*x, *y);
                            }
                        }
                        break;
                    //SETA BAIXO
                    //Função para mover o cursor para a linha de baixo caso houver, se a posição do cursor na linha exceder
                    //o número de caracteres da linha de baixo, o x é setado para o último caractere desta linha.
                    case 80:
                        q = retornar_no_atual(*lista, (*y)-1);
                        if(q->next != NULL){
                            q = q->next;
                            if((*x)-2 > q->tam){
                                if(q->linha[q->tam] == '\n'){
                                    *x = q->tam+1;
                                }
                                else{
                                    *x = q->tam+2;
                                }
                            }
                            (*y)++;
                            atualizar_cursor(*x, *y);
                        }
                        break;
                    //SETA ESQUERDA
                    //Função para mover o cursor para a esquerda, se houver uma linha acima e o cursor estiver no começo da tela
                    //ele vai para o último caractere da linha de cima, caso o contrário, não acontece nada.
                    case 75:
                        if(*y > 1){
                            q = retornar_no_anterior(*lista, (*y)-1);
                            if(*x > 1){
                            (*x)--;
                            }
                            else{
                                if(q->linha[q->tam] == '\n'){
                                    *x = q->tam+1;
                                }
                                else{
                                    *x = q->tam+2;
                                }
                                (*y)--;
                            }
                        }
                        else{
                            if(*x > 1){
                                (*x)--;
                            }
                        }
                        atualizar_cursor(*x, *y);
                        break;
                    //SETA CIMA
                    //Função para mover o cursor para cima, se o cursor da linha de baixo estiver numa posição acima da quantidade
                    //dos caracteres da linha de cima, x é setado para o último caractere da linha de cima.
                    case 72:
                        if(*y > 1){
                            q = retornar_no_anterior(*lista, (*y)-1);
                            if(*x > q->tam+1){
                                *x = q->tam+1;
                            }
                            (*y)--;
                            atualizar_cursor(*x, *y);
                        }
                        break;
                    //INSERT
                    case 82:
                        if(ins == 0){
                            ins = 1;
                        }
                        else{
                            ins = 0;
                        }
                        break;
                    //DELETE
                    //Nesta função, é apagado o caractere que estiver à frente do cursor,
                    //e se o caractere for o último, todo o conteúdo de baixo vai para a linha de cima, vulgo onde o cursor está posicionado(se o vetor estiver cheio, ele para de puxar o resto).
                    case 83:
                        q = retornar_no_atual(*lista, (*y)-1);
                        if(q->linha[(*x)-1] != '\n' && (*x)-1 < q->tam){
                            remover_caractere_posicao(lista, (*y)-1, (*x)-1);
                        }
                        else if(q->next != NULL){
                            aux = retornar_no_atual(*lista, (*y)-1);
                            aux = aux->next;
                            i = 0;
                            while(q->tam < 89 && i <= aux->tam){
                                if(aux->linha[i] != '\n'){
                                    inserir_caractere_posicao(lista, aux->linha[i],(*y)-1, q->tam);
                                }
                                i++;
                            }

                            if(aux->tam == -1 || aux->linha[0] == '\n'){
                                remover_linha_posicao(lista, *y);
                            }
                            else{
                                while(i >= 0){
                                    if(aux->linha[i] != '\n'){
                                        remover_caractere_posicao(lista, *y, i);
                                    }
                                    i--;
                                }
                                if(aux->tam == -1 || aux->linha[0] == '\n'){
                                    remover_linha_posicao(lista, *y);
                                }
                            }
                        }
                        else{
                            if((*x)-1 != q->tam+1){
                                remover_caractere_posicao(lista, (*y)-1, (*x)-1);
                            }
                        }

                        limpar_tela();
                        exibir(*lista);
                        atualizar_cursor(*x, *y);
                        break;
                    //END
                    //Para a função END, o cursor é posicionado no último caractere sem ser o '\n' que representa a quebra de linha.
                    case 79:
                        q = retornar_no_atual(*lista, (*y)-1);
                        if(q->linha[q->tam] == '\n'){
                            *x = q->tam+1;
                        }
                        else{
                            *x = q->tam+2;
                        }

                        limpar_tela();
                        exibir(*lista);
                        atualizar_cursor(*x, *y);
                        break;
                    //HOME
                    //O cursor apenas é posicionado no começo da tela, não é necessária nenhuma validação, já que toda linha tem um começo;
                    case 71:
                        *x = 1;
                        atualizar_cursor(*x, *y);
                        break;
                    //PAGEUP
                    //Função retorna o nó atual e percorre até o primeiro nó ou até o i incrementar 25 vezes, depois se o nó inicial estiver maior que o número
                    //de caracteres que a linha de destino, o x é setado para o último caracter do nó de destino
                    case 73:
                        i = 0;
                        while(*y > 1 && i < 25){
                            i++;
                            (*y)--;
                        }
                        q = retornar_no_atual(*lista, (*y)-1);

                        if(*x > q->tam+2){
                            if(q->linha[q->tam] == '\n'){
                                *x = q->tam+1;
                            }
                            else{
                                *x = q->tam+2;
                            }
                        }
                        atualizar_cursor(*x, *y);

                        break;
                    //PAGEDOWN
                    //Função retorna o nó atual e percorre até o último nó ou até o i incrementar 25 vezes, depois se o nó inicial estiver maior que o número
                    //de caracteres que a linha de destino, o x é setado para o último caracter do nó de destino
                    case 81:
                        q = retornar_no_atual(*lista, (*y)-1);
                        i = 0;
                        while(q->next != NULL && i < 25){
                            q = q->next;
                            i++;
                            (*y)++;
                        }

                        if(*x > q->tam+2){
                            if(q->linha[q->tam] == '\n'){
                                *x = q->tam+1;
                            }
                            else{
                                *x = q->tam+2;
                            }

                        }
                        atualizar_cursor(*x, *y);
                        break;
                }
            } else{
                //BACKSPACE
                //Nesta função, a função apaga o caractere que antescede o cursor, neste caso em específico, se o cursor estiver no começo da linha, todo o conteúdo dela vai para a linha de cima.
                if (tecla == 8) {
                    if(*x == 1 && *y > 1){
                        q = retornar_no_anterior(*lista, (*y)-1);
                        aux = retornar_no_atual(*lista, (*y)-1);
                        if(q->tam == 90){
                            (*y)--;
                            *x = 92;
                            limpar_tela();
                            exibir(*lista);
                            diminuir_x(x, y);
                        }
                        else{
                            if(aux->tam > -1){
                                i = 0;
                                while( i <= aux->tam && q->tam < 89){
                                    if(aux->linha[i] != '\n'){
                                        inserir_caractere_posicao(lista, aux->linha[i], (*y)-2, q->tam);
                                    }
                                    i++;
                                    backspace++;
                                }

                                while( i >= 0){
                                    if(aux->linha[i] != '\n'){
                                        remover_caractere_posicao(lista, (*y)-1, i);
                                    }
                                    i--;
                                }
                            }
                            if(aux->tam == -1 || aux->linha[0] == '\n'){
                                remover_linha_posicao(lista,(*y)-1);
                            }
                            limpar_tela();
                            exibir(*lista);

                            if(q->linha[q->tam] != '\n'){
                                *x = q->tam+2 - backspace;
                            }
                            else{
                                *x = q->tam+1 - backspace;
                            }
                            backspace = 0;
                            (*y)--;
                            atualizar_cursor(*x, *y);
                        }
                    }
                    else if(*x != 1){
                        remover_caractere_posicao(lista,(*y)-1, (*x)-2);
                        limpar_tela();
                        exibir(*lista);
                        diminuir_x(x, y);
                    }
                }
                //ESC
                else if(tecla == 27){
                    do{
                        limpar_tela();
                        printf("\nDeseja salvar as informações antes de sair?");
                        printf("\n[S] / [N]: ");
                        scanf("%c", &c);
                        if(c == 'S' || c == 's'){
                            q = retornar_no_atual(*lista, 0);
                            salvar_arquivo(q);
                            limpar_tela();
                            printf("\nArquivo Salvo, encerrando o programa");
                        }
                        else if(c == 'N' || 'n'){
                            printf("\nPrograma encerrado.");
                        }
                        else{
                            printf("\nDigite algo valido");
                        }
                    }while(c != 'S' && c!= 's' && c != 'N' && c != 'n');
                    break;
                }
                //ENTER
                //Função para inserir uma quebra de linha no final de cada linha, caso já ouver uma quebra de linha, cria um outro nó após o atual e coloca uma quebra de linha na primeira
                //posição do nó criado, acompanhando o cursor para o novo nó para inserções
                else if(tecla == 13){
                    q = retornar_no_atual(*lista, (*y)-1);

                    if(q->linha[q->tam] != '\n'){
                        inserir_caractere_final(lista,'\n', (*y)-1);
                    }
                    else if(q->linha[q->tam] == '\n'){
                    }

                    criar_linha_posicao(lista, (*y)-1);

                    if((*x)-1 < q->tam){
                        i = (*x)-1;
                        while(i < q->tam){
                            if(q->linha[i] != '\n'){
                                inserir_caractere_final(lista, q->linha[i], *y);
                            }
                            i++;
                        }

                        while(i >= (*x)-1){
                            if(q->linha[i] != '\n'){
                                remover_caractere_posicao(lista, (*y)-1, (*x)-1);
                            }
                            i--;
                        }
                    }

                    q = q->next;
                    if(q->next != NULL){
                        inserir_caractere_final(lista,'\n', *y);
                    }
                    limpar_tela();
                    exibir(*lista);
                    (*y)++;
                    *x = 1;
                    atualizar_cursor(*x, *y);
                }
                //TAB
                else if(tecla == 9){
                    q = retornar_no_atual(*lista, (*y)-1);
                    i = 0;
                    while((*x)-1 < 89 && i <= 1){
                        if((*x) < q->tam+2 && q->tam == 90){
                            descer_caracteres(lista, (*y)-1, ' ', (*x)-1);
                        }
                        else{
                            inserir_caractere_posicao(lista, ' ', (*y)-1, *(x)-1);
                        }
                        aumentar_x(x, y);
                        i++;
                    }
                    limpar_tela();
                    exibir(*lista);
                    atualizar_cursor(*x, *y);
                }
                //Se não for nenhuma das teclas acima, significa que é uma tecla de inserção padrão, neste caso armazena o caracter da estrutura, e se exceder o limite da tela/vetor
                //cria outro nó e vai para a linha de baixo continuando a preencher os dados
                else if(tecla >= 32 && tecla <= 126){
                    if(*x == 90){
                        q = retornar_no_atual(*lista, (*y)-1);

                        if(q->linhaa[q->tam] != '\n'){
                            inserir_caractere_posicao(lista,'\n', (*y)-1, (*x)-1);
                        }else{
                            criar_linha_posicao(lista, (*y)-1);
                            inserir_caractere_posicao(lista, '\n', *y, 0);
                        }

                        if(q->next == NULL){
                            criar_linha_final(lista);
                        }
                    }
                    if(ins == 1){
                        if(*x == 91){
                            q = retornar_no_atual(*lista, (*y)-1);
                            q = q->next;
                            *x = 1;
                            if((*x) < q->tam+2 && q->linha[(*x)-1] != '\n'){
                                remover_caractere_posicao(lista, (*y), 0);
                            }
                            inserir_caractere_posicao(lista, tecla, (*y), 0);
                            (*y)++;
                        }
                        else{
                            q = retornar_no_atual(*lista, (*y)-1);
                            if((*x) < q->tam+2 && q->linha[(*x)-1] != '\n'){
                                remover_caractere_posicao(lista, (*y)-1, (*x)-1);
                            }
                            inserir_caractere_posicao(lista, tecla, (*y)-1, (*x)-1);
                        }

                    }
                    else{
                        if(*x == 91){
                             q = retornar_no_atual(*lista, (*y)-1);
                             q = q->next;
                            if((*x) < q->tam+2 && q->tam == 90){
//                                system("pause");
                                descer_caracteres(lista, (*y), tecla, 0);
                                inserir_caractere_comeco(lista, tecla, *y);
                            }
                            else{
                                inserir_caractere_comeco(lista, tecla, *y);
                                *x = 1;
                                (*y)++;
                            }
                        }
                        else{
                            q = retornar_no_atual(*lista, (*y)-1);
                            if((*x) < q->tam+2 && q->tam == 90){
                                descer_caracteres(lista, (*y)-1, tecla, (*x)-1);
                            }
                            else{
                                inserir_caractere_posicao(lista, tecla, (*y)-1, (*x)-1);
                            }
                        }
                    }
                    limpar_tela();
                    exibir(*lista);
                    aumentar_x(x, y);
                }
            }
        }
    } while (1);
}

void main() {
    LISTA *lista;
    int x, y;
    terminal();
    x = 1;
    y = 1;
    setlocale(LC_ALL, "Portuguese");
    terminal();
    gotoxy(x, y);
    inicializar(&lista);
    criar_linha_comeco(&lista);
    limpar_tela();
    monitoramento_teclas(&lista, &x, &y);
}
