run:
	g++ -Wall auxiliar.cpp -o auxiliar
	g++ -Wall sequencial.cpp -o sequencial
	g++ -Wall threads.cpp -o threads -pthread
	g++ -Wall processos.cpp -o processos
