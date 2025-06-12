//
// Created by mavaa on 6/11/2025.
//
#ifndef VIDEO_H
#define VIDEO_H

#include <string>
#include <vector>

class Video {
protected:
    std::string id;
    std::string titulo;
    int duracion;
    std::string genero;
    std::vector<int> calificaciones;

public:
    Video(std::string id, std::string titulo, int duracion, std::string genero);
    virtual ~Video() {}

    // Método virtual puro - hace Video clase abstracta (interfaz)
    virtual void mostrar() const = 0;

    void agregarCalificacion(int calif);
    double promedioCalificacion() const;
    std::string getTitulo() const;
};

#endif
