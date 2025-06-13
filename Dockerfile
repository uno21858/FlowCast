# Dockerfile for FlowCast Qt6 GUI
FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=America/Mexico_City

# Install system dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    pkg-config \
    wget \
    curl \
    qt6-base-dev \
    qt6-tools-dev \
    qt6-base-dev-tools \
    qt6-qpa-plugins \
    libx11-6 \
    libxext6 \
    libxrender1 \
    libxtst6 \
    libxi6 \
    libgl1-mesa-glx \
    libglu1-mesa-dev \
    libglib2.0-0 \
    fonts-dejavu-core \
    gdb \
    valgrind \
    vim \
    nano \
    tree \
    && rm -rf /var/lib/apt/lists/*

# Set Qt environment variables
ENV QT_X11_NO_MITSHM=1
ENV QT_XKB_CONFIG_ROOT=/usr/share/X11/locale
ENV QT_QPA_PLATFORM_PLUGIN_PATH=/usr/lib/x86_64-linux-gnu/qt6/plugins
ENV QT_PLUGIN_PATH=/usr/lib/x86_64-linux-gnu/qt6/plugins
ENV LD_LIBRARY_PATH=/usr/lib/x86_64-linux-gnu:/usr/local/lib

# Create non-root user
RUN useradd -m -s /bin/bash -G audio,video developer && \
    echo "developer:developer" | chpasswd

USER developer
WORKDIR /home/developer/app

# Copy project files
COPY --chown=developer:developer . .

# Create build and data directories
RUN mkdir -p build data logs

# Build the project
WORKDIR /home/developer/app/build
RUN cmake .. && make -j$(nproc)

WORKDIR /home/developer/app

# Make scripts executable if present
RUN chmod +x scripts/*.sh 2>/dev/null || true

EXPOSE 8080

CMD ["./build/FlowCast"]