//
// Created by mavaa on 6/11/2025.
//

#ifndef SERIE_H
#define SERIE_H

#include "Video.h"
#include "Episodio.h"
#include <vector>
#include <map>

class Serie : public Video {
private:
    int anioInicio;
    int anioFin;
    std::string portada;
    std::map<int, std::vector<Episodio>> temporadas; // temporada -> episodios
    std::map<int, int> numEpisodiosPorTemporada; // temporada -> num episodios

public:
    // Constructor que coincide con el uso en MainWindow.cpp
    Serie(std::string titulo, std::string genero, int anioInicio, int anioFin, double calificacion);

    // Constructor original para compatibilidad
    Serie(std::string id, std::string titulo, int duracion, std::string genero, std::string portada);

    // Getters
    int getAnioInicio() const { return anioInicio; }
    int getAnioFin() const { return anioFin; }
    std::string getPortada() const { return portada; }
    int getNumTemporadas() const { return temporadas.size(); }
    int getNumEpisodiosTemporada(int temporada) const;

    // Métodos para manejar temporadas y episodios
    void agregarTemporada(int temporada, int numEpisodios);
    void agregarEpisodio(int temporada, const Episodio& episodio);
    void mostrarEpisodios() const;

    // Sobrescribir método virtual
    void mostrarInfo() const override;
};

#endif // SERIE_H
