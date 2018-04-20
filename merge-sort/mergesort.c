#include <stdio.h>
#include <stdlib.h>

int tamanhoArquivo(char* nomeArquivo)
{
    FILE* arq;
    int tamanho;

    if (! (arq = fopen(nomeArquivo, "r")))
    {
        printf("Erro na abertura do arquivo %s\n", nomeArquivo);
    }
    else
    {
        fseek(arq, 0L, SEEK_END);
        tamanho = ftell(arq);
    }
    return tamanho;
}

void leArquivo(char* nomeArquivo, int conteudo[], int *nValores)
{
    FILE *arq;
    int buffer, indice=0;
    char temp;

    if (! (arq = fopen(nomeArquivo, "r")))
    {
        printf("Erro na abertura do arquivo %s\n", nomeArquivo);
    }
    else
    {
        indice = 0;
        while(!feof(arq))
        {
            fscanf(arq, "%d,", &buffer);
            conteudo[indice] = buffer;
            indice++;
        }
    }

    *nValores = (indice-1);
}

void imprimeArray(int conteudo[], int tamanho)
{
    int i;

    for (i=0; i<tamanho; i++)
    {
        printf("%d ", conteudo[i]);
    }
}

void escreveArquivo(char *nomeArquivo, int conteudo[], int nValores)
{
    FILE *arq;
    int buffer, i;

    if (! (arq = fopen(nomeArquivo, "w")))
    {
        printf("Erro na abertura do arquivo %s\n", nomeArquivo);
    }
    else
    {
        for (i=0; i<nValores; i++)
        {
            buffer = conteudo[i];
            fprintf(arq, "%d,", buffer);
        }
    }
}

int merge(int conteudo[], int auxiliar[], int inicio, int meio, int final)
{
    int i=inicio, j=meio+1, k=inicio, trocas=0;

    while(i<=meio && j <= final)
    {
        if(auxiliar[i] <= auxiliar[j])
        {
            conteudo[k] = auxiliar[i++];
            //trocas++;
        }
        else
        {
            conteudo[k] = auxiliar[j++];
            trocas++;
        }
        k++;
    }

    while(i<=meio)
    {
        conteudo[k++] = auxiliar[i++];
    }

    while(j <= final)
    {
        conteudo[k++] = auxiliar[j++];
    }

    for (i=inicio; i<= final; i++)
    {
        auxiliar[i] = conteudo[i];
    }

    return trocas;
}

void sort(int conteudo[], int auxiliar[], int inicio, int final, int *trocas)
{
    if (inicio < final)
    {
        int meio = (inicio+final)/2;
        sort(conteudo, auxiliar, inicio, meio, trocas);
        sort(conteudo, auxiliar, meio+1, final, trocas);
        *trocas += merge(conteudo, auxiliar, inicio, meio, final);
    }
}

int main(int argc, char *argv[])
{
    int nValores, i;
    int trocas=0;

    if (argc !=3)
    {
        printf("\nNumero incorredo de parametros.");
        printf("\nUso correto: mergesort.exe <nome_arquivo_entrada.csv> <nome_arquivo_saida.csv>\n");
    }
    else
    {
        int tamanhoArq = tamanhoArquivo(argv[1]);
        int conteudo[tamanhoArq];
        int auxiliar[tamanhoArq];

        printf("\nLendo arquivo.");
        leArquivo(argv[1], conteudo, &nValores);

        for (i=0; i<nValores; i++)
        {
            auxiliar[i] = conteudo[i];
        }

        printf("\n%d\n", nValores);

        printf("\nOrdenando valores.");
        sort(conteudo, auxiliar, 0, nValores-1, &trocas);

        printf("\nForam realizadas %d trocas.", trocas);

        printf("\nEscrevendo arquivo de saida.");
        escreveArquivo(argv[2], conteudo, nValores);

    }

    return 0;
}
