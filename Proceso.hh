/**
 * @file Proceso.hh
 * @brief Representa un proceso con atributos id, peso y tiempo.
 */

#ifndef Proceso_hh
#define Proceso_hh

#ifndef NO_DIAGRAM
#include <iostream>
#include <string>
using namespace std;
#endif

class Proceso {

private:

    int ID;
    int peso;
    int tiempo;

public:

//Constructoras

    /** @brief Creadora por defecto.
        \pre Cierto.
        \post El resultado es un proceso vacío.
    */
    Proceso();

//Modificadoras

    /** @brief Modificadora del tiempo de un proceso.
        \pre t != 0.
        \post Se ha reducido t unidades al tiempo de ejecución del parámetro implícito.
    */
    void modificar_tiempo(uint t);

//Consultoras

    /** @brief Consultora que indica el identificador.
        \pre Cierto.
        \post El resultado es el ID del parámetro implícito.
    */
    int consultar_id() const;

    /** @brief Consultora que indica el peso.
        \pre Cierto.
        \post El resultado es el peso del parámetro implícito.
    */
    int consultar_peso() const;

    /** @brief Consultora que indica el tiempo de ejecución.
        \pre Cierto.
        \post El resultado es el tiempo del parámetro implícito.
    */
    int consultar_tiempo() const;

//Lectura y escritura

    /** @brief Operación de lectura.
        \pre Cierto.
        \post Lee un proceso.
    */
    void leer_proceso();

    /** @brief Escribe la información del proceso.
        \pre Cierto.
        \post Se ha escrito por el canal estándar de salida los atributos del parámetro implícito.
    */
    void imprimir_proceso() const;
};
#endif
