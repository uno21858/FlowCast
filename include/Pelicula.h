//
// Created by mavaa on 6/11/2025.
//

#ifndef PELICULA_H
#define PELICULA_H


#include "Video.h"
#include <string>

class Pelicula : public Video {
private:
    std::string director;
    int anio;
    std::string videoURL;

public:
    // Constructor que coincide con el uso en MainWindow.cpp
    Pelicula(std::string titulo, int duracion, std::string genero, std::string director, int anio, double calificacion);

    // Constructor original para compatibilidad
    Pelicula(std::string id, std::string titulo, int duracion, std::string genero, std::string videoURL);

    // Getters
    std::string getDirector() const { return director; }
    int getAnio() const { return anio; }
    std::string getVideoURL() const { return videoURL; }

    // Sobrescribir método virtual
    void mostrarInfo() const override;
};

#endif // PELICULA_H
