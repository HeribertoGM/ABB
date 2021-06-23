#ifndef BST_h
#define BST_h

#include <stack>
#include <queue>
#include "Node.h"

// definicion de clase Arbol
class BST{
public:
	BST();
	BST(const BST &otro);
	~BST();
	void add(int data);
	bool search(int data);
	void remove(int data);
	void print(int data);
	int count();
	int height();
	void ancestors(int data);
	int whatLevelAmI(int data);
	void mirror();
	bool operator==(const BST &otra);
	int nearestRelative(int data, int data2);
	int maxWidth();

private:
	NodeT *root;
	int howManyChildren(NodeT *r);
	int pred(NodeT *r);
	int succ(NodeT *r);
	void preOrder(NodeT *r);
	void inOrder(NodeT *r);
	void postOrder(NodeT *r);
	void LevelxLevel(NodeT *r);
	void liberar(NodeT *r);
	void printLeaves(NodeT *r);
	int cuenta(NodeT *r);
	int altura(NodeT *r);
	NodeT* copyPreorden(NodeT *r);
	void mirrorAux(NodeT *r);
	bool checa(NodeT *r1, NodeT *r2);
	int tMax(NodeT *r);
};

// Constructor por defecto de clase
BST::BST(){
	root = NULL;
}

// Constructor paramtrizado de clase (crea instancia copia a partir de otra instancia)
BST::BST(const BST &otro){
	root = copyPreorden(otro.root);
}

// destructor
BST::~BST(){
	liberar(root);
}

// inserta dato
void BST::add(int data){
	NodeT *father = NULL;
	NodeT *curr = root;
	while(curr != NULL){
		father = curr;
		if(curr->getData() == data){
			return;
		}
		curr = (curr->getData() > data ? curr->getLeft() : curr->getRight());

	}
	if(father == NULL){
		root = new NodeT(data);
	}
	else{
		if(father->getData() > data){
			father->setLeft(new NodeT(data));
		}
		else{
			father->setRight(new NodeT(data));
		}
		/*
		 ((father->getData() > data) ? father->setLeft(new NodeT(data)) :
		 father->setRight(new NodeT(data)) );
		 */
	}
}

// busqueda de nodo que contiene un dato n
bool BST::search(int data){
	NodeT *curr = root;
	while(curr != NULL){
		if(curr->getData() == data){
			return true;
		}
		curr = (curr->getData() > data ? curr->getLeft() : curr->getRight());
	}
	return false;
}

// elimina nodo que contiene dato n
void BST::remove(int data){
	NodeT *curr = root;
	NodeT *father = NULL;

	//Se busca el dato que se quiere borrar
	while(curr != NULL && curr->getData() != data){
		father = curr;
		curr = (curr->getData() > data) ? curr->getLeft() : curr->getRight();
	}
	if(curr == NULL){
		return;
	}

	int c = howManyChildren(curr);

	switch (c){
			//El que se quiere borrar no tiene hijos
		case 0:
			if(father == NULL){
				root = NULL;
			}
			else{
				if(father->getData() > data){
					father->setLeft(NULL);
				}
				else{
					father->setRight(NULL);
				}
			}
			delete curr;
			break;

			//El que se quiere borrar tiene 1 hijo
		case 1:
			//se quiere borrar la raiz
			if(father == NULL){
				if(curr->getLeft() != NULL){
					root = curr->getLeft();
				}
				else{
					root = curr->getRight();
				}
			}
			//se quiere borrar otro nodo que no es la raiz
			else{
				if(father->getData() > data){
					if(curr->getLeft() != NULL){
						father->setLeft(curr->getLeft());
					}
					else{
						father->setLeft(curr->getRight());
					}
				}
				else{
					if(curr->getLeft() != NULL){
						father->setRight(curr->getLeft());
					}
					else{
						father->setRight(curr->getRight());
					}
				}
			}
			delete curr;
			break;

			//se quiere borrar un nodo que tiene 2 hijos
		case 2:
			int x = succ(curr);
			remove(x);
			curr->setData(x);
			break;
	}
}

