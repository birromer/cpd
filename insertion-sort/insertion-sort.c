#include <stdio.h>
#include <stdlib.h>

int tamanhoArq(char* nomeArquivo)
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

void insertionSort(int conteudo[], int nValores)
{
    int i, j, testado;

    for (i=1; i<nValores; i++)
    {
        testado = conteudo[i];
        j = i - 1;

        while (j >= 0 && conteudo[j] > testado)
        {
            conteudo[j+1] = conteudo[j];
            j--;
        }

        conteudo[j+1] = testado;
    }
}


void shellSort(int conteudo[], int nValores)
{

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

int main(int argc, char *argv[])
{
    int nValores;

    if (argc !=3)
    {
        printf("\nNumero incorredo de parametros.");
        printf("\nUso correto: le-escreve.exe <nome_arquivo_entrada.csv> <nome_arquivo_saida.csv>\n");
    }
    else
    {
        int tamanho = tamanhoArq(argv[1]);
        int conteudo[tamanho];

        printf("\nGerando vetor.");
        leArquivo(argv[1], conteudo, &nValores);

        printf("\nOrdenando valores.");
        insertionSort(conteudo, nValores);
//        shellSort(conteudo, nValores);

        printf("\nEscrevendo arquivo de saida.");
        escreveArquivo(argv[2], conteudo, nValores);
    }
}
