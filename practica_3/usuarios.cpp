#include <string>
#include <cstring>
#include <iostream>
using namespace std;

string** crearlistausuarios(char* lista, int& filas_out) {
    int filas = 0;
    int columnas = 4;
    string dato = "";
    int f = 0, c = 0;

    for (int i = 0; lista[i] != '\0'; i++) {
        if (lista[i] == '\n') {
            filas++;
        }
    }
    if (lista[0] != '\0' && lista[strlen(lista) - 1] != '\n') filas++;

    string** matriz = new string*[filas];
    for (int i = 0; i < filas; i++) {
        matriz[i] = new string[columnas];
    }

    for (int i = 0; lista[i] != '\0'; i++) {
        char ch = lista[i];


        if (ch == '\r') continue;

        if (ch == ',' || ch == '\n') {
            matriz[f][c] = dato;
            dato = "";
            c++;
            if (c == columnas || ch == '\n') {
                f++;
                c = 0;
            }
        } else {
            dato += ch;
        }
    }

    if (!dato.empty() && f < filas && c < columnas) {
        matriz[f][c] = dato;
    }
    filas_out = filas;
    return matriz;
}

bool login(string** datos, int filas) {
    string cedula, clave;
    cout << "Ingrese su cedula: ";
    cin >> cedula;
    cout << "Ingrese su clave: ";
    cin >> clave;

    for (int i = 0; i < filas; i++) {
        if (datos[i][1] == cedula) { // posición [1] es la cédula
            if (datos[i][2] == clave) { // posición [2] es la clave
                if (datos[i][0] == "Usuario")
                    cout << "\nIngreso de usuario\n";
                else if (datos[i][0] == "Administrador")
                    cout << "\nIngreso administrador\n";
                return true;
            } else {
                cout << "\nClave incorrecta.\n";
                return false;
            }
        }
    }

    cout << "\nCedula no encontrada.\n";
    return false;
}