// imprime en consola de acuerdo a opcion
void BST::print(int data){
	switch(data){
		case 1: preOrder(root);
			break;
		case 2: inOrder(root);
			break;
		case 3: postOrder(root);
			break;
		case 4: printLeaves(root);
			break;
		case 5: LevelxLevel(root);
			break;
	}
	std::cout << std::endl;
}

// retorna cantidad de nodos en el arbol
int BST::count(){
	return cuenta(root);
}

// retorna la altura (cantidad de niveles) del arbol
int BST::height(){
	return altura(root);
}

// imprime en pantalla los ancestros de un nodo n
void BST::ancestors(int data){
	std::stack<int> pila;
	NodeT *curr = root;
	while(curr != NULL){
		if(curr->getData() == data){
			//empieza a sacar los datos del stack y sale del ciclo
			while(!pila.empty()){
				std::cout << pila.top() << " ";
				pila.pop();
			}
			std::cout << std::endl;
			break;
		}
		//mete el dato que tenga en un stack
		pila.push(curr->getData());
		curr = (curr->getData() > data ? curr->getLeft() : curr->getRight());
	}
}

// retorna el nivel en el que se encuentra el nodo con dato n
int BST::whatLevelAmI(int data){
	NodeT *curr = root;
	int contador = 1;

	while(curr != NULL){
		if(curr->getData() == data){
			return contador;
		}
		curr = (curr->getData() > data ? curr->getLeft() : curr->getRight());
		contador++;
	}
	return -1;
}

// invierte el arbol
void BST::mirror(){
	mirrorAux(root);
}

// operador de igualdad, revisa si 2 arboles son iguales
bool BST::operator==(const BST &otra){
	return checa(this->root, otra.root);
}

// retorna el pariente mas cercano de 2 nodos n,m
int BST::nearestRelative(int data, int data2){
	std::queue<NodeT*> fila1;
	std::queue<NodeT*> fila2;
	NodeT *curr = root;
	NodeT *curr2 = root;
	int aux = 0;
	while(curr != NULL){
		if(curr->getData() == data){
			break;
		}
		fila1.push(curr);
		curr = (curr->getData() > data ? curr->getLeft() : curr->getRight());
	}
	while(curr2 != NULL){
		if(curr2->getData() == data2){
			break;
		}
		fila2.push(curr2);
		curr2 = (curr2->getData() > data2 ? curr2->getLeft() : curr2->getRight());
	}
	aux = root->getData();
	while(!fila1.empty() && !fila2.empty()){
		fila1.pop();
		fila2.pop();

		if(fila1.front() == fila2.front() && fila1.front() != NULL){
			aux = (fila1.front())->getData();
		}
	}
	return aux;
}

// retorna la anchura maxima del arbol
int BST::maxWidth(){
	return tMax(root);
}

/*
 Auxiliar
 se cuentan la cantidad de hijos que tiene un nodo,
 se utiliza para facilitar el borrar nodos
*/
int BST::howManyChildren(NodeT *r){
	int cont = 0;

	if(r->getLeft() != NULL){
		cont++;
	}
	if(r->getRight() != NULL){
		cont++;
	}

	return cont;
}

// Auxiliar
// funcion que retorna el predecesor de un nodo
int BST::pred(NodeT *r){
	NodeT *curr = r->getLeft();

	while(curr->getRight() != NULL){
		curr = curr->getRight();
	}
	return curr->getData();
}

// Auxiliar
// funcion que retorna el sucesor de un nodo
int BST::succ(NodeT *r){
	NodeT *curr = r->getRight();

	while(curr->getLeft() != NULL){
		curr = curr->getLeft();
	}
	return curr->getData();
}

// Auxiliar
// se imprimen primero los padres y luego los hijos
void BST::preOrder(NodeT *r){
	if(r != NULL){
		std::cout << r->getData() << " ";
		preOrder(r->getLeft());
		preOrder(r->getRight());
	}
}

