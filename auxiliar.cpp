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
    outfile.open("matrizes/"+matriz);
    string infos = std::to_string(l) + " " + std::to_string(c);
    outfile << infos << endl;
    string linha;
    for (int i = 0; i < l; i++)
    {
        linha = "";
        for (int j = 0; j < c; j++)
            linha += std::to_string(rand() % 10) + " ";
        outfile << linha << endl;
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

    string n1, n2;
    n1 = "matriz1-"+std::to_string(l1)+"X"+std::to_string(c1)+".txt";
    n2 = "matriz2-"+std::to_string(l2)+"X"+std::to_string(c2)+".txt";

    create_matriz(l1, c1, n1);
    create_matriz(l2, c2, n2);
}