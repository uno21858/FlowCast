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
    std::vector<double> calificaciones;

public:
    Video(std::string id, std::string titulo, int duracion, std::string genero);
    virtual ~Video() = default;

    // Getters públicos
    std::string getId() const { return id; }
    std::string getTitulo() const { return titulo; }
    int getDuracion() const { return duracion; }
    std::string getGenero() const { return genero; }

    // Métodos para calificaciones
    void agregarCalificacion(double calificacion);
    double getCalificacion() const;
    void setCalificacion(double calificacion);

    // Método virtual puro para mostrar información
    virtual void mostrarInfo() const = 0;
};

#endif // VIDEO_H