#include<iomanip>
#include<iostream>
#include <string>
#include <fstream>

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

void radixLsbSort(string conteudo[], int nValores, int nSimbolos)
{
    string *temp = new string[nValores];

    for(int i = nSimbolos - 1; i >= 0; i--)
    {
        int contador[27] = {0};

        for(int j = 0; j < nValores; j++)
        {
            contador[static_cast<int>(conteudo[j][i]) - 96]++;
        }

        for(int j = 2; j < 26; j++)
        {
            contador[j] += contador[j - 1];
        }

        for(int j = 0; j < nValores; j++)
        {
            temp[contador[static_cast<int>(conteudo[j][i]) - 97]++] = conteudo[j];
        }

        for(int j = 0; j < nValores; j++)
        {
            conteudo[j] = temp[j];
        }
    }
    free(temp);
}

int main(int argc, char *argv[])
{
    string conteudo[50];
    int nValores;

    if (argc !=3)
    {
        cout << "\nNumero incorredo de parametros.";
        cout << "\nUso correto: radix-lsb-sort.exe <nome_arquivo_entrada.csv> <nome_arquivo_saida.csv>\n";
    }
    else
    {
        //int tamanhoArq = tamanhoArquivo(argv[1]);
        string conteudo[50];

        cout << "\nLendo arquivo.";

        leArquivo(argv[1], conteudo, &nValores);

        cout << "Numero de itens = " << nValores;

        cout << "\nOrdenando valores\n";
        radixLsbSort(conteudo, 50, 3);

        cout << "\nEscrevendo arquivo de saida.";
        escreveArquivo(argv[2], conteudo, nValores);

    }

    return 0;
}
