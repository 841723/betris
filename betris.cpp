#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <chrono>
#include <thread>

#include "betris.hpp"

using namespace std;



// Pre: true
// Post: Todas las componentes de tablero.matriz son -1 (casilla vacía)
void inicializarTablero(tpTablero &tablero) {

    for (int col = 0; col < tablero.ncols; col++) {

        for (int fil = 0; fil < tablero.nfils; fil++) {

            tablero.matriz[fil][col] = -1;
        }
    }
}

//Pre: 0 <= pieza < PIEZASDEF. Representa la componente que ocupa un pieza determinada en el vector Vpiezas.
//Post: Ha dibujado un pixel de ANCHO tamaño y el color correspondiente a la pieza introducida.
void dibujaPixel(const int pieza) {

    const int ANCHO = 2;

    if (pieza == -1) {

        cout << "\033[0m" << setw(ANCHO) << "" << "\033[0m";

    }

    else {

        cout << "\033[" << vPiezas[pieza].color << ";" << vPiezas[pieza].color << "m" << setw(ANCHO) << "" << "\033[0m";
    }

}


// Pre: vEntrada contiene los números de las piezas que entran y tablero contiene el estado actual
//      del tablero, en el que pueden estar colocadas algunas de dichas piezas
// Post: Se ha mostrado el tablero por pantalla (cada pieza se ha dibujado con su color)
void mostrarTablero(const tpTablero &tablero,const int vEntrada[MAXENTRADA] ) {

	cout << " ";	
	for (int i = 0; i < tablero.ncols;i++) {

		cout << "--";
	}

	cout << endl;

    for (int fil = 0; fil < tablero.nfils; fil++) {

    	 cout << "|";

        for (int col = 0; col < tablero.ncols; col++) {

        	if (tablero.matriz[fil][col] != -1) {
        		
        		dibujaPixel(vEntrada[tablero.matriz[fil][col]]);
        	}

        	else {

        		dibujaPixel(-1);
        	}
        }

        cout << "|" << endl;

    }

	cout << " ";
	for (int i = 0; i < tablero.ncols;i++) {

		cout << "--";
	}

	cout << endl;
}


//Pre: iPieza reprensenta la posición que ocupa una determinada pieza en el vector vEntrada
//Post: Ha recorrido tablero y escrito "-1" en los lugares que ocupa la iPieza en el vector vEntrada
void eliminarPieza(tpTablero &tablero, const int iPieza, int vSalida[]) {

    int columna = vSalida[iPieza];

    for (int col = 0; col < tablero.ncols; col++) {

    	for (int fil = 0; fil < tablero.nfils; fil++) {

	    	if (tablero.matriz[fil][col] == iPieza) {

	            tablero.matriz[fil][col] = -1;
	        }
	    }
	}
}

//Pre: iPieza reprensenta la posición que ocupa una determinada pieza en el vector vEntrada && 0<= columna, fila < MAXDIM
//Post: Ha escrito en la fila y columna correspondiente del tablero la pieza que ocupa la posición iPieza en vEntrada
void insertarPieza(tpTablero &tablero,const int iPieza,const int columna,const int fila,const int vEntrada[]) {

	int fil, col;
	for(int i = 0; i < TAMPIEZA; i++) {

		fil = fila + vPiezas[vEntrada[iPieza]].forma[i][0];
		col = columna + vPiezas[vEntrada[iPieza]].forma[i][1];

		tablero.matriz[fil][col] = iPieza;
	}
}

//Pre: iPieza reprensenta la posición que ocupa una determinada pieza en el vector vEntrada && 0<= columna, fila < MAXDIM
//Post: Ha comprobado si la pieza que ocupa iPieza en vEntrada puede escribirse en la fila y columna correspondiente del tablero.  Si es así,
//      comprueba si la pieza tiene hueco en una fila inferior. Si lo cumple, llama a esta función con fila+1 (que corresponde a una fila más abajo), 
//		sino inserta la pieza y la devuelve como valida.
bool piezaValida(tpTablero &tablero, const int iPieza, const int columna, int fila, int vSalida[],const int vEntrada[]) {

	int col, fil;
	bool valido = false;

	
	for(int i = TAMPIEZA - 1; i >= 0; i--) {

		fil = fila + vPiezas[vEntrada[iPieza]].forma[i][0];
		col = columna + vPiezas[vEntrada[iPieza]].forma[i][1];

	    if (tablero.matriz[fil][col] != -1 ||  col >= tablero.ncols || fil >= tablero.nfils) {

			// alguna posicion es incorrecta, o se sale de los limites
	        return false;
	    }

		else if (tablero.matriz[fil + 1][col] != -1) {

        	valido = true;
        }
	}

	if (valido) {
        	
        // hemos encontrado la posicion correcta

		insertarPieza(tablero, iPieza, columna, fila, vEntrada);
		vSalida[iPieza] = columna;

		return valido;
	
	} else {

		return piezaValida(tablero, iPieza, columna, fila + 1 ,vSalida ,vEntrada);

	}
}

//Pre: 0 < objetivo <= tablero.nfils
//Post: Recorre toda la matriz y comrpueba si hay objetivo filas llenas de piezas en tablero
bool compruebaObjetivo(tpTablero tablero, const int objetivo) {

    int filasllenas = 0, col = 0;
   
    for (int fil = 0 ; fil < tablero.nfils; fil++){

    	col = 0;

        while(tablero.matriz[fil][col] != -1 && col < tablero.ncols){
    		
			col++;
        }

        if(col == tablero.ncols){
    
            filasllenas++;
        }
    }

	return (filasllenas >= objetivo);        
}

//Pre: retardo > 0
//Post: Ha esperado retardo milisegudnos
void tiempo(const int retardo){

	std::this_thread::sleep_for(std::chrono::milliseconds(retardo));
}

// Pre: En el tablero se han colocada las n primeras piezas de vEntrada, en la columnas indicadas respectivamente en vSalida
// Post: Si las piezas colocadas completan al menos objetivo filas sin huecos,
//       entonces
//           devuelve el número de piezas colocadas, en vSalida las columnas en las que se han colocado
//           las piezas y el tablero con las piezas colocadas
//       si no devuelve -1
int buscaSolucion(tpTablero &tablero, const int vEntrada[MAXENTRADA], int vSalida[MAXENTRADA], const int objetivo, int n, const int retardo) {

	bool objetivo_cumplido = compruebaObjetivo(tablero, objetivo);

	if (objetivo_cumplido) {

		mostrarTablero(tablero, vEntrada);
		return n;
	}

	else {

		int col = 0;
		while (col < tablero.ncols && !objetivo_cumplido) {

			if (piezaValida(tablero, n, col, 0, vSalida, vEntrada)) {
				
				if (retardo > 0) {

					system("clear");
					mostrarTablero(tablero, vEntrada);
					tiempo(retardo);
				}

				int solucion = buscaSolucion(tablero,vEntrada,vSalida, objetivo, n+1, retardo);

				if (solucion == -1) {
					
					eliminarPieza(tablero, n, vSalida);
				}

				else {

					return solucion;
				}
			}

			col ++;
		}
	}
	
	return -1;
}