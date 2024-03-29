#include "pdi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int **alocaMatriz(int x, int y)
{
    int **M;

    M = (int **)calloc(x, sizeof(int *));
    for (int i = 0; i < x; i++)
    {
        M[i] = (int *)calloc(y, sizeof(int));
    }
    return M;
}

int ***alocaMatrizRGB(int x, int y)
{
    int ***matS;
    matS = (int ***)calloc(x, sizeof(int **));
    for (int k = 0; k < 3; k++)
    {
        matS[k] = (int **)calloc(x, sizeof(int *));
        for (int i = 0; i < x; i++)
        {
            matS[k][i] = (int *)calloc(x, sizeof(int));
        }
    }
    return matS;
}

void liberaMatrizRGB(int ***mat, int x)
{
    for (int k = 0; k < 3; k++)
    {
        for (int i = 0; i < x; i++)
        {
            free(mat[k][i]);
        }
        free(mat[k]);
    }
    free(mat);
}

void liberaMatriz(int **mat, int x)
{
    for (int i = 0; i < x; i++)
    {
        free(mat[i]);
    }
    free(mat);
}

void escreverArquivoCinza(char **nomeArq, char *p, char *comment, int x, int y, int max, int **mat)
{
    FILE *arq;
    arq = fopen(nomeArq, "w");
    if (arq != NULL)
    {
        fprintf(arq, "%s\n", p);
        fprintf(arq, "%s\n", comment);
        fprintf(arq, "%d %d\n", y, x);
        fprintf(arq, "%d\n", max);
        if (p[1] == '2')
        {
            for (int i = 0; i < x; i++)
            {
                for (int j = 0; j < y; j++)
                {
                    fprintf(arq, "%3d ", mat[i][j]);
                }
            }
            fclose(arq);
        }
        if (p[1] == '5')
        {
            for (int i = 0; i < x; i++)
            {
                for (int j = 0; j < y; j++)
                {
                    fwrite(&mat[i][j], sizeof(char), 1, arq);
                }
            }
            fclose(arq);
        }
    }
}

int **abrirArquivoCinza(char nomeArq[], char **p, char **comment, int *x, int *y, int *maxC)
{
    FILE **arq;
    arq = fopen(nomeArq, "r");
    if (arq == NULL)
    {
        return NULL;
    }
    else
    {
        fgets(p, 5, arq);
        fgets(comment, 100, arq);
        fscanf(arq, "%d %d", y, x);
        fscanf(arq, "%d", maxC);

        int aux1, aux2;
        aux1 = *x;
        aux2 = *y;

        int **mat;
        mat = alocaMatriz(aux1, aux2);
        char tipo[5];
        strcpy(tipo, p);
        if (tipo[1] == '2')
        {
            for (int i = 0; i < aux1; i++)
            {
                for (int j = 0; j < aux2; j++)
                {
                    fscanf(arq, "%d ", &mat[i][j]);
                }
            }
        }
        if (tipo[1] == '5')
        {
            for (int i = 0; i < aux1; i++)
            {
                for (int j = 0; j < aux2; j++)
                {
                    fread(&mat[i][j], sizeof(char), 1, arq);
                }
            }
        }
        fclose(arq);
        return mat;
    }
}

