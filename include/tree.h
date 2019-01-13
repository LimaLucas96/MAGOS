#ifndef TREE_H
#define TREE_H

#include <unordered_map>

class tree
{
private:

	class Node
	{
	private:
		int data;		// <! dado
		int rank;		// <! prioridade
		Node* parent;	// <! no seguinte.

	public:
		//construtor
		Node() : 
		data(-1),
		rank(0),
		parent(this){ /*empty*/ }

		//construtor
		Node(int d){
			data = d;
			rank = 0;
			parent = this;
		}
		//retorna o dado do nó.
		int GetData(){ return data; }
		//retorna a prioridade do nó.
		int GetRank(){ return rank; }
		//retorna o proximo nó.
		Node* GetParent(){ return parent; }
		//Retorna o dado do nó segunte.
		int GetParentData(){ return parent->GetData(); }

		//Adiciona um proximo nó.
		void SetParent( Node* p ){ parent = p; }
		//Aumenta a prioridade.
		void IncreaseRank(){ rank++; }
	};

	std::unordered_map< int, Node* > * data_n;  // <! Hash table dos nos.
	
	int n_nodes = 0;
	
	//Checa se o o no estao unidos.
	Node* FindSet(Node* n){
		
		Node* p = n->GetParent();

		if( p == n ){
			return p;
		}

		n->SetParent(FindSet(p));

		return n->GetParent();
	}

public:
	tree(){ data_n = new std::unordered_map< int, Node* >(); }  //construtor
	~tree(){ delete data_n; }
	
	//adiciona um nó.
	void makeSet(int d){
		
		Node* n = new Node(d);

		data_n->insert({d,n});

		n_nodes ++;
	}

	//Retorna o numero de nós.
	int size(){ return n_nodes; }
	//Checa se existe união dos nos.
	int FindSet(int d){

		Node* n = (*data_n)[d];

		return FindSet(n)->GetData();
	}
	/* União dos nós.
		@param d1 no 1.
		@param d2 no 2.
		@return retorna True se foi possivel fazer a união; False caso contrario.
	*/
	bool SetsUnion(int d1,int d2){

		Node* n1 = (*data_n)[d1];
		Node* n2 = (*data_n)[d2];

		Node* parent1 = FindSet(n1);
		Node* parent2 = FindSet(n2);

		if( parent1 == parent2 ){
			return false;
		}

		int rank1 = parent1->GetRank();
		int rank2 = parent2->GetRank();

		if(rank1 < rank2){
			parent1->SetParent(parent2);
		}
		else if(rank1 > rank2){
			parent2->SetParent(parent1);
		}
		else{
			if(d1>d2){
				parent1->SetParent(parent2);
				parent2->IncreaseRank();
			}else{
				parent2->SetParent(parent1);
				parent1->IncreaseRank();
			}
		}
		n_nodes --;
		return true;
	}
};
#endif