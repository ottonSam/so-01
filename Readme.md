
## Analise de multiplicação de matrizes ***threads*** vs ***processos***
### Autores:
- Samuel Ótton
- João Anisio
---
## Compilação
Foram construídos quatro programas auxiliar, sequencial, threads e processos respectivamente:
 1. Ferramenta util para a construção de matrizes NxM com valores aleatórios.
 2. Multiplicação de duas matrizes utilizando programação sequencial.
 3. Multiplicação de matrizes utilizando programação paralela com N threads.
 4. Multiplicação de matrizes utilizando programação paralela com N processos.

 Para facilitar os processos de compilação dos códigos produzidos criamos um script para automatizar essa tarefa um tanto quanto chata.

 Para a compilação de todos os códigos juntos basta executar o seguinte script
 ```bash
make
 ```

Caso queira compilar os códigos separadamente os seguintes script podem ser executados
```bash
make auxiliar
make sequencial
make threads
make processos
```
---
## Como devemos executar os binários
### Auxiliar
O programa deve ser executado passando como parâmetro as dimensões das matrizes, note que as matrizes devem sempre ser criadas em pares.
```bash
./auxiliar l1 c1 l2 c2
```
| Nome | Descrição |
| ---- | --------- |
| l1 | Quantidade de linhas da matriz 1 |
| c1 | Quantidade de colunas da matriz 1 |
| l2 | Quantidade de linhas da matriz 2 |
| c2 | Quantidade de colunas da matriz 2 |

#### Exemplo de saída
Se tudo ocorrer adequadamente deve ser criado dois arquivos contendo as matrizes criadas pelo programa. Os arquivos criados se encontram no diretório **/matrizes** com o seguinte padrão de nomenclatura `/matrizes/matriz(numero da matriz)-(quantidade de linhas)X(quantidade de colunas).txt`. Exemplo `/matrizes/matriz1-100X100.txt`.

### Sequencial
O programa deve ser executado passando como parâmetro as matrizes a serem multiplicadas.
```bash
./sequencial m1 m2
```
| Nome | Descrição |
| ---- | --------- |
| m1 | caminho para a matriz 1 |
| m2 | caminho para a matriz 2 |

#### Exemplo de saída
Se tudo ocorrer adequadamente deve ser criado um arquivo de log para registrar o tempo de execução do programa. O arquivo criado se encontra no diretório **/saidas** com o seguinte padrão de nomenclatura `/saidas/tempos-sequencial(numero de linhas da matriz resultante)X(numero de colunas da matriz resultante)-output.txt`. Exemplo `/saidas/tempos-sequencial100X100-output.txt`.

### Threads
