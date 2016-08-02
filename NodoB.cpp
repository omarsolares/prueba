/*
 * NodoB.cpp
 *
 *  Created on: Oct 11, 2013
 *      Author: ornelyz
 */

#include <iostream>
#include "NodoB.h"

namespace tikal {

/** Constructor default: inicializa todas las variables */
template <class TLlave, class TInfo>
NodoB<TLlave,TInfo>::NodoB() {
	llave = nullptr ;
	info = nullptr ;
	hijo = nullptr ;
	k = 0 ;
	numElementos = 0 ;
}

/** creación de un nodo simple.  Incluye la creación de los vectores de llaves, info e hijos */
template <class TLlave, class TInfo>
NodoB<TLlave,TInfo>::NodoB(int k, TLlave llv, TInfo info):NodoB() {
	this->k = k ;
	llave = new TLlave[k] ;
	info = new void*[k] ;
	hijo = new NodoB*[k+1] ;
	this->llave[0] = llv ;
	this->info[0] = info ;
	numElementos = 1 ;
}

/** Constructor con dos hijos.  Usado en la división.  Se supone que la llave que sube está
 * al final del hijo izquierdo  */
template <class TLlave, class TInfo>
NodoB<TLlave,TInfo>::NodoB (int orden, NodoB *izq, NodoB *der):
	NodoB(orden,izq->llave[izq->numElementos-1],
                izq->info[izq->numElementos-1]) {
	izq->numElementos-- ;
	hijo[0] = izq ;
	hijo[1] = der ;
}

/* destructor: elimina todos sus elementos dinámicos y llama recursivamente el
 * destructor de los hijos
 */
template <class TLlave, class TInfo>
NodoB<TLlave,TInfo>::~NodoB() {
	if (llave != nullptr)
		delete [] llave ;
	if (info != nullptr)
		delete [] info ;
	if (hijo != nullptr) {
		for (int i=0; i<numElementos; i++) {
			delete hijo[i] ;
			hijo[i] = nullptr ;
		}
		delete [] hijo ;
	}
}


/** Método de búsqueda */
template <class TLlave, class TInfo>
TInfo& NodoB<TLlave,TInfo>::get (TLlave llv) {
	bool encontrado = false ;
	int posicion = 0 ;
	/* búsqueda lineal dentro del nodo.  En caso de órdenes mayores
	 * es mejor utilizar una búsqueda binaria
	 */
	for (int i=0; i<numElementos && !encontrado; i++) {
		if (llv <= llave[i]) {
			encontrado = true ;
		}
		posicion = i ;
	}

	if ( posicion < numElementos && llv == llave[posicion]) { //existe
		return &info[posicion] ;
	}else { //la llave no existe en este nodo
		if (hijo[posicion] == nullptr) //es un nodo hoja
			return nullptr ;
		else
			return hijo[posicion]->get(llv) ;
	}
}


template <class TLlave, class TInfo>
NodoB<TLlave,TInfo> *NodoB<TLlave,TInfo>::add ( TLlave llv, TInfo inf) {
	bool encontrado = false ;
	int posicion = 0 ;
	NodoB *nvoNodo = nullptr ;

	for (int i=0; i<numElementos && !encontrado; i++) {
		if (llv <= llave[i]) {
			encontrado = true ;
		}
		posicion = i ;
	}

	if ( posicion < numElementos && llv == llave[posicion]) { //ya existe
		throw "Duplicado" ;
	}else {
		if (hijo[0] == nullptr){ // es hoja
			if (numElementos < k) { //cabe en el nodo
				corrimientoSimple (posicion, llv, inf) ;
			}else{ //nodo lleno: división
				nvoNodo = division(posicion, llv, inf) ;
			}
		}else { //no es hoja
			nvoNodo = hijo[posicion]->add(llv, inf) ; // se delega al hijo correspondiente
			if (nvoNodo != nullptr) { //hubo división
				if (numElementos < k) { //cabe en el nodo)
					corrimientoSimple (posicion,
							hijo[posicion]->llave[hijo[posicion]->numElementos-1],
							hijo[posicion]->info[hijo[posicion]->numElementos-1]) ;
					hijo[posicion+1] = nvoNodo ;
					nvoNodo = nullptr ;
				}else
					nvoNodo = division(posicion,
							hijo[posicion]->llave[hijo[posicion]->numElementos-1],
							hijo[posicion]->info[hijo[posicion]->numElementos-1]) ;
			}
		}
	}
	return nvoNodo ;
}

/** Inserción de un elemento, dentro del nodo, corriendo las posiciones posteriores
 * a la posición donde se desea insertar
 *
 *   |2|4|8|...|10|11|12|...|90|100|150|
 *                  ^
 */
template <class TLlave, class TInfo>
void NodoB<TLlave,TInfo>::corrimientoSimple(int posicion, TLlave llv, TInfo inf) {
	for (int i=numElementos; i>posicion; i--){
		llave[i] = llave[i-1] ;
		info[i] = info[i-1] ;
		hijo[i] = hijo[i-1] ;
	}
	llave[posicion]=llv ;
	info[posicion] = inf ;
	hijo[posicion] = nullptr ;
	numElementos ++ ;
}


/*           this                         nvoNodo
 *   |2|4|11|90|               |100|125|150| | | |
 */
template <class TLlave, class TInfo>
NodoB<TLlave,TInfo>* NodoB<TLlave,TInfo>::division (int posicion, TLlave llv, TInfo inf) {
	NodoB *nvoNodo = new NodoB(k,0,nullptr) ;
	int medio = k / 2 ;

	if (posicion >= medio) { //inserción en el derecho
		for (int i=medio+1; i<posicion;i++) {
			nvoNodo->llave[i-medio+1] = llave[i] ;
			nvoNodo->info[i-medio+1]  = info[i] ;
			nvoNodo->hijo[i-medio+1]  = hijo[i] ;
		}
		nvoNodo->llave[posicion-medio+1] = llv ;
		nvoNodo->info[posicion-medio+1]  = inf ;
		nvoNodo->hijo[posicion-medio+1]  = nullptr ;
		for (int i=posicion+1; i<numElementos;i++) {
			nvoNodo->llave[i-posicion] = llave[i] ;
			nvoNodo->info[i-posicion]  = info[i] ;
			nvoNodo->hijo[i-posicion]  = hijo[i] ;
		}
		numElementos = medio + 1 ;
		nvoNodo->numElementos = medio;
	}else{ //inserción a la izquierda el medio
		for (int i=medio-1; i<numElementos;i++) {
			nvoNodo->llave[i-medio] = llave[i] ;
			nvoNodo->info[i-medio]  = info[i] ;
			nvoNodo->hijo[i-medio]  = hijo[i] ;

		}
		llave[medio]=llv ;
		info[medio] = inf ;
		nvoNodo->hijo[medio] = nullptr ;

		numElementos = medio ;
		nvoNodo->numElementos = medio - 1 ;
	}
	return nvoNodo ;
}

/*
template <class TLlave, class TInfo>
void NodoB<TLlave,TInfo>::recorridoInverso() {

	for (int i=numElementos-1 ; i>=0; i--) {
		if (hijo[i+1] != nullptr )
			hijo[i+1]->recorridoInverso () ;
		std::cout << llave[i] ;
	}
	if (hijo[0] != nullptr )
		hijo[0]->recorridoInverso () ;
}
*/

} /* namespace tikal */
