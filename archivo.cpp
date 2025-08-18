#include <stdio.h>
#include <stdlib.h>
#include "archivo.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

ifstream manejador;

archivo setup(string nombre, string nombreF){
	archivo aux;
	aux.nombre = nombre;
	aux.nombrefisico = nombreF;
	aux.cantidad=0;
	return aux;
}
	
bool apertura(archivo X){
	manejador.open(X.nombrefisico.c_str());
	if (manejador.fail())
		return false;
	else
		return true;
}
	
string leerLinea(archivo & X, bool & final){
	string linea;
	final=false;
	if (manejador.eof()==false){
		getline(manejador, linea);
		X.cantidad++;
		}
	else
		final=true;
	return linea;
}
	
bool cierre(archivo X){
	manejador.close();
	if (manejador.fail())
		return false;
	else
		return true;
}
	
int leidas(archivo X){
	return X.cantidad;
}
	
	

