#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;



//Classe Nó da árvore
class Node{

	public:
		int value;
		Node* right;
		Node* left;
		int balance;

	//Cria um nó sem nenhum valor;
	Node(){
		this->right = NULL;
		this->left = NULL;
	}

	// Cria um nó e insere o valor dele;
	Node(int value){
		this->right = NULL;
		this->left = NULL;
		this->value = value;
		this->balance = 0;
	}

};

Node *pai = NULL;
int menor = 0, maior = 0;

typedef  int InfoType;

//Criar um árvore vazia;
Node* CreateEmptyTree(){
	return NULL;
}


/*Obtém o tamanho do nó baseado
 *no tamanho dos nós filhos
 */
int GetHeight(Node* node) {
  if (node == NULL)
    return 0;

  int heightOfLeft = GetHeight(node->left);
  int heightOfRight = GetHeight(node->right);

  return heightOfLeft > heightOfRight ?
  						heightOfLeft + 1 :
  						heightOfRight + 1;
}

/*Obtém o fator de balanceament do nó
 * a partir do tamanho de cada filho
 */
int GetBalance(Node* node)
{
    if(node == NULL)
    	return 0;

    return (GetHeight(node->left)- GetHeight(node->right));
}



Node* SearchNode(InfoType value, Node *node) {

    while (node!=NULL){
        if (node->value == value )
            return node; //achou então retorna o ponteiro para o nodo

        else
            if (node->value > value)
               node = node->left;
            else
               node = node->right;
    }
    return NULL; //se não achou
}



Node* SearchDad(InfoType value, Node* node){

	//case o nó a ser inserido seja maior que o atual;
	if(node->value < value){

		// case o nó atual não tenha filhos a sua righteita;
		//(Ele é o dad)
		if(node->right == NULL)
			return node;

		//case ele tenha filhos à sua righteita;
		else
			SearchDad(value, node->right);
	}

	//case o nó a ser inserido seja menor que o atual;
	else{

		// case o nó atual não tenha filhos a sua lefterda;
		//(Ele é o dad)
		if(node->left == NULL)
			return node;

		//case ele tenha filhos à sua leftuerda;
		else
			SearchDad(value, node->left);

	}
}


void BuscaMaiorAEsquerda(Node *arvore){

	if(arvore == NULL){
		return;
	}

	if(maior < arvore->value){
		maior = arvore->value;
	}

	BuscaMaiorAEsquerda(arvore->left);
	BuscaMaiorAEsquerda(arvore->right);
}

void BuscaMenorADireita(Node *arvore){
	if(arvore == NULL){
		return;
	}

	if(menor > arvore->value){
		menor = arvore->value;
	}

	BuscaMenorADireita(arvore->left);
	BuscaMenorADireita(arvore->right);
}

Node *encontraValor(Node *arvore, int valor){
	if (arvore != NULL){
        if(arvore->value == valor){
            return arvore;
        }

        pai = arvore;

        if (arvore->value > valor){
            encontraValor(arvore->left,valor);
        }else{
            encontraValor(arvore->right,valor);
        }
    }
}

Node *removet(Node *Raiz,Node *arvore,int valor){
	pai = NULL;
	arvore = encontraValor(arvore,valor);

	if(arvore != NULL){

		// Caso o elemento é Unico
		if(arvore->right == NULL && arvore->left == NULL && arvore == Raiz){
			return NULL;
		}

		//Primeiro Caso, Elemento está na Folha:
		if(arvore->right == NULL && arvore->left == NULL){
			if(pai->right == arvore){
				pai->right = NULL;
			}else{
				pai->left = NULL;
			}
			free(arvore);
			return Raiz;
		}
		// Segundo caso: Elemento possui somente um filho
		if(arvore->left != NULL && arvore->right == NULL){
			if(pai == NULL){
				return arvore->left;
			}else{
				if(pai->right == arvore){
					pai->right = arvore->left;
				}else{
					pai->left = arvore->left;
				}
				free(arvore);
				return Raiz;
			}
		}
		if(arvore->left == NULL && arvore->right != NULL){
			if(pai == NULL){
				return arvore->right;
			}else{
				if(pai->right == arvore){
					pai->right = arvore->right;
				}else{
					pai->left = arvore->right;
				}
				free(arvore);
				return Raiz;
			}
		}

		// Terceiro Caso: SubArvores
		if(arvore->left != NULL && arvore->right != NULL){

			maior = arvore->left->value;
			menor = arvore->right->value;

			BuscaMaiorAEsquerda(arvore->left);
			BuscaMenorADireita(arvore->right);

			//printf("\n\nMenor = %d, Maior = %d\n\n",menor,maior);

			if(valor-maior>(menor-valor)){
				removet(Raiz,arvore,menor);
				arvore->value = menor;
				return Raiz;
			}else{
				removet(Raiz,arvore,maior);
				arvore->value = maior;
				return Raiz;
			}
		}
	}else{
		printf("\n Elemento nao encontrado!\n\n");
		return Raiz;
	}
}


//insere um novo nó com seu respectivo valor;
void CreateNode(InfoType value, Node** node){

	//Cria o primeiro nó(nó raiz da árvore)
	if(*node == NULL){
		*node = new Node(value);
	}

	//Cria nós diferentes do primeiro nó da árvore
	else{

		//Procura qual será o dad do nó à ser inserido;
		Node * dad = SearchDad(value, (*node));

		// Veirifica se o nó é o filho da righteita, leftuerda ou se é igual ao dad;
		if(dad->value < value)
			dad->right = new Node(value);

		else if(dad->value > value)
			dad->left = new Node(value);

		else
			cout << "o valor já está inserido na árvore\n";
	}

}

// Imprime um árvore

/*	Cada tab representa um nível a mais na árvore
* 	Exemplo:
* 		1
* 			2
*
* 	Significa que 2 é filho de 1;
*/
void printTree(Node* Tree, int tabs){

	Node* node = Tree;
	int tabLeft, tabRight;

	tabRight = tabLeft = tabs;

	// Verifica se a árvore não está vazia;
	if(Tree != NULL){

		// imprime a quantidade necessária de tabs;
		while(tabs--)
			cout<< "\t";

		// Imprime o nó atual;
		printf("%5d\n",node->value);


		if(node->left != NULL)
			printTree(node->left,++tabLeft);

		if(node->right != NULL)
			printTree(node->right,++tabRight);
	}
}


Node* left_rotate(Node* node){

	Node* N2 = node->right;
	node->right = (N2->left) ? N2->left : NULL;
	N2->left = node;
	return N2;
}

Node* right_rotate(Node* node){

	Node* N2 = node->left;
	node->left = (N2->right) ? N2->right : NULL;
	N2->right = node;
	return N2;
}

Node* Double_right_rotate(Node* node){

	node->left = left_rotate(node->left);
	node = right_rotate(node);

	return node;
}

Node* Double_left_rotate(Node* node){

	node->right = right_rotate(node->right);
	node = left_rotate(node);

	return node;
}


Node* antecessor(Node* node){

  if(node->right == NULL)
    return node;

  antecessor(node->right);
}


Node* Balance(Node* node){

	if(node != NULL){
		node->balance = GetBalance(node);

		if(node->balance == 2){

			if(GetBalance(node->left) > 0)
				node = right_rotate(node);
			else
				node = Double_right_rotate(node);
		}

		if(node->balance == -2){

			if(GetBalance(node->right) < 0)
				node = left_rotate(node);
			else
				node = Double_left_rotate(node);
		}
		node->left = Balance(node->left);
		node->right = Balance(node->right);
	}
	return node;
}


