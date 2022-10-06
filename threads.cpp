#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <sstream>

using namespace std;

vector<vector<int>> matriz1;
vector<vector<int>> matriz2;
vector<vector<int>> matriz3;
int lm1 = 0, cm1 = 0, lm2 = 0, cm2 = 0;
int P = 0;
int linha_atual = 0;
int coluna_atual = 0;

void *multi(void *tid)
{    
    int linha_atual = (P * (size_t)tid) / lm2;
    int coluna_atual = (P * (size_t)tid) % cm1;
    
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < lm2; j++)
            matriz3[linha_atual][coluna_atual] += matriz1[linha_atual][j] * matriz2[j][coluna_atual];
        coluna_atual++;
        if (coluna_atual == cm1)
        {
            linha_atual++;
            coluna_atual = 0;
        }
    }
    pthread_exit(NULL);
}

vector<vector<int>> get_matriz(string filename)
{
    ifstream arquivo(filename);

    if (!arquivo)
        cout << "Error: no such file";

    vector<vector<int>> matriz;

    if (arquivo.is_open())
    {
        string slinha;
        getline(arquivo, slinha);
        std::stringstream ss;
        ss << slinha;
        int l, c;
        ss >> l;
        ss >> c;

        for (int i = 0; i < l; i++)
        {
            vector<int> ilinha;
            std::getline(arquivo, slinha);
            for (int j = 0; j < c; j++)
                ilinha.push_back(slinha[j] - '0');
            matriz.push_back(ilinha);
        }
    }
    arquivo.close();
    return matriz;
}

int main(int argc, char *argv[])
{
    string arquivo1, arquivo2;
    arquivo1 = argv[1];
    arquivo2 = argv[2];
    P = atoi(argv[3]);

    matriz1 = get_matriz(arquivo1);
    matriz2 = get_matriz(arquivo2);

    lm1 = (int)matriz1.size();
    cm1 = (int)matriz1[0].size();
    lm2 = (int)matriz2.size();
    cm2 = (int)matriz2[0].size();

    int MAX_THREADS = (cm1 * lm2) / P;

    ofstream outputfile;
    outputfile.open("saidas/tempos-threads" + to_string(lm2) + "X" + to_string(cm1) + "-" + to_string(P) + "-outputfile.txt", ios_base::app);

    if (cm1 != lm2)
    {
        cout << "Error: impossible multiplication" << endl;
        return 1;
    }

    for (int i = 0; i < lm2; i++)
    {
        matriz3.push_back(vector<int>());
        for (int j = 0; j < cm1; j++)
            matriz3[i].push_back(0);
    }

    pthread_t threads[MAX_THREADS];
    chrono::steady_clock::time_point tbegin = chrono::steady_clock::now();

    for (int i = 0; i < MAX_THREADS; i++)
        pthread_create(&threads[i], NULL, multi, (void *)(size_t)(i));

    chrono::steady_clock::time_point tend = chrono::steady_clock::now();
    outputfile << lm2 << " " << cm1 << endl;
    outputfile << "Tempo: " << chrono::duration_cast<chrono::milliseconds>(tend - tbegin).count() << "(ms)" << endl;
    
    outputfile.close();
    return 0;
}