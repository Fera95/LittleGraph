#include <Grafo.h>

using namespace std;

int main()
{
    Grafo nodos("grafo.txt");

    int opcion = 0;

    int partida = 0;
    int llegada = 0;

    do {
        system("CLS");
        cout << "Dijkstra y Floyd" << endl;
        cout << "" << endl;
        cout << "Menu" << endl;
        cout << "Seleccione una opcion: " << endl;
        cout << "1. Dijkstra" << endl;
        cout << "2. Floyd" << endl;
        cout << "3. Salir" << endl;
        cout << "" << endl;
        cout << "Grafo: " << endl;
        nodos.desplegar();

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
        system("pause");
    } while (opcion != 3);

    return 0;
}
