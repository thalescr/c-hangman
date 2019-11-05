#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 256

void clear() {
    #ifdef linux
    system("clear");
    #endif
    #ifdef _WIN32
    system("cls");
    #endif
}

int printaForca(int tentativas[26], int n, char *atual) {
    int i, count = 0;
    clear();
    for(i = 0; i < 26; i ++) {
        if(tentativas[i] == -1) {
            printf("%c ", i + 65);
            count++;
        }
    }
    printf("\n|-----|");
    printf("\n|     |");
    if(count > 0)
        printf("\n|     O");
    else
        printf("\n|");
    if(count > 5)
        printf("\n|    /|\\");
    else if(count > 4)
        printf("\n|    /|");
    else if(count > 1)
        printf("\n|     |");
    else
        printf("\n|");
    if(count > 3)
        printf("\n|    / \\");
    else if(count > 2)
        printf("\n|    /");
    else
        printf("\n|");
    printf("\n|");
    printf("\n|");

    if(count > 5)
        return -1;

    count = 0;
    for(i = 0; i < n; i ++) {
        printf("%c ", atual[i]);
        if(atual[i] == '_')
            count++;
    }
    printf("\n");

    if(count == 0)
        return 0;
    
    return 1;

}

int main() {
    char resposta[MAX], letra;
    int tentativas[26] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    printf("Joguinho de forca!\n");
    printf("Digite a palavra: ");
    scanf("%s", resposta);
    int n = strlen(resposta), i, count, fim = 1;

    char atual[n];
    for(i = 0; i < n; i ++) {
        resposta[i] = toupper(resposta[i]);
        atual[i] = '_';
    }

    printaForca(tentativas, n, atual);

    while(fim == 1) {
        letra = 0;
        while(letra < 65 || letra > 90) {
            getchar();
            printf("Digite uma letra: ");
            scanf("%c", &letra);
            letra = toupper(letra);
        }

        if(tentativas[letra - 65] == 0) {
            count = 0;
            for(i = 0; i < n; i ++) {
                if(resposta[i] == letra) {
                    count++;
                    atual[i] = letra;
                    tentativas[letra - 65] = 1;
                }
            }
            if(count == 0) {
                tentativas[letra - 65] = -1;
                fim = printaForca(tentativas, n, atual);
                printf("Errou!\n");
            }
            else {
                fim = printaForca(tentativas, n, atual);
                printf("Acertou %d letra(s)!\n", count);
            }
        
        }
        else {
            fim = printaForca(tentativas, n, atual);
            printf("Voce ja digitou essa letra!\n");
        }
    }

    if(fim == -1)
        printf("\nVoce perdeu!\n");
    else
        printf("Parabens! Voce advinhou!\n");

}