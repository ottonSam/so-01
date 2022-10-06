#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <sstream>

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

    vector<vector<int>> matriz1 = get_matriz(arquivo1);
    vector<vector<int>> matriz2 = get_matriz(arquivo2);

    int lm1, cm1, lm2, cm2;
    lm1 = (int)matriz1.size();
    cm1 = (int)matriz1[0].size();
    lm2 = (int)matriz2.size();
    cm2 = (int)matriz2[0].size();

    ofstream outputfile;
    outputfile.open("saidas/tempos-sequencial" + to_string(lm2) + "X" + to_string(cm1) + "-outputfile.txt", ios_base::app);

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    vector<vector<int>> res;

    if (cm1 != lm2)
    {
        cout << "Error: impossible multiplication" << endl;
        return 1;
    }

    outputfile << lm1 << " " << cm2 << endl;
    for (int i = 0; i < lm1; ++i)
    {
        vector<int> rlinha;
        for (int h = 0; h < cm2; ++h)
        {
            int nv = 0;
            for (int j = 0; j < lm2; ++j)
                nv += (matriz1[i][j] * matriz2[j][h]);
            rlinha.push_back(nv);
        }
        res.push_back(rlinha);
    }

    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    outputfile << "Tempo: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "(ms)" << endl;
    outputfile.close();

    return 0;
}