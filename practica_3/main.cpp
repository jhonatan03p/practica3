#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

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
char bitsachar(char* bits) {
    char valor = 0;
    for (int i = 0; i < 8; i++) {
        valor <<= 1;
        if (bits[i] == '1')
            valor |= 1;
    }
    return valor;
}
char* reconstruirmensaje(char* cadena,int filas,int columnas){
    char* mensaje=new char[((filas*columnas)/8)+1];
    char cad[8];
    int j=0;
    int n=0;
    for(int i=0;i<(filas*columnas);i++){
        cad[j]=cadena[i];
        j++;
        if((i+1)%8==0){
            char letra=bitsachar(cad);
            mensaje[n]=letra;
            n++;
            j=0;
        }

    }
    mensaje[n]='\0';
    return mensaje;
}
char* reconstruircadena(int** matriz, int filas, int columnas) {
    int n = 0;
    char* cadena = new char[filas * columnas + 1];
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cadena[n] = (matriz[i][j] == 1) ? '1' : '0';
            n++;
        }
    }
    cadena[n] = '\0';
    return cadena;
}
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

int** codificar1(int** lista, int filas, int columnas) {
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
                if (lista[i - 1][j] == 1) cont++;
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
    char* bits = leerArchivoEnBits("datos.txt", tamBits);
    if (!bits) return 1;
    int bit=bits[3]-'0';
    cout<<bit<<endl;
    int columnas = 4;
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
        int fil = 2; // porque hay dos usuarios
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

        char* mensaje=reconstruirmensaje(decodificado,filas,columnas);
        cout<<"\nMensaje Original: "<<mensaje<<endl;
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
