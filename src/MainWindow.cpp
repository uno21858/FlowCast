#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QSplitter>
#include <QtCore/QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , tabWidget(nullptr)
    , currentMovieIndex(-1)
    , currentSeriesIndex(-1)
{
    setWindowTitle("FlowCast - Streaming Platform");
    setMinimumSize(1200, 800);
    
    // Cargar datos
    loadData();
    
    // Configurar UI
    setupUI();
    setupMenuBar();
    setupStatusBar();
    
    // Actualizar listas
    refreshMoviesList();
    refreshSeriesList();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    // Widget central con tabs
    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);
    
    // Configurar tabs
    setupMoviesTab();
    setupSeriesTab();
    setupReportsTab();
    
    // Estilo moderno
    tabWidget->setStyleSheet(R"(
        QTabWidget::pane {
            border: 1px solid #C2C7CB;
            background-color: #FAFAFA;
        }
        QTabWidget::tab-bar {
            left: 5px;
        }
        QTabBar::tab {
            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,
                                      stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,
                                      stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);
            border: 2px solid #C4C4C3;
            border-bottom-color: #C2C7CB;
            border-top-left-radius: 4px;
            border-top-right-radius: 4px;
            min-width: 8ex;
            padding: 8px;
        }
        QTabBar::tab:selected, QTabBar::tab:hover {
            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,
                                      stop: 0 #fafafa, stop: 0.4 #f4f4f4,
                                      stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);
        }
        QTabBar::tab:selected {
            border-color: #9B9B9B;
            border-bottom-color: #C2C7CB;
        }
    )");
}

void MainWindow::setupMoviesTab()
{
    moviesTab = new QWidget();
    tabWidget->addTab(moviesTab, "🎬 Películas");
    
    // Layout principal horizontal
    QHBoxLayout *mainLayout = new QHBoxLayout(moviesTab);
    
    // Panel izquierdo - Lista de películas
    QFrame *leftPanel = new QFrame();
    leftPanel->setFrameStyle(QFrame::StyledPanel);
    leftPanel->setMaximumWidth(400);
    
    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);
    
    QLabel *moviesLabel = new QLabel("📽️ Catálogo de Películas");
    moviesLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2C3E50; padding: 10px;");
    leftLayout->addWidget(moviesLabel);
    
    moviesList = new QListWidget();
    moviesList->setStyleSheet(R"(
        QListWidget {
            border: 1px solid #BDC3C7;
            border-radius: 5px;
            background-color: white;
            selection-background-color: #3498DB;
        }
        QListWidget::item {
            padding: 8px;
            border-bottom: 1px solid #ECF0F1;
        }
        QListWidget::item:hover {
            background-color: #EBF3FD;
        }
    )");
    leftLayout->addWidget(moviesList);
    
    // Botones de acciones
    QHBoxLayout *movieButtonsLayout = new QHBoxLayout();
    
    rateMovieBtn = new QPushButton("⭐ Calificar");
    playMovieBtn = new QPushButton("▶️ Reproducir");
    
    rateMovieBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #F39C12;
            color: white;
            border: none;
            padding: 8px 16px;
            border-radius: 4px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #E67E22;
        }
    )");
    
    playMovieBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #27AE60;
            color: white;
            border: none;
            padding: 8px 16px;
            border-radius: 4px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #229954;
        }
    )");
    
    movieButtonsLayout->addWidget(rateMovieBtn);
    movieButtonsLayout->addWidget(playMovieBtn);
    leftLayout->addLayout(movieButtonsLayout);
    
    // Panel derecho - Información de película

