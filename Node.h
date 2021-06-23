#ifndef Node_h
#define Node_h

// Clase nodo usada como contenedores de datos en el arbol
class NodeT{
public:
	NodeT(int data);
	void setData(int data);
	void setLeft(NodeT *left);
	void setRight(NodeT *right);
	int getData();
	NodeT* getLeft();
	NodeT* getRight();

private:
	int data;
	NodeT *left;
	NodeT *right;
};

// constructor
NodeT::NodeT(int data){
	this->data = data;
	this->left = NULL;
	this->right = NULL;
}

// modifica dato del nodo
void NodeT::setData(int data){
	this->data = data;
}

// modifica apuntador a nodo izquierdo
void NodeT::setLeft(NodeT* left){
	this->left = left;
}

// modifica apuntador a nodo derecho
void NodeT::setRight(NodeT* right){
	this->right = right;
}

// retorna dato del nodo
int NodeT::getData(){
	return this->data;
}

// retorna apuntador a nodo izquierdo
NodeT* NodeT::getLeft(){
	return this->left;
}

// modifica apuntador a nodo derecho
NodeT* NodeT::getRight(){
	return this->right;
}

#endif /* Node_h */
