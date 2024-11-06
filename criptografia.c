#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define true 1
#define false 0

// Função para verificar se um número é primo
int verif_primo(int num) {
    if (num < 2 || (num != 2 && num % 2 == 0)) return false;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) return false;
    }
    return true;
}

// Função para calcular o MDC entre dois números
int mdc(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Função para calcular o inverso modular
int inverso_modular(int e, int Z) {
    int t = 0, t_02 = 1;
    int r = Z, r_02 = e;
    while (r_02 != 0) {
        int q = r / r_02;
        int temp = t;
        t = t_02;
        t_02 = temp - q * t_02;
        temp = r;
        r = r_02;
        r_02 = temp - q * r_02;
    }
    if (t < 0) t += Z;
    return t;
}

// Função para cálculo modular rápido
long long exp_mod(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// Função para criptografar um caractere
int criptografar_caractere(int m, int e, int n) {
    return exp_mod(m, e, n);
}

// Função para descriptografar um caractere
int descriptografar_caractere(int c, int d, int n) {
    return exp_mod(c, d, n);
}

int main() {
    char comando[20];
    int p, q, e, d, n;
    
    // Lê o comando
    if (scanf("%s", comando) != 1) {
        fprintf(stderr, "Erro ao ler comando.\n");
        return 1;
    }

    if (strcmp(comando, "gerar") == 0) {
        // Leitura dos valores de p, q e e
        scanf("%d %d %d", &p, &q, &e);

        // Verificação de primalidade de p e q
        if (!verif_primo(p)) {
            fprintf(stderr, "Erro: p não é primo.\n");
            return 1;
        }
        if (!verif_primo(q)) {
            fprintf(stderr, "Erro: q não é primo.\n");
            return 1;
        }

        // Calcula n e Z
        n = p * q;
        int Z = (p - 1) * (q - 1);

        // Verifica se e é coprimo com Z
        if (mdc(e, Z) != 1) {
            fprintf(stderr, "Erro: e não é coprimo com Z.\n");
            return 1;
        }

        // Calcula d (inverso modular de e)
        d = inverso_modular(e, Z);

        // Exibe as chaves e outros valores
        printf("%d %d %d\n", n, e, d);

        // Lê e criptografa a mensagem
        char mensagem[256];
        scanf(" %[^\n]", mensagem);  // Lê a linha inteira para a mensagem
        printf("Mensagem criptografada: ");
        for (int i = 0; mensagem[i] != '\0'; i++) {
            int m = (int)mensagem[i];
            if (m >= 32 && m <= 126) {
                int c = criptografar_caractere(m, e, n);
                printf("%d ", c);
            }
        }
        printf("\n");

    } else if (strcmp(comando, "descriptografar") == 0) {
        // Leitura dos valores de d, n e valores criptografados
        scanf("%d %d", &d, &n);

        int c;
        printf("Mensagem descriptografada: ");
        while (scanf("%d", &c) == 1) {
            int m = descriptografar_caractere(c, d, n);
            if (m >= 32 && m <= 126) {
                printf("%c", (char)m);
            }
        }
        printf("\n");
    }

    return 0;
}
