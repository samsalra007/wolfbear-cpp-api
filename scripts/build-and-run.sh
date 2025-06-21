#!/bin/sh

PROJECT_DIR="$( pwd )"

echo "Compilando Wolfbear API"

echo "Creando el directorio $PROJECT_DIR"
rm -rf $PROJECT_DIR/build
mkdir -p $PROJECT_DIR/build

echo "Accediendo al directorio $PROJECT_DIR"
cd $PROJECT_DIR/build

echo "Compilando"
cmake ..
make

echo "Ejecutando API de pruebas"
./wolfbear