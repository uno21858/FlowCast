//
// Created by mavaa on 6/11/2025.
//
#include "../include/Episodio.h"
#include <cstdlib>
#include <iostream>

using namespace std;

Episodio::Episodio(string titulo, int numero, string imagen)
    : titulo(titulo), numero(numero), imagen(imagen) {}

void Episodio::mostrar() const {
    cout << "Episodio " << numero << ": " << titulo << endl;
}

void Episodio::verImagen() const {
    system(("start " + imagen).c_str());
}

string Episodio::getTitulo() const {
    return titulo;
}
