#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
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



string** agregarUsuario(string** matriz, int& filas) {
    const int columnas = 4;
    string nuevoUsuario[columnas];
    int opcionTipo;

    cout << "\n--- Ingresar nuevo usuario ---\n";

    cout << "Seleccione el tipo de usuario:\n";
    cout << "1. Administrador\n";
    cout << "2. Usuario\n";
    cout << "Opcion: ";
    cin >> opcionTipo;

    switch (opcionTipo) {
    case 1:
        nuevoUsuario[0] = "Administrador";
        break;
    case 2:
        nuevoUsuario[0] = "Usuario";
        break;
    default:
        cout << "Opcion invalida. Se asignara 'Usuario' por defecto.\n";
        nuevoUsuario[0] = "Usuario";
        break;
    }

    cout << "Numero de documento: ";
    cin >> nuevoUsuario[1];
    cout << "Contrasena: ";
    cin >> nuevoUsuario[2];
    cout << "Saldo inicial: ";
    cin >> nuevoUsuario[3];

    string** nuevaMatriz = new string*[filas + 1];
    for (int i = 0; i < filas; i++) {
        nuevaMatriz[i] = new string[columnas];
        for (int j = 0; j < columnas; j++) {
            nuevaMatriz[i][j] = matriz[i][j];
        }
    }

    // Agregar el nuevo usuario
    nuevaMatriz[filas] = new string[columnas];
    for (int j = 0; j < columnas; j++) {
        nuevaMatriz[filas][j] = nuevoUsuario[j];
    }

    for (int i = 0; i < filas; i++)
        delete[] matriz[i];
    delete[] matriz;

    filas++;

    cout << "\nUsuario agregado correctamente.\n";
    return nuevaMatriz;
}

char* matrizachar(string** matriz, int filas, int columnas) {
    string resultado = "";

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            resultado += matriz[i][j];
            if (j < columnas - 1) resultado += ",";
        }
        if (i < filas - 1) resultado += "\n";
    }

    char* cadena = new char[resultado.length() + 1];
    strcpy(cadena, resultado.c_str());
    for (int i = 0; i < filas; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
    return cadena;
}

void guardarEnArchivo(const char* nombreArchivo, const char* contenido) {
    ofstream archivo(nombreArchivo);

    if (!archivo) {
        cout << "Error: no se pudo crear o abrir el archivo." << endl;
        return;
    }

    archivo << contenido;
    archivo.close();
}


void consultar(string** datos,int filas,string cedula){
    for(int i=0;i<filas;i++){
        if (datos[i][1]==cedula){
            cout<<"saldo disponible:" <<datos[i][3]<<"$"<<endl;
            return;
        }
    }
    return;
}

string** cobrarmovimiento(string** datos,int filas, string cedula){
    for(int i=0;i<filas;i++){
        if (datos[i][1]==cedula){
           int saldoActual = stoi(datos[i][3]);
            saldoActual-=1000;
           if (saldoActual<0)saldoActual=0;
           datos[i][3] = to_string(saldoActual);
           return datos;
        }
    }
    return datos;
}

string** retirar(string** datos, int filas, string cedula) {
    int monto;
    for (int i = 0; i < filas; i++) {
        if (datos[i][1] == cedula) {
            cout << "Cuanto desea retirar?: ";
            if (!(cin >> monto)) {           // validar entrada
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Entrada invalida.\n";
                return datos;
            }
            if (monto <= 0) {
                cout << "Cantidad invalida.\n";
                return datos;
            }

            int saldoActual = 0;
            try {
                saldoActual = stoi(datos[i][3]);
            } catch (...) {
                cout << "Saldo no valido en la cuenta.\n";
                return datos;
            }

            if (saldoActual < monto) {
                cout << "\nDinero insuficiente\n";
            } else {
                saldoActual -= monto;
                datos[i][3] = to_string(saldoActual);
                cout << "\nDinero retirado\n";
            }
            return datos; // retornamos después de procesar la fila encontrada
        }
    }
    cout << "Cedula no encontrada.\n";
    return datos;
}

bool verificaradmin(string** datos,int filas,string cedula){
    for(int i=0;i<filas;i++){
        if(datos[i][1]==cedula){
            if (datos[i][0]=="Administrador"){
                return true;
            }
            else{
                return false;
            }
        }
    }
}
