//
// Created by mavaa on 6/11/2025.
//
#include "../include/Pelicula.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Pelicula::Pelicula(string id, string titulo, int duracion, string genero, string videoURL)
    : Video(id, titulo, duracion, genero), videoURL(videoURL) {}

void Pelicula::mostrar() const {
    cout << titulo << " (" << genero << ", " << duracion << " min) - ";
    cout << "Promedio: " << promedioCalificacion() << "/5\n";
}

void Pelicula::verPelicula() const {
    system(("start " + videoURL).c_str());
}