int ***abrirArquivoColorido(char nomeArq[], char *p, char *comment, int *x, int *y, int *maxC)
{
    FILE **arq;
    arq = fopen(nomeArq, "r");
    if (arq == NULL)
    {
        return NULL;
    }
    else
    {
        fgets(p, 5, arq);
        fgets(comment, 100, arq);
        fscanf(arq, "%d %d", y, x);
        fscanf(arq, "%d", maxC);
        int aux1, aux2;
        aux1 = *x;
        aux2 = *y;

        int ***mat;

        mat = alocaMatrizRGB(aux1, aux2);

        if (p[1] == '3')
        {
            for (int i = 0; i < aux1; i++)
            {
                for (int j = 0; j < aux2; j++)
                {
                    fscanf(arq, "%d ", &mat[0][i][j]);
                    fscanf(arq, "%d ", &mat[1][i][j]);
                    fscanf(arq, "%d ", &mat[2][i][j]);
                }
            }
        }
        if (p[1] == '6')
        {
            for (int i = 0; i < aux1; i++)
            {
                for (int j = 0; j < aux2; j++)
                {
                    fread(&mat[0][i][j], sizeof(char), 1, arq);
                    fread(&mat[1][i][j], sizeof(char), 1, arq);
                    fread(&mat[2][i][j], sizeof(char), 1, arq);
                    printf("%d %d %d\t", mat[0][i][j], mat[1][i][j], mat[2][i][j]);
                }
            }
        }
        fclose(arq);
        return mat;
    }
}

void escreverArquivoColorido(char nomeArq[], char *p, char *comment, int x, int y, int maxC, int ***mat)
{
    FILE *arq;
    arq = fopen(nomeArq, "w");
    if (arq != NULL)
    {
        fprintf(arq, "%s\n", p);
        fprintf(arq, "%s\n", comment);
        fprintf(arq, "%d %d\n", y, x);
        fprintf(arq, "%d\n", maxC);
        if (p[1] == '3')
        {
            for (int i = 0; i < x; i++)
            {
                for (int j = 0; j < y; j++)
                {
                    fprintf(arq, "%3d ", mat[0][i][j]);
                    fprintf(arq, "%3d ", mat[1][i][j]);
                    fprintf(arq, "%3d ", mat[2][i][j]);
                }
            }
        }
        if (p[1] == '6')
        {
            for (int i = 0; i < x; i++)
            {
                for (int j = 0; j < y; j++)
                {
                    fwrite(&mat[0][i][j], sizeof(char), 1, arq);
                    fwrite(&mat[1][i][j], sizeof(char), 1, arq);
                    fwrite(&mat[2][i][j], sizeof(char), 1, arq);
                }
            }
        }

        fclose(arq);
    }
}

void bubbleSort(int *vetor, int n)
{
    int k, j, aux;
    for (k = 1; k < n; k++)
    {
        for (j = 0; j < n - 1; j++)
        {
            if (vetor[j] > vetor[j + 1])
            {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

//***PGM
int *histograma(int **mat, int nvlCinza, int x, int y)
{
    int *vet;
    vet = (int *)calloc(nvlCinza, sizeof(int *));
    for (int i = 0; i < nvlCinza + 1; i++)
    {
        vet[i] = 0;
    }
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            vet[mat[i][j]] += 1;
        }
    }
    return vet;
}

int **equalizacao(int **mat, int nvlCinza, int x, int y)
{
    int *vetHist = histograma(mat, nvlCinza, x, y);

    int **matSaida = alocaMatriz(x, y);
    int vetEqual[nvlCinza + 1];
    int aux = 0;
    for (int k = 0; k < nvlCinza + 1; k++)
    {
        aux += vetHist[k];
        vetEqual[k] = round(aux * 1.0 * ((nvlCinza - 1.0) / (x * y * 1.0)));
    }
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            matSaida[i][j] = vetEqual[mat[i][j]];
        }
    }
    return matSaida;
}

