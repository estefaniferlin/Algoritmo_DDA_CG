#include <iostream>
#include <cmath>
#include <fstream>
#include "PGM.hpp"

using namespace std;

int main(void)
{
	setlocale(LC_ALL, "Portuguese");

	PGM *img = new PGM();
	img->ler("feep.pgm");

	int x1, y1, x2, y2, cor, linhas, count=0;

	cout << "-----------------------------------------------------" << endl;
	cout << "--- Algoritmo DDA (Digital Differential Analyser) ---" << endl;
	cout << "-----------------------------------------------------";

	cout << endl << "Quantas linhas deseja desenhar: ";
	cin >> linhas;

	do
	{
		cout << endl << "Informe a posicao x1 para a linha " << count+1 << ": ";
		cin >> x1;

		cout << "Informe a posicao y1 para a linha " << count+1 << ": ";
		cin >> y1;

		cout << "Informe a posicao x2 para a linha " << count+1 << ": ";
		cin >> x2;

		cout << "Informe a posicao y2 para a linha " << count+1 << ": ";
		cin >> y2;

		cout << "Informe a cor para a linha "<< count+1 << ": "; 
		cin >> cor;

		img->desenharLinha(x1, y1, x2, y2, cor);

		count++;
	}while(count < linhas);

	img->gravar("saida.pgm");

	delete img;

	return EXIT_SUCCESS; 
}
