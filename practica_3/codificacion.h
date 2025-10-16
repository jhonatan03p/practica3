// codificacion.h
#ifndef CODIFICACION_H
#define CODIFICACION_H

// funciones que están implementadas en codificacion.cpp
char* leerArchivoEnBits(const char* nombreArchivo, int& tamBits);
char* leerarchivo(const char* archivo, int& tam);

int** matrizordenada(int columnas, int filas, char* lista, int totalBits);
int** codificar1(int** lista, int filas, int columnas);
int** descodificar1(int** lista, int filas, int columnas);

char* codificarMetodo2(char* bits, int tam, int n);
char* decodificarMetodo2(char* bits, int tam, int n);
char* textoABits(const char* texto, int& tamBits);

char bitsachar(char* bits);
char* reconstruirmensaje(char* cadena,int filas,int columnas);
char* reconstruircadena(int** matriz, int filas, int columnas);

#endif // CODIFICACION_H
