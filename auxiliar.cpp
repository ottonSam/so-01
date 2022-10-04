#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>

using std::cout;
using std::endl;
using std::ofstream;
using std::string;

void create_matriz(int l, int c, string matriz)
{
    std::ofstream outfile;
    outfile.open("../matrizes/" + matriz + ".txt", std::ios_base::app);
    std::vector<std::vector<int>> coluna;
    for (int i = 0; i < l; i++)
    {
        coluna.push_back(std::vector<int>());
        for (int j = 0; j < c; j++)
        {
            coluna[i].push_back(rand() % 10);
            outfile << coluna[i][j] << " ";
        }
        outfile << endl;
    }
    outfile.close();
}

int main(int argc, char *argv[])
{
    int l1, c1, l2, c2;
    l1 = atoi(argv[1]);
    c1 = atoi(argv[2]);
    l2 = atoi(argv[3]);
    c2 = atoi(argv[4]);

    create_matriz(l1, c1, "matriz1");
    create_matriz(l2, c2, "matriz2");
}