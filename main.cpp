
//======================================================== LIBRERÍAS ==================================================================//
//============================================================ Y ======================================================================//
//======================================================= DEFINICIONES ================================================================//

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>
#include <cstring>
#include <conio.h>
#include <iomanip>
#include <chrono>
#include <ctime>

//========================== LIBRERIAS TDA =========================//
#include "archivo.h"
#include "libro.h"
#include <cstddef>
//=================================================================//

using namespace std;

#define color SetConsoleTextAttribute
#define BWHITE 15
#define BYELLOW 14
#define BRED 12
#define TURQUOISE 11
#define BGREEN 10
#define BBLUE 9
#define WHITE 7
#define YELLOW 6
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75

//=====================================================================================================================================//
//======================================================== ESTRUCTURAS ================================================================//
//=====================================================================================================================================//

struct Fecha {
	int anio, mes, dia;
};

struct Hora {
	int hora, mins, segs;
};

struct Usuario {
	
	char nombre[20], apellido[20], sexo, legajo[6], pass[6], rol[15];
	Fecha F_ultAcceso;
	Hora H_ultAcceso;
	
}usuarios[100];

//=====================================================================================================================================//
//======================================================== VARIABLES GLOBALES =========================================================//
//=====================================================================================================================================//

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

const char pixel = char(219), noPixel = char(176);
int Frec = 250;
int SegsFrec = 40;
string palabrasTXT [100];
DWORD volumeLevel = 0x11111111;
int plusX, plusY;
int paddingX = 1, paddingY = 1, textoY = 0;
const int altMarco = 35, lonMarco = 108;

Libro sherlock;
string abc; //abecedario del libro a analizar
unsigned int cantLetras = 0; // cantidad de letras del abecedario del libro a analizar
unsigned int longMaxPal = 0; 
unsigned int longPalProm = 0;
float porcentajeVocales, porcentajeConsonantes;
Usuario usuarioActual;
int indiceUser;



//======================================================== PROTOTIPOS =================================================================//
//============================================================ DE =====================================================================//
//========================================================= FUNCIONES =================================================================//

void gotoxy(USHORT x, USHORT y); 
void pantallaBienvenida (const bool mostrarCaratula, const bool mostrarLogo);
void Login ();
void mainMenu ();
void dibujoAhorcado (int vidas);
void extraerPalabras (string palabrasTXT[]);
void palabraAleatoria (string & palabraEnJuego, string palabras[]);
void mostrarVectorChar (char letras[], int tl, int posY);
void juegoAhorcado ();
void cifrarPalabra (const char x[], char y[], int tl);
void juegoPalCifrada ();
void menuJuegos ();
void menuABC();
void ponerMarco (int largo, int alto,int x = paddingX + 2,int y = paddingY);
void transicion ();
int PassValida (const int numLegajo, const char Pass[]); //Función en desuso, ahora no hace falta validar la contraseña con el algoritmo, se compara directamente con aquella guardada en "usuarios.bin"
int busqSecPalCifrada (char letra, int longPalEnJuego, char palCifrada[], int& c);
bool checkHistorial (char x[], int letra);
bool busquedaSecAhorcado (char letra, int longPalEnJuego, const char c_palEnJuego[], char letrasOcultas[], int& c);
void display(const int &fa, const int& n, int x, int y, char wh = noPixel, char bl = pixel);
void calcRespuestas(string ps[], string & pl, int & v, char & l);
void juegoMemoria(string palabrasTXT[]);
void centrarPalabras(string ps[]);
void juegoNumero();
int pedirNumero(unsigned int maxDigitos);
int pedirFactor(int y);
void mostrarCursor(bool mostrar);
void imprimirAviso(string frase, USHORT y);
int pedirIdioma(string idi[], int y);
void abecedario(int idioma);
string pedirContra(bool ocultar = true);
void volver(bool continuar = false);
void configurar();
void mostrarLetrasJugadas (char letrasJugadas [],int tl);

void menuTexto ();
void statsChar (Libro& libro);
void statsPals ();
void MatrizPalabras(int longMaxPal,int cantLetras);
void Consultas();
void obtenerUsuarios (Usuario usuarios[]);
bool existeUser (const char user[], int& indiceUser);
void modificarUltAcceso (int indiceUser);
bool correctPass (const char pass[], int indiceUser);



//============================================================ LA =====================================================================//
//========================================================== FUNCION ==================================================================//
//========================================================= PRINCIPAL =================================================================//

int main(int argc, char *argv[]) {
	
	cout<<"Asegurese de maximizar la ventana. El programa está pensado para usarse en pantalla completa. Luego presione cualquier tecla para continuar.";
	getch();
	
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);
	configurar(); 
	
	obtenerUsuarios(usuarios);
	
	extraerPalabras(palabrasTXT);
	
	asignarTitulo (sherlock, "The adventures of Sherlock Holmes");
	asignarAutor (sherlock, "Arthur Conan Doyle");
	asignarIdioma (sherlock, "Ingles");
	asignarCapitulos (sherlock, 12);
	
	obtenerContenido(sherlock, "The adventures of Sherlock Holmes.txt");
	obtenerFrecuenciaCar (sherlock);
	obtenerAbecedario (sherlock, cantLetras, abc);
	obtenerLongMaxPal (sherlock, longMaxPal);
	obtenerLongPalProm (sherlock, longPalProm);
	obtenerPctjVoC(sherlock, porcentajeVocales,0);
	obtenerPctjVoC(sherlock, porcentajeConsonantes, 1);
	
	crearListaEnlazada(sherlock);
	imprimirListaEnArchivo("palabrasX.txt");
	
	pantallaBienvenida(1,1);
	Login();
	mainMenu();

	return 0;

}

