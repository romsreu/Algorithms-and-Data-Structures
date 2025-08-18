#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

struct archivo{
	string nombre;
	string nombrefisico;
	int cantidad;
}; 

archivo setup(string nombre, string nombreF);
bool apertura(archivo X);
string leerLinea(archivo & X, bool & final);
int leidas(archivo X);
bool cierre(archivo X);
