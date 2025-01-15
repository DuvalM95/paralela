# Utilizar Debian como base
FROM debian:12

# Actualizar el sistema y herramientas necesarias
RUN apt-get update && apt-get install -y \
    gcc \
    g++ \
    cmake \
    libomp-dev \
    make \
    bash

# Crear un directorio de trabajo
WORKDIR /app

# Comando por defecto (puede ser sobrescrito en el contenedor)
CMD ["/bin/bash"]