// Continúa desde la línea en la que se quedó el código
    QFrame *rightPanel = new QFrame();
    rightPanel->setFrameStyle(QFrame::StyledPanel);

    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);

    QLabel *infoTitleLabel = new QLabel("📝 Información de la Película");
    infoTitleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2C3E50; padding: 10px;");
    rightLayout->addWidget(infoTitleLabel);

    movieInfoLabel = new QLabel("Selecciona una película para ver detalles");
    movieInfoLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    movieInfoLabel->setWordWrap(true);
    movieInfoLabel->setStyleSheet(R"(
        background-color: white;
        padding: 15px;
        border-radius: 8px;
        border: 1px solid #E0E0E0;
    )");

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(movieInfoLabel);
    scrollArea->setStyleSheet("border: none; background-color: transparent;");

    rightLayout->addWidget(scrollArea);

    // Organizar paneles en el layout principal
    mainLayout->addWidget(leftPanel, 1);
    mainLayout->addWidget(rightPanel, 2);

    // Conexiones
    connect(moviesList, &QListWidget::itemClicked, this, &MainWindow::onMovieSelected);
    connect(rateMovieBtn, &QPushButton::clicked, this, &MainWindow::onRateMovie);
    connect(playMovieBtn, &QPushButton::clicked, this, &MainWindow::onPlayMovie);
}

void MainWindow::setupSeriesTab()
{
    seriesTab = new QWidget();
    tabWidget->addTab(seriesTab, "📺 Series");

    // Layout principal horizontal
    QHBoxLayout *mainLayout = new QHBoxLayout(seriesTab);

    // Panel izquierdo - Lista de series
    QFrame *leftPanel = new QFrame();
    leftPanel->setFrameStyle(QFrame::StyledPanel);
    leftPanel->setMaximumWidth(400);

    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);

    QLabel *seriesLabel = new QLabel("📺 Catálogo de Series");
    seriesLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2C3E50; padding: 10px;");
    leftLayout->addWidget(seriesLabel);

    seriesList = new QListWidget();
    seriesList->setStyleSheet(R"(
        QListWidget {
            border: 1px solid #BDC3C7;
            border-radius: 5px;
            background-color: white;
            selection-background-color: #9B59B6;
        }
        QListWidget::item {
            padding: 8px;
            border-bottom: 1px solid #ECF0F1;
        }
        QListWidget::item:hover {
            background-color: #F5EEF8;
        }
    )");
    leftLayout->addWidget(seriesList);

    // Botones de acción
    QVBoxLayout *seriesButtonsLayout = new QVBoxLayout();

    QHBoxLayout *topButtons = new QHBoxLayout();
    rateSeriesBtn = new QPushButton("⭐ Calificar");
    viewEpisodesBtn = new QPushButton("🎬 Ver Episodios");

    rateSeriesBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #F39C12;
            color: white;
            border: none;
            padding: 8px 16px;
            border-radius: 4px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #E67E22;
        }
    )");

    viewEpisodesBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #9B59B6;
            color: white;
            border: none;
            padding: 8px 16px;
            border-radius: 4px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #8E44AD;
        }
    )");

    topButtons->addWidget(rateSeriesBtn);
    topButtons->addWidget(viewEpisodesBtn);

    viewPortadaBtn = new QPushButton("🖼️ Ver Portada");
    viewPortadaBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #3498DB;
            color: white;
            border: none;
            padding: 8px 16px;
            border-radius: 4px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #2980B9;
        }
    )");

    seriesButtonsLayout->addLayout(topButtons);
    seriesButtonsLayout->addWidget(viewPortadaBtn);
    leftLayout->addLayout(seriesButtonsLayout);

    // Panel derecho - Información de serie
    QFrame *rightPanel = new QFrame();
    rightPanel->setFrameStyle(QFrame::StyledPanel);

    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);

    QLabel *infoTitleLabel = new QLabel("📝 Información de la Serie");
    infoTitleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2C3E50; padding: 10px;");
    rightLayout->addWidget(infoTitleLabel);

    seriesInfoLabel = new QLabel("Selecciona una serie para ver detalles");
    seriesInfoLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    seriesInfoLabel->setWordWrap(true);
    seriesInfoLabel->setStyleSheet(R"(
        background-color: white;
        padding: 15px;
        border-radius: 8px;
        border: 1px solid #E0E0E0;
    )");

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(seriesInfoLabel);
    scrollArea->setStyleSheet("border: none; background-color: transparent;");

    rightLayout->addWidget(scrollArea);

    // Organizar paneles
    mainLayout->addWidget(leftPanel, 1);
    mainLayout->addWidget(rightPanel, 2);

    // Conexiones
    connect(seriesList, &QListWidget::itemClicked, this, &MainWindow::onSeriesSelected);
    connect(rateSeriesBtn, &QPushButton::clicked, this, &MainWindow::onRateSeries);
    connect(viewEpisodesBtn, &QPushButton::clicked, this, &MainWindow::onViewEpisodes);
    connect(viewPortadaBtn, &QPushButton::clicked, this, &MainWindow::onViewPortada);
}

