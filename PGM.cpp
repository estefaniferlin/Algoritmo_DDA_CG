#include "PGM.hpp"
#include <iostream>
#include <cmath>
#include <iostream>

using namespace std;

PGM::PGM(){ // struct 
    pixels = nullptr;
	larg = 0;
	alt = 0;
	tipo = "";
}

PGM::~PGM() {
    if (pixels)
        delete pixels;
    pixels = nullptr;
}

void PGM::desenharLinha(int x1, int y1, int x2, int y2, int cor)
{

    if(!pixels)
    {
        cout << "Leia a imagem primeiro!!\n";
        return;
    }

	// variáveis para armazenar a diferença entre as posições x e y
	int diferencaX, diferencaY;
	int qtdPassos;

	diferencaX = x2 - x1;
	diferencaY = y2 - y1;

	// calcula o valor absoluto
	int valAbsolutoX = abs(diferencaX);
	int valAbsolutoY = abs(diferencaY);

	// variaveis para incrementar x e y em cada passo
	float auxX, auxY;

	// valores iniciais de x e y
	float x = x1;
	float y = y1;

	// expressão apra determinar o numero de passos necessarios para percorrer a linha desejada pelo algoritmo DDA
	if(valAbsolutoX > valAbsolutoY)
	{
		qtdPassos = valAbsolutoX;
	}else{
		qtdPassos = valAbsolutoY;
	}

    // para saber quantas posições de qual eixo vai se mexer
	auxX = diferencaX / qtdPassos;
	auxY = diferencaY / qtdPassos;

	// desenha a linha na imagem
	for(int i = 0; i <= qtdPassos; i++)
	{
		int posicaoX = round(x);
		int posicaoY = round(y);

		//verificar se o pixel existe
		if(posicaoX >= 0 && posicaoX < larg && posicaoY >= 0 && posicaoY < alt)
		{
			this->setPixel(posicaoX, posicaoY, cor);
		}

		x += auxX;
		y += auxY;
	}
}


int PGM::getLargura()
{
    return larg;
}

int PGM::getAltura()
{
    return alt;
}


unsigned char* & PGM::getPixels()
{
    return pixels;
}

unsigned char PGM::getPixel(int x, int y){
    return pixels[y*larg + x];
}

void PGM::setPixel(int x, int y, unsigned char cor){

    if(pixels)
        pixels[y*larg + x] = cor;
}

bool PGM::ler(string caminho) {
    ifstream arq;
    string aux;

    

    arq.open(caminho);
    if (!arq.is_open()) {
        cout << "PGM: endereco do arquivo invalido\n";
        return false;
    }

    if (!lerDado(arq, &aux)) {
        cout << "PGM: erro ao ler o tipo da imagem\n";
        return false;
    }
    tipo = aux;


    if (!lerDado(arq, &aux)) {
        cout << "PGM: erro ao ler a largura da imagem\n";
        return false;
    }
    larg = atoi(aux.c_str());

    if (!lerDado(arq, &aux)) {
        cout << "PGM: erro ao ler a altura da imagem\n";
        return false;
    }
    alt = atoi(aux.c_str());


    if (!lerDado(arq, &aux)) {
        cout << "PGM: erro ao ler o valor máximo de cor\n";
        return false;
    }
    vmax = atoi(aux.c_str());

    if (pixels)
        delete pixels;
    pixels = new unsigned char[larg * alt];

    int i = 0;
    while (!arq.eof()) {
        if (!lerDado(arq, &aux)) {
            break;
        }

        pixels[i] = (unsigned char) atoi(aux.c_str());
        i++;

    }

    //cout << "i: " << i << endl;
    if (i != larg * alt) {
        cout << "PGM: erro ao ler os pixels\n";
        return false;
    }

    //cout << this->tipo << endl;
    //cout << this->larg << endl;
    //cout << this->alt << endl;
    //cout << this->vmax << endl;


    return true;
}

bool PGM::gravar(string caminho) {

    if (!pixels)
        return false;

    ofstream arq;

    arq.open(caminho);
    if (!arq.is_open()) {
        cout << "PGM: endereco do arquivo invalido\n";
        return false;
    }

    arq << tipo << endl;

    arq << larg << " " << alt << endl;

    arq << 255 << endl; // valor máximo de cor fixo em 255

    int tam = larg * alt;
    for (int i = 0; i < tam; i++)
    {
        arq << (int) pixels[i] << endl;
        arq.flush();
    }
        

    arq.close();
    return true;
}

bool PGM::lerDado(ifstream &arq, string *dado) {
    string aux;
    while (!arq.eof()) {
        arq >> aux;
        if (aux.size() > 0 && aux[0] == '#') {
            std::getline(arq, aux);
        }else if(aux.size() > 0){
            *dado = aux;
            return true;
        }

        aux = "";
    }
    return false;
}
