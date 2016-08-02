/*
 * ArbolB.cpp
 *
 *  Created on: Oct 11, 2013
 *      Author: ornelyz
 */

#include "ArbolB.h"

namespace tikal {

template <class TLlave, class TInfo>
ArbolB<TLlave,TInfo>::ArbolB() {
	raiz = nullptr ;
	k = 0 ;
}

template <class TLlave, class TInfo>
ArbolB<TLlave,TInfo>::ArbolB(int k) : ArbolB() {
	setOrden (k) ;
}

template <class TLlave, class TInfo>
ArbolB<TLlave,TInfo>::~ArbolB() {
	if (raiz != nullptr)
		delete raiz ;
}

template <class TLlave, class TInfo>
int ArbolB<TLlave,TInfo>::getOrden() {
	return k ;
}

template <class TLlave, class TInfo>
void ArbolB<TLlave,TInfo>::setOrden(int orden) {
	if (orden < 2)
		throw "Orden debe ser mayor o igual a 2 " ;
	if (raiz != nullptr) //hay nodos creados
		throw "Sólo se puede cambiar orden en árbol vacio" ;
	this->k = orden ;
}


/** busca elemento dado por <llave> y lo devuelve si se encuentra
 * en el árbol.  Retorna nullptr si no lo encuentra
 */
template <class TLlave, class TInfo>
TInfo& ArbolB<TLlave,TInfo>::get (TLlave llave) {
	if (raiz == nullptr) { //árbol vacio
		return nullptr ;
	}else{
		return raiz->get(llave) ;
	}
}

//insertar elemento
template <class TLlave, class TInfo>
void ArbolB<TLlave,TInfo>::add(TLlave llave, TInfo info) {
	NodoB<TLlave,TInfo>* nvoNodo = nullptr ;

	if (raiz == nullptr) { //árbol vacio
		raiz = new NodoB<TLlave,TInfo>(k, llave, info) ;
	}else{
		nvoNodo = raiz->add(llave, info) ;

		if (nvoNodo != nullptr) { //hubo división
			NodoB<TInfo,TLlave> *raizTmp = new NodoB<TLlave,TInfo>(k, raiz, nvoNodo) ;
			raiz = raizTmp ;
		}
	}
	return true ;
}

/** elimina el elemento dado por <llave> y lo devuelve si se logra borrar
 * del árbol.  Retorna nullptr si no lo encuentra
 */
template <class TLlave, class TInfo>
TInfo& ArbolB<TLlave,TInfo>::del (TLlave llave) {
	return nullptr ;
}

} /* namespace tikal */