void MainWindow::setupReportsTab()
{
    reportsTab = new QWidget();
    tabWidget->addTab(reportsTab, "📊 Reportes");

    QVBoxLayout *layout = new QVBoxLayout(reportsTab);

    QLabel *reportsLabel = new QLabel("📈 Informes y Estadísticas");
    reportsLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2C3E50; padding: 10px;");
    layout->addWidget(reportsLabel);

    reportsText = new QTextEdit();
    reportsText->setReadOnly(true);
    reportsText->setStyleSheet(R"(
        QTextEdit {
            border: 1px solid #BDC3C7;
            border-radius: 5px;
            background-color: white;
            padding: 10px;
            font-size: 14px;
        }
    )");
    layout->addWidget(reportsText);

    generateReportBtn = new QPushButton("🔄 Generar Reporte");
    generateReportBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #2C3E50;
            color: white;
            border: none;
            padding: 12px 24px;
            border-radius: 4px;
            font-weight: bold;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color: #34495E;
        }
    )");
    layout->addWidget(generateReportBtn, 0, Qt::AlignCenter);

    // Aquí puedes conectar el botón a una función que genere reportes
}

void MainWindow::setupMenuBar()
{
    QMenuBar *menuBar = new QMenuBar(this);
    this->setMenuBar(menuBar);

    // Menú Archivo
    QMenu *fileMenu = menuBar->addMenu("&Archivo");

    QAction *exitAction = new QAction("&Salir", this);
    exitAction->setShortcut(QKeySequence("Ctrl+Q"));
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    fileMenu->addAction(exitAction);

    // Menú Ver
    QMenu *viewMenu = menuBar->addMenu("&Ver");

    QAction *refreshAction = new QAction("&Actualizar Catálogo", this);
    refreshAction->setShortcut(QKeySequence("F5"));
    connect(refreshAction, &QAction::triggered, [this](){
        refreshMoviesList();
        refreshSeriesList();
    });
    viewMenu->addAction(refreshAction);

    // Menú Ayuda
    QMenu *helpMenu = menuBar->addMenu("A&yuda");

    QAction *aboutAction = new QAction("&Acerca de", this);
    connect(aboutAction, &QAction::triggered, [this](){
        QMessageBox::about(this, "Acerca de FlowCast",
                          "FlowCast - Plataforma de Streaming\n"
                          "Versión 1.0.0\n\n"
                          "Desarrollado con Qt 6\n\n"
                          "© 2025 FlowCast Team");
    });
    helpMenu->addAction(aboutAction);
}

void MainWindow::setupStatusBar()
{
    QStatusBar *statusBar = new QStatusBar(this);
    this->setStatusBar(statusBar);
    statusBar->showMessage("FlowCast listo", 3000);
}

void MainWindow::loadData()
{
    // Ejemplo: Cargar películas
    peliculas.push_back(Pelicula("El Padrino", 175, "Drama/Crimen", "Francis Ford Coppola", 1972, 9.2));
    peliculas.push_back(Pelicula("Interestelar", 169, "Ciencia Ficción", "Christopher Nolan", 2014, 8.6));
    peliculas.push_back(Pelicula("La La Land", 128, "Musical/Romance", "Damien Chazelle", 2016, 8.0));
    peliculas.push_back(Pelicula("El Rey León", 88, "Animación", "Rob Minkoff", 1994, 8.5));
    peliculas.push_back(Pelicula("Matrix", 136, "Ciencia Ficción", "Hermanas Wachowski", 1999, 8.7));

    // Ejemplo: Cargar series
    Serie got("Game of Thrones", "Drama/Fantasía", 2011, 2019, 8.9);
    got.agregarTemporada(1, 10);
    got.agregarTemporada(2, 10);
    series.push_back(got);

    Serie bb("Breaking Bad", "Drama/Crimen", 2008, 2013, 9.5);
    bb.agregarTemporada(1, 7);
    bb.agregarTemporada(2, 13);
    bb.agregarTemporada(3, 13);
    series.push_back(bb);

    Serie st("Stranger Things", "Ciencia Ficción/Drama", 2016, 2022, 8.7);
    st.agregarTemporada(1, 8);
    st.agregarTemporada(2, 9);
    series.push_back(st);
}

