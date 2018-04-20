#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int tJanela(int n)
{
    int janela = 1;

    while(janela < n)
    {
        janela = 3 * janela + 1;
    }

    printf("\n%d\n", janela);
    return janela;
}

void imprimeArray(int conteudo[], int tamanho)
{
    int i;

    for (i=0; i<tamanho; i++)
    {
        printf("%d ", conteudo[i]);
    }
}

int shellSort(int conteudo[], int nValores)
{
    int i, j, valor, count=0, valoresH = 0, trocasJanela;

    int janela = tJanela(nValores);

    while (janela > 1)
    {
        valoresH++;
        janela/=3;
        printf("Segmentos na janela atual de %d = %d\n", janela, (nValores/janela) + (nValores%janela) );
        for (i = janela, trocasJanela=0; i < nValores; i++)
        {
            valor = conteudo[i];
            j = i;
            while (j >= janela && valor < conteudo[j - janela])
            {
                conteudo[j] = conteudo[j-janela];
                j -= janela;
                count++;
                trocasJanela++;
            }
            conteudo[j] = valor;
            printf("Numero total de trocas na janela %d = %d\n", janela, trocasJanela);
        }
    }

    printf("trocas do valor de H = %d\n", valoresH);

    printf("Numero total de trocas = %d\n", count);
    return count;
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

void geraAleatorios(int numerosAleatorios, int conteudo[100])
{

    int valores[numerosAleatorios], i;

    for (i=0; i<numerosAleatorios; i++)
    {
        conteudo[i] = (1 + (rand()%1000));
    }

    imprimeArray(conteudo, 100);

}

void geraOrdeados(int numerosOrdenados, int conteudo[])
{
    int inicio = 1 + rand()%1000-numerosOrdenados, i;
    int contador=inicio;
    int valores[numerosOrdenados];

    for (i=0; i<numerosOrdenados; i++)
    {
        conteudo[i] = inicio;
        inicio++;
    }
}

void geraInverso(int numerosInversos, int conteudo[])
{
    int final = (numerosInversos+1 + (rand()%1000-numerosInversos)), i;
    int valores[numerosInversos];

    for (i=0; i<numerosInversos; i++)
    {
        conteudo[i] = final;
        final--;
    }
}


int main(int argc, char *argv[])
{
    int nValores, trocas;

    srand(time(NULL));

    if (argc !=3)
    {
        printf("\nNumero incorredo de parametros.");
        printf("\nUso correto: le-escreve.exe <nome_arquivo_entrada.csv> <nome_arquivo_saida.csv>\n");
    }
    else
    {
        int tamanho = tamanhoArq(argv[1]);
        //int conteudo[tamanho];
        int conteudo[20000];


        printf("\nLendo o arquivo.");
        leArquivo(argv[1], conteudo, &nValores);

        printf("\nOrdenando valores.");
        //insertionSort(conteudo, nValores);
        trocas = shellSort(conteudo, nValores);

        printf("\nEscrevendo arquivo de saida.\n");
        escreveArquivo(argv[2], conteudo, nValores);
        printf("Foram realizadas %d trocas.\n", trocas);

/*

        printf("\n\n100 valores aleatorios:\n");
        geraAleatorios(100, conteudo);
        imprimeArray(conteudo, 100);
        escreveArquivo("entradaaleatorio.csv", conteudo, 100);
        trocas = shellSort(conteudo, 100);
        imprimeArray(conteudo, 100);
        escreveArquivo("saidaaleatorio.csv", conteudo, 100);
        printf("Foram realizadas %d trocas\n", trocas);


        printf("\n\n30 valores ordenados:\n");
        geraOrdeados(30, conteudo);
        imprimeArray(conteudo, 30);
        escreveArquivo("entradaordenado.csv", conteudo, 30);
        trocas = shellSort(conteudo, 30);
        imprimeArray(conteudo, 30);
        escreveArquivo("saidaordenado.csv", conteudo, 30);
        printf("Foram realizadas %d trocas\n", trocas);


        printf("\n\n120 valores invertidos:\n");
        geraInverso(120, conteudo);
        imprimeArray(conteudo, 120);
        escreveArquivo("entradainversa.csv", conteudo, 120);
        trocas = shellSort(conteudo, 120);
        imprimeArray(conteudo, 120);
        escreveArquivo("saidainversa.csv", conteudo, 120);
        printf("Foram realizadas %d trocas\n", trocas);
*/

    }
}
