#ifndef USUARIOS_H
#define USUARIOS_H
#include <string>

using namespace std;

string** crearlistausuarios(char* lista, int& filas_out);
bool login(string** datos, int filas);

#endif