void MainWindow::refreshMoviesList()
{
    moviesList->clear();
    for (const auto& pelicula : peliculas) {
        QString itemText = QString::fromStdString(pelicula.getTitulo());
        QListWidgetItem *item = new QListWidgetItem(itemText);
        moviesList->addItem(item);
    }
}

void MainWindow::refreshSeriesList()
{
    seriesList->clear();
    for (const auto& serie : series) {
        QString itemText = QString::fromStdString(serie.getTitulo());
        QListWidgetItem *item = new QListWidgetItem(itemText);
        seriesList->addItem(item);
    }
}

void MainWindow::onMovieSelected()
{
    int index = moviesList->currentRow();
    if (index >= 0 && index < peliculas.size()) {
        currentMovieIndex = index;
        showMovieInfo(peliculas[index]);
    }
}

void MainWindow::onSeriesSelected()
{
    int index = seriesList->currentRow();
    if (index >= 0 && index < series.size()) {
        currentSeriesIndex = index;
        showSeriesInfo(series[index]);
    }
}

void MainWindow::showMovieInfo(const Pelicula& movie)
{
    QString info = QString(R"(
        <div style="color: #2C3E50; font-family: Arial, sans-serif;">
            <h2 style="color: #2980B9;">%1</h2>
            <hr style="border: 1px solid #ECF0F1;">
            <p><b>Género:</b> %2</p>
            <p><b>Director:</b> %3</p>
            <p><b>Año:</b> %4</p>
            <p><b>Duración:</b> %5 minutos</p>
            <p><b>Calificación:</b> <span style="color: #F39C12; font-weight: bold;">★ %6 / 10</span></p>
        </div>
    )").arg(
        QString::fromStdString(movie.getTitulo()),
        QString::fromStdString(movie.getGenero()),
        QString::fromStdString(movie.getDirector()),
        QString::number(movie.getAnio()),
        QString::number(movie.getDuracion()),
        QString::number(movie.getCalificacion(), 'f', 1)
    );

    movieInfoLabel->setText(info);
}

void MainWindow::showSeriesInfo(const Serie& serie)
{
    QString info = QString(R"(
        <div style="color: #2C3E50; font-family: Arial, sans-serif;">
            <h2 style="color: #8E44AD;">%1</h2>
            <hr style="border: 1px solid #ECF0F1;">
            <p><b>Género:</b> %2</p>
            <p><b>Año de inicio:</b> %3</p>
            <p><b>Año de fin:</b> %4</p>
            <p><b>Temporadas:</b> %5</p>
            <p><b>Calificación:</b> <span style="color: #F39C12; font-weight: bold;">★ %6 / 10</span></p>
        </div>
    )").arg(
        QString::fromStdString(serie.getTitulo()),
        QString::fromStdString(serie.getGenero()),
        QString::number(serie.getAnioInicio()),
        QString::number(serie.getAnioFin()),
        QString::number(serie.getNumTemporadas()),
        QString::number(serie.getCalificacion(), 'f', 1)
    );

    seriesInfoLabel->setText(info);
}

int MainWindow::getRatingFromUser()
{
    bool ok;
    int rating = QInputDialog::getInt(
        this,
        "Calificar",
        "Introduce una calificación (1-10):",
        8, 1, 10, 1, &ok
    );

    if (ok) return rating;
    return -1;
}

