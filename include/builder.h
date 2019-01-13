#ifndef BUILDER_H
#define BUILDER_H 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

#include <vector>

#include "tree.h"
#include "mazer.h"
namespace mgs{

	class builder
	{
	private:

		tree* tr;					//<! Classe com os nós.
		int m_rows;  				//<! Variavel com o numero de linhas.
		int m_cols;					//<! Variavel com o numero de colunas.

		mgs::mazer* mz;				//<! Ponteiro para a Classe mazer.

		std::vector<int> cells;		//<! Vetor com as celulas ainda nao usada.
		std::vector<int> direcoes;	//<! Vetor com as direções disponiveis para cada celula.

		/* <! Checa quais as direções disponivel na celula.
			@param celula : A celula a ser checada as direções disponiveis.
		*/
		void CheckDirections(int celula);

	public:
		/* <! Construtor Da classe builder.
			@param r numero de linhas.
			@param c numero de colunas.
			@param mz_ ponteiro para a classe mazer.
		*/
		builder(int r, int c, mgs::mazer* mz_) : m_rows(r), m_cols(c), mz( mz_ ){
			std::srand(time(NULL));
			tr = new tree();

			for(int i(0); i < r*c; i++){
				cells.push_back(i);
				tr->makeSet(i);
			}

			std::random_shuffle(cells.begin(),cells.end());

		}

		//Funcao responsavel para criar o labirinto.
		void execute();

		//retorna o numero de celulas disponiveis.
		int size(){ return cells.size(); }

		//retorna o numero de celulas disponiveis.
		int sizeN(){ return tr->size(); }
		//retorna True se todas as celulas ja foram usadas; False caso contrario.
		bool empty(){ return cells.empty(); }
	};

	void builder::execute(){

		//std::cout <<"abriu \n";
		direcoes.clear();

		//std::cout <<"abriu "<<celula<<"\n";
		while(direcoes.empty()){
		int celula = cells[rand() % cells.size()];
		CheckDirections(celula);

		//std::cout <<"abriu \n";

		if( not direcoes.empty() ){

			switch( direcoes[ rand() % direcoes.size() ] ){
				case 0:
					tr->SetsUnion(celula,(celula - m_cols));
					mz->RemoveTop(celula);
					break;
				
				case 1:
					tr->SetsUnion(celula,(celula + m_cols));
					mz->RemoveBottom(celula);
					break;
				
				case 2:
					tr->SetsUnion(celula,(celula - 1));
					mz->RemoveLeft(celula);
					break;
				
				case 3:
					tr->SetsUnion(celula,(celula + 1));
					mz->RemoveRight(celula);
					break;
			}
		}
	}
		//std::cout <<"abriu \n";

		//cells.pop_back();

	}

	void builder::CheckDirections(int celula){
		//std::cout <<"check 1 \n";
		//esquerda
		if((celula - 1) >= 0){
			if(tr->FindSet(celula) != tr->FindSet(celula - 1) && (celula%m_cols) != 0 ){
				direcoes.push_back(2);
			}
		}
		//std::cout <<"check 2\n";

		if(( celula + 1 ) < m_rows * m_cols){
		//direita
			if(tr->FindSet(celula) != tr->FindSet(celula + 1) && ((celula+1)%m_cols) != 0){
				direcoes.push_back(3);
			}
		}
		//std::cout <<"check 3\n";
		//cima

		if((celula - m_cols) > 0){
		//	std::cout <<"check abriu esse cu 3 "<< (celula - m_cols) << "\n";
			if(tr->FindSet(celula) != tr->FindSet(celula - m_cols)){
				direcoes.push_back(0);
			}
		}

		//std::cout <<"check 4\n";

		// baixo
		if((celula + m_cols) < m_rows * m_cols ){
			if( tr->FindSet(celula) != tr->FindSet(celula + m_cols) ){
				direcoes.push_back(1);
			}
		}

		//std::cout <<"check 5\n";
	}
}

#endif