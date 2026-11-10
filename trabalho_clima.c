#include <stdio.h>
#define M_SECOS 10       // quantos dias mais secos listar
#define MAX_DADOS 10500  // capacidade dos vetores (os arquivos têm até 10.000)

typedef struct {
    int id_sensor;
    char datas[11];
    float temperaturas_c;
    int umidade;
    float particulas25;
} Registro; // apelido que dei pra struct

long long comparacoes = 0;

// copia n elementos de origem para destino
void copiar(float *destino, float *origem, int n) {
    for (int j = 0; j < n; j++) {
        destino[j] = origem[j];
    }
}

// ABORDAGEM A: BOLHA
void abordagem_a(float *vetor, int n) {
    for (int i = 0; i < n - 1; i++) {
        int trocou = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            comparacoes++;
            if (vetor[j] > vetor[j + 1]) {
                float aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
                trocou = 1;
            }
        }
        if (trocou == 0) {
            break;
        }
    }
}

// ABORDAGEM B: PARTICIONAMENTO
float abordagem_B(float *vetor, int n, int k) {
    int inicio = 0;
    int fim = n - 1;
    int posicao_procurada = k - 1;   // posicao procurada (indice comeca em 0)

    while (inicio < fim) {
        // 1) pivo central, levado para o fim do trecho
        int meio = (inicio + fim) / 2;
        float aux = vetor[meio];
        vetor[meio] = vetor[fim];
        vetor[fim] = aux;
        float pivo = vetor[fim];

        // 2) particao: i marca onde vai o proximo elemento menor que o pivo
        int i = inicio;
        for (int j = inicio; j < fim; j++) {
            comparacoes++;
            if (vetor[j] < pivo) {
                aux = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = aux;
                i++;
            }
        }

        // 3) pivo vai para a sua posicao final (i)
        aux = vetor[i];
        vetor[i] = vetor[fim];
        vetor[fim] = aux;

        // 4) decide para que lado continuar
        if (posicao_procurada == i) {
            return vetor[i];
        } else if (posicao_procurada < i) {
            fim = i - 1;
        } else {
            inicio = i + 1;
        }
    }
    return vetor[inicio];
}

