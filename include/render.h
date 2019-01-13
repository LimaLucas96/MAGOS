#ifndef RENDER_H
#define RENDER_H

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <sstream>

#include "canvas.h"
#include "common.h"
//#include "MagosGame.h"
#include "mazer.h"


using cubes = unsigned int;
using byte = unsigned char;

using namespace canvas;

namespace mgs{


	class render
	{
	public:
		/* Construtor
			@param w altura.
			@param h largura.
			@param line numero de linhas.
			@param colum numero de colunas.
		*/
		render(size_t w = 0, size_t h = 0, size_t line = 0, size_t colum = 0) :
		 altura{w},
		 largura{h},
		 offsetA{static_cast<size_t> (w * 0.10)},
		 offsetL{static_cast<size_t> (h * 0.10)},
		 row{line},
		 col{colum}
		 { c.reset(w,h); }

		~render(void){
			//TODO
		}
		/*funcao que gerencia a criação da imagem.
			@param matrix referencia a classe mazer.
		*/
		void draw(mgs::mazer& matrix);
		
		
	
	private:
		size_t altura;		// <! altura da imagem.
		size_t largura;		// <! largura da imagem.
		size_t offsetA;		// <! offset da imagem da altura para o labirinto
		size_t offsetL;		// <! offset da imagem da largura para o labirinto.
		size_t row;			// <! numero de linhas.
		size_t col;			// <! numero de colunas.

		int cont = 0;		//contador para o numero da imagem.

		Canvas c; // <! classe canvas.

		/*Desenha a as bordas do labirinto.*/
		void drawBoders();

		//monta cada celula do labirinto.
		void MountMatrix(mgs::mazer& matrix);
	};

	void render::draw(mgs::mazer& matrix){
		c.clear( LIGHT_GREY ); //coloca uma imagem de fundo na cor LIGHT_GREY
		
		MountMatrix(matrix); //coloca as paredes de cada celula.
		
		auto pixels = c.buffer(); 

		stbi_write_png_compression_level = 0;    // defaults to 8; set to higher for more compression
    	
    	

    	std::ostringstream oss;
    	oss << "imgs/building_"<< cont << ".png"; //nome da imagem a ser salva.

    	//gera a imagem.
    	stbi_write_png( oss.str().c_str() ,      // file name
                altura, largura,        // image dimensions
                3,                    // # of channels per pixel
                pixels,               // the pixels
                altura * 3);

    	cont ++;
	}

	void render::drawBoders(){

		size_t coord_inicial_x = offsetL;
		size_t coord_inicial_y = offsetA;

		size_t legth_a = largura - 2*offsetA;
		size_t legth_l = altura - 2*offsetL; 

		c.hline( coord_inicial_x , coord_inicial_y , legth_l , BLACK );
		c.hline( coord_inicial_x , coord_inicial_y + legth_a, legth_l , BLACK );
		
		c.vline( coord_inicial_x , coord_inicial_y , legth_a , BLACK );
		
		c.vline( coord_inicial_x + legth_l , coord_inicial_y , legth_a , BLACK );
		
	}

