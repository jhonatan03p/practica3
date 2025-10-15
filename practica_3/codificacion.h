#ifndef CODIFICACION_H
#define CODIFICACION_H
#include <string>
using namespace std;

char* leerArchivoEnBits(const char* nombreArchivo, int& tamBits);

int** matrizordenada(int columnas, int filas, char* lista, int totalBits);
int** codificar1(int** lista, int filas, int columnas);
int** descodificar1(int** lista, int filas, int columnas);
char* codificarMetodo2(char* bits, int tam, int n);
char* decodificarMetodo2(char* bits, int tam, int n);

string** crearlistausuarios(char* lista, int& filas_out);
char bitsachar(char* bits);
char* reconstruirmensaje(char* cadena,int filas,int columnas);
char* reconstruircadena(int** matriz, int filas, int columnas);

#endif
