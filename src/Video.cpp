//
// Created by mavaa on 6/11/2025.
//
#include "Video.h"
#include <numeric>
#include <algorithm>

Video::Video(std::string id, std::string titulo, int duracion, std::string genero)
    : id(id), titulo(titulo), duracion(duracion), genero(genero) {
}

void Video::agregarCalificacion(double calificacion) {
    if (calificacion >= 0.0 && calificacion <= 10.0) {
        calificaciones.push_back(calificacion);
    }
}

double Video::getCalificacion() const {
    if (calificaciones.empty()) {
        return 0.0;
    }
    double suma = std::accumulate(calificaciones.begin(), calificaciones.end(), 0.0);
    return suma / calificaciones.size();
}

void Video::setCalificacion(double calificacion) {
    calificaciones.clear();
    agregarCalificacion(calificacion);
}
