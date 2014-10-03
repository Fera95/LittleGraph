#include "Grafo.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    Grafo nodos("grafo.txt");

    int opcion = 0;
    int partida = 0;
    int llegada = 0;

    while (opcion != 3){
        cout << "Dijkstra y Floyd algoritmos de caminos cortos" << endl;
        cout << "=============================================" << endl;
        cout << "Menu" << endl;
        cout << "\tSeleccione una opcion: " << endl;
        cout << "\t1. Dijkstra" << endl;
        cout << "\t2. Floyd" << endl;
        cout << "\t3. Salir" << endl << endl;
        cout << "Grafo: " << endl;
        cout << "=============================================" << endl;
        nodos.desplegar();
        cout << "=============================================" << endl;
        cout << "inserte su opcion: ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                cout << "Ingrese el nodo de inicio: " << endl;
                cin >> partida;
                cout << "Ingrese el nodo al que desea llegar: " << endl;
                cin >> llegada;
                nodos.dijkstra(partida, llegada);
                break;
            case 2:
                cout << "Ingrese el nodo de inicio: " << endl;
                cin >> partida;
                cout << "Ingrese el nodo al que desea llegar: " << endl;
                cin >> llegada;
                nodos.floyd(partida, llegada);
                break;
            case 3:
                cout << "Termina el programa" << endl;
                return 0;
                break;
        }
        opcion = 0;
        partida = 0;
        llegada = 0;
    }
    return 0;
}