int **equalizacaoLocalHistograma(int **mat, int x, int y, int max, int viz)
{
    int **matS;
    matS = alocaMatriz(x, y);

    int restoAltura = x % viz;
    int restoLargura = y % viz;

    int altura = x - restoAltura;
    int largura = y - restoLargura;

    for (int i = 0; i < altura; i += viz)
    {
        for (int j = 0; j < largura; j += viz)
        {

            int **temp = alocaMatriz(viz, viz);
            for (int auxi = 0; auxi < viz; auxi++)
            {
                for (int auxj = 0; auxj < viz; auxj++)
                {
                    temp[auxi][auxj] = mat[i + auxi][j + auxj];
                }
            }

            int **temp2 = equalizacao(temp, max, viz, viz);

            for (int auxi = 0; auxi < viz; auxi++)
            {
                for (int auxj = 0; auxj < viz; auxj++)
                {
                    matS[i + auxi][j + auxj] = temp2[auxi][auxj];
                }
            }
        }
    }
    if (restoAltura > 0)
    {
        for (int i = 0; i < restoAltura; i++)
        {
            for (int j = 0; j < y; j++)
            {
                matS[i + altura][j] = mat[i + altura][j];
            }
        }
    }

    if (restoLargura > 0)
    {
        for (int i = altura; i < x; i++)
        {
            for (int j = 0; j < restoLargura; j++)
            {
                matS[i][j + largura] = mat[i][j + largura];
            }
        }
    }
    return matS;
}

float mediaMat(int **mat, int x, int y)
{
    float m;
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            m += (mat[i][j]);
        }
    }
    m = m / (float)(x * y);
    return m;
}

int medianaVet(int *vet, int len)
{
    bubbleSort(vet, len);
    int index = (int)(len / 2);
    return vet[index];
}

float variancia(int **mat, int x, int y)
{
    float Va;
    float m = mediaMat(mat, x, y);
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            Va += pow((mat[i][j] - m), 2);
        }
    }
    Va = Va / (float)(x * y);
    return Va;
}

int **filtroMedia(int **mat, int x, int y, int tam)
{
    int **imagemFiltrada;
    imagemFiltrada = alocaMatriz(x, y);
    int deslocamento = tam / 2;

    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            int soma = 0;
            int totalPixels = 0;
            for (int k = -deslocamento; k <= deslocamento; k++)
            {
                for (int l = -deslocamento; l <= deslocamento; l++)
                {
                    int pixel = 0;
                    int posX = i + k;
                    int posY = j + l;
                    if (posX < 0)
                    {
                        posX = 0;
                    }
                    else if (posX >= x)
                    {
                        posX = x - 1;
                    }
                    if (posY < 0)
                    {
                        posY = 0;
                    }
                    else if (posY >= y)
                    {
                        posY = y - 1;
                    }
                    pixel = mat[posX][posY];
                    soma += pixel;
                    totalPixels++;
                }
            }
            imagemFiltrada[i][j] = soma / totalPixels;
        }
    }
    return imagemFiltrada;
}


int **filtroMediana(int **mat, int x, int y, int tam)
{
    int **matS;
    matS = alocaMatriz(x, y);
    int deslocamento = tam / 2;
    int *vet;
    vet = (int *)calloc((tam * tam), sizeof(int));
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            int aux = 0;
            for (int k = -deslocamento; k <= deslocamento; k++)
            {
                for (int l = -deslocamento; l <= deslocamento; l++)
                {
                    int posX = i + k;
                    int posY = j + l;
                    if (posX < 0)
                    {
                        posX = 0;
                    }
                    else if (posX >= x)
                    {
                        posX = x - 1;
                    }
                    if (posY < 0)
                    {
                        posY = 0;
                    }
                    else if (posY >= y)
                    {
                        posY = y - 1;
                    }
                    vet[aux] = mat[posX][posY];
                    aux++;
                }
            }
            matS[i][j] = medianaVet(vet, tam * tam);
        }
    }
    return matS;
}

int **filtroLaplace(int **mat, int x, int y, int tipo)
{
    int **matS;
    matS = alocaMatriz(x, y);
    int deslocamento = 1;
    int filtro[4][3][3] = {
        {{0, 1, 0}, {1, -4, 1}, {0, 1, 0}},
        {{1, 1, 1}, {1, -8, 1}, {1, 1, 1}},
        {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}},
        {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}}};

    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            int aux = 0;
            for (int k = -deslocamento; k <= deslocamento; k++)
            {
                for (int l = -deslocamento; l <= deslocamento; l++)
                {
                    int posX = i + k;
                    int posY = j + l;
                    if (posX < 0)
                    {
                        posX = 0;
                    }
                    else if (posX >= x)
                    {
                        posX = x - 1;
                    }
                    if (posY < 0)
                    {
                        posY = 0;
                    }
                    else if (posY >= y)
                    {
                        posY = y - 1;
                    }
                    aux += filtro[tipo][k + deslocamento][l + deslocamento] * mat[posX][posY];
                }
            }
            if (aux < 0)
            {
                matS[i][j] = 0;
            }
            else
            {
                matS[i][j] = aux;
            }
        }
    }
    return matS;
}

