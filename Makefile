run: auxiliar sequencial threads processos

auxiliar:
	g++ -Wall auxiliar.cpp -o auxiliar

sequencial:
	g++ -Wall sequencial.cpp -o sequencial

threads:
	g++ -Wall threads.cpp -o threads -pthread

processos:
	g++ -Wall processos.cpp -o processos