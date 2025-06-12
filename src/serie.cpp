//
// Created by mavaa on 6/11/2025.
//

#include "../include/Serie.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Serie::Serie(string id, string titulo, int duracion, string genero, string portada)
    : Video(id, titulo, duracion, genero), portada(portada) {}

void Serie::agregarEpisodio(const Episodio& episodio) {
    episodios.push_back(episodio);
}

void Serie::mostrar() const {
    cout << titulo << " (" << genero << ", " << duracion << " min) - ";
    cout << "Promedio: " << promedioCalificacion() << "/5\n";
}

void Serie::mostrarEpisodios() const {
    for (int i = 0; i < episodios.size(); ++i) {
        cout << i + 1 << ". ";
        episodios[i].mostrar();
    }
}

void Serie::verPortada() const {
    system(("start " + portada).c_str());
}

vector<Episodio>& Serie::getEpisodios() {
    return episodios;
}

ostream& operator<<(ostream& os, const Serie& serie) {
    os << serie.titulo << " (" << serie.genero << ", " << serie.duracion << " min)";
    os << "Promedio: " << serie.promedioCalificacion() << "/5";
    return os;
}