// ABORDAGEM C: CONTAGEM COMPARATIVA SEQUENCIAL
float abordagem_C(float *vetor, int n, int k) {
    for (int i = 0; i < n; i++) {
        float x = vetor[i];
        int menores = 0;   // quantos sao menores que x
        int iguais = 0;    // quantos sao iguais a x (incluindo ele mesmo)

        for (int j = 0; j < n; j++) {
            comparacoes++;
            if (vetor[j] < x) {
                menores++;
            } else {
                comparacoes++;
                if (vetor[j] == x) {
                    iguais++;
                }
            }
        }
        // x ocupa as posicoes menores+1 ... menores+iguais no vetor ordenado
        if (menores < k && k <= menores + iguais) {
            return x;
        }
    }
    return -1;   // nao deveria chegar aqui se 1 <= k <= n
}

    int main(void) {
    float pm25[MAX_DADOS];
    float umid[MAX_DADOS];
    float copia[MAX_DADOS];
    int quantidade = 0;

    const char *arquivos[3] = {
        "dados_clima_manaus_1e3.csv",
        "dados_clima_manaus_5e3.csv",
        "dados_clima_manaus_1e4.csv"
    };

    // 1. Abre o arquivo pelo nome (o teclado fica livre para o menu)
    int lido;
    printf("Digite o numero do arquivo que deseja ler:\n 1 - 1000\n 2 - 5000\n 3 - 10.000\nEscolha: ");
    scanf("%d", &lido);

    const char *nome;
    switch (lido) {
        case 1: nome = arquivos[0]; break;
        case 2: nome = arquivos[1]; break;
        case 3: nome = arquivos[2]; break;
        default:
            printf("Opcao invalida\n");
            return 1;
}
   

    FILE *arq = fopen(nome, "r");
    if (arq == NULL) {
        printf("Nao foi possivel abrir %s\n", nome);
        return 1;
    }

    fscanf(arq, "%*[^\n]");   // descarta o cabecalho

    Registro temp;
    while (quantidade < MAX_DADOS &&
           fscanf(arq, " %d,%10[^,],%f,%d,%f",
                  &temp.id_sensor,
                  temp.datas,
                  &temp.temperaturas_c,
                  &temp.umidade,
                  &temp.particulas25) == 5) {
        pm25[quantidade] = temp.particulas25;
        umid[quantidade] = temp.umidade;   // int vira float
        quantidade++;
    }
    fclose(arq);

    printf("Registros lidos: %d\n", quantidade);
    if (quantidade == 0) {
        return 1;
    }

    int k_mediana = quantidade / 2;             // k com indice 1
    int k_p90 = (9 * quantidade + 9) / 10;      // teto(0,9 * N), em inteiros


    int opcao;
    do {
        printf("\n1 - Bolha (A)\n2 - Particao (B)\n3 - Contagem (C)\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                // ABORDAGEM A: mediana e P90
                copiar(copia, pm25, quantidade);
                comparacoes = 0;
                abordagem_a(copia, quantidade);
                long long comp_A = comparacoes;
                float mediana_A = copia[k_mediana - 1];
                float p90_A = copia[k_p90 - 1];

                // ABORDAGEM A: dias secos
                float secos_A[M_SECOS];
                copiar(copia, umid, quantidade);
                comparacoes = 0;
                abordagem_a(copia, quantidade);
                long long secos_comp_A = comparacoes;
                for (int s = 0; s < M_SECOS; s++) {
                    secos_A[s] = copia[s];
                }

                printf("\n  A: mediana = %.1f | P90 = %.1f\n", mediana_A, p90_A);
                printf("  Dias mais secos (%d menores umidades):\n  ", M_SECOS);
                for (int s = 0; s < M_SECOS; s++) {
                    printf("%.0f ", secos_A[s]);
                }
                printf("\n\n  comparacoes (mediana + P90): %lld\n", comp_A);
                printf("  comparacoes (dias secos):    %lld\n", secos_comp_A);
                break;
            }
            case 2: {
                // ABORDAGEM B: mediana e P90
                copiar(copia, pm25, quantidade);
                comparacoes = 0;
                float mediana_B = abordagem_B(copia, quantidade, k_mediana);
                long long comp_B = comparacoes;

                copiar(copia, pm25, quantidade);
                comparacoes = 0;
                float p90_B = abordagem_B(copia, quantidade, k_p90);
                comp_B += comparacoes;

                // ABORDAGEM B: dias secos
                float secos_B[M_SECOS];
                copiar(copia, umid, quantidade);
                comparacoes = 0;
                abordagem_B(copia, quantidade, M_SECOS);
                long long secos_comp_B = comparacoes;   // salva ANTES de ordenar
                abordagem_a(copia, M_SECOS);            // so para exibir em ordem
                for (int s = 0; s < M_SECOS; s++) {
                    secos_B[s] = copia[s];
                }

                printf("\n  B: mediana = %.1f | P90 = %.1f\n", mediana_B, p90_B);
                printf("  Dias mais secos (%d menores umidades):\n  ", M_SECOS);
                for (int s = 0; s < M_SECOS; s++) {
                    printf("%.0f ", secos_B[s]);
                }
                printf("\n\n  comparacoes (mediana + P90): %lld\n", comp_B);
                printf("  comparacoes (dias secos):    %lld\n", secos_comp_B);
                break;
            }
            case 3: {
                // ABORDAGEM C: mediana e P90
                comparacoes = 0;
                float mediana_C = abordagem_C(pm25, quantidade, k_mediana);
                long long comp_C = comparacoes;

                comparacoes = 0;
                float p90_C = abordagem_C(pm25, quantidade, k_p90);
                comp_C += comparacoes;

                // ABORDAGEM C: dias secos
                float secos_C[M_SECOS];
                comparacoes = 0;
                for (int s = 0; s < M_SECOS; s++) {
                    secos_C[s] = abordagem_C(umid, quantidade, s + 1);
                }
                long long secos_comp_C = comparacoes;

                printf("\n  C: mediana = %.1f | P90 = %.1f\n", mediana_C, p90_C);
                printf("  Dias mais secos (%d menores umidades):\n  ", M_SECOS);
                for (int s = 0; s < M_SECOS; s++) {
                    printf("%.0f ", secos_C[s]);
                }
                printf("\n\n  comparacoes (mediana + P90): %lld\n", comp_C);
                printf("  comparacoes (dias secos):    %lld\n", secos_comp_C);
                break;
            }
            case 0:
                printf("Encerrando.\n");
                break;
            default:
                printf("Opcao invalida\n");
        }
    } while (opcao != 0);

    return 0;
}