// Auxiliar
// se imprimen en orden ascendente
void BST::inOrder(NodeT *r){
	if(r != NULL){
		inOrder(r->getLeft());
		std::cout << r->getData() << " ";
		inOrder(r->getRight());
	}
}

// Auxiliar
// se imprimen primero los hijos (izquierda->derecha) y despues el padre
void BST::postOrder(NodeT *r){
	if(r != NULL){
		postOrder(r->getLeft());
		postOrder(r->getRight());
		std::cout << r->getData() << " ";
	}
}

// Auxiliar
// imprime todos los nodos dependiendo del nivel que se encuentren
void BST::LevelxLevel(NodeT *r){
	if(r != NULL){
		std::queue<NodeT*> fila;
		fila.push(r);
		while(fila.empty() == false){
			NodeT *aux = fila.front();
			std::cout << aux->getData() << " ";
			fila.pop();
			if(aux->getLeft() != NULL){
				fila.push(aux->getLeft());
			}
			if(aux->getRight() != NULL){
				fila.push(aux->getRight());
			}
		}
	}
}

// Auxiliar del destructor
void BST::liberar(NodeT *r){
	if(r != NULL){
		liberar(r->getLeft());
		liberar(r->getRight());
		delete r;
	}
}

// Auxiliar
// Imprime los nodos hoja del arbol
void BST::printLeaves(NodeT *r){
	if(r != NULL){
		if(r->getLeft() == NULL && r->getRight() == NULL){
			std::cout << r->getData() << " ";
		}
		printLeaves(r->getLeft());
		printLeaves(r->getRight());
	}
}

// Auxiliar
// retorna la cantidad de nodos en el arbol
int BST::cuenta(NodeT *r){
	if(r != NULL){
		return 1 + cuenta(r->getLeft()) + cuenta (r->getRight());
	}
	else{
		return 0;
	}
}

// Auxiliar
// retorna la altura del arbol
int BST::altura(NodeT *r){
	if(r == NULL){
		return 0;
	}
	int izq = altura(r->getLeft());
	int der = altura(r->getRight());
	return 1 + (izq > der ? izq : der);
}

// Auxiliar
// auxiliar que retorna una copia de un arbol
NodeT* BST::copyPreorden(NodeT *r){
	if(r == NULL){
		return NULL;
	}
	NodeT* curr = new NodeT(r->getData());
	curr->setLeft(copyPreorden(r->getLeft()));
	curr->setRight(copyPreorden(r->getRight()));
	return curr;
}

// Auxiliar
// auxiliar que invierte el orden de un arbol
void BST::mirrorAux(NodeT *r){
	if(r != NULL){
		NodeT* aux;

		mirrorAux(r->getLeft());
		mirrorAux(r->getRight());

		aux = r->getLeft();
		r->setLeft(r->getRight());
		r->setRight(aux);
	}
}

// Auxiliar
// auxiliar que revisa la igualdad de dos arboles
bool BST::checa(NodeT *r1, NodeT *r2){
	if(r1 == NULL && r2 == NULL){
		return true;
	}
	if(r1 == NULL || r2 == NULL){
		return false;
	}
	if(r1->getData() != r2->getData()){
		return false;
	}
	else{
		return checa(r1->getLeft(), r2->getLeft()) && checa(r1->getRight(), r2->getRight());
	}
}

// Auxiliar
// auxiliar que retorna la anchura maxima de un arbol
int BST::tMax(NodeT *r){
	if(r == NULL){
		return 0;
	}

	int tamano = 0;
	std::queue<NodeT*> fila;
	fila.push(r);

	while(!fila.empty()){
		int aux = fila.size();
		tamano = (aux > tamano ? aux : tamano);
		while(aux--){
			NodeT *temp = fila.front();
			fila.pop();
			if(temp->getLeft() != NULL){
				fila.push(temp->getLeft());
			}
			if(temp->getRight() != NULL){
				fila.push(temp->getRight());
			}
		}
	}

return tamano;
}

#endif /* BST_h */
