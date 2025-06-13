#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include "include/Pelicula.h"
#include "include/Serie.h"
#include "include/Episodio.h"

using namespace std;

// Excepcion personalizada para calificaciones inválidas
class CalificacionInvalida : public exception {
public:
    const char* what() const noexcept override {
        return "Calificacion inválida: Solo puedes dar entre 1 y 5 estrellas";
    }
};

int pedirCalificacion() {
    int calif;
    while (true) {
        cout << "Ingresa una cuantas estrellas quieras dar de 1 al 5: ";
        cin >> calif;
        try {
            if (calif < 1 || calif > 5) throw CalificacionInvalida();
            return calif;
        } catch (const CalificacionInvalida& e) {
            cout << e.what() << "Calificacion inválida. Prueba de nuevo \n: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}

int pedirOpcion(int min, int max) {
    int opcion;
    while (true) {
        cin >> opcion;
        try {
            if (opcion < min || opcion > max) throw out_of_range("Opcion fuera de rango");
            return opcion;
        } catch (const out_of_range& e) {
            cout << "Error: " << e.what() << ". Prueba de nuevo: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}

void mostrarPeliculas(vector<Pelicula>& peliculas) {
    int op;
    do {
        cout << "\n----------MOVIES----------:\n";
        for (int i = 0; i < peliculas.size(); i++) {
            cout << i + 1 << ". ";
            peliculas[i].mostrar();
        }

        cout << "\n==========================\n";
        cout << "------------MENU----------\n";
        cout << "===========================\n";
        cout << "\nQue quieres hacer?\n";
        cout << "1. Calificar una pelicula\n";
        cout << "2. Ver una pelicula\n";
        cout << "3. Regresar\n";
        cout << "Opcion: ";
        op = pedirOpcion(1, 3);

        if (op == 1) {
            cout << "Selecciona el numero de la pelicula que deseas calificar: ";
            int sel = pedirOpcion(1, peliculas.size());
            int calif = pedirCalificacion();
            peliculas[sel - 1].agregarCalificacion(calif);
            cout << "GRACIAS!\n";
            cout << "Tu calificacion ha sido guardada :)\n";
        }
        else if (op == 2) {
            cout << "Selecciona el numero de la pelicula que deseas mirar: ";
            int sel = pedirOpcion(1, peliculas.size());
            // Abrir la pelicula usando la ruta relativa
            switch (sel) {
                case 1: system("start ../data/Videos/chihiro.mp4"); break;
                case 2: system("start ../data/Videos/totoro.mp4"); break;
                case 3: system("start ../data/Videos/mononoke.mp4"); break;
                case 4: system("start ../data/Videos/castillo_ambulante.mp4"); break;
                case 5: system("start ../data/Videos/Ponyo.mp4"); break;
                case 6: system("start ../data/Videos/Marnie.mp4"); break;
                case 7: system("start ../data/Videos/Arrietty.mp4"); break;
                case 8: system("start ../data/Videos/yn.mp4"); break;
                case 9: system("start ../data/Videos/sv.mp4"); break;
                case 10: system("start ../data/Videos/weather.mp4"); break;
            }
        }
    } while (op != 3);
}

void mostrarSeries(vector<Serie>& series) {
    int op;
    do {
        cout << "\n----------SERIES----------:\n";
        for (int i = 0; i < series.size(); i++) {
            cout << i + 1 << ". ";
            cout << series[i];
            cout << endl;
        }

        cout << "\n==========================\n";
        cout << "------------MENU----------\n";
        cout << "===========================\n";
        cout << "\nQue deseas hacer?\n";
        cout << "1. Ir a episodios\n";
        cout << "2. Calificar un episodio\n";
        cout << "3. Ver portada\n";
        cout << "4. Regresar\n";
        cout << "Opcion: ";
        op = pedirOpcion(1, 4);

        if (op == 1) {
            cout << "Selecciona una serie: ";
            int sel = pedirOpcion(1, series.size());
            series[sel - 1].mostrarEpisodios();

            cout << "Selecciona el episodio para ver la imagen (0 para regresar): ";
            int ep = pedirOpcion(0, series[sel - 1].getEpisodios().size());
            if (ep != 0) {
                if (sel == 1) {
                    if (ep == 1) system("start ../data/episodios/aot_ep1.jpg");
                    if (ep == 2) system("start ../data/episodios/aot_ep2.jpg");
                    if (ep == 3) system("start ../data/episodios/aot_ep3.jpg");
                }
                if (sel == 2) {
                    if (ep == 1) system("start ../data/episodios/tg_ep1.jpg");
                    if (ep == 2) system("start ../data/episodios/tg_ep2.jpg");
                    if (ep == 3) system("start ../data/episodios/tg_ep3.jpg");
                }
                if (sel == 3) {
                    if (ep == 1) system("start ../data/episodios/sl_ep1.jpg");
                    if (ep == 2) system("start ../data/episodios/sl_ep2.jpg");
                    if (ep == 3) system("start ../data/episodios/sl_ep3.jpg");
                }
            }
        } else if (op == 2) {
            cout << "Selecciona la serie para calificar un episodio: ";
            int sel = pedirOpcion(1, series.size());
            series[sel - 1].mostrarEpisodios();

            cout << "Selecciona el episodio: ";
            int ep = pedirOpcion(1, series[sel - 1].getEpisodios().size());
            int calif = pedirCalificacion();
            series[sel - 1].agregarCalificacion(calif);
            cout << "GRACIAS! Tu calificacion ha sido guardada :)\n";
        } else if (op == 3) {
            cout << "Selecciona la serie para ver la portada: ";
            int sel = pedirOpcion(1, series.size());
            if (sel == 1) system("start ../data/portadas/attack.jpg");
            if (sel == 2) system("start ../data/portadas/Tokyo.jpg");
            if (sel == 3) system("start ../data/portadas/Solo.jpg");
        }
    } while (op != 4);
}

int main() {
    vector<Pelicula> peliculas = {
        Pelicula("P001", "Spirited Away", 125, "Fantasia", "../data/Videos/chihiro.mp4"),
        Pelicula("P002", "My neighbourhood Totoro", 86, "Fantasia", "../data/Videos/totoro.mp4"),
        Pelicula("P003", "Princess Mononoke", 134, "Accion","../data/Videos/mononoke.mp4"),
        Pelicula("P004", "Howl's Moving Castle", 119, "Fantasia","../data/Videos/castillo_ambulante.mp4"),
        Pelicula("P005", "Ponyo", 101, "Aventura","../data/Videos/Ponyo.mp4"),
        Pelicula("P006", "Marnie", 103, "Drama","../data/Videos/Marnie.mp4"),
        Pelicula("P007", "Arrietty", 102, "Aventura", "../data/Videos/Arrietty.mp4"),
        Pelicula("P008", "Your Name", 117, "Romance", "../data/Videos/yn.mp4"),
        Pelicula("P009", "Silent Voice", 115, "Fantasia", "../data/Videos/sv.mp4"),
        Pelicula("P010", "Weathering with you", 126, "Romance", "../data/Videos/weather.mp4")
    };

    vector<Serie> series;

    Serie s1("S001", "Attack on Titan", 1500, "Accion", "../data/portadas/attack.jpg");
    s1.agregarEpisodio(Episodio("Shingeki 1", 1, "../data/episodios/aot_ep1.jpg"));
    s1.agregarEpisodio(Episodio("Shingeki 2", 1, "../data/episodios/aot_ep2.jpg"));
    s1.agregarEpisodio(Episodio("Shingeki 3", 1, "../data/episodios/aot_ep3.jpg"));
    series.push_back(s1);

    Serie s2("S002", "Tokyo Ghoul", 10000, "Aventura", "../data/portadas/Tokyo.jpg");
    s2.agregarEpisodio(Episodio("Tragedy", 1, "../data/episodios/tg_ep1.jpg"));
    s2.agregarEpisodio(Episodio("Incubation", 1, "../data/episodios/tg_ep2.jpg"));
    s2.agregarEpisodio(Episodio("Dove", 1, "../data/episodios/tg_ep3.jpg"));
    series.push_back(s2);

    Serie s3("S003", "Solo Levening", 10000, "Aventura", "../data/portadas/Solo.jpg");
    s3.agregarEpisodio(Episodio("I´m used to it", 1, "../data/episodios/sl_ep1.jpg"));
    s3.agregarEpisodio(Episodio("If i Had one more chance", 1, "../data/episodios/sl_ep2.jpg"));
    s3.agregarEpisodio(Episodio("It´s like a game", 1, "../data/episodios/sl_ep3.jpg"));
    series.push_back(s3);

    int opcion;
    do {
        cout << "\n=============================\n";
        cout << "BIENVENIDO A FLOWCAST!\n";
        cout << "=============================\n";
        cout << "En que mood estas hoy?\n";
        cout << "1. De pelis :)\n";
        cout << "2. De series :)\n";
        cout << "3. SALIR\nNo quiero ver nada\n";
        cout << "=============================\n";
        cout << "Selecciona una opcion: ";

        opcion = pedirOpcion(1, 3);

        switch (opcion) {
            case 1:
                mostrarPeliculas(peliculas);
                break;
            case 2:
                mostrarSeries(series);
                break;
            case 3:
                cout << "REGRESA A TERMINAR DE MIRAR PRONTO!\n";
                break;
        }
    } while (opcion != 3);

    return 0;
}