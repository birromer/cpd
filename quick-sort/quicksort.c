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
    int buffer, indice=0, flagVirgula=0, n=0;
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

int particione(int conteudo[], int inicio, int final)
{
    int pivo=conteudo[inicio];
    int i=inicio, j=final+1, temp;

    while(1)
    {
        do
        {
            i++;
        } while(conteudo[i] <= pivo && i <= final);

        do
        {
            j--;
        } while(conteudo[j] > pivo);

        if (i >= j)
        {
            break;
        }

        temp = conteudo[i];
        conteudo[i] = conteudo[j];
        conteudo[j] = temp;
    }

    temp = conteudo[inicio];
    conteudo[inicio] = conteudo[j];
    conteudo[j] = temp;

    return j;
}

int quickSort(int conteudo[], int inicio, int final)
{
    int pivo;

    if (final > inicio)
    {
        pivo = particione(conteudo, inicio, final);
        quickSort(conteudo, inicio, pivo-1);
        quickSort(conteudo, pivo+1, final);
    }
}

int main(int argc, char *argv[])
{
    int nValores;

    if (argc !=3)
    {
        printf("\nNumero incorredo de parametros.");
        printf("\nUso correto: quicksort.exe <nome_arquivo_entrada.csv> <nome_arquivo_saida.csv>\n");
    }
    else
    {
        int tamanhoArq = tamanhoArquivo(argv[1]);
        int conteudo[tamanhoArq];

        printf("\nLendo arquivo.");
        leArquivo(argv[1], conteudo, &nValores);

        printf("\n%d\n", nValores);

        printf("\nOrdenando valores.");
        quickSort(conteudo, 0, nValores-1);

        printf("\nEscrevendo arquivo de saida.");
        escreveArquivo(argv[2], conteudo, nValores);
    }

    return 0;
}
