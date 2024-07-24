#ifndef ANALIZADOR_H
#define ANALIZADOR_H

#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;
int preanalisis;
string cadena ;

int getga(){
    string temp;
    int charl = cadena[0];
    for (size_t i = 1; i < cadena.length(); ++i) {
        temp += cadena[i];
    }
    cadena = temp;
    return charl;
}
//rutinas auxiliares
void error()
{
	printf("Error de sintaxis");
}

void parea(int t)
{
	if (preanalisis==t)
		preanalisis=getga();
	else
		error();
}

//rutinas de reglas
void giro(){

        parea('g');
        parea('i');
        parea('r');
        parea('a');
        parea('r');

    if (preanalisis == 'I'){
        parea('I');
        parea('z');
        parea('q');
        parea('u');
        parea('i');
        parea('e');
        parea('r');
        parea('d');
        parea('a');
        parea(';');
    }
    else if(preanalisis == 'D'){
        parea('D');
        parea('e');
        parea('r');
        parea('e');
        parea('c');
        parea('h');
        parea('o');
        parea(';');
    }
		
	else
		error();
}
void comando(){
    if (preanalisis == 'g')
	{ 
		giro();
	}
	else if (preanalisis == 'e')
	{ 
        parea('e');
        parea('n');
        parea('c');
        parea('e');
        parea('n');
        parea('d');
        parea('e');
        parea('r');
        parea(';');
	}
    else if (preanalisis == 'a')
    {
        parea('a');
        parea('v');
        parea('a');
        parea('n');
        parea('z');
        parea('a');
        parea('r');
        parea(';');
    }
	else
		error();
}

void comandos(){
    if(preanalisis == 'g' || preanalisis == 'e' || preanalisis == 'a'){
        comando();
        comandos();
    }
    else if(preanalisis == '.'){
        parea('.');
    }
    else
		error();
}

void inicio()
{
	if (preanalisis == 'i')
	{ 
		parea('i'); 
        parea('n'); 
        parea('i'); 
        parea('c');
        parea('i');
        parea('a');
        parea('r'); 
        parea('('); 
        parea(')');    
		comandos(); 
	}
	else
		error();
}

void analizadorSyx(string texto){
    cadena = texto;
    preanalisis=getga();
    inicio();
}

#endif // ANALIZADOR_H
