//
// Created by elmer on 6/12/2025.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QFrame>
#include <QtWidgets/QSlider>
#include <QtWidgets/QProgressBar>
#include <QtCore/QTimer>
#include <vector>
#include "Pelicula.h"
#include "Serie.h"

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onMovieSelected();
    void onSeriesSelected();
    void onRateMovie();
    void onPlayMovie();
    void onRateSeries();
    void onViewEpisodes();
    void onViewPortada();
    void refreshMoviesList();
    void refreshSeriesList();

private:
    // Métodos privados
    void setupUI();
    void setupMenuBar();
    void setupStatusBar();
    void loadData();
    void setupMoviesTab();
    void setupSeriesTab();
    void setupReportsTab();
    int getRatingFromUser();
    void showMovieInfo(const Pelicula& movie);
    void showSeriesInfo(const Serie& series);

    // Widgets principales
    QTabWidget *tabWidget;

    // Tab de películas
    QWidget *moviesTab;
    QListWidget *moviesList;
    QPushButton *rateMovieBtn;
    QPushButton *playMovieBtn;
    QLabel *movieInfoLabel;

    // Tab de series
    QWidget *seriesTab;
    QListWidget *seriesList;
    QPushButton *rateSeriesBtn;
    QPushButton *viewEpisodesBtn;
    QPushButton *viewPortadaBtn;
    QLabel *seriesInfoLabel;

    // Tab de reportes
    QWidget *reportsTab;
    QTextEdit *reportsText;
    QPushButton *generateReportBtn;

    // Layout principal
    QVBoxLayout *mainLayout;

    // Datos
    std::vector<Pelicula> peliculas;
    std::vector<Serie> series;

    // Estado actual
    int currentMovieIndex;
    int currentSeriesIndex;
};

#endif // MAINWINDOW_H