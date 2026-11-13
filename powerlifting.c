#include <stdio.h>
#include <stdlib.h>

/* Prototipos: nao alterar. */
int **alocarMatriz(int linhas, int colunas);
void lerCargas(int **matriz, int linhas, int colunas);
void imprimirCargas(int **matriz, int linhas, int colunas);
int calcularTotalAtletaRecursivo(int **matriz, int indiceAtleta, int colunas);
int contarAtletasAcimaMinimo(int **matriz, int linhas, int indiceLevantamento, int minimo);
void liberarMatriz(int **matriz, int linhas);

/* MAIN PRONTA: NAO MODIFICAR. */
int main() {
    int qtdAtletas;
    const int qtdLevantamentos = 3;

    printf("Digite a quantidade de atletas: ");
    scanf("%d", &qtdAtletas);

    /* Considere que a quantidade informada e pelo menos 2. */
    int **cargas = alocarMatriz(qtdAtletas, qtdLevantamentos);

    lerCargas(cargas, qtdAtletas, qtdLevantamentos);

    printf("\nCARGAS DA COMPETICAO:\n");
    imprimirCargas(cargas, qtdAtletas, qtdLevantamentos);

    int totalAtleta = calcularTotalAtletaRecursivo(cargas, 1, qtdLevantamentos);
    printf("\nTotal levantado pelo atleta de indice 1: %d kg\n", totalAtleta);
      
    int atletasAcimaMinimo = contarAtletasAcimaMinimo(cargas, qtdAtletas, 2, 180); 
    printf("Atletas com pelo menos 180 kg no deadlift: %d\n", atletasAcimaMinimo);

    liberarMatriz(cargas, qtdAtletas);
    cargas = NULL;

    return 0;
}

/* ================= FUNCOES A IMPLEMENTAR ================= */

/* 1) Aloque dinamicamente uma matriz de inteiros com 'linhas' linhas
   e 'colunas' colunas, utilizando malloc.
   Retorne o ponteiro para a matriz alocada.
   Considere que as alocacoes sao bem-sucedidas. */
int **alocarMatriz(int linhas, int colunas) {
   int **matriz = malloc(linhas * sizeof(int *));
   for (int i = 0; i < linhas; i++) {
      matriz[i] = malloc(colunas * sizeof(int));
   }
   return matriz;
}
/* 2) Leia pelo teclado as tres cargas de cada atleta e armazene
   na matriz utilizando a notacao matriz[i][j].
   As colunas representam, nesta ordem:
   0 - Agachamento; 1 - Supino; 2 - Deadlift. */
void lerCargas(int **matriz, int linhas, int colunas) {
   for(int i=0;i<linhas;i++){
      for(int j=0;j<colunas;j++){
         printf("Atleta %d, Levantamento %d", i, j);
         scanf("%d", &matriz[i][j]);
      }
   }
}  
/* 3) Imprima as cargas de todos os atletas, identificando o indice
   de cada atleta e os tres levantamentos.
   Acesse os elementos utilizando matriz[i][j]. */
void imprimirCargas(int **matriz, int linhas, int colunas) {
   for(int i=0;i<linhas;i++){
      printf("Atleta %d", i);
      for(int j=0;j<colunas;j++){
         printf("KG %d", matriz[i][j]);
      }
   }
}
/* 4) RECURSIVA: calcule a soma das cargas do atleta de indice
   'indiceAtleta'.
   O parametro 'colunas' indica quantas cargas ainda devem ser somadas.
   Caso-base: se colunas == 0, retorne 0.
   Caso recursivo: some matriz[indiceAtleta][colunas - 1] com a
   chamada recursiva que considera uma coluna a menos. */
int calcularTotalAtletaRecursivo(int **matriz, int indiceAtleta, int colunas) {
   if (colunas=0){
      return 0;
   }
   return matriz[indiceAtleta][colunas - 1] +
      calcularTotalAtletaRecursivo(matriz, indiceAtleta, colunas - 1);
}

/* 5) Conte quantos atletas levantaram pelo menos 'minimo' kg
   no levantamento de indice 'indiceLevantamento'.
   Percorra as linhas da matriz e retorne a contagem. */
int contarAtletasAcimaMinimo(int **matriz, int linhas, int indiceLevantamento, int minimo) {
   int contador = 0;
   for (int i = 0; i < linhas; i++) {
      if (matriz[i][indiceLevantamento] >= minimo) {
            contador++;
      }
   }
   return contador;
}

/* 6) Libere toda a memoria alocada para a matriz: primeiro as linhas,
   depois o vetor de ponteiros. Nao e necessario atribuir NULL aqui,
   pois isso ja sera feito na main. */
void liberarMatriz(int **matriz, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}