int **filtroHighBoost(int **mat, int x, int y, int tam, float boost)
{
    int **imagemFiltrada;
    imagemFiltrada = alocaMatriz(x, y);
    int deslocamento = tam / 2;

    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            int soma = 0;
            int totalPixels = 0;
            for (int k = -deslocamento; k <= deslocamento; k++)
            {
                for (int l = -deslocamento; l <= deslocamento; l++)
                {
                    int pixel = 0;
                    int posX = i + k;
                    int posY = j + l;
                    if (posX < 0)
                    {
                        posX = 0;
                    }
                    else if (posX >= x)
                    {
                        posX = x - 1;
                    }
                    if (posY < 0)
                    {
                        posY = 0;
                    }
                    else if (posY >= y)
                    {
                        posY = y - 1;
                    }
                    pixel = mat[posX][posY];
                    soma += pixel;
                    totalPixels++;
                }
            }
            imagemFiltrada[i][j] = (mat[i][j] + ((int)((mat[i][j] - (soma / totalPixels)) * boost)));
        }
    }
    return imagemFiltrada;
}

int **extrairRGB(int ***matRGB, int x, int y, char canal)
{
    int **matS;
    matS = alocaMatriz(x, y);
    if (canal == 'R')
    {
        for (int i = 0; i < x; i++)
        {
            for (int j = 0; j < y; j++)
            {
                matS[i][j] = matRGB[0][i][j];
            }
        }
        return matS;
    }
    if (canal == 'G')
    {
        for (int i = 0; i < x; i++)
        {
            for (int j = 0; j < y; j++)
            {
                matS[i][j] = matRGB[1][i][j];
            }
        }
        return matS;
    }
    if (canal == 'B')
    {
        for (int i = 0; i < x; i++)
        {
            for (int j = 0; j < y; j++)
            {
                matS[i][j] = matRGB[2][i][j];
            }
        }
        return matS;
    }
}

int **misturarCanaisRGB(int **matrizR, int **matrizG, int **matrizB, int x, int y)
{
    int ***matS;
    matS = alocaMatrizRGB(x, y);
    matS[0] = matrizR;
    matS[1] = matrizG;
    matS[2] = matrizB;
    return matS;
}

//***Implementa��es Extras
int **escurecer(int **matE, int x, int y, int n)
{
    int **matS;
    matS = alocaMatriz(x, y);
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            matS[i][j] = matE[i][j] - n;
            if (matS[i][j] < 0)
            {
                matS[i][j] = 0;
            }
        }
    }
    return matS;
}

int **clarear(int **mat, int x, int y, int max, int n)
{
    int **matS;
    matS = alocaMatriz(x, y);
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            matS[i][j] = mat[i][j] + n;
            if (matS[i][j] > max)
            {
                matS[i][j] = max;
            }
        }
    }
    return matS;
}

int **negativo(int **matE, int x, int y)
{
    int **matS;
    matS = alocaMatriz(x, y);
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            matS[i][j] = 255 - matE[i][j];
        }
    }
    return matS;
}

int **binarizar(int **matE, int x, int y, int limiar, int max)
{
    int **matS;
    matS = alocaMatriz(x, y);
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            if (matE[i][j] <= limiar)
            {
                matS[i][j] = 0;
            }
            else
            {
                matS[i][j] = max;
            }
        }
    }
    return matS;
}
