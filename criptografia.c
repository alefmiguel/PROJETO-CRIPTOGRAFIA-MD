#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <gmp.h>

#define true 1
#define false 0

// Função para verificar se um número é primo
long long int verif_primo( long long int num) {
    if (num < 2 || (num != 2 && num % 2 == 0)) return false;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) return false;
    }
    return true;
}

// Função para calcular o MDC entre dois números
long long int mdc(long long int a, long int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Função para calcular o inverso modular
long long int inverso_modular(long long int e, long long int Z) {
    long long int t = 0, t_02 = 1;
    long long int r = Z, r_02 = e;
    while (r_02 != 0) {
        long long int q = r / r_02;
        long long int temp = t;
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
void exp_mod(mpz_t result, mpz_t base, mpz_t exp, mpz_t mod) {

    mpz_t BASE, EXP;
    mpz_init_set(BASE, base);  
    mpz_init_set(EXP, exp);    

    mpz_set_ui(result, 1);  

    while (mpz_cmp_ui(EXP, 0) > 0) {
        if (mpz_odd_p(EXP)) {  
            mpz_mul(result, result, BASE);
            mpz_mod(result, result, mod);
        }
        mpz_mul(BASE, BASE, BASE);
        mpz_mod(BASE, BASE, mod);

        mpz_fdiv_q_2exp(EXP, EXP, 1);  
    }

    mpz_clear(BASE);
    mpz_clear(EXP);
}


int main() {
    char comando[20];
    long long int p, q, e, d, n;
    
    // Lê o comando
    if (scanf("%s", comando) != 1) {
        fprintf(stderr, "Erro ao ler comando.\n");
        return 1;
    }

    if (strcmp(comando, "gerar") == 0) {
        // Leitura dos valores de p, q e e
        scanf("%lld %lld %lld", &p, &q, &e);

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
        long long int Z = (p - 1) * (q - 1);

        // Verifica se e é coprimo com Z
        if (mdc(e, Z) != 1) {
            fprintf(stderr, "Erro: e não é coprimo com Z.\n");
            return 1;
        }

        // Calcula d (inverso modular de e)
        d = inverso_modular(e, Z);

        // Exibe as chaves e outros valores
        printf("Chave Pública: (%lld, %lld)\n", e, n);
        printf("Chave Privada: (%lld, %lld)\n", d, n);

        // Lê e criptografa a mensagem
        char mensagem[256];
        scanf(" %[^\n]", mensagem);  // Lê a linha inteira para a mensagem
        printf("Mensagem criptografada: ");

        for (int i = 0; mensagem[i] != '\0'; i++) {
            int m = (int)mensagem[i];
           // unsigned long long int C;
            /// C recebrá valor encriptado;
           mpz_t gmp_E, gmp_N, gmp_men, gmp_result;

            mpz_init_set_si(gmp_E, e);
            mpz_init_set_si(gmp_N, n);
            mpz_init_set_si(gmp_men, m);
            mpz_init_set_ui(gmp_result, 1);

            if (m >= 32 && m <= 126) {

            exp_mod(gmp_result, gmp_men, gmp_E, gmp_N);

            //C = mpz_get_ui(gmp_result);

            gmp_printf("%Zd ", gmp_result);

            mpz_clears(gmp_result, gmp_men, gmp_N, gmp_E, NULL);
            
            }
        }
        printf("\n");

    } else if (strcmp(comando, "descriptografar") == 0) {
        // Leitura dos valores de d, n e valores criptografados
       
        mpz_t gmp_d, gmp_n;

       
        mpz_inits(gmp_d, gmp_n, NULL);
       
        gmp_scanf("%Zd %Zd", gmp_d, gmp_n);

        
        long long int c;
        printf("Mensagem descriptografada: ");


        while (scanf("%lld", &c) == 1) {
            mpz_t gmp_c, gmp_result;

            mpz_init_set_si(gmp_c, c);
            mpz_init_set_ui(gmp_result, 1);

            exp_mod(gmp_result, gmp_c, gmp_d,gmp_n);

            int men = mpz_get_ui(gmp_result);
           
            char MEN = men;

            if (men >= 32 && men <= 126) {
                printf("%c", (char)MEN);
               }
        }
        printf("\n");
    }

    return 0;
}