#ifndef MAZER_H
#define MAZER_H

#include <stdlib.h>
#include <vector>

//#include "render.h"
//#include "MagosGame.h"

using byte = unsigned char;
//class MagosGame;

namespace mgs{

	//tabela para auxiliar no Bitwise
	static const unsigned char top = 0x1;
	static const unsigned char bottom = 0x2;
	static const unsigned char left = 0x4;
	static const unsigned char right = 0x8;
	static const unsigned char visitada = 0x10;
	static const unsigned char caminho = 0x20;
	static const unsigned char output = 0x40;
	static const unsigned char input = 0x80;

	class mazer
	{
	private:
		std::vector<byte> mazers;  //<! Vetor com as celulas do labirinto.
		size_t row;				   //<! Numero de linhas;
		size_t col;				   //<! Numero de colunas.
		
	public:
		/*construtor 
			@param r numero de linhas.
			@param c numero de colunas.
		*/
		mazer(size_t r=0, size_t c=0):
		row{r},
		col{c}{ 
			mazers.assign( r * c , mgs::top | mgs::bottom | mgs::left | mgs::right );

			mazers[0] |= mgs::input;
			mazers[(row * col) - 1] |= mgs::output; 
		}

		~mazer(void){
			//TODO
		}

		/*transforma as coordenadas (x,y) em indice.
			@param coordenada x.
			@param coordenada y.
		*/
		int index(size_t x, size_t y);

		/* remove a linha do topo.
			@param indice da celula.
		*/
		void RemoveTop(int x);
		/* remove a linha de baixo.
			@param indice da celula.
		*/
		void RemoveBottom(int x);
		/* remove a linha da esquerda.
			@param indice da celula.
		*/
		void RemoveLeft(int x);
		/* remove a linha da direita.
			@param indice da celula.
		*/
		void RemoveRight(int x);
		
		//operador []
		byte& operator[](size_t t){ return mazers[t]; }

	};

	void mazer::RemoveTop(int x){

		auto position = x;

		if(mazers[position] & mgs::top){
			
			//std::cout << (int)mazers[position] << "\n";
			mazers[position] = mazers[position] & ~mgs::top;

			RemoveBottom(x - col);
		}
	}

	void mazer::RemoveBottom(int x){

		auto position = x;
		//std::cout << "index  bottom = "<< position << "\n";
		if(mazers[position] & mgs::bottom){
			
			mazers[position] = mazers[position] & ~mgs::bottom;

			RemoveTop(x + col);
		}
	}

	void mazer::RemoveLeft(int x){

		auto position = x;

		if(mazers[position] & mgs::left){
			
			//std::cout << (int)mazers[position] << "\n";
			mazers[position] = mazers[position] & ~mgs::left;

			RemoveRight(x-1);
		}
	}

	void mazer::RemoveRight(int x){

		auto position = x;

		if(mazers[position] & mgs::right){
			
			mazers[position] = mazers[position] & ~mgs::right;

			RemoveLeft(x + 1);
		}
	}

	int mazer::index( size_t x, size_t y){

		int id = y * col + x ;

		return id;
	}
}

#endif