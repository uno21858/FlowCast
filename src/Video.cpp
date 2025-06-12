//
// Created by mavaa on 6/11/2025.
//
#include "../include/Video.h"
#include <numeric>

using namespace std;

Video::Video(string id, string titulo, int duracion, string genero)
    : id(id), titulo(titulo), duracion(duracion), genero(genero) {}

void Video::agregarCalificacion(int calif) {
    calificaciones.push_back(calif);
}

double Video::promedioCalificacion() const {
    if (calificaciones.empty()) return 0.0;
    double suma = accumulate(calificaciones.begin(), calificaciones.end(), 0);
    return suma / calificaciones.size();
}

string Video::getTitulo() const {
    return titulo;
}
