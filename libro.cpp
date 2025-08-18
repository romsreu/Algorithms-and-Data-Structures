#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <conio.h>
#include "libro.h"
#include "archivo.h"
#define CHARS 255 
using namespace std;


const int TF = 10000; 
string historialPalsUnicas[TF];
int tlHist = 0;
int frecuencia [CHARS] = {0};
Nodo* sPtr = NULL; //Se crea la lista enlazada 

//=============== FUNCIONES AUXILIARES PARA LA IMPLEMENTACIÓN DE FUNCIONES DE CABECERA ===============//

bool comparador(const statsPalabras& palabra1, const statsPalabras& palabra2) {
	if (palabra1.repeticiones != palabra2.repeticiones) {
		return palabra1.repeticiones > palabra2.repeticiones;
	} else if (palabra1.longitud != palabra2.longitud) {
		return palabra1.longitud > palabra2.longitud;
	} else {
		return palabra1.letraInicial < palabra2.letraInicial;
	}
}

bool compararFrecuenciasChars(FrecuenciaCaracter a, FrecuenciaCaracter b) {
	return a.frecuencia > b.frecuencia;
}

bool compararFrecuenciasPals (statsPalabras a, statsPalabras b){
	return (a.repeticiones > b.repeticiones);
}

void gotoxyAUX(USHORT x, USHORT y) {
	COORD cp = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cp);
}

bool esVocal (char x){
	x = tolower(x);
	return (x == 'a' || x== 'e' || x == 'i' || x == 'o' || x == 'u');
}

bool esConsonante (char x){
	x = tolower(x);
	if (isalpha(x)){
		if(!esVocal(x)){
			return true;
		}
	}
	return false; 
}

//====================================== IMPLEMENTACION DE FUNCIONES DE CABECERA ===================================//

void asignarTitulo (Libro& libro, string TITULO){
	libro.titulo = TITULO;
}

void asignarAutor (Libro& libro, string AUTOR){
	libro.autor = AUTOR;
}
void asignarCapitulos(Libro& libro, int CAPITULOS){
	libro.capitulos = CAPITULOS;
}
void asignarIdioma (Libro& libro, string IDIOMA){
	libro.idioma = IDIOMA;
}
bool obtenerContenido (Libro& libro, string tituloTXT){
	
	archivo LibroObj;
	string linea;
	LibroObj=setup("Libro",tituloTXT);
	if (apertura(LibroObj)==false){
		return false;
	}
	else{
		bool final=false;
		while (!final and libro.lineas<LINEAS){
			linea = leerLinea(LibroObj, final);
			libro.Contenido[libro.lineas] = linea;
			libro.lineas++;
			
		}
	}
	cierre(LibroObj);
	
	
	string aux, palabra, temp;
	
	for (int i = 0; i<libro.lineas; i++){
		aux = libro.Contenido[i];
		palabra.clear();
		
		for(unsigned int j = 0; j<aux.size(); j++){
			
			if(isalpha(aux[j])){
				palabra += tolower(aux[j]);
			}
			else { 
				
				bool palabraRepetida = false;
				
				for (int k = 0; k < tlHist; k++) {
					if (palabra == historialPalsUnicas[k]) {
						palabraRepetida = true;
						break;
					}
				}
				
				if (!palabraRepetida) {
					historialPalsUnicas[tlHist] = palabra;
					tlHist++;
					
					statsPalabras nuevaPalabra;
					nuevaPalabra.palabra = palabra;
					nuevaPalabra.repeticiones = 1;
					nuevaPalabra.longitud = palabra.size();
					nuevaPalabra.letraInicial = palabra[0];
					libro.palabras.push_back(nuevaPalabra);
				}
				else{
					for (unsigned int i = 0; i < libro.palabras.size(); i++) {
						if (libro.palabras[i].palabra == palabra) {
							libro.palabras[i].repeticiones++;
							break;
						}
					}
				}
				palabra.clear();
			}
		}
	}
	
	/*system("CLS");
	temp = "Todas las palabras únicas que contiene el libro son: ";
	cout<<temp<<endl<<endl;
	for (int i = 0; i<tlHist; i++){
		cout<<i<<" "<<historialPalsUnicas[i]<<", ";
		
	}
	cout<<endl<<endl;
	temp = "Pulse cualquier tecla para continuar.";
	cout<<temp;
	getch();*/
	
	return true;
}
	
