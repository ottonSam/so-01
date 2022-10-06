#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>
#include <bits/stdc++.h>

using namespace std;

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
            {
                ilinha.push_back(slinha[j] - '0');
                // cout << stoi(to_string(slinha[j])) << " ";
            }
            // cout << endl;
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
    int P = atoi(argv[3]);

    vector<vector<int>> matriz1 = get_matriz(arquivo1);
    vector<vector<int>> matriz2 = get_matriz(arquivo2);
    vector<vector<int>> matriz3;

    int lm1, cm1, lm2, cm2;
    lm1 = (int)matriz1.size();
    cm1 = (int)matriz1[0].size();
    lm2 = (int)matriz2.size();
    cm2 = (int)matriz2[0].size();

    vector<int> tempos;

    for (int i = 0; i < lm2; i++)
    {
        matriz3.push_back(vector<int>());
        for (int j = 0; j < cm1; j++)
            matriz3[i].push_back(0);
    }

    int nprocessos = (cm1 * lm2) / P;
    int vetor_pid[nprocessos];

    ofstream outputfile;
    outputfile.open("saidas/tempos-processos" + to_string(lm2) + "X" + to_string(cm1) + "-" + to_string(P) + "-outputfile.txt", ios_base::app);
    outputfile << lm1 << " " << cm2 << endl;
    
    int inicial{0}, final{0}, l{0}, c{0};

    for (int i{0}; i < nprocessos; i++)
    {
        inicial = P * i;
        final = P * (i + 1);

        vetor_pid[i] = fork();

        if (vetor_pid[i] == 0)
        {

            // ofstream file;
            // file.open("saidas/processos/processo-" + to_string(lm2) + "X" + to_string(cm1) + "-" + to_string(P) + "-id_" + to_string(i) + ".txt");

            chrono::steady_clock::time_point begin = chrono::steady_clock::now();

            for (int k{inicial}; k < final; k++)
            {
                l = k / lm2;
                c = k % cm1;

                for (size_t a{0}; (int) a < lm2; a++)
                {
                    matriz3[l][c] += matriz1[l][a] * matriz2[a][c];
                }
                // file << "c" << l << "-" << c << " " << matriz3[l][c] << endl;
            }
            chrono::steady_clock::time_point end = chrono::steady_clock::now();
            tempos.push_back(chrono::duration_cast<chrono::milliseconds>(end - begin).count());
            // file.close();
            break;
        }
    }

    if (cm1 != lm2)
    {
        cout << "Error: impossible multiplication" << endl;
        return 1;
    }
    
    for (int j = 0; j < (int)tempos.size(); j++)
    {
        outputfile << "Tempo: " << tempos[j] << "(ms)" << endl;
    }

    outputfile.close();

    return 0;
}
