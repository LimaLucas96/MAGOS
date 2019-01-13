#ifndef MAGOSGAME_H
#define MAGOSGAME_H

#include <iostream>
#include <cstdlib>

#include "mazer.h"
#include "render.h"
#include "builder.h"
#include "solve.h"
namespace mgs{

	class MagosGame
	{
	private:
		
		bool fim = false; //bool para dizer se o programa chegou ao fim

		int linhas = 10;
		int colunas = 10;
		int altura = 400;
		int largura = 400;

		mgs::mazer* m; //ponteiro para a classe mazer
		mgs::builder* b; //ponteiro para a classe builder
		mgs::render* r; //ponteiro para a classe render
		mgs::solve* s; //ponteiro para a classe solve
		int c = 0; //contador para criar a barra de progresso.

	public:
		//construtor
		MagosGame(){ /*empty*/ }

		~MagosGame(){}

		/*funcao para iniciar as outras classes e validar a entrada
			@param argc informa o tamnho da entrada.
			@param argv char com as informacoes da entrada.
		*/
		bool initialize(int agrc, char *agrv[]){
			if(agrc < 6){
				for(auto i(0); i < agrc; i++){
					//std::cout <<"i = "<<i;
					if(i == 1){ linhas = atoi(agrv[i]); }
					if(i == 2){ colunas = atoi(agrv[i]); }
					if(i == 3){ largura = atoi(agrv[i]); }
					if(i == 4){ altura = atoi(agrv[i]); }
				}if( agrc == 4){
					int temp = (largura - (2*(largura*0.10)))/colunas;

					altura = (int)((temp*linhas));
					}
				//std::cout << "linha = "<< linhas << " col = "<<colunas<<" , "<<altura<<largura<<std::flush;
				m = new mgs::mazer(linhas,colunas);
				b = new mgs::builder(linhas,colunas,m);
				r = new mgs::render(largura,altura,linhas,colunas);
				s = new mgs::solve(linhas,colunas,*m,*r);
				
				return true;
			}

			return false;
		}
		
		//checa se o usuario clicou em alguma tecla (Não é necessario para o projeto magos)
		void process_events();

		//Atualiza as classes, cria o labirinto e tambem cria a solução do mesmo.
		void update(){
			//verifica se existe mais de um no, se existir continua a contruir o labirinto.
			if(b->sizeN() != 1){
				std::cout << "\r ⎡ CRIANDO LABIRINTO ... ["<<(100*c)/(linhas*colunas) <<"%]"<<std::flush;

				b->execute();
				c++;
			}else{ // se o labirinto ja foi contruido, tenta solucionar o labirinto.

				std::cout << "\n ⎟\n";
				std::cout << " ⎟-> LABIRINTO CONCLUIDO 😎\n";
				std::cout << " ⎟\n";
				std::cout << " ⎟-> RESOLVENDO LABIRINTO ...\n";

				//inicia a função para solucionar o labirinto
				if(s->execute(0)){
					render(); // cria uma imagem do labirinto
					std::cout << " ⎟\n";
					fim = true; //diz que o programa chegou ao fim.
					std::cout << " ⎣ LABIRINTO RESOLVIDO 🤙🏼\n\n";
				}
			}
		}

		//Executa a classe render para criar a imagem do labirinto
		void render(){ r->draw(*m); }
		//retorna True se o labirinto ja foi contruido e solucionado; retorna False caso contrario.
		bool done(){ return fim; }
		
	};	
}

#endif