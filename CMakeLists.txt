cmake_minimum_required(VERSION 3.20)
project(FlowCast VERSION 1.0.0 LANGUAGES CXX)

# Configuración del compilador C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Encontrar Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Directorios de include
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Archivos fuente principales
set(SOURCES
    src/Video.cpp
    src/Pelicula.cpp
    src/serie.cpp
    src/Episodio.cpp
    src/MainWindow.cpp
)

set(HEADERS
    include/Video.h
    include/Pelicula.h
    include/Serie.h
    include/Episodio.h
    include/MainWindow.h
)

# Crear el ejecutable principal
add_executable(FlowCast
    main.cpp  # Asegúrate de que este archivo llama a MainWindow
    ${SOURCES}
    ${HEADERS}
)

# Enlazar con Qt
target_link_libraries(FlowCast
    Qt6::Core
    Qt6::Widgets
)

# Configuraciones específicas de compilador
target_compile_options(FlowCast PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra>
    $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)