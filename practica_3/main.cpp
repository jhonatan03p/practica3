#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "codificacion.h"
#include "usuarios.h"

using namespace std;

//----------------------------------------------
int main() {
    int opcion;
    cout << "Seleccione una opcion:\n";
    cout << "1. Codificar/decodificar metodo 1\n";
    cout << "2. Codificar/decodificar metodo 2\n";
    cout << "Opcion: ";
    cin >> opcion;

    char nombreArchivo[100];
    cout << "Ingrese el nombre del archivo: ";
    cin >> nombreArchivo;

    int tamBits;
    char* bits = leerArchivoEnBits("datos.txt", tamBits);
    if (!bits) return 1;
    int bit=bits[3]-'0';
    cout<<bit<<endl;
    int columnas = 3;
    int filas = tamBits / columnas;
    switch (opcion) {
    case 1: {
        if (tamBits % columnas != 0) filas++;

        int** matriz = matrizordenada(columnas, filas, bits, tamBits);

        cout << "\n--- MATRIZ ORIGINAL ---\n";
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                cout << matriz[i][j];
            }
            cout << endl;
        }
        int** codificada=codificar1(matriz,filas,columnas);
        cout << "\n--- MATRIZ CODIFICADA ---\n";
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                cout << codificada[i][j];
            }
            cout << endl;
        }
        int** decodificada = descodificar1(codificada, filas, columnas);
        cout << "\n MATRIZ DECODIFICADA \n";
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                cout << decodificada[i][j];
            }
            cout << endl;
        }
        char* cadena=reconstruircadena(decodificada,filas,columnas);
        // cout<<cadena<<endl;
        char* mensaje=reconstruirmensaje(cadena,filas,columnas);
        // cout<<mensaje<<endl;
        cout<<endl<<endl<<endl;
        int filasusuarios;
        string** datos = crearlistausuarios(mensaje, filasusuarios);
        int fil = 4; // porque hay 4 usuarios
        int col = 4;

        for (int i = 0; i < fil; i++) {
            for (int j = 0; j < col; j++) {
                cout << datos[i][j] << " ";
            }
            cout << endl;
        }
        delete[] cadena;
        delete[] mensaje;

        for (int i = 0; i < filas; i++) {
            delete[] codificada[i];
            delete[] matriz[i];
            delete[] decodificada[i];
        }
        delete[] matriz;
        delete[] decodificada;
        delete[] codificada;

        bool acceso = login(datos, fil);

        if (acceso) {
            cout << "\nBienvenido al sistema.\n";
        } else {
            cout << "\nAcceso denegado.\n";
        }

        // Liberar memoria
        for (int i = 0; i < fil; i++) delete[] datos[i];
        delete[] datos;

        break;
    }

    case 2: {
        int n;
        cout << "Ingrese el tamano del bloque de bits (n): ";
        cin >> n;

        char* codificado = codificarMetodo2(bits, tamBits, n);
        cout << "\nCodificacion metodo 2:\n" << codificado << endl;

        char* decodificado = decodificarMetodo2(codificado, tamBits, n);
        cout << "\nDecodificacion metodo 2:\n" << decodificado << endl;

        char* mensaje=reconstruirmensaje(decodificado,filas,columnas);
        cout<<endl<<endl<<endl;
        int filasusuarios;
        string** datos = crearlistausuarios(mensaje, filasusuarios);
        delete[] mensaje;
        int fil = 4; // porque hay 4 usuarios
        int col = 4;

        for (int i = 0; i < fil; i++) {
            for (int j = 0; j < col; j++) {
                cout << datos[i][j] << " ";
            }
            cout << endl;
        }

        bool acceso = login(datos, fil);

        if (acceso) {
            cout << "\nBienvenido al sistema.\n";
        } else {
            cout << "\nAcceso denegado.\n";
        }

        // Liberar memoria
        for (int i = 0; i < fil; i++) delete[] datos[i];
        delete[] datos;

        delete[] codificado;
        delete[] decodificado;
        break;
    }

    default:
        cout << "Opcion invalida.\n";
    }



    delete[] bits;
    return 0;
}
