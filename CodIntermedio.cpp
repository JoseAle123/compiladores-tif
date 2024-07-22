#include <iostream>
#include <fstream>
#include <string>

void escribirInstruccion(int numero, std::ofstream& archivo) {
    switch (numero) {
        case 1:
            archivo << "avanzar;" << std::endl;
            break;
        case 2:
            archivo << "girarDerecho;" << std::endl;
            break;
        case 3:
            archivo << "girarIzquierda;" << std::endl;
            break;
        case 4:
            archivo << "encender;" << std::endl;
            break;
        default:
            std::cerr << "Número inválido en el array: " << numero << std::endl;
            break;
    }
}

void guardarInstrucciones(int* array, int tamaño,int* array2, int tamaño2,int* array3, int tamaño3, const std::string& nombreArchivo, int iter) {
    std::ofstream archivo(nombreArchivo, std::ios::out);
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo para escribir." << std::endl;
        return;
    }
    archivo << "iniciar()" << std::endl;
    for (int i = 0; i < tamaño; ++i) {
        escribirInstruccion(array[i], archivo);
        if(array[i] == 5){
            for (int j = 0; j < tamaño2; ++j) {
                escribirInstruccion(array2[j], archivo);
            }
        }
        if(array[i] == 6){
            for(int g = 0; g < iter; ++g){
                for (int k = 0; k < tamaño3; ++k) {
                    escribirInstruccion(array3[k], archivo);
                }
            }
        }
    }

    archivo.close();
}

int main() {
    const int tamaño = 8;
    int array[10] = {6, 1, 2, 3, 4, 1, 3, 2, 4, 5};
    int array2[3] = {1, 2, 3};
    int array3[2] = {3, 4};
    std::string nombreArchivo = "instrucciones.txt";

    guardarInstrucciones(array, 10,array2, 3,array3, 2, nombreArchivo, 3);

    std::cout << "Instrucciones guardadas en " << nombreArchivo << std::endl;

    return 0;
}
