#include <iostream>
#include "BST.h"

using namespace std;

// muestra de toda la funcionalidad
int main() {
	cout << endl;
	cout << "1. crea instancia arbol1" << endl;
	BST arbol1;

	cout << "2. agrega [20,14,25,10,18,17,28,27,30,19] a arbol1" << endl << endl;
	arbol1.add(20);
	arbol1.add(14);
	arbol1.add(25);
	arbol1.add(10);
	arbol1.add(18);
	arbol1.add(17);
	arbol1.add(28);
	arbol1.add(27);
	arbol1.add(30);
	arbol1.add(19);

	cout << "3. print a arbol1 de todos los tipos" << endl;
	cout << "\tprint arbol1 pre-order: ";
	arbol1.print(1);
	cout << "\tprint arbol1 in-order: ";
	arbol1.print(2);
	cout << "\tprint arbol1 post-order: ";
	arbol1.print(3);
	cout << "\tprint leaves arbol1: ";
	arbol1.print(4);
	cout << "\tprint Level x Level arbol1: ";
	arbol1.print(5);
	cout << endl;

	cout << "4. crea instancia arbol2 a partir de arbol1" << endl;
	BST arbol2(arbol1);

	cout << "\tprint arbol2 in-order: ";
	arbol2.print(2);
	cout << endl;

	cout << "5. imprime los niveles de nodos [20, 14, 10, 19] en arbol2" << endl;
	cout << "\tNivel de nodo 20: ";
	cout << arbol2.whatLevelAmI(20) << endl;
	cout << "\tNivel de nodo 14: ";
	cout << arbol2.whatLevelAmI(14) << endl;
	cout << "\tNivel de nodo 10: ";
	cout << arbol2.whatLevelAmI(10) << endl;
	cout << "\tNivel de nodo 19: ";
	cout << arbol2.whatLevelAmI(19) << endl;
	cout << endl;

	cout << "6. altura arbol1: " << arbol1.height() << endl << endl;

	cout << "7. compara arboles 1 y 2 para revisar si son iguales: " << endl;
	if(arbol1 == arbol2){
		cout << "\tarbol1 y arbol2 son iguales" << endl;
	}
	else{
		cout << "\tarbol1 y arbol2 son diferentes" << endl;
	}
	cout << endl;

	cout << "8. elimina elemento 18 de arbol1" << endl << endl;
	arbol1.remove(18);

	cout << "9. vuelve a comparar arboles 1 y 2 para revisar si son iguales: " << endl;
	if(arbol1 == arbol2){
		cout << "\tarbol1 y arbol2 son iguales" << endl;
	}
	else{
		cout << "\tarbol1 y arbol2 son diferentes" << endl;
	}
	cout << endl;

	cout << "10. crea instancia arbol3 a partir de arbol2" << endl << endl;
	BST arbol3(arbol2);
	cout << "11. agrega [102] a arbol3" << endl;
	arbol3.add(102);

	cout << "\tprint arbol3 in-order: ";
	arbol3.print(2);
	cout << endl;

	cout << "12. compara cantidad de elementos en arboles 1, 2 y 3: " << endl;
	cout << "\tarbol1: " << arbol1.count() << endl;
	cout << "\tarbol2: " << arbol2.count() << endl;
	cout << "\tarbol3: " << arbol3.count() << endl;
	cout << endl;

	cout << "13. compara anchuras de arboles 1, 2 y 3: " << endl;
	cout << "\tAnchura arbol1: " << arbol1.maxWidth() << endl;
	cout << "\tAnchura arbol2: " << arbol2.maxWidth() << endl;
	cout << "\tAnchura arbol3: " << arbol3.maxWidth() << endl;
	cout << endl;

	cout << "14. revisa en arboles 1 y 2 si existe el elemento 18: " << endl;
	cout << "\tsearch 18 en arbol1: " << (arbol1.search(18) == 1 ? "true" : "false") << endl;
	cout << "\tsearch 18 en arbol2: " << (arbol2.search(18) == 1 ? "true" : "false") << endl;
	cout << endl;

	cout << "15. imprime los ancestros de los elementos 27 y 17 en arbol 1: " << endl;
	cout << "\tancestros de elemento 17: ";
	arbol1.ancestors(17);
	cout << "\tancestros de elemento 27: ";
	arbol1.ancestors(27);
	cout << endl;

	cout << "16. encuentra el pariente en comun mas cercano de los elementos 17 y 27: " << endl;
	cout << "\tpariente mas cercano: " << arbol1.nearestRelative(17, 27) << endl;
	cout << endl;

	cout << "17. Invierte el arbol2: " << endl;
	cout << "\tprint arbol2 in-order: ";
	arbol2.print(2);

	arbol2.mirror();

	cout << "\tprint arbol2 in-order: ";
	arbol2.print(2);

	return 0;
}

