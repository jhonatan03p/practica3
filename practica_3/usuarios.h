#ifndef USUARIOS_H
#define USUARIOS_H
#include <string>

using namespace std;

string** crearlistausuarios(char* lista, int& filas_out);
bool login(string** datos, int filas);
string** agregarUsuario(string** matriz, int& filas);
char* matrizachar(string** matriz, int filas, int columnas);
void guardarEnArchivo(const char* nombreArchivo, const char* contenido);

void consultar(string** datos,int filas,string cedula);
string** cobrarmovimiento(string** datos,int filas, string cedula);
string** retirar(string** datos,int filas,string cedula);

bool verificaradmin(string** datos,int filas,string cedula);
#endif