	void render::MountMatrix(mgs::mazer& matrix){
		
		auto tam_length_l_cube = (altura - 2*offsetL) / col;
		auto tam_length_a_cube = (largura - 2*offsetA) / row;
		
		size_t coord_inicial_x = offsetL;
		size_t coord_inicial_y = offsetA;
		
		int i(0);

		for(auto line(0); line < row; line++){
			for(auto colum(0); colum < col; colum++){
				
				if(matrix[i] & mgs::caminho){

					c.box( (colum*tam_length_l_cube) + coord_inicial_x  + (tam_length_l_cube * 0.30),
					 coord_inicial_y + (line*tam_length_a_cube) + (tam_length_a_cube * 0.30),
					  tam_length_a_cube - (2*(tam_length_a_cube * 0.25)),
					  tam_length_l_cube - (2*(tam_length_l_cube * 0.25)), YELLOW );	

					//esquerda
					if( (i%col) != 0 && (i - 1) > 0 ){
				        if((matrix[i] & mgs::left) == false){
				        c.box( (colum*tam_length_l_cube) + coord_inicial_x /* + (tam_length_l_cube * 0.30)*/,
					      coord_inicial_y + (line*tam_length_a_cube) + (tam_length_a_cube * 0.30),
					      tam_length_a_cube - (2*(tam_length_a_cube * 0.25)),
					      /* tam_length_l_cube - */(2*(tam_length_l_cube * 0.25)), YELLOW );
					    }
			     	}
			     	//direita
			     	if( ((i + 1)%col) != 0 && (i + 1) < row*col ){
			     		if((matrix[i] & mgs::right) == false){
			     			c.box( (colum*tam_length_l_cube) + coord_inicial_x  + (tam_length_l_cube * 0.30),
					      coord_inicial_y + (line*tam_length_a_cube) + (tam_length_a_cube * 0.30),
					      tam_length_a_cube - (2*(tam_length_a_cube * 0.25)),
					      tam_length_l_cube/* - (2*(tam_length_l_cube * 0.25))*/, YELLOW );
			     		}
			     	}
			     	//cima
			     	if((i - col) >= 0){
			     		if(matrix[i - col] & mgs::visitada && (matrix[i] & mgs::top) == false ){
			     			c.box( (colum*tam_length_l_cube) + coord_inicial_x  + (tam_length_l_cube * 0.30),
					      coord_inicial_y + (line*tam_length_a_cube) /*+ (tam_length_a_cube * 0.30)*/,
					       (2*(tam_length_a_cube * 0.25)),
					      tam_length_l_cube - (2*(tam_length_l_cube * 0.25)), YELLOW );
			     		}
			     	}
			     	//baixo
			     	if((i + col) < row*col){
			     		if(matrix[i + col] & mgs::visitada && (matrix[i] & mgs::bottom) == false ){
			     			c.box( (colum*tam_length_l_cube) + coord_inicial_x  + (tam_length_l_cube * 0.30),
					      coord_inicial_y + (line*tam_length_a_cube) + (tam_length_a_cube * 0.30),
					       tam_length_a_cube /*- (2*(tam_length_a_cube * 0.25))*/,
					      tam_length_l_cube - (2*(tam_length_l_cube * 0.25)), YELLOW );
			     		}
			     	}
				}

				else if(matrix[i] & mgs::visitada){

					if( ((i + 1)%col) != 0 && (i + 1) < row*col ){
			     		if((matrix[i] & mgs::right) == false && matrix[i+1] & mgs::caminho){
			     			c.box( (colum*tam_length_l_cube) + coord_inicial_x  + (tam_length_l_cube * 0.30),
					      coord_inicial_y + (line*tam_length_a_cube) + (tam_length_a_cube * 0.30),
					      tam_length_a_cube - (2*(tam_length_a_cube * 0.25)),
					      tam_length_l_cube/* - (2*(tam_length_l_cube * 0.25))*/, YELLOW );
			     		}
			     	}
			     	
					c.box( (colum*tam_length_l_cube) + coord_inicial_x  + (tam_length_l_cube * 0.30),
					 coord_inicial_y + (line*tam_length_a_cube) + (tam_length_a_cube * 0.30),
					  tam_length_a_cube - (2*(tam_length_a_cube * 0.25)),
					  tam_length_l_cube - (2*(tam_length_l_cube * 0.25)), RED );	


					//esquerda
					if( (i%col) != 0 && (i - 1) > 0 ){
				        if(matrix[i-1] & mgs::visitada && (matrix[i - 1] & mgs::caminho) == false && (matrix[i] & mgs::left) == false){
				        c.box( (colum*tam_length_l_cube) + coord_inicial_x /* + (tam_length_l_cube * 0.30)*/,
					      coord_inicial_y + (line*tam_length_a_cube) + (tam_length_a_cube * 0.30),
					      tam_length_a_cube - (2*(tam_length_a_cube * 0.25)),
					      /* tam_length_l_cube - */(2*(tam_length_l_cube * 0.25)), RED );
					    }
			     	}
			     	//direita
			     	if( ((i + 1)%col) != 0 && (i + 1) < row*col ){
			     		if(matrix[i+1] & mgs::visitada && (matrix[i + 1] & mgs::caminho) == false && (matrix[i] & mgs::right) == false){
			     			c.box( (colum*tam_length_l_cube) + coord_inicial_x  + (tam_length_l_cube * 0.30),
					      coord_inicial_y + (line*tam_length_a_cube) + (tam_length_a_cube * 0.30),
					      tam_length_a_cube - (2*(tam_length_a_cube * 0.25)),
					      tam_length_l_cube/* - (2*(tam_length_l_cube * 0.25))*/, RED );
			     		}
			     	}
			     	//cima
			     	if((i - col) >= 0){
			     		if(matrix[i - col] & mgs::visitada && (matrix[i] & mgs::top) == false && (matrix[i - col] & mgs::caminho) == false){
			     			c.box( (colum*tam_length_l_cube) + coord_inicial_x  + (tam_length_l_cube * 0.30),
					      coord_inicial_y + (line*tam_length_a_cube) /*+ (tam_length_a_cube * 0.30)*/,
					       (2*(tam_length_a_cube * 0.25)),
					      tam_length_l_cube - (2*(tam_length_l_cube * 0.25)), RED );
			     		}
			     	}
			     	//baixo
			     	if((i + col) < row*col){
			     		if(matrix[i + col] & mgs::visitada && (matrix[i] & mgs::bottom) == false && (matrix[i + col] & mgs::caminho) == false ){
			     			c.box( (colum*tam_length_l_cube) + coord_inicial_x  + (tam_length_l_cube * 0.30),
					      coord_inicial_y + (line*tam_length_a_cube) + (tam_length_a_cube * 0.30),
					       tam_length_a_cube /*- (2*(tam_length_a_cube * 0.25))*/,
					      tam_length_l_cube - (2*(tam_length_l_cube * 0.25)), RED );
			     		}
			     	}
			     	
				}


				if(matrix[i] & mgs::top ){
					c.hline( (colum*tam_length_l_cube) + coord_inicial_x, coord_inicial_y + (line*tam_length_a_cube), tam_length_l_cube, BLACK);
				}
				if(matrix[i] & mgs::bottom ){
					c.hline( (colum*tam_length_l_cube) + coord_inicial_x , coord_inicial_y + (line*tam_length_a_cube) + tam_length_a_cube , tam_length_l_cube, BLACK);
				}
				if(matrix[i] & mgs::left){
					c.vline( (colum*tam_length_l_cube) + coord_inicial_x , coord_inicial_y + (line*tam_length_a_cube), tam_length_a_cube, BLACK);
				}
				if(matrix[i] & mgs::right ){
					c.vline( ( colum * tam_length_l_cube ) + coord_inicial_x + tam_length_l_cube, coord_inicial_y + (line*tam_length_a_cube) , tam_length_a_cube , BLACK);
				}

				

				if(matrix[i] & mgs::input){

					
					c.box( (colum*tam_length_l_cube) + coord_inicial_x  + (tam_length_l_cube * 0.30),
					 coord_inicial_y + (line*tam_length_a_cube) + (tam_length_a_cube * 0.30),
					  tam_length_a_cube - (2*(tam_length_a_cube * 0.25)),
					  tam_length_l_cube - (2*(tam_length_l_cube * 0.25)), DEEP_SKY_BLUE );	

				}else if(matrix[i] & mgs::output){

					c.box( (colum*tam_length_l_cube) + coord_inicial_x + (tam_length_l_cube * 0.30),
					 coord_inicial_y + (line*tam_length_a_cube) + (tam_length_a_cube * 0.30),
					  tam_length_a_cube - (2*(tam_length_a_cube * 0.25)),
					  tam_length_l_cube - (2*(tam_length_l_cube * 0.25)), GREEN );	
				}

				i ++;
			}
		}

	}
}

#endif