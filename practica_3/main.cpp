#include <iostream>
#include <fstream>
using namespace std;

int** matrizordenada(int columnas, int filas, char* lista, int totalBits) {
    int n = 0;
    int** matriz = new int*[filas];
    for (int i = 0; i < filas; i++) {
        matriz[i] = new int[columnas];
        for (int j = 0; j < columnas; j++) {
            if (n < totalBits) {

                matriz[i][j] = (lista[n] == '1') ? 1 : 0;
            } else {

                matriz[i][j] = 0;
            }
            n++;
        }
    }
    return matriz;
}

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

int main() {
    int tam;
    char* datos = leerArchivoEnBits("datos.txt", tam);
    if (!datos) return 1;

    int columnas = 3;
    int filas = tam / columnas;
    if (tam % columnas != 0) filas++;

    int** matrizord = matrizordenada(columnas, filas, datos, tam);

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << matrizord[i][j];
        }
        cout << endl;
    }

    for (int i = 0; i < filas; i++)
        delete[] matrizord[i];
    delete[] matrizord;
    delete[] datos;

    return 0;
}
