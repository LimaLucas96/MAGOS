#include <iostream>

#include "../include/MagosGame.h"  //Classe MagosGame


int main(int argc, char *argv[])
{
	mgs::MagosGame mg; //constroi a classe MagosGame

	/*inicializa o programa, passando os argumentos de entrada.
		@return True caso tenha ocorrido tudo certo; false caso contrario.
	*/
	bool result = mg.initialize(argc,argv);
	//se tiver ocorrido algum problema o progama exibe a mensagem de erro e encerra.
	if(result == false){
		std::cout << " ERROR NA ENTRADA DO ARQUIVO\n";
		return -1;
	}

	//enquanto o programa tiver criando ou solucionando o labirinto
	while(not mg.done()){
		mg.render(); //Cria uma imagem do labirinto.
		mg.update(); //atualiza a executao do labirinto.
		
	}

	return 0;
}