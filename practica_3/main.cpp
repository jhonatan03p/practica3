#include <iostream>
#include <cstring>
#include "codificacion.h"
#include "usuarios.h"
using namespace std;

// valida credenciales en la matriz 'datos' y devuelve la cédula ("" si falla)
string pedirYValidarCred(string** datos, int filas) {
    string ced, clave;
    cout << "Cedula: "; cin >> ced;
    cout << "Clave : "; cin >> clave;
    for (int i = 0; i < filas; ++i)
        if (datos[i][1] == ced && datos[i][2] == clave) return ced;
    cout << "Cedula/clave incorrectos\n";
    return string("");
}

int main() {
    int tam = 0;
    char* buffer = leerarchivo("sudo.txt", tam);
    if (!buffer || tam == 0) { cerr << "Error leyendo sudo.txt\n"; return 1; }

    const int columnas = 3;
    int filas = (tam + columnas - 1) / columnas;

    cout << "Seleccione metodo (1 o 2): ";
    int aux; cin >> aux;

    // variables comunes
    string** datos = nullptr;
    int filasusuarios = 0;

    if (aux == 1) {
        // --- Metodo 1 ---
        int** matrizBits = matrizordenada(columnas, filas, buffer, tam);          // bits -> matriz
        int** dec = descodificar1(matrizBits, filas, columnas);                  // descodificar
        char* cadena = reconstruircadena(dec, filas, columnas /* placeholder */); // (we'll fix next line)
        // CORRECCIÓN: usar columnas (no columns)
        delete[] cadena;
        cadena = reconstruircadena(dec, filas, columnas);
        char* mensaje = reconstruirmensaje(cadena, filas, columnas);

        datos = crearlistausuarios(mensaje, filasusuarios);

        //cout << "\n--- Usuarios cargados ---\n";
        //for (int i = 0; i < filasusuarios; ++i) {
        //    for (int j = 0; j < 4; ++j) cout << datos[i][j] << " ";
        //    cout << "\n";
        //}

        // LOGIN
        string ced = pedirYValidarCred(datos, filasusuarios);
        if (ced != "") {
            bool esAdmin = verificaradmin(datos, filasusuarios, ced);
            if (esAdmin) {
                bool salir = false, cobrar = false;
                while (!salir) {
                    int op;
                    cout << "\n--- MENU ADMIN ---\n1. Crear Usuario\n2. Consultar saldo\n3. Retirar dinero\n4. Salir\nOpcion: ";
                    cin >> op;
                    switch (op) {
                    case 1: datos = agregarUsuario(datos, filasusuarios); cobrar = false; break;
                    case 2: consultar(datos, filasusuarios, ced); cobrar = true; break;
                    case 3: datos = retirar(datos, filasusuarios, ced); cobrar = true; break;
                    case 4: if (cobrar) datos = cobrarmovimiento(datos, filasusuarios, ced); salir = true; break;
                    default: cout << "Accion invalida\n";
                    }
                }
            } else {
                bool salir = false;
                while (!salir) {
                    int op; bool cobrar_local = false;
                    cout << "\n--- MENU USUARIO ---\n1. Consultar saldo\n2. Retirar dinero\n3. Cancelar\nOpcion: ";
                    cin >> op;
                    switch (op) {
                    case 1: consultar(datos, filasusuarios, ced); cobrar_local = true; break;
                    case 2: datos = retirar(datos, filasusuarios, ced); cobrar_local = true; break;
                    case 3: if (cobrar_local) datos = cobrarmovimiento(datos, filasusuarios, ced); salir = true; break;
                    default: cout << "Accion invalida\n";
                    }
                }
            }
        }

        // despues de sesion: reconstruir texto desde matriz (matrizachar libera 'datos')
        char* texto = matrizachar(datos, filasusuarios, 4);
        cout << "\nTexto reconstruido:\n" << texto << endl;

        // convertir texto -> bits y recodificar con metodo 1
        int tamBitsTexto; char* bitsTexto = textoABits(texto, tamBitsTexto);
        int filasBits = (tamBitsTexto + columnas - 1) / columnas;
        int** matrizParaCod = matrizordenada(columnas, filasBits, bitsTexto, tamBitsTexto);
        int** codificada = codificar1(matrizParaCod, filasBits, columnas);
        char* recodificada = reconstruircadena(codificada, filasBits, columnas);

        guardarEnArchivo("sudo.txt", recodificada);

        // liberar
        delete[] texto; delete[] bitsTexto; delete[] recodificada;
        for (int i = 0; i < filasBits; ++i) delete[] matrizParaCod[i];
        delete[] matrizParaCod;
        for (int i = 0; i < filasBits; ++i) delete[] codificada[i];
        delete[] codificada;

        // liberar decodificación inicial
        delete[] cadena; delete[] mensaje;
        for (int i = 0; i < filas; ++i) delete[] matrizBits[i];
        delete[] matrizBits;
        for (int i = 0; i < filas; ++i) delete[] dec[i];
        delete[] dec;
    }
    else if (aux == 2) {
        // --- Metodo 2 ---
        int n = 3;
        char* decod = decodificarMetodo2(buffer, tam, n);                       // decod bits
        int** matrizDec = matrizordenada(columnas, filas, decod, tam);
        char* cadena = reconstruircadena(matrizDec, filas, columnas);
        char* mensaje = reconstruirmensaje(cadena, filas, columnas);

        datos = crearlistausuarios(mensaje, filasusuarios);

        //cout << "\n--- Usuarios cargados ---\n";
        //for (int i = 0; i < filasusuarios; ++i) {
        //    for (int j = 0; j < 4; ++j) cout << datos[i][j] << " ";
        //    cout << "\n";
        //}

        // LOGIN
        string ced = pedirYValidarCred(datos, filasusuarios);
        if (ced != "") {
            bool esAdmin = verificaradmin(datos, filasusuarios, ced);
            if (esAdmin) {
                bool salir = false, cobrar = false;
                while (!salir) {
                    int op;
                    cout << "\n--- MENU ADMIN ---\n1. Crear Usuario\n2. Consultar saldo\n3. Retirar dinero\n4. Salir\nOpcion: ";
                    cin >> op;
                    switch (op) {
                    case 1: datos = agregarUsuario(datos, filasusuarios); cobrar = false; break;
                    case 2: consultar(datos, filasusuarios, ced); cobrar = true; break;
                    case 3: datos = retirar(datos, filasusuarios, ced); cobrar = true; break;
                    case 4: if (cobrar) datos = cobrarmovimiento(datos, filasusuarios, ced); salir = true; break;
                    default: cout << "Accion invalida\n";
                    }
                }
            } else {
                bool salir = false;
                while (!salir) {
                    int op; bool cobrar_local = false;
                    cout << "\n--- MENU USUARIO ---\n1. Consultar saldo\n2. Retirar dinero\n3. Cancelar\nOpcion: ";
                    cin >> op;
                    switch (op) {
                    case 1: consultar(datos, filasusuarios, ced); cobrar_local = true; break;
                    case 2: datos = retirar(datos, filasusuarios, ced); cobrar_local = true; break;
                    case 3: if (cobrar_local) datos = cobrarmovimiento(datos, filasusuarios, ced); salir = true; break;
                    default: cout << "Accion invalida\n";
                    }
                }
            }
        }

        // despues de sesion: reconstruir texto y recodificar con metodo 2
        char* texto = matrizachar(datos, filasusuarios, 4);

        int tamBitsTexto; char* bitsTexto = textoABits(texto, tamBitsTexto);
        char* recodificado = codificarMetodo2(bitsTexto, tamBitsTexto, n);

        guardarEnArchivo("sudo.txt", recodificado);

        // liberar
        delete[] texto; delete[] bitsTexto; delete[] recodificado;
        delete[] decod; delete[] cadena; delete[] mensaje;
        for (int i = 0; i < filas; ++i) delete[] matrizDec[i];
        delete[] matrizDec;
    }
    else {
        cout << "Metodo invalido\n";
    }

    // liberar lectura original
    delete[] buffer;
    cout << "\nFin.\n";
    return 0;
}
