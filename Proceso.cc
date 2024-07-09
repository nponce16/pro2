/**
 * @file Proceso.cc
 * @brief Código de la clase Proceso.
 */

#include "Proceso.hh"

Proceso::Proceso() {}

void Proceso::modificar_tiempo(uint t) {
    tiempo -= t;
}

int Proceso::consultar_id() const {
    return ID;
}

int Proceso::consultar_peso() const {
    return peso;
}

int Proceso::consultar_tiempo() const {
    return tiempo;
}

void Proceso::leer_proceso() {
    cin >> ID >> peso >> tiempo;
}

void Proceso::imprimir_proceso() const {
    cout << ID << ' ' << peso << ' ' << tiempo << endl;
}