void MainWindow::onRateMovie()
{
    if (currentMovieIndex < 0) {
        QMessageBox::warning(this, "Advertencia", "Debes seleccionar una película primero");
        return;
    }

    int rating = getRatingFromUser();
    if (rating > 0) {
        peliculas[currentMovieIndex].setCalificacion(rating);
        showMovieInfo(peliculas[currentMovieIndex]);
        QMessageBox::information(this, "Calificación",
            QString("Has calificado '%1' con %2 estrellas")
                .arg(QString::fromStdString(peliculas[currentMovieIndex].getTitulo()))
                .arg(rating));
    }
}

void MainWindow::onPlayMovie()
{
    if (currentMovieIndex < 0) {
        QMessageBox::warning(this, "Advertencia", "Debes seleccionar una película primero");
        return;
    }

    QProgressBar *progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    statusBar()->addWidget(progressBar, 1);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this, progressBar, timer]() {
        static int progress = 0;
        progressBar->setValue(++progress);

        if (progress >= 100) {
            timer->stop();
            statusBar()->removeWidget(progressBar);
            progressBar->deleteLater();
            timer->deleteLater();

            QMessageBox::information(this, "Reproducción Completada",
                QString("Has terminado de ver '%1'")
                    .arg(QString::fromStdString(peliculas[currentMovieIndex].getTitulo())));
        }
    });

    timer->start(50);  // Simulación rápida para demo

    QMessageBox::information(this, "Reproduciendo",
        QString("Reproduciendo '%1'")
            .arg(QString::fromStdString(peliculas[currentMovieIndex].getTitulo())));
}

void MainWindow::onRateSeries()
{
    if (currentSeriesIndex < 0) {
        QMessageBox::warning(this, "Advertencia", "Debes seleccionar una serie primero");
        return;
    }

    int rating = getRatingFromUser();
    if (rating > 0) {
        series[currentSeriesIndex].setCalificacion(rating);
        showSeriesInfo(series[currentSeriesIndex]);
        QMessageBox::information(this, "Calificación",
            QString("Has calificado '%1' con %2 estrellas")
                .arg(QString::fromStdString(series[currentSeriesIndex].getTitulo()))
                .arg(rating));
    }
}

void MainWindow::onViewEpisodes()
{
    if (currentSeriesIndex < 0) {
        QMessageBox::warning(this, "Advertencia", "Debes seleccionar una serie primero");
        return;
    }

    const Serie& serie = series[currentSeriesIndex];
    QString episodesList = QString("<h3>Episodios de %1</h3><hr>")
                               .arg(QString::fromStdString(serie.getTitulo()));

    for (int i = 1; i <= serie.getNumTemporadas(); i++) {
        episodesList += QString("<h4>Temporada %1</h4><ul>").arg(i);

        for (int j = 1; j <= serie.getNumEpisodiosTemporada(i); j++) {
            episodesList += QString("<li>Episodio %1</li>").arg(j);
        }

        episodesList += "</ul>";
    }

    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Episodios");
    dialog->setMinimumSize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(dialog);

    QLabel *episodesLabel = new QLabel(episodesList);
    episodesLabel->setWordWrap(true);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(episodesLabel);

    layout->addWidget(scrollArea);

    QPushButton *closeButton = new QPushButton("Cerrar");
    connect(closeButton, &QPushButton::clicked, dialog, &QDialog::accept);
    layout->addWidget(closeButton);

    dialog->exec();
}

void MainWindow::onViewPortada()
{
    if (currentSeriesIndex < 0) {
        QMessageBox::warning(this, "Advertencia", "Debes seleccionar una serie primero");
        return;
    }

    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Portada");
    dialog->setMinimumSize(400, 500);

    QVBoxLayout *layout = new QVBoxLayout(dialog);

    // Aquí normalmente cargarías una imagen real
    // Como ejemplo, mostramos un label con mensaje
    QLabel *imageLabel = new QLabel();
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setText("Portada de " + QString::fromStdString(series[currentSeriesIndex].getTitulo()));
    imageLabel->setStyleSheet("font-size: 18px; border: 2px solid gray; border-radius: 5px; padding: 100px;");

    layout->addWidget(imageLabel);

    QPushButton *closeButton = new QPushButton("Cerrar");
    connect(closeButton, &QPushButton::clicked, dialog, &QDialog::accept);
    layout->addWidget(closeButton);

    dialog->exec();
}
