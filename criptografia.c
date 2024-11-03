#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define true 1
#define false 0

// Verifica se um número é primo
int verif_primo(int num) {
    if (num < 2 || (num != 2 && num % 2 == 0)) return false;
    
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) return false;
    }
    
    return true;
}

// Calcula o MDC entre dois números
int mdc(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Calcula o inverso modular
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

// Calcula (base^exp) % mod de forma eficiente
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

// Criptografa um caractere por vez
int criptografar_caractere(int m, int e, int n) {
    return exp_mod(m, e, n);
}

// Descriptografa um caractere por vez
int descriptografar_caractere(int c, int d, int n) {
    return exp_mod(c, d, n);
}

// Gera as chaves pública e privada de acordo com p e q 
int gerar_chaves(int* n, int* e, int* d) {
    int p, q;
    scanf("%d", &p);
    if (!verif_primo(p)) {
        printf("Erro: p não é primo.\n");
        return 0;
    }
    scanf("%d", &q);
    if (!verif_primo(q)) {
        printf("Erro: q não é primo.\n");
        return false;
    }

    *n = p * q;
    int Z = (p - 1) * (q - 1);
    scanf("%d", e);
    
    if (mdc(*e, Z) != 1) {
        printf("Erro: e não é coprimo com Z.\n");
        return false;
    }

    *d = inverso_modular(*e, Z);
    printf("%d %d %d\n", *n, *e, *d); // Retorna n, e, d
    return 1;
}

int main() {
    int n, e, d;
    char modo[10];

    // Lê o modo de operação
    scanf("%s", modo);
    
    if (strcmp(modo, "gerar") == 0) {
        // Gerar chaves públicas e privadas
        if (!gerar_chaves(&n, &e, &d)) {
            return 1;
        }
        
        // Criptografar a mensagem
        char mensagem[256];
        getchar(); // Limpar o buffer
        fgets(mensagem, 256, stdin);
        
        printf("Mensagem criptografada: ");
        for (int i = 0; mensagem[i] != '\0'; i++) {
            int m = (int)mensagem[i];
            if (m >= 32 && m <= 126) {
                int aux = criptografar_caractere(m, e, n);
                printf("%d ", aux);
            }
        }
        printf("\n");

    } else if (strcmp(modo, "descriptografar") == 0) {
        // Ler chave privada d e n
        scanf("%d %d", &d, &n);
        
        // Descriptografar a mensagem
        int c;
        printf("Mensagem descriptografada: ");
        while (scanf("%d", &c) == true) {
            int m = descriptografar_caractere(c, d, n);
            if (m >= 32 && m <= 126) {
                printf("%c", (char)m);
            }
        }
        printf("\n");
    } else {
        printf("Modo inválido.\n");
    }

    return 0;
}
