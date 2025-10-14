#include <iostream>
#include <fstream>
using namespace std;

//------------------------- LECTURA ARCHIVO EN BITS
char* leerArchivoEnBits(const char* nombreArchivo, int& tamBits) {
    ifstream archivo(nombreArchivo, ios::binary);
    if (!archivo) {
        cout << "Error: no se pudo abrir el archivo." << endl;
        tamBits = 0;
        return nullptr;
    }

    archivo.seekg(0, ios::end);
    streamsize tamBytes = archivo.tellg();
    archivo.seekg(0, ios::beg);

    char* datos = new char[tamBytes];
    archivo.read(datos, tamBytes);
    archivo.close();

    tamBits = (int)tamBytes * 8;
    char* bits = new char[tamBits + 1];

    int pos = 0;
    for (int i = 0; i < tamBytes; ++i) {
        unsigned char byte = datos[i];
        for (int b = 7; b >= 0; --b) {
            bits[pos++] = ((byte >> b) & 1) ? '1' : '0';
        }
    }

    bits[tamBits] = '\0';
    delete[] datos;
    return bits;
}


// ----------------------- METODO 1
int** matrizordenada(int columnas, int filas, char* lista, int totalBits) {
    int n = 0;
    int** matriz = new int*[filas];
    for (int i = 0; i < filas; i++) {
        matriz[i] = new int[columnas];
        for (int j = 0; j < columnas; j++) {
            if (n < totalBits)
                matriz[i][j] = (lista[n] == '1') ? 1 : 0;
            else
                matriz[i][j] = 0;
            n++;
        }
    }
    return matriz;
}


// ---------------- DECODIFICACION METODO 1
int** descodificar1(int** lista, int filas, int columnas) {
    int** new_lista = new int*[filas];
    for (int i = 0; i < filas; i++) {
        new_lista[i] = new int[columnas];
    }

    for (int i = 0; i < filas; i++) {
        if (i == 0) {
            for (int j = 0; j < columnas; j++) {
                new_lista[i][j] = (lista[i][j] == 1) ? 0 : 1;
            }
        } else {
            int cont = 0;
            for (int j = 0; j < columnas; j++) {
                if (new_lista[i - 1][j] == 1) cont++;
            }

            if (cont > columnas / 2) {
                for (int j = 0; j < columnas; j++) {
                    if ((j + 1) % 3 == 0)
                        new_lista[i][j] = (lista[i][j] == 1) ? 0 : 1;
                    else
                        new_lista[i][j] = lista[i][j];
                }
            } else if (cont < columnas / 2) {
                for (int j = 0; j < columnas; j++) {
                    if (j % 2 == 1)
                        new_lista[i][j] = (lista[i][j] == 1) ? 0 : 1;
                    else
                        new_lista[i][j] = lista[i][j];
                }
            } else {
                for (int j = 0; j < columnas; j++) {
                    new_lista[i][j] = (lista[i][j] == 1) ? 0 : 1;
                }
            }
        }
    }
    return new_lista;
}

// ------------- METODO 2
char* codificarMetodo2(char* bits, int tam, int n) {
    char* codificado = new char[tam + 1];
    codificado[tam] = '\0';

    for (int i = 0; i < tam; i += n) {
        int fin = (i + n > tam) ? tam : i + n;
        int len = fin - i;
        if (len > 1) {
            codificado[i] = bits[i + len - 1];
            for (int j = 1; j < len; j++)
                codificado[i + j] = bits[i + j - 1];
        } else codificado[i] = bits[i];
    }
    return codificado;
}


// ---------------- DECODIFICACION METODO 2
char* decodificarMetodo2(char* bits, int tam, int n) {
    char* decodificado = new char[tam + 1];
    decodificado[tam] = '\0';

    for (int i = 0; i < tam; i += n) {
        int fin = (i + n > tam) ? tam : i + n;
        int len = fin - i;
        if (len > 1) {
            for (int j = 0; j < len - 1; j++)
                decodificado[i + j] = bits[i + j + 1];
            decodificado[i + len - 1] = bits[i];
        } else decodificado[i] = bits[i];
    }
    return decodificado;
}

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
    char* bits = leerArchivoEnBits(nombreArchivo, tamBits);
    if (!bits) return 1;

    switch (opcion) {
    case 1: {
        int columnas = 4;
        int filas = tamBits / columnas;
        if (tamBits % columnas != 0) filas++;

        int** matriz = matrizordenada(columnas, filas, bits, tamBits);

        cout << "\n--- MATRIZ ORIGINAL ---\n";
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                cout << matriz[i][j];
            }
            cout << endl;
        }

        int** decodificada = descodificar1(matriz, filas, columnas);
        cout << "\n MATRIZ DECODIFICADA \n";
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                cout << decodificada[i][j];
            }
            cout << endl;
        }

        for (int i = 0; i < filas; i++) {
            delete[] matriz[i];
            delete[] decodificada[i];
        }
        delete[] matriz;
        delete[] decodificada;
        break;
    }

    case 2: {
        int n;
        cout << "Ingrese el tamaño del bloque de bits (n): ";
        cin >> n;

        char* codificado = codificarMetodo2(bits, tamBits, n);
        cout << "\Codificacion metodo 2:\n" << codificado << endl;

        char* decodificado = decodificarMetodo2(codificado, tamBits, n);
        cout << "\nDecodificacion metodo 2:\n" << decodificado << endl;

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
