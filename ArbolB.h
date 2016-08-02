/*
 * ArbolB.h
 *
 *  Created on: Oct 11, 2013
 *      Author: ornelyz
 */

#ifndef ARBOLB_H_
#define ARBOLB_H_

#include "NodoB.h"

namespace tikal {

template <class TLlave, class TInfo>
class ArbolB {
public:
	ArbolB();
	ArbolB(int k) ;
	virtual ~ArbolB();

	int getOrden() ;
	void setOrden(int k) ;

	//insertar elemento
	void add (TLlave llave, TInfo info) ;

	/** busca elemento dado por <llv> y lo devuelve si se encuentra
	 * en el árbol.  Retorna NULL si no lo encuentra
	 */
	TInfo& get (TLlave llv) ;

	/** elimina el elemento dado por <llv> y lo devuelve si se logra borrar
	 * del árbol.  Retorna NULL si no lo encuentra
	 */
	TInfo& del (TLlave llv) ;
protected:
	NodoB<TLlave,TInfo> *raiz ;
	int k ;
};

} /* namespace tikal */
#endif /* ARBOLB_H_ */