bool libroSinContenido (const Libro& libro){
	return (libro.lineas == 0);
}

bool obtenerAbecedario (Libro& libro, unsigned int& cantLetras, string& abc){
	if(libro.idioma.empty()) return false;
	else {
		if(libro.idioma == "Ingles"){
			libro.cantLetrasIdioma = 26;
			abc = "abcdefghijklmnopqrstuvwxyz";
		}
		else if (libro.idioma == "Español"){
			libro.cantLetrasIdioma = 27;
			abc = "abcdefghijklmnñopqrstuvwxyz";
		}
		// .
		// .
		// .
		cantLetras = libro.cantLetrasIdioma;
	}
	return true;
}
bool obtenerFrecuenciaCar (Libro& libro){
	if(libro.lineas == 0) return false; //El libro no tiene contenido
	else{
		string aux;
		for (int i = 0; i<libro.lineas; i++){
			aux = libro.Contenido[i];
			for (unsigned int j = 0; j<aux.size(); j++){
				frecuencia[(int)aux[j]]++;
			}
		}
	}
	for (char x = 'a'; x <= 'z'; x++) {
		if (frecuencia[(int)x] > 0) {
			FrecuenciaCaracter temp = {x, frecuencia[(int)x]};
			libro.caracteres.push_back(temp);
		}
	}
	sort(libro.caracteres.begin(), libro.caracteres.end(), compararFrecuenciasChars);
	return true;
}

bool mostrarLibro (const Libro& libro){
	if(libro.lineas == 0) return false;
	else{
		for (int i = 0; i<libro.lineas; i++){
			cout<<libro.Contenido[i]<<endl;
		}
	}
	return true;
}

bool mostrarFrecuenciasCar (const Libro& libro, USHORT x, USHORT y){
	
	if(libro.lineas == 0){
		return false;
	}
	else{
		string temp="Caracter | Apariciones";
		gotoxyAUX(x-temp.size()/2, y);
		cout<<temp<<endl;
		y=y+2;
		for (unsigned int i = 0; i < libro.caracteres.size(); ++i) {
			temp = "'" + string(1,libro.caracteres[i].caracter) + "'" + " -> " + to_string(libro.caracteres[i].frecuencia);
			gotoxyAUX(x-temp.size()/2,y++);
			cout<<temp;
		}
	}
	return true;
}
	
bool crearFrecuenciaTXT (Libro& libro){
	ofstream txt;
	txt.open("frecuencia.txt");
	if(txt.fail()){
		return false;
	}
	else{
		string temp;
		temp = "Char | Frecuencia";
		txt<<temp<<endl;
		for (unsigned int i = 0; i < libro.caracteres.size(); ++i) {
			temp = "'" + string(1,libro.caracteres[i].caracter) + "'" + " -> " + to_string(libro.caracteres[i].frecuencia);
			txt<<temp<<endl;
		}
	}
	txt.close();
	return true;
}
	
bool contarPals (const Libro& libro, unsigned int L, char X, int& pals){
	if(libro.lineas == 0)return false;
	else{
		const int TF = 100;
		string historialAux[TF], temp; 
		int tlHist = 0;
		string aux, palabra;
		pals = 0;
		X = tolower(X);
		
		for (int i = 0; i<libro.lineas; i++){
			aux = libro.Contenido[i];
			palabra.clear();
			
			for(unsigned int j = 0; j<aux.size(); j++){
				
				if(isalpha(aux[j])){
					palabra += tolower(aux[j]);
					
				}
				else { 
					if(palabra.size() == L && palabra[0] == X){
						bool palabraRepetida = false;
						
						for (int k = 0; k < tlHist; k++) {
							if (palabra == historialAux[k]) {
								palabraRepetida = true;
								break;
							}
						}
						
						if (!palabraRepetida) {
							historialAux[tlHist] = palabra;
							tlHist++;
							pals++;
						}
						
					}
					palabra.clear();
				}
				
			}
		}
		system("CLS");
		temp = "Las palabras encontradas que cumplen con los requerimientos solicitados son: ";
		cout<<temp<<endl<<endl;
		for (int i = 0; i<tlHist; i++){
			cout<<historialAux[i]<<", ";
		}
		cout<<endl<<endl;
		temp = "Pulse cualquier tecla para continuar.";
		cout<<temp;
		getch();
	}
	
	return true;
}

