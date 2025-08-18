
// ================================ LIMITACIONES DEL TDA ====================================//
//===============// EL TDA PROCESA ARCHIVOS (LIBROS) DE MÁXIMO 10000 LINEAS //===============//
// TAMBIÉN ASUME QUE LA CANTIDAD MÁXIMA DE PALABRAS ÚNICAS DE UN LIBRO ES DE 10000 PALABRAS. //


#include <vector>
#include <windows.h>
#include <conio.h>
#define LINEAS 10000 
#define PALS 10000
using namespace std;

struct FrecuenciaCaracter {
	char caracter;
	int frecuencia;
};

struct statsPalabras{
	string palabra;
	int repeticiones, longitud;
	char letraInicial;
	
};

struct Libro {
	string autor, titulo, idioma;
	string Contenido[LINEAS];
	int capitulos, cantLetrasIdioma;
	int lineas = 0; //Tamaño lógico
	vector <FrecuenciaCaracter> caracteres;
	vector <statsPalabras> palabras;
};


struct Nodo {
	statsPalabras palabraS;
	Nodo* sig;
};

void asignarTitulo (Libro& libro, string titulo);
void asignarAutor (Libro& libro, string autor);
void asignarCapitulos (Libro& libro, int capitulos);
void asignarIdioma (Libro& libro, string idioma); 
bool mostrarLibro (const Libro& libro); // Muestra todo el contenido del libro.
bool mostrarFrecuenciaPals (const Libro& libro); //Muestra todas las palabras del libro, con sus respectivas frecuencias.
bool mostrarFrecuenciaPals2 (const Libro& libro, char X, USHORT x, USHORT y); // Muestra cinco palabras del libro ordenadas según cantidad de apariciones cuya letra inicial es X. Permite además elegir dónde se muestra en pantalla.
bool obtenerAbecedario (Libro& libro, unsigned int& cantLetras, string& abc); // Obtiene el abecedario del libro teniendo en cuenta su idioma. Devuelve además la cantidad de letras que tiene dicho abecedario.

bool obtenerContenido (Libro& libro, string tituloTXT); // Obtiene el contenido del libro, genera un vector de palabras únicas del mismo para futuro procesamiento de datos, y también guarda las palabras con sus respectivas repeticiones.
bool libroSinContenido (const Libro& libro); // Devuelve true si el libro tiene contenido, false en caso contrario.
bool obtenerFrecuenciaCar (Libro& libro); // Obtiene la frecuencia de cada caracter del libro en un vector ordenado descendentemente.
bool mostrarFrecuenciasCar (const Libro& libro, USHORT x, USHORT y); // Muestra la frecuencia de cada caracter ordenado de forma descendente. Permite además elegir dónde se muestra en pantalla.
bool crearFrecuenciaTXT (Libro& libro); // Crea el archivo frecuencia.txt.
bool obtenerLongMaxPal (const Libro& libro, unsigned int& longMaxPal); // Devuelve la longitud de la palabra máxima encontrada en el libro.
bool contarPals (const Libro& libro, unsigned int L, char X, int& pals); // Cuenta las palabras que comienzan con caracter X y tienen longitud L. Además, las muestra hasta que el usuario presione cualquier tecla.
bool obtenerLongPalProm (const Libro& libro, unsigned int& longPalProm); // Obtiene la longitud de la palabra promedio en el libro teniendo en cuenta las palabras únicas del mismo.
bool obtenerPctjVoC (const Libro& libro, float& porcentaje, bool VoC); // Devuelve el porcentaje de palabras que comienzan con vocal si VoC = 0, y el porcentaje de palabras que comienzan con consonante si VoC = 1.

bool crearListaEnlazada (Libro& libro); //Crea una lista enlazada con el tipo de dato statsPalabras.
void imprimirListaEnArchivo (const string& nombreArchivo); //Ordena e imprime la lista según lo solicitado en el enunciado.
