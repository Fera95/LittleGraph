#include "Grafo.h"
#include <fstream>
#include <iostream>
using namespace std;
Grafo::Grafo(string nombreArchivo)
{
    leer(nombreArchivo);
}

Grafo::~Grafo()
{
}

void Grafo::crearNodos() {
    for (int i = 0; i < numeroNodos; i ++) {
        Nodo nuevo;
        nuevo.etiqueta = i;
        nuevo.visitado = false;
        nodos.push_back(nuevo);
    }
}

void Grafo::crearMatriz() {
    matrizAdyacencia = new int *[numeroNodos];
    for (int i = 0; i < numeroNodos; i ++) {
        int * distancias = new int[numeroNodos];
        for (int j = 0; j < numeroNodos; j ++) {
            Nodo n = nodos[i];
            if (i == j) {
                distancias[j] = 0;
            } else {
                distancias[j] = numeric_limits<int>::max();
            }
        }
        unsigned int k = 0;
        Conexion cambio;
        while (k < nodos[i].adyacentes.size()) {
            cambio = nodos[i].adyacentes[k];
            distancias[cambio.nodoAdyacente] = cambio.costo;
            k ++;
        }
        matrizAdyacencia[i] = distancias;
    }
}

Conexion Grafo::menor(vector<Conexion> &frontera) {
    int posicion = 0;
    for (unsigned int i = 0; i < frontera.size(); i ++) {
        if (frontera[i].costo < frontera[posicion].costo) {
            posicion = i;
        }
    }
    Conexion menor = frontera[posicion];
    vector<Conexion>::iterator comienzo = frontera.begin();
    frontera.erase(comienzo + posicion, comienzo + posicion + 1);
    return menor;
}

void Grafo::dijkstra(int inicio, int fin) {
    vector<int> camino;
    vector<Conexion> frontera;
    Nodo cambio = nodos[inicio];
    Nodo llegada = nodos[fin];
    camino.push_back(cambio.etiqueta);
    bool vacio = false;
    while (cambio.etiqueta != llegada.etiqueta && !vacio) {
        if (!cambio.visitado) {
            cambio.visitado = true;
            if (cambio.adyacentes.size() == 0 && camino.size() > 1) {
                vector<int>::iterator comienzo = camino.begin();
                camino.erase(comienzo + 1, camino.end());
            } else {
                for (unsigned int i = 0; i < cambio.adyacentes.size(); i ++) {
                    frontera.push_back(cambio.adyacentes[i]);
                }
            }
        }
        Conexion proximo = menor(frontera);
        camino.push_back(proximo.nodoAdyacente);
        cambio = nodos[proximo.nodoAdyacente];
        vacio = frontera.empty();
    }
    for (unsigned int k = 0; k < nodos.size(); k ++) {
        nodos[k].visitado = false;
    }
    if (!frontera.empty()) {
        desplegarCamino(camino);
    } else {
        vector<int> nuevo;
        desplegarCamino(nuevo);
    }
}

void Grafo::floyd(int inicio, int fin) {
    /*en esta matriz se guarda la distancia mas corta de un nodo a otro*/
    int matrizDeDistanciasCortas[numeroNodos][numeroNodos];
    //en esta matriz se guarda el camino por el que pasa el nodo para llegar a el por el camino mas corto
    int matrizDeCaminoCortos[numeroNodos][numeroNodos];
    /*copia de la matriz de caminos a una matriz en la cual se calculara los caminos cortos*/
    //esta parte se encarga de copiar las filas
    for (int filaDeCaminosCortos = 0; filaDeCaminosCortos < numeroNodos; filaDeCaminosCortos ++) {
        // esta se encarga de colocar cada un delos valores de la fila o sea los valores de las columnas
        for (int columnaDeCaminosCortos = 0; columnaDeCaminosCortos < numeroNodos; columnaDeCaminosCortos ++) {
            //esta se encarga de copiar la matriz de adyacencia a la matriz de distancias cortas
            matrizDeDistanciasCortas[filaDeCaminosCortos][columnaDeCaminosCortos] = matrizAdyacencia[filaDeCaminosCortos][columnaDeCaminosCortos];
            //esta se encarga de llenar los caminos con ceros
            matrizDeCaminoCortos[filaDeCaminosCortos][columnaDeCaminosCortos] = 0;

        }
    }
    //cambio de caminos
    int tmp;
    for (int identidaDeMatriz = 0; identidaDeMatriz < numeroNodos; identidaDeMatriz ++) {
        for (int i = 0; i < numeroNodos; i ++) {
            for (int j = 0; j < numeroNodos; j ++) {
                tmp = matrizDeDistanciasCortas[i][identidaDeMatriz] + matrizDeDistanciasCortas[identidaDeMatriz][j];
                if (matrizDeDistanciasCortas[i][j] > tmp ) {
                    matrizDeDistanciasCortas[i][j] = tmp;
                    matrizDeCaminoCortos[i][j] = nodos[identidaDeMatriz].etiqueta;
                }
            }
        }
    }
    /*
    vector<int> recorrido;
    int nodo = fin;

    while (matrizDeCaminoCortos[inicio][nodo] != 0 && matrizDeCaminoCortos[inicio][nodo] != inicio) {
        if (recorrido.size() == 0) {
            recorrido.push_back(inicio);
        }
        nodo = matrizDeCaminoCortos[inicio][nodo];
        cout << "Nodo " << nodo << endl;
        recorrido.push_back(nodo);
        if (matrizDeCaminoCortos[inicio][nodo] == inicio) {
            recorrido.push_back(fin);
            break;
        }
    }

    desplegarCamino(recorrido);
    */
    cout << "==============matriz de distancias=================" << endl;
    for (int x = 0; x < numeroNodos; x++){
        for (int y= 0; y < numeroNodos; y++){
            cout << matrizDeDistanciasCortas[x][y];
            cout <<" ";
        }
        cout << endl;
    }
    cout << "================================================" << endl;
    cout << "===============matriz de caminos=============" << endl;
    for (int x = 0; x < numeroNodos; x++){
        for (int y= 0; y < numeroNodos; y++){
            cout << matrizDeCaminoCortos[x][y];
            cout <<" ";
        }
        cout << endl;
    }
    cout << "================================================" << endl;
}