//================================================== PANTALLA DE BIENVENIDA =========================================================//
void pantallaBienvenida (const bool mostrarCaratula, const bool mostrarLogo){

	SetConsoleTitleA("pantallaBienvenida");
	mostrarCursor(false);
	int x = paddingX + lonMarco/2;
	int y = textoY - 4;
	string temp;
	string integrantes[] = {
		{"\033[3mScarabino\033[0m, Román."},
		{"\033[3mSome\033[0m, Student."},
		{"\033[3mSome\033[0m, Student."}
	};
	
	if (mostrarCaratula){
		const int Caratula[25][50] = 
		
		{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1,1,1,0,0},
		{0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0},
		{0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0},
		{0,0,0,0,1,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0},
		{0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0},
		{0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0},
		{0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,1,1,1,0,0,0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,1,1,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,0,0,0,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,1,1,1,1,0,0,1,1,1,1,1,0,0,1,0,0,0,1,1,1,1,0,0,0,1,1,1,0},
		{1,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1},
		{1,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,0,1},
		{1,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,0,1},
		{1,0,0,0,0,0,0,1,0,0,1,0,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,0,1},
		{1,0,0,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,0,1},
		{1,0,0,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,1,1,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,1,1,1,0,0,0,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
		
		
		for (int i = 0; i<25; i++){
			gotoxy(x - 24, y++); 
			for (int j = 0; j<50; j++){
				if(Caratula[i][j] == 1){
					color(hConsole, BWHITE);
					cout<<pixel;
				} else
					cout<<" ";
			}
		}
		ponerMarco(lonMarco, altMarco);
		color(hConsole, YELLOW);
		temp = " \033[4mGrupo 03\033[0m - Segunda Parte";
		gotoxy(x - temp.size()/2 + 7/2, y);
		cout << temp;
		y += 2;
		
		for(int i = 0; i < 3; i++){
			gotoxy(x - integrantes[i].length()/2 + 4, y++);
			color(hConsole, BRED);
			cout << integrantes[i];
		}
		
		color(hConsole, WHITE);
		
		volver(true);
		system("CLS");
	}
	
	y = textoY;
	
	if (mostrarLogo){
		SetConsoleTitleA("~ IPS ~");
		
		int Logo[25][34] = 
		{{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,0,0,1,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{1,0,0,3,3,3,3,3,3,3,0,0,0,0,2,2,2,2,2,0,0,0,0,0,3,3,3,3,3,3,0,0,1,9},
		{1,0,0,0,0,0,3,0,0,0,0,0,0,2,0,0,0,0,0,2,0,0,0,3,0,0,0,0,0,0,0,0,1,0},
		{1,0,0,0,0,0,3,0,0,0,0,0,0,2,0,0,0,0,0,2,0,0,0,3,0,0,0,0,0,0,0,0,1,0},
		{1,0,0,0,0,0,3,0,0,0,0,0,0,2,0,0,0,0,0,2,0,0,0,3,0,0,0,0,0,0,0,0,1,0},
		{1,0,0,0,0,0,3,0,0,0,0,0,0,2,0,0,0,0,0,2,0,0,0,3,0,0,0,0,0,0,0,0,1,0},
		{1,0,0,0,0,0,3,0,0,0,0,0,0,2,0,0,0,0,0,2,0,0,0,3,0,0,0,0,0,0,0,0,1,0},
		{1,0,0,0,0,0,3,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,3,0,0,0,0,0,0,0,0,1,0},
		{1,0,0,0,0,0,3,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,0,0,0,1,8},
		{1,0,0,0,0,0,3,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,1,0},
		{1,0,0,0,0,0,3,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,1,0},
		{1,0,0,0,0,0,3,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,1,0},
		{1,0,0,0,0,0,3,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,1,0},
		{1,0,0,0,0,0,3,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,1,0},
		{1,0,0,0,0,0,3,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,1,0},
		{1,0,0,3,3,3,3,3,3,3,0,0,0,2,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,0,0,0,1,7},
		{1,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{1,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}};
		
		ponerMarco(lonMarco, altMarco);
		
		for (int i = 0; i<25; i++){
			gotoxy(x - 17, y++);
			for (int j = 0; j<34; j++){
				if(Logo[i][j] == 3 or Logo[i][j] == 1){
					color(hConsole, BWHITE);
					cout<<pixel;
				}
				else if (Logo[i][j] == 2){
					color(hConsole, YELLOW);
					cout<<pixel;
					Sleep(5);
				}
				else if (Logo[i][j] == 9){
					Beep(Frec,SegsFrec+200);
					cout<<" \033[1m~ IDIOMAS";
				}
				else if (Logo[i][j] == 8){
					Beep(Frec-100,SegsFrec+100);
					cout<<"   \033[1mPARA";
				}
				else if (Logo[i][j] == 7){
					Beep(Frec+200,SegsFrec+50);
					cout<<"   \033[1mSORPRENDER ~ ";
				}
				else cout<<" ";
			}
		}
		volver(true);
		Beep(Frec+400,SegsFrec+100); 
	}
}
	
//===================================================== FUNCION GOTOXY ==============================================================//	
void gotoxy(USHORT x, USHORT y) {
	COORD cp = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cp);
}
	
//==================================================== VALIDACION PASS ==============================================================//
int PassValida (const int numLegajo, const char Pass[]){
	
	int longitud = strlen(Pass);
	
	if(longitud <5) {
		return -1; // contraseña demasiado corta
	}
	
	else if (longitud>5){
		return -2; // contraseña demasiado larga
	}
	
	
	int PassGen[5];
	unsigned int aux = numLegajo;
	
	for (int i = 0; i<4; i++){
		PassGen[i] = aux%10;
		aux = aux/10;
	}
	
	PassGen[4] = ((numLegajo/10000)+(numLegajo%10))%10;
	
	int c = 0;
	for (int i = 0; i<5; i++){
		if(PassGen[i] == int(Pass[i] - '0')) c++;
		else c=0;
	}
	
	return (c==5);	
}		
	
//========================================================= LOGIN ===================================================================//
void Login (){
	SetConsoleTitleA("Login");
	system("CLS");
	
	int x = paddingX + lonMarco/2;
	int y = textoY;
	string temp, sLegajo, sPass;
	
	
	const int M[21][21] = 
	{{4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,7},  
	{6,0,1,0,0,0,1,1,1,0,1,1,1,0,1,0,1,1,1,0,6},
	{6,0,1,0,0,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,6},
	{6,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,6},
	{6,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,6},
	{6,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,6},
	{6,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,6},
	{6,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,6},
	{6,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,0,6},
	{6,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{9,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,8}};
	
	ponerMarco(lonMarco, altMarco);
		
		for (int i = 0; i<21; i++){
			gotoxy(x - 10, y++);
			for (int j = 0; j<21; j++){
				if(M[i][j] == 1) {
					color(hConsole, YELLOW);
					cout<<char(178);
					color(hConsole, WHITE);
				}
				else if (M[i][j] == 4) cout<<char(201);
				else if (M[i][j] == 5) cout<<char(205);
				else if (M[i][j] == 6) cout<<char(186);
				else if (M[i][j] == 7) cout<<char(187);
				else if (M[i][j] == 8) cout<<char(188);
				else if (M[i][j] == 9) cout<<char(200);
				else cout<<" ";
			}
		}
		
		int intentos = 3;
		
		gotoxy(x - 10,y - 8);
		cout<<char(186)<<"ID: ";
		
		gotoxy(x - 10,y - 5);
		cout<<char(186)<<"Pass:";
		
		temp = "Intentos restantes: ";
		temp += to_string(intentos);
		gotoxy(x - temp.length()/2, paddingY + altMarco - 5);
		cout<<temp;
		
		bool enWhiteList; //Variable fueraDeRango eliminada, no tenía sentido dejarla ya que en la base de datos solo habrán contraseñas dentro del rango. En su lugar fue reemplaza por enWhiteList.
		bool salidalogin = false;
		
		do{
			
			temp = "Intentos restantes: ";
			temp += to_string(intentos);
			gotoxy(x - temp.length()/2, paddingY + altMarco - 5);
			cout<<temp;
			
			gotoxy(x - 5,y - 8);
			cout<<"     ";
			gotoxy(x - 5,y - 8);
			mostrarCursor(true);
			sLegajo = pedirContra(false);
			
			enWhiteList = existeUser(sLegajo.c_str(),indiceUser); 
			
			if(!enWhiteList) {
				Beep(Frec+100,SegsFrec+50); 
				intentos--;
				temp = "Intentos restantes: ";
				temp += to_string(intentos);
			}
			else Beep(Frec+300,SegsFrec+50);
			
			if (intentos > 0 and !enWhiteList){
				temp = "El id ingresado no se encuentra registrado en el sistema. Vuelva a intentar.";
				gotoxy(x - temp.length()/2,paddingY + altMarco - 3);
				cout << temp;
				Sleep(3000);
				gotoxy(x - temp.length()/2,paddingY + altMarco - 3);
				cout<<"                                                                                    ";
			}
			else if (intentos == 0){
				temp = "Intentos restantes: ";
				temp += to_string(intentos);
				gotoxy(x - temp.length()/2, paddingY + altMarco - 5);
				cout<<temp;
				
				temp = "Ha ingresado un ID erróneo multiples veces.";
				gotoxy(x - temp.length()/2,paddingY + altMarco - 3);
				cout << temp;
				
				Sleep(2000);
				
				for (unsigned int i = 0; i < temp.length(); i++) cout << "\b \b";
				
				temp = "Por seguridad, el programa se cerrará.";
				gotoxy(x - temp.length()/2,paddingY + altMarco - 3);
				cout << temp;
				
				salidalogin = true;
				Sleep(2000);
				exit(405);
			}
		} while(!enWhiteList and intentos>0 and !salidalogin);
		
		//=============================LOGICA PASS================================//
		
		string Pass;
		string temp2;
		const char* c_Pass;
		int estadoPass;
		bool salidapass = false;
		do{
			temp = "Intentos restantes: ";
			temp += to_string(intentos);
			gotoxy(x - temp.length()/2, paddingY + altMarco - 5);
			cout<<temp;
			
			gotoxy(x - 3,y - 5);	
			Pass = pedirContra();
			gotoxy(x - 3,y - 5);	
			cout<<"     ";
			c_Pass  = Pass.c_str();
			estadoPass = correctPass(c_Pass,indiceUser);
			
			if (!estadoPass){
				Beep(Frec+100,SegsFrec+50); 
				intentos--;
				temp = "Intentos restantes: ";
				temp += to_string(intentos);
			}
			
			else{
				system("CLS");
				ponerMarco(lonMarco, altMarco);
				temp = "Sesión iniciada correctamente";
				temp2 = (string)(usuarios[indiceUser].nombre) + " " + (string)(usuarios[indiceUser].apellido);
				gotoxy(x - temp.length()/2,paddingY + altMarco/2-3);
				Beep(Frec+300,SegsFrec+50);
				cout<<"\033[3m";
				cout<<temp;
				cout<<"\x1B[0m";
				if(usuarios[indiceUser].sexo == 'M'){
					temp = "Bienvenido ";
					gotoxy(x - (temp.length()/2) - (temp2.size()/2),paddingY + altMarco/2);
					cout<<temp;
					for(unsigned int i = 0; i<temp2.size(); i++){
						color (hConsole, YELLOW);
						cout<<"\x1B[4m";
						
						cout<<temp2[i];
					}
					cout<<"\x1B[0m";
					
					temp = "Ultimo acceso a la aplicación: " + to_string(usuarios[indiceUser].F_ultAcceso.dia) + "-" + to_string(usuarios[indiceUser].F_ultAcceso.mes) + "-" + to_string(usuarios[indiceUser].F_ultAcceso.anio);
					gotoxy(x - temp.length()/2,paddingY + altMarco/2+3);
					cout<<temp;
				}
				else {
					temp = "Bienvenida ";
					gotoxy(x - (temp.length()/2) - (temp2.size()/2),paddingY + altMarco/2);
					cout<<temp;
					for(unsigned int i = 0; i<temp2.size(); i++){
						color (hConsole, YELLOW);
						cout<<"\x1B[4m";
						
						cout<<temp2[i];
					}
					cout<<"\x1B[0m";
					
					temp = "Ultimo acceso a la aplicación: " + to_string(usuarios[indiceUser].F_ultAcceso.dia) + "-" + to_string(usuarios[indiceUser].F_ultAcceso.mes) + "-" + to_string(usuarios[indiceUser].F_ultAcceso.anio);
					gotoxy(x - temp.length()/2,paddingY + altMarco/2+3);
					cout<<temp;
				}
				salidapass = true;
			}
			
			if (estadoPass == 0){
				temp = "La contraseña ingresada no corresponde a esa cuenta.";
				gotoxy(x - temp.length()/2,paddingY + altMarco - 3);
				cout << temp;
				
				Sleep(3000);
				
				for (unsigned int i = 0; i < temp.length(); i++) cout << "\b \b";
			}
			
			if(intentos==0){
				temp = "Intentos restantes: ";
				temp += to_string(intentos);
				gotoxy(x - temp.length()/2, paddingY + altMarco - 5);
				cout<<temp;
				
				
				temp = "Su contraseña no está registrada en el sistema.";
				gotoxy(x - temp.length()/2,paddingY + altMarco - 3);
				cout << temp;
				
				Sleep(2000);
				
				for (unsigned int i = 0; i < temp.length(); i++) cout << "\b \b";
				
				temp = "Por seguridad, el programa se cerrará.";
				gotoxy(x - temp.length()/2,paddingY + altMarco - 3);
				cout << temp;
				
				Sleep(2000);
				
				exit(404);
			}
		} while(!estadoPass and intentos >0 and !salidapass);
		
		modificarUltAcceso(indiceUser);
		
		mostrarCursor(false);
		volver(1);
}
//===================================================== MENU PRINCIPAL ==============================================================//
void mainMenu (){
	SetConsoleTitleA("Menu Principal");
	system("CLS");
	waveOutSetVolume(0, volumeLevel);
	PlaySound("menuPrincipalMusica.wav", NULL, SND_ASYNC|SND_FILENAME);
	transicion();
	string temp;
	int x, y;
	int MenuPrincipal [13][43] =

	{{0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0},
	{0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0},
	{0,0,2,0,0,0,0,0,1,0,1,0,0,0,0,1,1,1,1,1,1,0,1,1,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,2,0,0},
	{0,0,0,0,0,0,0,1,0,1,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0},
	{0,0,2,0,0,0,1,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,0,0,1,0,0,0,2,0,0},
	{0,0,2,0,0,0,1,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,0,0,1,0,0,0,2,0,0},
	{2,2,2,0,0,0,1,0,0,1,0,0,1,0,1,1,1,1,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,0,0,1,0,0,0,2,2,2},
	{0,0,2,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,0,0,1,0,0,0,2,0,0},
	{0,0,2,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,0,0,1,0,0,0,2,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,2,0,0,0,1,0,0,0,0,0,1,0,1,1,1,1,1,1,1,0,1,0,0,0,1,1,0,0,0,0,1,1,1,0,0,0,0,0,2,0,0},
	{0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0},
	{0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0}};
	
	char select;
	bool cond;
	do{
		
		system("CLS");
		cond = true;
		ponerMarco(lonMarco, altMarco);
		x = paddingX + lonMarco/2;
		y = paddingY+2;
		
		for (int i = 0; i<13; i++){
			gotoxy(x - 43/2, y++);
			for (int j = 0; j<43;j++){
				if(MenuPrincipal[i][j] == 1){
					color(hConsole, BWHITE);
					cout<<pixel;
				}
				else if (MenuPrincipal[i][j] == 2){
					color(hConsole, YELLOW);
					cout<<pixel;
				}
				else
					cout<<" ";
			}
		}
		color(hConsole, BWHITE);
		
		ponerMarco(strlen(usuarios[indiceUser].nombre) + strlen(usuarios[indiceUser].apellido)+7, 6 );
		temp =  (string)(usuarios[indiceUser].nombre) + " " + (string)(usuarios[indiceUser].apellido);
		gotoxy(paddingX+5, paddingY+2);
		color(hConsole,YELLOW);
		cout<<temp;
		color(hConsole,BWHITE);
		temp =  (string)(usuarios[indiceUser].rol);
		gotoxy(paddingX+1+strlen(usuarios[indiceUser].nombre)/2 + strlen(usuarios[indiceUser].apellido)/2 , paddingY+3);
		cout<<"\x1B[3m"<<temp<<"\x1B[0m";
		
		temp = "1.- Abecedarios";
		gotoxy(x - temp.size()/2, y+=5);
		color(hConsole, BWHITE);
		cout<<temp;
		
		temp = "2.- Juegos";
		gotoxy(x - temp.size()/2, y+=2);
		cout<<temp;
		
		temp = "3.- Procesador de texto";
		gotoxy(x - temp.size()/2, y+=2);
		cout<<temp;
		
		temp = "X.- Salir de la aplicación";
		gotoxy(x - temp.size()/2, y+=2);
		cout<<temp;
		
		temp = "Ingrese una opción: ";
		gotoxy(x - temp.size()/2, y+=2);
		color(hConsole, YELLOW);
		cout<<temp;
		
		cin>>select;
		
		color(hConsole,BWHITE);
		switch(select){
		case '1': {
			menuABC();
			break;
		}
		case '2':{
			menuJuegos(); 
			break;
		}
		case '3':{
			menuTexto ();
			break;
		}
		case 'x':
		case 'X':{
			system("CLS");
			ponerMarco(lonMarco,altMarco);
			temp = "¿Seguro que quiere salir?";
			gotoxy(x - temp.size()/2, y=altMarco/2);
			cout<<temp;
			temp = "(S/N): ";
			gotoxy(x - temp.size()/2, y+=1);
			cout<<temp;
			char select;
			bool cond2;
			do{
				cin>>select;
				switch(select){
					case 's':
					case 'S':
						system("CLS");
						ponerMarco(lonMarco,altMarco);
						temp = "¡Muchas gracias por probar la aplicación!";
						gotoxy(x - temp.size()/2, y=altMarco/2);
						cout<<temp;
						exit(0);
						break;
					case 'N':
						system("CLS");
						cond2 = false;
						cond = true;
						break;
				}
			} while(cond2);
			break;
		}
		default:{
				cin.ignore();
				temp = "¡Esa opción no es válida!";
				gotoxy (x-temp.size()/2,y+1);
				color(hConsole, BRED);
				cout<<temp;
				Beep(Frec+100,SegsFrec+50); 
				color(hConsole, WHITE);
				Sleep(1000);
				gotoxy (x-temp.size(),y+1);
				for(unsigned int i=0; i<temp.size()*2; i++) cout<<" ";
			}
		}
	} while(cond);
}
	

	
//==================================================== DIBUJO AHORCADO ==============================================================//
void dibujoAhorcado (int vidas){
	int const dibAhorcado [24][22] =
	{{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
	{0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0},
	{0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0},
	{0,0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
	{0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0},
	{0,0,0,1,0,1,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0},
	{0,0,0,1,1,0,0,0,0,0,0,0,0,2,0,0,2,0,2,0,0,2},
	{0,0,0,1,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2},
	{0,0,0,1,0,0,0,0,0,0,0,0,0,2,0,0,2,2,2,0,0,2},
	{0,0,0,1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0},
	{0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0},
	{0,0,0,1,0,0,0,0,0,0,0,0,0,3,0,0,0,4,0,0,0,5},
	{0,0,0,1,0,0,0,0,0,0,0,0,0,0,3,0,0,4,0,0,5,0},
	{0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,3,0,4,0,5,0,0},
	{0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,3,4,5,0,0,0},
	{0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0},
	{0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0},
	{0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0},
	{0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0},
	{0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,6,0,7,0,0,0},
	{0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,6,0,0,0,7,0,0},
	{0,1,0,0,0,1,0,0,0,0,0,0,0,0,6,6,0,0,0,7,7,0},
	{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,1,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0}};
	
	int x = paddingX + lonMarco/2;
	int y = textoY - 2;
	
	int aux; 
	if(vidas<=6 and vidas>=4) aux = 10; 
	else if(vidas<=3 and vidas >1) aux = 6;
	else aux = 4; 
	
	for(int i = 0; i<24; i++){
		
		gotoxy(x - 11, y++);
		
		for(int j = 0; j<22; j++){
			
			if(dibAhorcado[i][j] == 8){
				string temp = "\033[1mVidas restantes: \033[0m";
				gotoxy(x - temp.length()/2, y);
				cout << temp;
				color(hConsole, aux);
				cout<<vidas;
				color(hConsole, WHITE);
			}
			
			if(dibAhorcado[i][j] == 1 && vidas <=6){
				color(hConsole, BWHITE);
				cout<<pixel;
			}
			else if (dibAhorcado[i][j] == 2 && vidas <=5){
				color(hConsole, aux);
				cout<<pixel;
			}
			else if (dibAhorcado[i][j] == 4 && vidas <= 4){
				color(hConsole, aux);
				cout<<pixel;
			}
			else if (dibAhorcado[i][j] == 3 && vidas <= 3){
				color(hConsole, aux);
				cout<<pixel;
			}
			else if (dibAhorcado[i][j] == 5 && vidas <= 2){
				color(hConsole, aux);
				cout<<pixel;
			}
			else if (dibAhorcado[i][j] == 6 && vidas <= 1){
				color(hConsole, aux);
				cout<<pixel;
			}
			else if (dibAhorcado[i][j] == 7 && vidas <= 0){
				color(hConsole, aux);
				cout<<pixel;
			}
			else{
				cout<<" ";
			}
		}
	}
		
}

//==================================================== EXTRAER PALABRAS =============================================================//
void extraerPalabras (string palabras[]){
	
	string linea;
	archivo Entrada;
	int lineas;

	Entrada=setup("Ahorcado en Español", "palabras-3.txt");
	lineas = 100;
	
	if (apertura(Entrada)==false){
		cout << "Error en apertura de archivo." << endl;
	}
	else {
		
		bool final=false;
		int i = 0;
		
		while (!final and i<lineas){
			linea = leerLinea(Entrada, final);
			palabras [i] = linea;
			i++;
			
		}
	}
		cierre(Entrada);
	}
	
//==================================================== PALABRA ALEATORIA ============================================================//
void palabraAleatoria (string & palabraEnJuego, string palabras[]){		
	srand(time(NULL));
	int aux = rand() % 100; 
	palabraEnJuego = palabras[aux];
}
	
//==================================================== BUSQUEDA AHORCADO ============================================================//
bool busquedaSecAhorcado (char letra, int longPalEnJuego, const char c_palEnJuego[], char letrasOcultas[], int& c){
	bool estado = false;
	for (int i = 0; i<longPalEnJuego; i++){
		if(c_palEnJuego[i] == letra){
			letrasOcultas[i] = letra;
			c++;
			estado = true;
		}
	}
	return estado;
}

//===================================================== MOSTRAR VECTOR ==============================================================//
void mostrarVectorChar (char letras[], int tl, int posY){
	int x = paddingX + lonMarco/2;
	int y = paddingY + posY;
	
	string temp = "La palabra oculta tiene ";
	temp += to_string(tl);
	temp += " letras en total:";
	
	gotoxy(x - (temp.length() + tl)/2, y);
	cout << temp;
	
	for (int i = 0; i<tl; i++){
		if(letras[i] >= 'A' and letras[i] <= 'Z'){
			color(hConsole, BGREEN);
			cout<<letras[i];
			color(hConsole, WHITE);
		}
		else{
			color(hConsole, WHITE);
			cout<<letras[i];
		}
	}
}

//===================================================== CHECK HISTORIAL =============================================================//
bool checkHistorial (char x[], int letra){
	for (int i = 0; i<27; i++){
		if(x[i] == letra) return true;
	}
	return false;
}
	
//===================================================== JUEGO AHORCADO ==============================================================//
void juegoAhorcado (){
	SetConsoleTitleA("Ahorcado");
	string palabraEnJuego;
	
	palabraAleatoria(palabraEnJuego, palabrasTXT);
	
	int x = paddingX + lonMarco/2;
	int y = paddingY + altMarco - 3;
	string temp;
	int vidas = 6;
	int longPalEnJuego = palabraEnJuego.length();
	int c = 0, pos = 0, puntos = 100;
	
	const char* c_palEnJuego  = palabraEnJuego.c_str();
	char letrasOcultas [15] = "______________";
	char letrasJugadas [27] = {};
	char letra;
	
	bool hayLetra;
	bool victoria = false;
	bool char_valido;
	bool CheckHist;
	bool bandera = false;
	
	do{
		system("CLS");
		y -= 2;
		ponerMarco(lonMarco, altMarco);
		dibujoAhorcado(vidas);
		mostrarVectorChar(letrasOcultas, longPalEnJuego, 24 + 4);
		
		gotoxy(x - lonMarco/2 + 8, y - 27);
		
		temp = "===== Letras Jugadas =====";
		color(hConsole, YELLOW);
		cout<<temp;
		color(hConsole, BWHITE);
		
		gotoxy(x - lonMarco/2 + 4, y - 25);
		mostrarLetrasJugadas (letrasJugadas,pos);
		
		temp = "Marque una tecla:";
		gotoxy(x - temp.length()/2 - 2, y);
		cout<<temp;
		gotoxy(x + temp.length()/2 + 1, y);
		cin>>letra;
		letra = tolower(letra);
		y += 2;
		
		CheckHist = (checkHistorial(letrasJugadas, letra));
		char_valido = true;
		
		if(!CheckHist){
			if(letra >='a' and letra <='z' ){
				letrasJugadas[pos] = letra;
				pos++; 
			}
			else
				char_valido = false;
			bandera = true;
			hayLetra = busquedaSecAhorcado(letra,longPalEnJuego, c_palEnJuego, letrasOcultas, c);
		} else if (CheckHist){
			Beep(Frec+100,SegsFrec+50);
			temp = "Ya jugaste esa letra, ¡prueba con otra!";
			gotoxy(x - temp.length()/2,y);
			cout<< temp;
			bandera = false;
		}
		
		if (!char_valido){
			Beep(Frec+100,SegsFrec+50);
			temp = "El caracter ingresado no es una letra";
			gotoxy(x - temp.length()/2,y);
			cout<< temp;
			bandera = false;
		}
		
		int aux = rand() % 3;;
		
		if(hayLetra and char_valido and bandera){
			Beep(Frec+300,SegsFrec+50);
			if(aux==0)temp = "¡Fantástico!";
			else if(aux==1) temp = "¡Estupendo!";
			else temp = "¡Bien!";
			gotoxy(x - temp.length()/2, y);
			cout << temp;
		} else if(!(hayLetra) and char_valido and bandera)  {
			Beep(Frec+100,SegsFrec+50);
			gotoxy(59,30);
			if(aux==0) temp = "¡Que mal!";
			else if(aux==1)  temp = "¡Casi, pero no!";
			else temp = "¡Estuviste cerca!";
			gotoxy(x - temp.length()/2, y);
			cout << temp;
			vidas--;
		}
		if(c==longPalEnJuego) victoria = true;
		Sleep(1000);
	} while(((!(letra>='a' and letra<='z'))  or (checkHistorial(letrasJugadas, letra))) and (vidas>0 and !victoria));
	y -= 4;
	if(vidas<=0){
		puntos = 0;
		Sleep(1000);
		system("CLS");
		ponerMarco(lonMarco, altMarco);
		dibujoAhorcado(vidas);
		temp = "La palabra era: \"";
		temp += palabraEnJuego;
		temp += "\"";
		gotoxy(x - temp.length()/2,y);
		cout << temp;
		y += 2;
		temp = "Lo siento, ha perdido.";
		gotoxy(x - temp.length()/2,y);
		cout<<temp;
	}
	else if (victoria){
		puntos  = puntos-(10*vidas);
		Sleep(1000);
		system("CLS");
		ponerMarco(lonMarco, altMarco);
		dibujoAhorcado(vidas);
		temp = "La palabra era: \"";
		temp += palabraEnJuego;
		temp += "\"";
		gotoxy(x - temp.length()/2,y);
		cout << temp;
		y += 2;
		temp = "GANADOR";
		gotoxy(x - temp.length()/2,y);
		cout<<temp;
	}
	
	y += 2;
	
	temp = "Su puntuación es de";
	temp += puntos;
	temp += " puntos.";
	
	gotoxy(x + temp.length()/2,y);
	
	
	volver();
}

//===================================================== CIFRAR PALABRA ==============================================================//
void cifrarPalabra (const char x[], char y[], int tl){
	
	for (int i = 0; i<tl; i++){
		y[i] = x[i];
	}
	
	for (int i = 0; i<tl; i++){
		y[i] = y[i] + 3; 
	}
	
}
	
//================================================== BUSQUEDA PAL. CIFRADA ==========================================================//
int busqSecPalCifrada (char letra, int longPalEnJuego, char palCifrada[], int& c){
	
	
	for (int i = 0; i<longPalEnJuego; i++){
			if(palCifrada[i] - 3  == letra){
				c++;
				palCifrada[i] = 'w'; //w no está en ninguna palabra de la lista
				return i;
			}
		}
		return -1;
	}

//================================================== JUEGO PALABRA CIFRADA ===========================================================//
void juegoPalCifrada (){
	SetConsoleTitleA("Palabra Cifrada");
	string palabraEnJuego;
	palabraAleatoria(palabraEnJuego, palabrasTXT);
	int longPalEnJuego = palabraEnJuego.length();
	const char* c_palSinCifrar  = palabraEnJuego.c_str();
	char palCifrada[16] = {};
	
	cifrarPalabra(c_palSinCifrar , palCifrada, longPalEnJuego);
	
	int intentos = longPalEnJuego*3 - longPalEnJuego*2; 
	
	int c = 0, acierto;
	bool victoria = false;
	bool char_valido;
	char letra;
	int x = paddingX + lonMarco/2;
	int y = paddingY;
	string temp;
	
	do{
		mostrarCursor(false);
		system("CLS");
		mostrarVectorChar(palCifrada, longPalEnJuego, altMarco/2);
		ponerMarco(lonMarco,altMarco);
		temp = "Intentos: ";
		temp += to_string(intentos);
		temp += " (+1 por acierto)";
		gotoxy(x - temp.length()/2, y + altMarco/2 + 4);
		cout << temp;
		
		temp = "Marque una tecla: ";
		gotoxy(x - temp.length()/2 - 2, y + altMarco/2 + 2);
		cout << temp << " ";
		mostrarCursor(true);
		cin >> letra;
		mostrarCursor(false);
		
		char_valido = (letra>='a' and letra<='z') or (letra>='A' and letra<='Z');
		if(char_valido){ 
			acierto = busqSecPalCifrada(letra, longPalEnJuego, palCifrada, c);
			if(acierto != -1){
				palCifrada[acierto] = toupper(letra);
				Beep(Frec+300,SegsFrec+50);
				intentos++;
				temp = "¡CORRECTO, PRESTA ATENCION AL CAMBIO!";
				gotoxy(x - temp.length()/2, altMarco/2 + 6);
				cout<< temp;
			} else{
				Beep(Frec+100,SegsFrec+50);
				intentos--;
				temp = "INCORRECTO, PUEDES RELAJARTE";
				gotoxy(x - temp.length()/2, altMarco/2 + 6);
				cout<< temp;
			}
		} else {
			Beep(Frec+100,SegsFrec+50);
			temp = "Lo ingresado no es una letra... de momento.";
			gotoxy(x - temp.length()/2, altMarco/2 + 6);
			cout<< temp;
		}
		if (c == longPalEnJuego){
			system("CLS");
			ponerMarco(lonMarco, altMarco);
			temp = "Felicidades, la palabra cifrada era: ";
			temp += palabraEnJuego;
			gotoxy(x - temp.length()/2, altMarco/2);
			cout<<temp;
			victoria = true;
			volver(false);
		}
		
	} while(intentos>0 and !victoria);
}


//====================================================== MENU DE JUEGOS ==============================================================//
void menuJuegos (){
	SetConsoleTitleA("Menu de Juegos");
	char select;
	bool cond;
	string temp;
	const int LogoPS [25][37] =
	{{0,0,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,0,0,0},
	{8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,0,0},
	{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,8,0,0},
	{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,8,0,0},
	{8,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2,2,2,2,0,2,2,2,2,3,3,3,0,0,0,0,0,0,0,8,0,0},
	{8,0,0,0,0,0,0,0,0,0,0,6,6,6,6,2,2,2,2,0,0,3,3,3,3,3,3,3,3,3,0,0,0,0,8,0,0},
	{8,0,0,0,0,0,0,0,6,6,6,6,6,6,6,2,2,2,2,3,3,3,3,0,0,0,0,3,3,3,0,0,0,0,8,0,0},
	{8,0,0,0,0,5,5,5,5,6,6,6,6,0,0,2,2,2,2,6,3,3,3,0,0,0,0,3,3,3,0,0,0,0,8,0,0},
	{8,0,0,0,0,5,5,5,5,5,0,0,0,0,5,2,2,2,2,6,6,0,0,0,0,3,3,3,3,3,3,0,0,0,8,0,0},
	{8,0,0,0,5,5,5,5,5,0,0,5,5,5,5,2,2,2,2,0,0,0,0,6,6,6,6,6,3,3,0,0,0,0,8,0,0},
	{8,0,0,0,0,5,5,5,5,5,5,5,5,5,5,2,2,2,2,0,0,0,6,6,6,6,6,6,0,0,0,0,0,0,8,0,0},
	{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,6,6,6,6,6,6,6,0,0,0,0,0,0,0,0,8,0,0},
	{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,5,6,6,6,6,6,0,0,0,0,0,0,0,0,8,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0},
	{8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,0,0},
	{0,0,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,0,0,0,0}};
	
	
	do{
		system("CLS");
		cond = true;
		ponerMarco(lonMarco, altMarco);
		int x = paddingX + lonMarco/2;
		int y = paddingY+2;
		
		for (int i = 0; i<25; i++){
			gotoxy(x - 37/2, y++);
			for(int j = 0; j<37;j++){
				if (LogoPS[i][j] == 8){
					color(hConsole, YELLOW);
					cout<<pixel;
					color(hConsole,WHITE);
				}
				else if (LogoPS[i][j] == 2){
					color(hConsole, BRED);
					cout<<pixel; 
					color(hConsole,WHITE);
				}
				else if (LogoPS[i][j] == 6){
					color(hConsole, TURQUOISE); 
					cout<<pixel; 
					color(hConsole,7);
				}
				else if (LogoPS[i][j] == 5){
					color(hConsole, BYELLOW);
					cout<<pixel; 
					color(hConsole,WHITE);
				}
				else if (LogoPS[i][j] == 3){
					color(hConsole,BBLUE);
					cout<<pixel; 
					color(hConsole,WHITE);
				}
				else {
					cout<<" ";
				}
			}
		}
		
		
		temp = "1.- Ahorcado";
		gotoxy(x-temp.size()/2, y-=5);
		cout<<temp;
		
		temp = "2.- Palabra Cifrada";
		gotoxy(x-temp.size()/2, y+=2);
		cout<<temp;
		
		temp = "3.- Numeros en otro idioma";
		gotoxy(x-temp.size()/2, y+=2);
		cout<<temp;
		
		temp = "4.- Memoria";
		gotoxy(x-temp.size()/2, y+=2);
		cout<<temp;
		
		temp = "X.- Volver al menú principal";
		gotoxy(x-temp.size()/2, y+=2);
		cout<<temp;
		
		temp = "Ingrese una opción: ";
		gotoxy(x-temp.size()/2, y+=2);
		
		color(hConsole, YELLOW);
		cout<<temp;
		cin>>select;
		color(hConsole, BWHITE);
		
		switch(select){
		case '1':
			juegoAhorcado();
			break;
		case '2':
			juegoPalCifrada();
			break;
		case '3':
			juegoNumero();
			break;
		case '4':
			juegoMemoria(palabrasTXT);
			break;
		case 'x':
		case 'X':{
			cond = false;
			break;
		}
		default:{
				temp = "¡Esa opción no es válida!";
				gotoxy (x-temp.size()/2,y+1);
				color(hConsole, BRED);
				cout<<temp;
				Beep(Frec+100,SegsFrec+50); 
				color(hConsole, WHITE);
				Sleep(1000);
				gotoxy (x-temp.size(),y+1);
				for(unsigned int i=0; i<temp.size()*2; i++) cout<<" ";
			}
		}
	} while(cond);
}
//====================================================== MENU DE ABC =================================================================//
void menuABC(){
	SetConsoleTitleA("Menu de Abecedarios");
	system("CLS");
	cout<<"\n\n\n";
	char select;
	bool cond = true;
	int x, y;
	string temp;
	const int ABC [13][35] = 
	{{0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0},
	{0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0},
	{0,0,2,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,2,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,2,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,2,0,0},
	{0,0,2,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,2,0,0},
	{2,2,2,0,0,0,1,1,1,1,1,1,1,0,1,0,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,2,2,2},
	{0,0,2,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,2,0,0},
	{0,0,2,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,2,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,2,0,0,0,1,0,0,0,0,0,1,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,2,0,0},
	{0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0},
	{0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0}};
	
	
	do{
		ponerMarco(lonMarco, altMarco);
		x = paddingX + lonMarco/2;
		y = paddingY + 2;
		
		for (int i = 0; i<13; i++){
			gotoxy(x - 17, y++);
			for (int j = 0; j<34; j++){
				if(ABC[i][j] == 1) {
					color(hConsole, BWHITE);
					cout<<pixel;
				}
				else if (ABC[i][j] == 2){
					color(hConsole, YELLOW);
					cout<<pixel;
				}
				else cout<<" ";
			}
		}
		color(hConsole,BWHITE);
		
		y+=1;
		
		temp = "1.- Español";
		gotoxy(x-temp.size()/2, y+=2);
		cout<<temp;
		
		
		temp = "2.- Ingles";
		gotoxy(x-temp.size()/2, y+=2);
		cout<<temp;
		
		
		temp = "3.- Italiano";
		gotoxy(x-temp.size()/2, y+=2);
		cout<<temp;
		
		
		temp = "4.- Portugues";
		gotoxy(x-temp.size()/2, y+=2);
		cout<<temp;
		
		
		temp = "5.- Frances";
		gotoxy(x-temp.size()/2, y+=2);
		cout<<temp;
		
		
		temp="X.- Volver al menu principal";
		gotoxy(x-temp.size()/2, y+=2);
		cout<<temp;
		
		
		temp = "Ingrese una opción: ";
		gotoxy(x-temp.size()/2, y+=2);
		
		color(hConsole,YELLOW);
		cout<<temp;
		cin>>select;
		color(hConsole,BWHITE);
		
		switch(select){
			case '1':
			case '2': 
			case '3': 
			case '4':
			case '5':
				abecedario(int(select) - int('0') - 1);
				break;
			case 'x':
			case 'X':{
				cond = false;
				break;
			}
			default:{
					temp = "¡Esa opción no es válida!";
					gotoxy (x-temp.size()/2,y+1);
					color(hConsole, BRED);
					cout<<temp;
					Beep(Frec+100,SegsFrec+50); 
					color(hConsole, WHITE);
					Sleep(1000);
					gotoxy (x-temp.size(),y+1);
					for(unsigned int i=0; i<temp.size()*2; i++) cout<<" ";
			};
			}
		
	} while(cond);
	return;
}
//====================================================== PONER MARCO =================================================================//
void ponerMarco(int largo, int alto, int x, int y) {
	
	for (int i = x; i < x + largo; i++) {
		gotoxy(i, y);
		cout << pixel;
		gotoxy(i, y + alto - 1);
		cout << pixel;
		}
		
	
	for (int i = y; i < y + alto; i++) {
		gotoxy(x, i);
		cout << pixel;
		gotoxy(x + largo - 1, i);
		cout << pixel;
		}
}
//======================================================= TRANSICION =================================================================//
void transicion (){
	mostrarCursor(false);
	system("CLS");
	bool inicio = true;
	int largo = lonMarco;
	int alto = altMarco;
	int x = paddingX;
	int y = paddingY;
	int aux;
	srand(time(NULL));
	while (inicio){
		aux = rand() % 16; 
		color(hConsole,aux);
		ponerMarco(largo,alto,x,y);
		Sleep(100);
		system("CLS");
		largo -= 4;
		alto -= 4;
		x+=2;
		y+=2;
		
		if(largo<=0 or alto <=0){
			color(hConsole,7);
			inicio = false;
		}
	}
	mostrarCursor(true);
}
//====================================================== PEDIR CONTRA ================================================================//
string pedirContra(bool ocultar){   
	const char BACKSPACE = 8;
	const char RETURN = '\r';

	string contra;
	unsigned char ch=0;

	DWORD con_mode;
	DWORD dwRead;

	HANDLE hle = GetStdHandle(STD_INPUT_HANDLE);
	
	GetConsoleMode( hle, &con_mode );
	SetConsoleMode( hle, con_mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT) );

	
	while(ReadConsoleA( hle, &ch, 1, &dwRead, NULL) and ch !=RETURN and contra.length() >= 0){
		if(ch==BACKSPACE){
			if(contra.length()!=0){
				cout <<"\b \b";
				contra.resize(contra.length()-1);
			}
		}
		else if (contra.length() < 5 and ch >= '0' and ch <= '9'){
			contra+=ch;
			cout << ch;
			Sleep(50);
			if (ocultar)cout <<"\b*";
		}
	}
	cout << endl;
	SetConsoleMode( hle, con_mode & (ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT) );
	return contra;
}	
//====================================================== JUEGO MEMORIA ===============================================================//
void juegoMemoria(string palabrasTXT[]) {
	SetConsoleTitleA("Memoria");
	system("CLS");
	srand((unsigned) time(NULL));
	
	string palabras[5];
	string palabraLarga, rPalabraLarga;
	int vocales = 0, rVocales = 0, puntaje = 0;
	char letra, rLetra;
	int y = textoY;
	int x = paddingX + lonMarco/2;
	
	for (int i = 0; i < 5; i++){
		int random = rand() % 100;
		for(int j = 0; j < i; j++){
			// TODO: Eliminar palabra de misma longitud o revisar puntaje
			if (palabras[i] ==  palabrasTXT[random])
				random = rand() % 100;
			
		}
		
		palabras[i] = palabrasTXT[random];
		
	}
	
	calcRespuestas(palabras, palabraLarga, vocales, letra);
	
	ponerMarco(lonMarco, altMarco);
	
	mostrarCursor(false);
	
	for(int i = 3; i > 0; i--){
		display(4, i, (x - 3), paddingY + altMarco/2 - 5, ' ');
		Sleep(1000);
		system("CLS");
		ponerMarco(lonMarco, altMarco);
	}
	
	centrarPalabras(palabras);
	
	Sleep(2000);
	system("CLS");
	
	
	ponerMarco(lonMarco, altMarco);
	
	string s = "Responda:";
	mostrarCursor(true);
	gotoxy(x - s.length()/2, y);
	cout << s;
	
	s = "¿Cuál fue la letra más repetida?";
	gotoxy(x - s.length()/2, y += 2);
	cout << s;
	gotoxy(x - 1, y += 2);
	cin >> rLetra;
	
	s = "¿Cuántas vocales aparecieron?";
	gotoxy(x - s.length()/2, y += 2);
	cout << s;
	gotoxy(x - 1, y += 2);
	cin >> rVocales;
	
	s = "¿Cuál fue la palabra de mayor longitud?";
	gotoxy(x - s.length()/2, y += 2);
	cout << s;
	gotoxy(x - palabraLarga.length()/2, y += 2);
	cin >> rPalabraLarga;
	
	system("CLS");
	
	y = textoY;
	ponerMarco(lonMarco, altMarco);
	
	s = "RESULTADO";
	gotoxy(x - s.length()/2, y);
	cout << s;
	
	if (rLetra == letra) puntaje += 10;
	
	s = rLetra;
	s += " | ";
	s += letra;
	gotoxy(x - s.length()/2, y += 2);
	cout << s;
	
	if (2*vocales > rVocales){
		if (vocales >= rVocales)
			puntaje += rVocales*10/vocales; // regla de 3
		else
			puntaje += (2*vocales - rVocales)*10/vocales; // regla de 3 por sobre mas
	}
	
	s = to_string(rVocales) + " | " + to_string(vocales);
	gotoxy(x - s.length()/2, y += 2);
	cout << s;
	
	
	if (palabraLarga.compare(rPalabraLarga) == 0 ) puntaje += 10;
	
	s = rPalabraLarga + " | " + palabraLarga;
	gotoxy(x - s.length()/2, y += 2);
	cout << s;
	
	s = "PUNTAJE: " + to_string(puntaje);
	gotoxy(x - s.length()/2, y += 2);
	cout << s;	
	
	volver();
	
}
//========================================================= DISPLAY ==================================================================//
void display(const int &fa, const int& n, int x, int y, char wh, char bl){
	
	int height = 3 + 2 * fa;
	int width = 2 + fa;
	
	char** grid = new char*[height];
	
	for(int i = 0; i < height; i++)
		grid[i] = new char[width];
	
	
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			grid[i][j] = wh;
		}
	}
	
	// a
	if (n != 1 and n != 4) {
		for(int i = 0; i < width; i++){
			grid[0][i] = bl;
		}
	}
	// b
	if (n != 5 and n != 6) {
		for(int i = 0; i < fa + 2; i++){
			grid[i][width - 1] = bl;
		}
	}
	// c
	if (n != 2) {
		for(int i = height - 1; i > fa + 1; i--){
			grid[i][width - 1] = bl;
		}
	}
	// d
	if (n != 1 and n!= 4 and n != 7 and n != 9) {
		for(int i = 0; i < width; i++){
			grid[height - 1][i] = bl;
		}
	}
	// e
	if (n == 0 or n == 2 or n == 6 or n == 8) {
		for(int i = height - 1; i > fa + 1; i--){
			grid[i][0] = bl;
		}
	}
	// f
	if (n != 1 and n != 2 and n != 3 and n != 7) {
		for(int i = 0; i < fa + 2; i++){
			grid[i][0] = bl;
		}
	}
	// g
	if (n != 0 and n != 1 and n != 7) {
		for(int i = 0; i < width; i++){
			grid[fa + 1][i] = bl;
		}
	}
	
	for(int i = 0; i < height; i++){
		gotoxy(x, y + i);
		for(int j = 0; j < width; j++){
			cout << grid[i][j];
		}
	}
	
	for(int i = 0; i < height; i++)
		delete grid[i];
	
	delete grid;
}
//====================================================== CALC RESPUESTAS =============================================================//
void calcRespuestas(string ps[], string & pl, int & v, char & l){
	
	int contador[25] = { 0 };
	int max = 0;
	
	char resultado;
	
	for(int i = 0; i < 5; i++){
		for (unsigned int j = 0; j < ps[i].length(); j++){
			//vocales
			switch(ps[i][j]){
			case 'a':
			case 'e':
			case 'i':
			case 'o':
			case 'u':
				v++;
				break;
			}
			
			// letra mas repetida
			int iLetra = (int) ps[i][j] - 97; // 97 empieza la 'a' en tabla ASCII
			contador[iLetra]++;
			if (max < contador[iLetra]) {
				max = contador[iLetra];
				resultado = ps[i][j];
			}
		}
		// palabra larga
		if (ps[i].length() > pl.length()) pl = ps[i];
	}
	
	l = resultado;
}	
//===================================================== CENTRAR PALABRAS =============================================================//
void centrarPalabras(string ps[]){
	srand((unsigned) time(NULL));
	
	unsigned short int coords[5][2];
	
	int x = 0;
	int y = 0;
	
	for (int i = 0; i < 5; i++){
		x = paddingX + 3 + ps[i].length()/2 + rand() % (lonMarco - ps[i].length()/2 - 1);
		y = paddingY + 1 + rand() % (35 - 1);
		coords[i][0] = x;
		coords[i][1] = y;
	}
	
	for (int i = 0; i < 5; i++){
		gotoxy(coords[i][0] - (ps[i].length() / 2), coords[i][1]);
		cout << ps[i];
	}
}	
//======================================================= JUEGO NUMERO ===============================================================//
void juegoNumero(){
	SetConsoleTitleA("Numeros en otro idioma");
	system("CLS");
	
	int aumento, numero, idioma;
	int x = paddingX + lonMarco/2;
	int y = textoY - 2;
	string numerosIdiomas[10][5] = {
		{"cero",	"zero",		"zero",		"zero",		"zero"},
		{"uno",		"one",		"uno",		"um",		"un"},
		{"dos",		"two",		"due",		"dois",		"deux"},
		{"tres",	"three",	"tre",		"tres",		"trois"},
		{"cuatro",	"four",		"quattro",	"quatro",	"quatre"},
		{"cinco",	"five",		"cinque",	"cinco",	"cinq"},
		{"seis",	"six",		"sei",		"seis",		"six"},
		{"siete",	"seven",	"sette",	"sete",		"sept"},
		{"ocho",	"eight",	"otto",		"oito",		"huit"},
		{"nueve",	"nine",		"nove",		"nove",		"neuf"}
	};
	string idiomas[] = {"Español", "Inglés", "Italiano", "Portugués", "Francés"};
	
	ponerMarco(lonMarco, altMarco);
	
	gotoxy(x - 3, y);
	cout << "IDIOMA";
	y += 3;
	
	mostrarCursor(false);
	imprimirAviso("«« Utilizá las flechas izquierda y derecha »»", y - 1);
	idioma = pedirIdioma(idiomas, y);
	mostrarCursor(true);
	y += 3;
	
	gotoxy(x - 3, y);
	cout << "NUMERO";
	y += 3;
	
	imprimirAviso("«« Digita un número del 0 al 9 »»", y - 1);
	gotoxy(x - 1, y);
	numero = pedirNumero(1);
	y += 3;
	
	gotoxy(x - 8, y);
	cout << "FACTOR DE AUMENTO";
	y += 3;
	
	mostrarCursor(false);
	imprimirAviso("«« Utilizá las flechas izquierda y derecha »»", y - 1);
	aumento = pedirFactor(y);
	
	Sleep(1000);
	mostrarCursor(true);
	
	system("CLS");
	
	y = textoY;
	
	ponerMarco(lonMarco, altMarco);
	gotoxy(x - 18/2 - idiomas[idioma].length()/2, y);
	cout << "Forma escrita en " << idiomas[idioma] <<":";
	y += 2;
	gotoxy(x - numerosIdiomas[numero][idioma].length()/2, y);
	for(unsigned int i = 0; i < numerosIdiomas[numero][idioma].length(); i++){
		cout << char(toupper(numerosIdiomas[numero][idioma][i]));
	}
	y+=3;
	gotoxy(x - 4, y);
	
	cout << "Gráfico:" << endl;
	y+=3;
	
	display(aumento, numero, (x + 2 - (aumento/2 + 3)), y);
	
	volver();
}
//======================================================= PEDIR NUMERO ===============================================================//
int pedirNumero(unsigned int maxDigitos){
	const char BACKSPACE = 8;
	const char RETURN = '\r';
	
	string numero;
	unsigned char ch=0;
	
	DWORD con_mode;
	DWORD dwRead;
	
	HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
	
	GetConsoleMode( hConsole, &con_mode );
	SetConsoleMode( hConsole, con_mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT) );
	
	while(ReadConsoleA( hConsole, &ch, 1, &dwRead, NULL) && ch != RETURN){
		if(ch==BACKSPACE){
			if(numero.length()!=0){
				cout <<"\b \b";  
				numero.resize(numero.length()-1);
			}
		}
		else if (numero.length() < maxDigitos and ch >= '0' and ch <= '9'){
			numero+=ch;
			cout << ch;
		}
	}
	
	SetConsoleMode( hConsole, con_mode & (ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT) );
	
	return stoi(numero);
}	
//======================================================== ABECEDARIO ================================================================//
void abecedario(int idioma){
	system("CLS");
	string abc;
	abc.clear();
	int y = textoY, x = paddingX + lonMarco/2;
	
	ponerMarco(lonMarco, altMarco);
	
	string idiomas[] = { "Español", "Inglés", "Italiano", "Portugués", "Francés"};
	string temp = "Idioma ";
	
	temp += idiomas[idioma] + ":";
	
	gotoxy(x - temp.length()/2, y);
	cout << temp;
	y +=2;
	
	gotoxy(x - 10, y);
	for (unsigned int i = 0; i < 20; i++){
		cout<<"=";
	}
	
	y += 2;
	
	for (int i = 0; i <= int('z' - 'a'); i++){
		abc += char(i + 'a');
	}
	
	if (idioma == 0){
		abc.insert(int('o' - 'a'), "ñ");
	}
	
	for (unsigned int i = 0; i < abc.size(); i++){
		if (i % 10 == 0) x = paddingX + lonMarco/2 - 10;
		if (i % 10 == 0 and i > 0) y++;
		gotoxy(x, y);
		x += 2;
		cout << abc[i];
	}
	
	y += 2;
	
	if (idioma == 0){
		abc.replace(int('o' - 'a'), 1, "Ñ");
	}
	
	for (unsigned int i = 0; i < abc.size(); i++){
		if (i % 10 == 0) x = paddingX + lonMarco/2 - 10;
		if (i % 10 == 0 and i > 0) y++;
		gotoxy(x, y);
		x += 2;
		cout << char(toupper(abc[i]));
	}
	
	string acentuadas[] = {
		{"áéíóúü"},
		{},
		{"àèéìíòóùú"}, 
		{"áàâçéêíóôú"},
		{"àâçéèêëîïôùûü"}
	};
	
	string adicionales;

	adicionales = char(198);
	acentuadas[3].insert(4, adicionales);
	adicionales = char(228);
	acentuadas[3].insert(9, adicionales);
	adicionales = char(145);
	acentuadas[4].insert(3, adicionales);
	
	y += 2;

	for (unsigned int i = 0; i < acentuadas[idioma].size(); i++){
		if (i % 10 == 0) x = paddingX + lonMarco/2 - 10;
		if (i % 10 == 0 and i > 0) y++;
		gotoxy(x, y);
		x += 2;
		cout << acentuadas[idioma][i];
	}
	
	volver();
}
//====================================================== MOSTRAR CURSOR ==============================================================//
void mostrarCursor(bool mostrar){
	CONSOLE_CURSOR_INFO     cursorInfo;
	
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = mostrar;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}
//====================================================== IMPRIMIR AVISO ==============================================================//
void imprimirAviso(string frase, USHORT y){
	
	gotoxy(paddingX + lonMarco/2 - frase.length() / 2, y + 1);
	for(unsigned int i = 0; i < frase.length(); i++){
		cout << frase[i];
		Sleep(25);
	}
	Sleep(1000);
	for(unsigned int i = frase.length(); i > 0; i--){
		cout << "\b \b";
		Sleep(25);
	}
}
//======================================================= PEDIR FACTOR ===============================================================//
int pedirFactor(int y){
	
	bool cond = true;
	int centrado = (lonMarco)/5, counter = 1;
	int colores[] = {BRED, BWHITE, BWHITE, BWHITE};
	char relleno[] = {pixel, noPixel, noPixel, noPixel};
	char key;
	
	while(cond){
		
		for(int i = 0; i < 4; i++){
			color(hConsole, colores[i]);
			display(i + 1, 9, paddingX + centrado * (i+1), paddingY + altMarco / 5 * 4 - (3 + i*2), relleno[i], relleno[i]);
			color(hConsole, BWHITE);
		}
		
		if (key == '\r'){
			cond = false;
			continue;
		}
		
		key = getch();
		
		if (key == LEFT && (counter >= 2 and counter <= 5)){
			counter--;
		}
		if (key == RIGHT && (counter >= 1 and counter < 5)){
			counter++;
		}
		
		for(int i = 0; i < 4; i++){
			if (counter == i + 1) {
				colores[i] = key == '\r' ? BGREEN : BRED;
				relleno[i] = pixel;
			} else {
				colores[i] = WHITE;
				relleno[i] = noPixel;
			}
		}
	}
	return counter;
}
//======================================================= PEDIR IDIOMA ===============================================================//
int pedirIdioma(string idi[], int y){
	
	bool cond = true;
	int offcolores = (lonMarco)/6, counter = 1;
	int colores[] = {BRED, BWHITE, BWHITE, BWHITE, BWHITE};
	char key;
	int x = paddingX;
	while(cond){
		
		for (int i = 0; i < 5; i++){
			gotoxy(x + offcolores * (i + 1) - idi[i].length() / 2, y);
			color(hConsole, colores[i]);
			cout << idi[i];
			color(hConsole, BWHITE);
		}
		
		if (key == '\r'){
			cond = false;
			continue;
		}
		
		key = getch();
		
		if (key == LEFT && (counter >= 2 and counter <= 5)){
			counter--;
		}
		if (key == RIGHT && (counter >= 1 and counter < 5)){
			counter++;
		}
		
		for(int i = 0; i < 5; i++){
			if (counter == i + 1)
				colores[i] = (key == '\r') ? BGREEN : BRED;
			else
				colores[i] = BWHITE;
		}
		
	}
	return counter - 1;
}
//========================================================== VOLVER ==================================================================//
void volver(bool continuar){
	
	int x;
	string s;
		
	if(!continuar){
		x = paddingX + lonMarco/2;
		s = "Pulse \033[1mCUALQUIER TECLA\033[0m para regresar.";
		gotoxy(x - (s.length() - 14) / 2, paddingY + altMarco - 3);
		cout << s;
		getch();
		system("CLS");
	}
	
	else{
		x = paddingX + lonMarco/2;
		gotoxy(x - (s.length() + 38) / 2, paddingY + altMarco - 3);
		s = "Pulse \033[1mCUALQUIER TECLA\033[0m para continuar.";
		cout << s;
		getch();
		system("CLS");
	}
}
//======================================================== CONFIGURAR ================================================================//
void configurar(){
	
	CONSOLE_SCREEN_BUFFER_INFO infoPantalla;
	
	GetConsoleScreenBufferInfo(hConsole, &infoPantalla);
	
	COORD tamano = infoPantalla.dwMaximumWindowSize;
	
	paddingX = (tamano.X - lonMarco) / 2;
	paddingY = (tamano.Y - altMarco) / 2;
	textoY = paddingY + 4;
}
//=================================================== MOSTAR LETRAS JUGADAS ==========================================================//
void mostrarLetrasJugadas (char letrasJugadas [],int tl){
	for (int i = 0; i<tl;  i++){
		cout<<letrasJugadas[i]<<" ";
	}
}

//================================== FUNCIONES DE ARRIBA REALIZADAS DURANTE LA PRIMERA PARTE =========================================// 
//================================ A CONTINUACIÓN FUNCIONES REALIZADAS DURANTE LA SEGUNDA PARTE ======================================//
//=================== NOTA: EL MENU PRINCIPAL FUE ADAPTADO PARA CONTENER LA NUEVA OPCIÓN DE PROCESADOR DE TEXTO ======================//
	
//=========================================================== MENU TEXTO =============================================================//
void menuTexto (){

	SetConsoleTitleA("Procesador de Texto");
	system("CLS");
	color(hConsole,BWHITE);
	const int M[28][67] = 
	{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,5,5,5,5,0,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,0},
	{5,0,0,0,0,5,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,1,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1},
	{5,0,0,0,0,5,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,1},
	{5,0,0,0,0,5,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,1},
	{5,5,5,5,5,0,0,1,0,0,0,1,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,1,1,1,0,0,0,1,0,0,0,0,0,1,1,1,1,1,1,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,1,0},
	{5,0,0,0,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,1,1,1,1,0,0},
	{5,0,0,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,1,0},
	{5,0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,1,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1},
	{5,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,1,1,1,1,0,1,1,1,1,0,0,1,0,0,0,0,1,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,1,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,5,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,5,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,5,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,5,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,5,0,0,1,1,1,0,1,0,0,0,1,0,1,1,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,1,1,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,1,1,1,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
	
	
	bool cond;
	char select;
	
	
	do{
		system("CLS");
		int x = paddingX + lonMarco/2, y = paddingY+1;
		for (int i = 0; i<24; i++){
			gotoxy(x - 67/2, y++);
			for (int j = 0; j<67; j++){
				if(M[i][j] == 1) {
					color(hConsole, BWHITE);
					cout<<pixel;
				}
				else if (M[i][j] == 5){
					color(hConsole, YELLOW);
					cout<<pixel;
				}
				else cout<<" ";
			}
			cout<<endl;
		}
		ponerMarco(lonMarco, altMarco);
		string temp = "1.- Estadísticas a nivel de caracteres";
		y += 1;
		gotoxy(x - temp.size()/2, y);
		cout<<temp;
		y += 2;
		temp = "2.- Estadísticas a nivel palabras";
		gotoxy(x - temp.size()/2, y);
		cout<<temp;
		y += 2;
		temp = "X.- Volver al menu principal";
		gotoxy(x - temp.size()/2, y);
		cout<<temp;
		y += 2;		temp = "Ingrese una opción: ";
		gotoxy(x - temp.size()/2, y);
		
		color (hConsole, YELLOW);
		cout<<temp;
		gotoxy(x - temp.size()/2 + temp.size(), y);
		cout<<"                 ";
		gotoxy(x - temp.size()/2 + temp.size(), y);
		cin>>select;
		color(hConsole, BWHITE);
		
		cond = (select != '1' or select != '2' or select != 'x' or select != 'X');
		switch(select){
		case '1':{
			statsChar(sherlock);
			break;
		};
		case '2':{
			statsPals ();
			break;
		};
		case 'x':
		case 'X': {
			cond = false;
			break;
			}
		default: {
			temp = "¡Esa opción no es válida!";
			gotoxy (x-temp.size()/2,y+1);
			color(hConsole, BRED);
			cout<<temp;
			Beep(Frec+100,SegsFrec+50); 
			color(hConsole, WHITE);
			Sleep(1000);
			gotoxy (x-temp.size(),y+1);
			for(unsigned int i=0; i<temp.size()*2; i++) cout<<" ";
			temp = "Ingrese una opción: ";
		}
		}
	}while(cond);
}

//========================================================= MENU STATSCHAR ===========================================================//
void statsChar (Libro& libro){
	SetConsoleTitleA("Estadísticas de Caracteres");
	system("CLS");
	mostrarFrecuenciasCar(libro,paddingX+lonMarco/2,paddingY+2);
	crearFrecuenciaTXT (libro);
	ponerMarco(lonMarco,altMarco);
	volver();
	return;
}
//========================================================= MENU STATSPALS ===========================================================//
void statsPals (){
	bool cond;
	char select;
	SetConsoleTitleA("Estadísticas de Palabras");
	color(hConsole,BWHITE);
	do{
		system("CLS");
		int x = paddingX + lonMarco/2, y = altMarco/2 - 4;
		ponerMarco(lonMarco, altMarco);
		string temp = "1.- Visualizar matriz Palabras";
		y += 1;
		gotoxy(x - temp.size()/2, y);
		cout<<temp;
		y += 2;
		temp = "2.- Consultas";
		gotoxy(x - temp.size()/2, y);
		cout<<temp;
		y += 2;
		temp = "X.- Volver";
		gotoxy(x - temp.size()/2, y);
		cout<<temp;
		y += 2;		temp = "Ingrese una opción: ";
		gotoxy(x - temp.size()/2, y);
		color (hConsole, YELLOW);
		cout<<temp;
		
		gotoxy(x - temp.size()/2 + temp.size(), y);
		cout<<"                 ";
		gotoxy(x - temp.size()/2 + temp.size(), y);
		cin>>select;
		color (hConsole, BWHITE);
		cond = (select != '1' or select != '2' or select != 'x' or select != 'X');
		switch(select){
		case '1':{
			MatrizPalabras(longMaxPal, cantLetras);
			break;
		};
		case '2':{
			Consultas();
			break;
		};
		case 'x':
		case 'X': {
			cond = false;
			break;
		}
		default: {
			temp = "¡Esa opción no es válida!";
			gotoxy (x-temp.size()/2,y+1);
			color(hConsole, BRED);
			cout<<temp;
			Beep(Frec+100,SegsFrec+50); 
			color(hConsole, WHITE);
			Sleep(1000);
			gotoxy (x-temp.size(),y+1);
			for(unsigned int i=0; i<temp.size()*2; i++) cout<<" ";
			temp = "Ingrese una opción: ";
		}
		}
	}while(cond);
}
//========================================================= MATRIZ PALABRAS ==========================================================//	
void MatrizPalabras(int longMaxPal, int cantLetras){
	
	system("CLS");
	string temp;
	char caracterInicial, select;
	unsigned int longitudBuscada, cols = 1;
	int pals = 0, x, y, auxY;
	
	bool cond = true;
	
	//DECLARACION E INICIALIZACIÓN DE MATRIZ DINÁMICA CON FILAS = longMaxPal Y COLUMNAS = cantLetras
	int** ptr = new int*[longMaxPal]; 
	for (int i = 0; i < longMaxPal; ++i) {
		ptr[i] = new int[cantLetras];
		fill(ptr[i], ptr[i] + cantLetras, 0); 
	}
	
	do{
		system("CLS");
		ponerMarco(lonMarco,altMarco);
		cols=1;
		
		x = paddingX + lonMarco/2, y = paddingY+2;
		temp = "  ";
		gotoxy(x - abc.size()/2-temp.size()*cantLetras/2, y);
		
		color(hConsole, BYELLOW);
		
		for(unsigned int i = 0; i<abc.size(); i++){
			cout<<abc[i]<<temp;
		}
		
		x = paddingX + lonMarco/2, y = paddingY+4;
		auxY = y;
		for(int i = 0; i<longMaxPal; i++){
			gotoxy(x-cantLetras/2-temp.size()*cantLetras/2 - 6, auxY++);
			cout<<cols++;
		}
		
		color(hConsole, BWHITE);
		
		temp = "  ";
		for (int i = 0; i<longMaxPal; i++){
			gotoxy(x-cantLetras/2-temp.size()*cantLetras/2 ,y++);
			for (int j = 0; j<cantLetras; j++){
				cout<<ptr[i][j]<<temp;
			}
		}
		
		temp = "1.- Operar en matriz";
		gotoxy (x-temp.size()/2, ++y);
		cout<<temp;
		
		temp = "X.- Volver";
		gotoxy (x-temp.size()/2, y+=2);
		cout<<temp;
		
		temp = "Marque una opción: ";
		gotoxy (x-temp.size()/2, y+=2);
		color (hConsole, YELLOW);
		cout<<temp;
		cin>>select;
		color (hConsole, BWHITE);
		bool correcto = false;
		switch(select){
		case '1':{
			do {
				
				temp = "Ingrese la longitud de las palabras a contabilizar: ";
				gotoxy(x - temp.size() / 2, y + 2);
				cout << "                                                                            ";
				gotoxy(x - temp.size() / 2, y + 2);
				cout << temp;
				
				
				while (!(cin >> longitudBuscada)) {
					cin.clear(); 
					cin.ignore(20,'\n'); 
					
					color(hConsole, BRED);
					temp = "Entrada no válida. Por favor, ingrese un número.";
					gotoxy(x - temp.size() / 2, y + 5);
					cout << temp;
					Beep(Frec + 100, SegsFrec + 50);
					color(hConsole, WHITE);
					Sleep(1000);
					
					
					
					
					temp = "Ingrese la longitud de las palabras a contabilizar: ";
					gotoxy(x - temp.size() / 2, y + 2);
					cout << "                                                                            ";
					gotoxy(x - temp.size() / 2, y + 2);
					cout << temp;
				}
				
				if (longitudBuscada >= 1 and longitudBuscada <= (unsigned)longMaxPal) {
					correcto = true;
				} else {
					color(hConsole, BRED);
					temp = "La cantidad de letras de las palabras a contabilizar debe estar dentro del rango [1-" + to_string(longMaxPal) + "]";
					gotoxy(x - temp.size() / 2, y + 5);
					cout << temp;
					Beep(Frec + 100, SegsFrec + 50);
					color(hConsole, WHITE);
					Sleep(1000);
				}
				
			} while (!correcto);
			
			do{
				temp = "                                                                                           ";
				gotoxy (x-temp.size()/2,y+5);
				cout<<temp;
				
				cout<<endl;
				temp = "Ingrese el caracter inicial con el que comienzan las palabras a contabilizar: ";
				gotoxy(x-temp.size()/2, y+4);
				cout<<temp;
				cin>>caracterInicial;
				
				if(isalpha(caracterInicial)){
					correcto=true;
				} else {
					correcto=false;
					color(hConsole, BRED);
					temp = "Ingrese un caracter alfabetico valido.";
					Beep(Frec+100,SegsFrec+50);
					gotoxy (x-temp.size()/2,y+5);
					cout<<temp;
					Sleep(2000);
					color(hConsole, WHITE);
				}
				
			} while(!correcto);
			
			
			
			caracterInicial = tolower(caracterInicial);
			contarPals(sherlock,longitudBuscada,caracterInicial, pals);
			ptr[longitudBuscada-1][(int)(caracterInicial - 'a')] = pals;
			
			
			break;
		}
		case 'x':
		case 'X':{
			cond = false;
			break;
		}
		default: {
				temp = "¡Esa opción no es válida!";
				gotoxy (x-temp.size()/2,y+1);
				color(hConsole, BRED);
				cout<<temp;
				Beep(Frec+100,SegsFrec+50); 
				color(hConsole, WHITE);
				Sleep(1000);
				gotoxy (x-temp.size(),y+1);
				for(unsigned int i=0; i<temp.size()*2; i++) cout<<" ";
			}
		}
		
		
	} while(cond);

	//GESTION DE MEMORIA DE MATRIZ DINÁMICA
	for (int i = 0; i < longMaxPal; ++i) {
		delete[] ptr[i];
	}
	
	delete[] ptr;
	
	return;
}

//============================================================= CONSULTAS ============================================================//
void Consultas(){
	system("CLS");
	string temp;
	char select, letra;
	int x, y, auxY;
	
	bool cond = true;
	
	
	do{
		system("CLS");
		ponerMarco(lonMarco,altMarco);
		
		x = paddingX + lonMarco/2, y = (altMarco/2)-4;
		
		temp = "1.- Longitud palabra promedio";
		gotoxy (x-temp.size()/2, ++y);
		cout<<temp;
		
		temp = "2.- Ocurrencia palabras";
		gotoxy (x-temp.size()/2, y+=2);
		cout<<temp;
		
		temp = "3.- Vocal vs Consonante";
		gotoxy (x-temp.size()/2, y+=2);
		cout<<temp;
		
		temp = "X.- Volver";
		gotoxy (x-temp.size()/2, y+=2);
		cout<<temp;
		color (hConsole, YELLOW);
		temp = "Marque una opción: ";
		gotoxy (x-temp.size()/2, y+=2);
		cout<<temp;
		cin>>select;
		color (hConsole, BWHITE);
		switch(select){
		case '1':{
			
			temp = "La longitud de palabra promedio es de " + to_string(longPalProm) + " letras.";
			gotoxy (x-temp.size()/2, y+=2);
			cout<<temp;
			volver();
			break;
		};
		case '2':{
			do{
				auxY = y;
				temp = "Ingrese una letra: ";
				gotoxy(x-temp.size()/2,auxY+=2);
				cout<<temp;
				cin>>letra;
				mostrarFrecuenciaPals2 (sherlock, letra, x+temp.size(), auxY+=2);
				volver();
			} while(!isalpha(letra));
			break;
		};
		case '3':{
			
			temp = "Porcentaje de palabras que comienzan con vocal: ";
			gotoxy (x-temp.size()/2, y+=2);
			cout<<temp<<fixed<<setprecision(2)<<porcentajeVocales<< "%.";
			temp = "Porcentaje de palabras que comienzan con consonante: ";
			gotoxy (x-temp.size()/2, y+=2);
			cout<<temp<<fixed<<setprecision(2)<<porcentajeConsonantes<< "%.";
			volver();
			break;
		};
		case 'x':
		case 'X': {
			cond = false;
			break;
		};
		default:{
			temp = "¡Esa opción no es válida!";
			gotoxy (x-temp.size()/2,y+1);
			color(hConsole, BRED);
			cout<<temp;
			Beep(Frec+100,SegsFrec+50); 
			color(hConsole, WHITE);
			Sleep(1000);
			gotoxy (x-temp.size(),y+1);
			for(unsigned int i=0; i<temp.size()*2; i++) cout<<" ";
		};
		}
	}while(cond);
	return;
}

//============================================================= existeUser ===========================================================//	
bool existeUser (const char user[], int& indiceUser){
	
	for (int i = 0; i<100; i++){
		if(strcmp(user,usuarios[i].legajo)==0){
			indiceUser = i;
			return true;
		}
	}
	
	return false;
}
//============================================================ correctPass ===========================================================//
bool correctPass (const char pass[], int indiceUser){
	
	for (int i = 0; i<100; i++){
		if(strcmp(pass,usuarios[indiceUser].pass)==0){
			return true;
		}
	}
	
	return false;
}
//========================================================== obtenerUsuarios =========================================================//
void obtenerUsuarios (Usuario usuarios[]){
	ifstream infoUsuarios;
	infoUsuarios.open("usuarios.bin", ios::binary | ios::in);
	
	if(infoUsuarios.fail()){
		cout << "Lo sentimos, ha ocurrido un error al intentar abrir el archivo usuarios.bin.";
		exit(999);
	}
	else{
		int i = 0;
		while((!infoUsuarios.eof()) and i <100){
			infoUsuarios.read((char*)(&usuarioActual), sizeof(usuarioActual));
			usuarios[i] = usuarioActual;
			i++;
		}
		infoUsuarios.close();
	}
}

//======================================================== modificarUltAcceso =======================================================//
void modificarUltAcceso (int indiceUser){
	fstream infoUsuarios;
	infoUsuarios.open("usuarios.bin", ios::binary | ios::in | ios::out);
	if(infoUsuarios.fail()){
		system("CLS");
		cout<<"Ha ocurrido un error al intentar abrir el archivo usuarios.bin."<<endl;
		exit(655);
	}
	else{
		auto ahora = chrono::system_clock::now();
		
		// Convertir la marca de tiempo a std::time_t
		time_t tiempo_actual = chrono::system_clock::to_time_t(ahora);
		
		// Obtener la información del día, mes y año actual
		tm* fecha = std::localtime(&tiempo_actual);
		
		usuarios[indiceUser].F_ultAcceso.dia = fecha->tm_mday;
		usuarios[indiceUser].F_ultAcceso.mes = (fecha->tm_mon + 1);
		usuarios[indiceUser].F_ultAcceso.anio = (fecha->tm_year + 1900);
		
		infoUsuarios.seekp(indiceUser * sizeof(Usuario) + offsetof(Usuario, F_ultAcceso));
		infoUsuarios.write((char*)(&usuarios[indiceUser].F_ultAcceso), sizeof(Fecha));
	}
	infoUsuarios.close();
}
