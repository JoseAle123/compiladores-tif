#ifndef CONVERTTXT_H
#define CONVERTTXT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

string eliminarSaltosDeLinea(const string& texto) {
    string resultado;
    for (char c : texto) {
        if (c != '\n' && c != '\r') {
            resultado += c;
        }
    }
    return resultado;
}

string leerArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    stringstream buffer;
    if (archivo) {
        buffer << archivo.rdbuf();
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
    }
    return buffer.str();
}

string txtConvertstring(string nametxt ){
    string result;
    result = eliminarSaltosDeLinea(leerArchivo(nametxt));
    return result;
}

#endif // CONVERTTXT_H