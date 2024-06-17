#include <iostream>
#include "betris.hpp"
#include <chrono>
#include <thread>

using namespace std;
//numero de parametros antes de la primera pieza
const int PARAMETROS = 5;

//Pre: 0 <= a <= b < PIEZASDEF
//Post: Devuelve un pseudoaleatorio del intervalo [a,b]
int randInt(const int a, const int b){

    return a + rand() % (b - a + 1);
}



// Pre: true
// Post: vEntrada se ha rellenado con números aletarios entre 0 y PIEZASDEF -1
void randomPiezas(int vEntrada[]){

    time_t semilla = time(nullptr); // tiempo actual como semilla
    srand(semilla);
    unsigned i=0, n=-(vEntrada[0]);

    for(i; i < n; i++){

        vEntrada[i] = randInt(0, PIEZASDEF-1);
    }
    
    vEntrada[i] = -1;
}


/*En "betris" se dispone de un tablero rectangular cuyas dimensiones las determinan los
parámetros de entrada dados al juego. En dicho tablero se colocan las piezas
según su orden de llegada. Cada familia de piezas válidas tiene una forma, un color y se
identifica por un número. 
Ha devuelto, si lo ha encontrado, el primer tablero que cumple objetivo con las piezas 
introducidas (si el quinto parámetro p es > 0, sino con p piezas random), cuales, cuantas y 
en que columna han sido colocadas. Mostrando, si el cuarto parámetro, correspondiente al retrado, 
es mayor que 0, los pasos hasta llegar a esa conclusión.
Sino ha devuelto un tablero vacíoo, vEntrada con las piezas que no han conseguido cumplir objetivo 
y -1 piezas colocadas.
*/
int main(int argc, char* argv[]) {

	tpTablero tablero;

	if (argc < PARAMETROS) {
		cout << "Error: numero de argumentos insuficiente." << endl;
		cout << "\tUso: " << argv[0] << " <numero de filas> <numero de columnas> <objetivo> <retardo> <lista de piezas>" << endl;
		cout << "\tDonde <lista-piezas> puede ser un valor negativo, que crea una lista con piezas aleatorias." << endl;
		return -1;
	}

	tablero.nfils = atoi(argv[1]);
	tablero.ncols = atoi(argv[2]);

	if(tablero.nfils > MAXDIM || tablero.ncols > MAXDIM){
		cout << "Error: este tablero supera las dimensiones permitidas." << endl;
		return -1;
	}

	unsigned objetivo = atoi(argv[3]), retardo = atoi(argv[4]);

	if(objetivo >= tablero.nfils){
		cout << "Warning: el objetivo nunca va a cumplirse debido a que es mayor que el número ";
		cout << "de filas del tablero. " << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	}


	// llenamos tablero con -1
	inicializarTablero(tablero);
	

   	// definimos los vectores
	int vEntrada[MAXENTRADA] = {}, vSalida[MAXENTRADA] = {};
	
	//guardamos la primera pieza en el vector
	vEntrada[0] = atoi(argv[5]);

	if(argc > MAXENTRADA - PARAMETROS || -(vEntrada[0]) > MAXENTRADA){

		cout << "Error: el número de piezas supera las permitidas." << endl;
		return -1;
	}

	//si la primera pieza es negativa, genera piezas aleatorias
	if(vEntrada[0] < 0){

        randomPiezas(vEntrada);
    }

	//sino rellena el vector con las entradas del usuario
    else {
        
        unsigned i = PARAMETROS + 1;
        while(i < argc) {

	        vEntrada[i - PARAMETROS] = atoi(argv[i]);
	        i++;
        }
    }

	int solucion = buscaSolucion(tablero, vEntrada, vSalida, objetivo, 0, retardo);

	system("clear");
	if (solucion == -1) {

		inicializarTablero(tablero);

	}
	mostrarTablero(tablero, vEntrada);

	// devuelve la solución expresada númericamente
	cout << "Entrada (números de piezas): ";
	int i = 0;
 
	// piezas introducidas
	while (vEntrada[i] != -1) {

		cout << vEntrada[i] << " ";
		++i;
	}

	//número de piezas colocadas
	cout << endl << "Número de piezas colocadas: " << solucion << endl << "Salida (números de columnas): ";

	//columna que ocupan las piezas introducidas
	for (int i = 0; i < solucion; i++) {

		cout << vSalida[i] << " ";
	}

	cout << endl;

	return 0;

}