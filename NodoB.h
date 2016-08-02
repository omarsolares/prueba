/*
 * NodoB.h
 *
 *  Created on: Oct 11, 2013
 *      Author: ornelyz
 */

#ifndef NODOB_H_
#define NODOB_H_

namespace tikal {

template <class TLlave, class TInfo>
class NodoB {
public:
	NodoB() ;
	NodoB(int k, TLlave llv, TInfo inf) ;
	NodoB(int k, NodoB *izq, NodoB *der) ;
	virtual ~NodoB() ;

	TInfo &get (TLlave llv) ;
	NodoB *add (TLlave llv, TInfo inf) ;
	TInfo &del (TLlave llv) ;

private:
	TLlave *llave ;  //TLlave llave[]
 	TInfo *info ;    //TInfo info[]
	NodoB **hijo ;   //NodoB *hijo[]
	int k ;  // orden
	int numElementos ;

	void corrimientoSimple(int posicion, TLlave llv, TInfo inf) ;
	NodoB *division (int posicion, TLlave llv, TInfo inf) ;
};

} /* namespace tikal */
#endif /* NODOB_H_ */
