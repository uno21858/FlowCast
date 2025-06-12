//
// Created by mavaa on 6/11/2025.
//

#ifndef EPISODIO_H
#define EPISODIO_H

#include <string>

class Episodio {
private:
    std::string titulo;
    int numero;
    std::string imagen;

public:
    Episodio(std::string titulo, int numero, std::string imagen);
    void mostrar() const;
    void verImagen() const;

    std::string getTitulo() const;
};

#endif
