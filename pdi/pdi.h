#ifdef PDI_H
#define PDI_H

int **alocaMatriz (int x, int y);
int ***alocaMatrizRGB(int x, int y);
void liberaMatrizRGB(int ***mat, int x);
void liberaMatriz (int **mat, int x);
void escreverArquivoCinza (char **nomeArq, char *p, char *comment, int x, int y, int max, int **mat);
int **abrirArquivoCinza (char nomeArq[], char **p, char **comment, int *x, int *y, int *maxC);
int ***abrirArquivoColorido (char nomeArq[], char **p, char **comment, int *x, int *y, int *maxC);
void escreverArquivoColorido (char nomeArq[], char **p, char **comment, int *x, int *y, int *maxC, int ***mat);
void bubbleSort(int *vetor, int n);

int* histograma (int** mat, int nvlCinza, int x, int y);
int** equalizacao (int** mat, int nvlCinza, int x, int y);
void equalizacaoLocalHistograma (int** mat, int x, int y, int max, int viz, int **matS);
float mediaMat (int **mat, int x, int y);
int medianaVet(int *vet, int len);
float variancia (int **matE, int x, int y);
int** filtroMedia(int **matE, int x, int y, int viz);
int** filtroMediana (int** matE, int linhas, int colunas);
int** filtroLaplace(int **matE, int x, int y, int tipo);
int** filtroHighBoost(int **matE, int x, int y, int tam, int boost);

int** extrairRGB(int*** matRGB, int x, int y, char canal);
void alterarCanalRGB (int valor, int **mat, int nvlCinza, int x, int y, int **matSaida);
void misturarCanaisRGB (int **matrizR, int **matrizG, int **matrizB, int **matrizSaiR, int **matrizSaiG, int **matrizSaiB, int x, int y);

int** escurecer (int **matE, int x, int y, int n);
int** clarear (int **mat, int x, int y, int n);
int** negativo (int **matE, int **matS, int x, int y);
int** binarizar (int **matE, int**matS, int x, int y, int limiar, int max);
int** correcaoGama (int **matE, int **matS, int x, int y, int max, int c, float gama);

#endif // PDI_H
