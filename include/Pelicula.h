//
// Created by mavaa on 6/11/2025.
//

#ifndef PELICULA_H
#define PELICULA_H

#include "Video.h"
#include <string>


class Pelicula : public Video {
private:
    std::string videoURL;

public:
    Pelicula(std::string id, std::string titulo, int duracion, std::string genero, std::string videoURL);
    void mostrar() const override;
    void verPelicula() const;

    // Sobrecarga operador ==
    bool operator==(const Pelicula& otra) const {
        return titulo == otra.titulo;
    }
};

#endif
