/*
 * caja.h
 *
 *  Created on: 23/04/2016
 *      Author: ornelyz
 */

#ifndef CAJA_H_
#define CAJA_H_

namespace ixtabai {

template <class Tipo>
class caja {
public:
	caja();
	virtual ~caja();

	void setValor (Tipo valor) {
		this->valor = valor ;
	}
	Tipo getValor () {
		return valor ;
	}
private:
	Tipo valor ;
};




main {

	caja<int> cint() ;
	caja<char *> cchar () ;

	int x = o ;
	char *s ;

	cint.setValor (x) ;
	cchar.setValor (s) ;
}

class caja {
public:
	caja();
	virtual ~caja();

	void setValor (int valor) {
		this->valor = valor ;
	}
	int getValor () {
		return valor ;
	}
private:
	int valor ;
};

class cajaStr {
public:
	cajaStr ();
	virtual ~cajaStr();

	void setValor (char *valor) {
		this->valor = valor ;
	}
	char *getValor () {
		return valor ;
	}
private:
	char *valor ;
};


} /* namespace ixtabai */

#endif /* CAJA_H_ */
