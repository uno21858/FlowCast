//
// Created by mavaa on 6/11/2025.
//

#ifndef SERIE_H
#define SERIE_H

#include "Video.h"
#include "Episodio.h"
#include <vector>
#include <iostream>

class Serie : public Video {
private:
    std::vector<Episodio> episodios;
    std::string portada;

public:
    Serie(std::string id, std::string titulo, int duracion, std::string genero, std::string portada);
    void agregarEpisodio(const Episodio& episodio);
    void mostrar() const override;
    void mostrarEpisodios() const;
    void verPortada() const;
    std::vector<Episodio>& getEpisodios();

    // Sobrecarga operador <<
    friend std::ostream& operator<<(std::ostream& os, const Serie& serie);
};

#endif
