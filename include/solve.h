#ifndef SOLVE_H
#define SOLVE_H 

#include <stack>

//#include "include/MagosGame.h"

namespace mgs{

	class solve
	{
	private:
		//std::stack<int> caminho;  

		int m_rol;			// <! Numero de linhas
		int m_col;			// <! Numero de colunas

		mgs::mazer& mz;		// <! referencia para a classe mazer
		mgs::render& rd;	// <! Referencia para a classe render
		//int process = 0;	// <!

	public:
		/*Construtor.
			@param mz_ referencia mazer.
			@param rd_ referencia ao render.
		*/
		solve(mgs::mazer& mz_, mgs::render& rd_ ):mz(mz_),rd(rd_){ }

		/*construtor
			@param r numero de linhas.
			@param c numero de colunas.
			@param mz_ referencia a mazer.
			@param rd_ referencia a render.
		*/
		solve(int r,int c, mgs::mazer& mz_, mgs::render& rd_ ) : 
		m_rol(r),m_col(c), mz( mz_ ),rd(rd_){ /*empty*/ }

		~solve(){}
		//funcao recursiva para a solução do labirinto
		//	@param x indice inicial da celula.
		bool execute( int x );
	};

	bool solve::execute( int x ){
		//process++;
		if( mz[x] & mgs::output) return true;
		if( mz[x] & mgs::visitada){ /*mz[x] = mz[x] |= mgs::caminho;*/ return false; }

		mz[x] |= mgs::visitada;
		rd.draw(mz);
		//esquerda
		if( (x%m_col) != 0 && (x - 1) > 0 && ((mz[x] & mgs::left) == false) ){
			if( execute(x - 1) ){
				return true;
			}
		}
		//direita
		if( ((x + 1)%m_col) != 0 && (x + 1) < m_rol*m_col && ((mz[x] & mgs::right) == false) ){
			
			if( execute(x + 1) ){
				return true;
			}
		}
		//cima
		if( (x - m_col) >= 0 && ((mz[x] & mgs::top) == false) ){
			
			if( execute(x - m_col) ){
				return true;
			}
		}
		//baixo
		if( (x + m_col) < m_rol*m_col && ((mz[x] & mgs::bottom) == false) ){
			
			if( execute(x + m_col) ){
				return true;
			}
		}
		mz[x] = mz[x] & ~mgs::caminho;
		mz[x] |= mgs::caminho;
		return false;
	}
}

#endif