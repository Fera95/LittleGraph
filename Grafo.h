#ifndef GRAFO_H
#define GRAFO_H
#include <vector>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>


using namespace std;

struct Conexion {
    int nodoAdyacente;
    float costo;
};

struct Nodo {
    int etiqueta;
    bool visitado;
    vector<Conexion> adyacentes;
};

class Grafo
{
    private:
        int numeroNodos;
        int numeroAristas;
        vector<Nodo> nodos;
        int **matrizAdyacencia;

        void crearNodos();
        void crearMatriz();
        void floydHelper();

    public:
        Grafo(string nombreArchivo);
        virtual ~Grafo();

        Conexion menor(vector<Conexion> &frontera);
        void dijkstra(int inicio, int fin);
        void floyd(int inicio, int fin);
        void leer(string nombreArchivo);
        void desplegarCamino(vector<int> &camino);
        void desplegar();

        void imprimirMatriz();

        int getNumeroNodos();
};

#endif // GRAFO_H