void Grafo::leer(string nombreArchivo) {
    ifstream archivo(nombreArchivo.c_str());
    string linea = "";
    int opcion = 0;
    int cambio = 0;
    string partida = "";
    string llegada = "";
    string costo = "";
    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            if (linea != "") {
                if (opcion == 0) {
                    opcion = atoi(linea.c_str());
                } else {
                    switch (opcion) {
                        case 1:
                            numeroNodos = atoi(linea.c_str());
                            crearNodos();
                            opcion = 0;
                            break;
                        case 2:
                            numeroAristas = atoi(linea.c_str());
                            opcion = 0;
                            break;
                        case 3:
                            for (unsigned int i = 0; i < linea.length(); i ++) {
                                if (cambio == 0) {
                                    if (linea[i] != ',') {
                                        partida.push_back(linea[i]);
                                    } else {
                                        cambio = 1;
                                    }
                                } else if (cambio == 1) {
                                    if (linea[i] != '-') {
                                        llegada.push_back(linea[i]);
                                    } else {
                                        cambio = 2;
                                    }
                                } else {
                                    costo.push_back(linea[i]);
                                }
                            }
                            cambio = 0;
                            Conexion nuevo;
                            nuevo.nodoAdyacente = atoi(llegada.c_str());
                            nuevo.costo = atof(costo.c_str());
                            int nodoPartida = atoi(partida.c_str());
                            nodos[nodoPartida].adyacentes.push_back(nuevo);
                            llegada = "";
                            partida = "";
                            costo = "";
                            break;
                    }
                }
            }
        }
    }
    crearMatriz();
    archivo.close();
}

void Grafo::desplegarCamino(vector<int> &camino) {
    string linea = "";
    if (camino.size() > 0) {
        linea = "El camino es: ";
        stringstream stream;
        for (unsigned int i = 0; i < camino.size(); i ++) {
            stream << camino[i];
            linea.append(stream.str());
            linea.push_back('-');
            stream.str("");
            stream.clear();
        }
        linea.erase(linea.size() - 1, 1);
    } else {
        linea = "No hay camino";
    }
    cout << linea << endl;
}

void Grafo::desplegar() {
    stringstream stream;
    for (unsigned int  i = 0; i < nodos.size(); i ++) {
        cout << "Nodo " << nodos[i].etiqueta << ": ";
        stream << nodos[i].etiqueta;
        string nodo = stream.str();
        stream.str("");
        stream.clear();
        string linea = "{(";
        for (unsigned int k = 0; k < nodos[i].adyacentes.size(); k ++) {
            linea.append(nodo);
            linea.push_back('-');
            stream << nodos[i].adyacentes[k].nodoAdyacente;
            linea.append(stream.str());
            linea.append("),");
            stream.str("");
            stream.clear();
        }
        linea.erase(linea.length()- 1, 1);
        linea.push_back('}');
        cout << linea << endl;
    }
}

void Grafo::imprimirMatriz() {
    for (int i = 0; i < numeroNodos; i ++) {
        for (int j = 0; j < numeroNodos; j ++) {
            cout << matrizAdyacencia[i][j] << ", ";
        }
        cout << endl;
    }
}

int Grafo::getNumeroNodos() {
    return numeroNodos;
}
