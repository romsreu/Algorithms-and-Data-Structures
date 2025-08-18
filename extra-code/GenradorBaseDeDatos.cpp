#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;

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
};

// Función para calcular la contraseña según la condición dada 
string calcularContrasena(const char* legajo) {
	int longitud = strlen(legajo);
	string contrasena = "";
	
	// Calcula el legajo dado vuelta
	for (int i = longitud - 1; i > 0; i--) {
		contrasena += legajo[i];
	}
	
	// Suma del primer y último dígito original módulo 10
	int sumaDigitos = (legajo[0] - '0' + legajo[longitud - 1] - '0') % 10;
	
	// Concatena la suma al legajo dado vuelta
	contrasena += to_string(sumaDigitos);
	return contrasena;
}

string nombres[100] = {"Roman", "Olivia", "Noah", "Daniel", "Oliver", "Diana", "William", "Sophia", "Elijah", "Isabella",
	"James", "Charlotte", "Benjamin", "Amelia", "Lucas", "Mia", "Henry", "Harper", "Alexander", "Evelyn",
	"Michael", "Abigail", "Daniel", "Emily", "Matthew", "Elizabeth", "Jackson", "Avery", "David", "Sofia",
	"Joseph", "Ella", "Samuel", "Scarlett", "Sebastian", "Grace", "Carter", "Chloe", "Owen", "Victoria",
	"Wyatt", "Riley", "John", "Aria", "Gabriel", "Lily", "Anthony", "Zoey", "Dylan", "Hannah","Ethan", "Madison", "Jayden", "Layla", "Nathan", "Aubrey", "Levi", "Brooklyn", "Isaac", "Zoe",
	"Christopher", "Nora", "Lincoln", "Addison", "Joshua", "Hailey", "Andrew", "Eleanor", "Julian", "Skylar",
	"Grayson", "Paisley", "Levi", "Hazel", "Isaiah", "Audrey", "Charles", "Claire", "Hunter", "Savannah",
	"Aaron", "Bella", "Christian", "Stella", "Adrian", "Maya", "Eli", "Lucy", "Mateo", "Nova",
	"Colton", "Ellie", "Thomas", "Kinsley", "Jordan", "Natalie", "Dominic", "Katherine", "Evan", "Allison"};

string apellidos [100] = {"Scarabino", "Johnson", "Williams", "Ambort", "Jones", "Margarita", "Miller", "Davis", "Rodriguez", "Martinez",
	"Hernandez", "Lopez", "Gonzalez", "Wilson", "Anderson", "Thomas", "Taylor", "Moore", "Jackson", "Martin",
	"Lee", "Perez", "Thompson", "White", "Harris", "Sanchez", "Clark", "Ramirez", "Lewis", "Robinson",
	"Walker", "Young", "Allen", "King", "Wright", "Scott", "Torres", "Nguyen", "Hill", "Flores",
	"Green", "Adams", "Nelson", "Baker", "Hall", "Rivera", "Campbell", "Mitchell", "Carter", "Collins", "Cooper", "Howard", "Ward", "Evans", "Reed", "Cook", "Bailey", "Bell", "Murphy", "Parker",
	"Collins", "Bennett", "Wood", "Richardson", "Gray", "James", "Watson", "Sanders", "Price", "Barnes",
	"Mitchell", "Simmons", "Ortiz", "Jenkins", "Bishop", "Harvey", "Russell", "Perry", "Crawford", "Mendoza",
	"Franklin", "Garza", "Newman", "Grant", "Carter", "Carpenter", "Hansen", "Fernandez", "Spencer", "Gilbert",
	"Gomez", "Stevens", "Jimenez", "Lawrence", "Caldwell", "Lambert", "Snyder", "Williams", "Johnston", "Ray"};

string rol [2] = {"Estudiante", "Profesor"};

int main() {
	srand(time(NULL));
	int numero_aleatorio;
	
	ofstream fPers;
	fPers.open("datosPersonas.bin", ios::binary | ios::out); 
	if (!fPers) {
		cout << "Error al abrir el fichero" << endl;
	} else {
		Usuario p;
		
		for (int i = 0; i < 100; ++i) {
			
			strcpy(p.nombre, nombres[i].c_str());
			strcpy(p.apellido, apellidos[i].c_str());
			p.sexo = (i % 2 == 0) ? 'M' : 'F';
			strcpy(p.legajo, to_string(12345 + i).c_str()); 
			strcpy(p.pass, calcularContrasena(p.legajo).c_str());
			numero_aleatorio = rand() % 2;
			cout<<numero_aleatorio;
			strcpy(p.rol, rol [numero_aleatorio].c_str());
			p.F_ultAcceso.anio = 2023;
			p.F_ultAcceso.mes = 10;
			p.F_ultAcceso.dia = 22;
			p.H_ultAcceso.hora = 21;
			p.H_ultAcceso.mins = 16;
			p.H_ultAcceso.segs = 13;
			
			fPers.write((char *)(&p), sizeof(p));
		}
		
		fPers.close();
	}
	return 0;
}
