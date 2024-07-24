#include <iostream>
#include <fstream>
#include <string>
#include "generarcodinter.h"

int main() {
    const int tamaño = 8;
    int array[10] = {6, 1, 2, 3, 4, 1, 3, 2, 4, 5};
    int array2[3] = {1, 2, 3};
    int array3[3] = {3, 4, 5};
    std::string nombreArchivo = "instrucciones.txt";

    guardarInstrucciones(array, 10,array2, 3,array3, 3, nombreArchivo, 2);

    std::cout << "Instrucciones guardadas en " << nombreArchivo << std::endl;

    return 0;
}
