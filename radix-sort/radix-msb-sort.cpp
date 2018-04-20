/*Bernardo Hummes Flores e Maria Cecilia Matos Correa
RadixSort MSD*/
#include<iomanip>
#include<iostream>
#include <string>
#include <fstream>

const int alfabeto = 26;

using namespace std;

void leArquivo(string nomeArquivo, string conteudo[], int *nValores)
{
    ifstream arq (nomeArquivo);
    int indice=0;
    string buffer;

    if (!(arq.is_open()))
    {
        cout << "Erro na abertura do arquivo " << nomeArquivo << "\n";
    }
    else
    {
        while (!(arq.eof())) {

            getline(arq, buffer);
            conteudo[indice] = buffer;
            indice++;
        }
    }
    *nValores = (indice-1);
    arq.close();
}

void escreveArquivo(string nomeArquivo, string conteudo[], int nValores)
{
    ofstream arq (nomeArquivo);
    string buffer;

    if (! (arq.is_open()))
    {
        cout << "Erro na abertura do arquivo %s " << nomeArquivo << "\n";
    }
    else
    {
        for (int i = 0; i < nValores; i++){
            arq << conteudo[i];
            arq << ",\n";
        }
    }
    arq.close();
}

void radixLsbSort(string conteudo[], string temp[], int inicio, int fim, int nSimbolos)
{
    //printf("entrou - simbolo = %c - inicio = %d - fim = %d - nSimbolos = %d", conteudo[inicio][nSimbolos], inicio, fim, nSimbolos);

    //int contador[alfabeto+2] = {0};

    if (fim <= inicio)
    {
        return;
    }

    int *contador = new int[alfabeto+2];

    for(int i = inicio; i <= fim; i++)
    {
        contador[static_cast<int>(conteudo[i][nSimbolos]) - 96]++;
    }

    for(int j = 0; j < alfabeto+1; j++)
    {
        contador[j+1] += contador[j];
    }

    for(int j = inicio; j <= fim; j++)
    {
        temp[contador[(conteudo[j][nSimbolos]) - 97]++] = conteudo[j];
    }

    for(int j = inicio; j <= fim; j++)
    {
        conteudo[j] = temp[j-inicio];
    }

    for (int i = 0; i < alfabeto; i++)
    {
        radixLsbSort(conteudo, temp, inicio+contador[i], inicio+contador[i+1]-1, nSimbolos+1);
    }
}

void sort(string conteudo[], int nValores, int nSimbolos)
{
    string *temp = new string[nValores];

    radixLsbSort(conteudo, temp, 0, nValores-1, 0);
}


int main(int argc, char *argv[])
{
    string conteudo[50];
    int nValores;

    if (argc !=3)
    {
        printf("\nNumero incorredo de parametros.");
        printf("\nUso correto: radix-lsb-sort.exe <nome_arquivo_entrada.csv> <nome_arquivo_saida.csv>\n");
    }
    else
    {
        //int tamanhoArq = tamanhoArquivo(argv[1]);
        string conteudo[50];

        cout << "\nLendo arquivo.";

        leArquivo(argv[1], conteudo, &nValores);

        cout << "Numero de itens = " << nValores;

        cout << "\nOrdenando valores\n";
        sort(conteudo, 50, 3);

        cout << "\nEscrevendo arquivo de saida.";
        escreveArquivo(argv[2], conteudo, nValores);

    }

    return 0;
}
