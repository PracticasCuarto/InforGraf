#!/bin/bash

# Nombre del archivo Makefile
MAKEFILE="Makefile"

# Comprobamos si el archivo Makefile existe en el directorio actual
if [ ! -f "$MAKEFILE" ]; then
  echo "El archivo $MAKEFILE no se encuentra en el directorio actual."
  exit 1
fi

# Compilamos el programa utilizando make
make

# Comprobamos si la compilación fue exitosa
if [ $? -eq 0 ]; then
  # Ejecutamos el programa "tests"
  ./exec/main
else
  echo "La compilación ha fallado. Por favor, corrige los errores antes de ejecutar el programa."
fi