bool obtenerLongMaxPal(const Libro& libro, unsigned int& longMaxPal){
	if(libro.lineas == 0){
		longMaxPal = 0;
		return false;
	}
	else{
		string aux, palabra;
		longMaxPal = 0;
		for (int i = 0; i<libro.lineas; i++){
			aux = libro.Contenido[i];
			palabra.clear();
			for(unsigned int j = 0; j<aux.size(); j++){
				if(isalpha(aux[j])){
					palabra += tolower(aux[j]);
				}
				else{
					if(palabra.size() > longMaxPal){
						longMaxPal = palabra.size();
					}
					palabra="";
				}
				
			}
		}
	}
	return true;
}
	
bool obtenerLongPalProm (const Libro& libro, unsigned int& longPalProm){
	
	if(libro.lineas == 0)return false;
	else{
		string temp;
		string aux, palabra;
		
		for (int i = 0; i<tlHist; i++){
			longPalProm += historialPalsUnicas[i].size();
		}
		longPalProm = longPalProm / tlHist;
	}
	return true;
}
	
bool obtenerPctjVoC (const Libro& libro, float& porcentaje, bool VoC){
	if(libro.lineas == 0) return false;
	else{
		porcentaje = 0;
		string aux;
		if(VoC == 0){
			for(int i = 0; i<tlHist; i++){
				aux = historialPalsUnicas[i];
				if(esVocal(aux[0])){
					porcentaje++;
				}
			}
			porcentaje = (porcentaje/tlHist) * 100;
			return true;
		}
		else{
			for(int i = 0; i<tlHist; i++){
				aux = historialPalsUnicas[i];
				if(esConsonante(aux[0])){
					porcentaje++;
				}
			}
			porcentaje = (porcentaje/tlHist) * 100;
			return true;
		}
		
		
		
	}
	return true;
}
	
bool mostrarFrecuenciaPals (const Libro& libro) {
	if(libro.lineas==0)return false;
	else{
		system("CLS");
		for(unsigned int i = 0; i<libro.palabras.size(); i++){
			cout<<libro.palabras[i].palabra<<" "<<libro.palabras[i].repeticiones<<endl;
		}
	}
	return true;
}

bool mostrarFrecuenciaPals2 (const Libro& libro, char X, USHORT x, USHORT y){
	if(libro.lineas==0)return false;
	else{
	X = tolower(X);
	string temp;
	vector <statsPalabras> aux;
	for (unsigned int i = 0; i<libro.palabras.size(); i++){
		if (libro.palabras[i].palabra[0] == X){
			aux.push_back(libro.palabras[i]);
		}
	}
		sort(aux.begin(), aux.end(), compararFrecuenciasPals);	
		for (unsigned int i = 0; i<5; i++){
			
			temp = "La palabra \"" + aux[i].palabra + "\"" + " aparece " + to_string(aux[i].repeticiones) + " veces.";
			gotoxyAUX(x-temp.size(), y++);
			cout<<temp;
	}
	}
	return true;
}

bool crearListaEnlazada(Libro& libro) {
if (libro.lineas == 0 || libro.palabras.empty()) return false;
else {
	
	for (unsigned int i = 0; i < libro.palabras.size(); i++) {
		Nodo* nuevo = new Nodo; 
		nuevo->palabraS = libro.palabras[i];
		nuevo->sig = NULL;
		
		// Si la lista está vacía
		if (sPtr == NULL) {
			nuevo->sig = sPtr;
			sPtr = nuevo;
		} else {
			Nodo* aux = sPtr;
			//Agg
			while (aux->sig != NULL){
				aux = aux->sig;
			}
			
			nuevo->sig = aux->sig;
			aux->sig = nuevo;
		}
	}
	return true;
}
}

void imprimirListaEnArchivo(const string& nombreArchivo) {
	ofstream archivo (nombreArchivo);
	if (archivo.fail()) {
		cerr << "No se pudo abrir el archivo." << endl;
		return;
	}

vector<statsPalabras> palabras;

//Se agrega el contenido de la lista a un vector
Nodo* actual = sPtr;
while (actual != NULL) {
	palabras.push_back(actual->palabraS);
	actual = actual->sig;
}

sort(palabras.begin(), palabras.end(), comparador);

for (const auto& palabra : palabras) {
	archivo << "Palabra: " << palabra.palabra
	<< " | Repeticiones: " << palabra.repeticiones
	<< " | Longitud: " << palabra.longitud
	<< " | Letra inicial: " << palabra.letraInicial << endl;
}

archivo.close();
}
