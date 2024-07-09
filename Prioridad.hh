/**
 * @file Prioridad.hh
 * @brief Clase para clasificar a los procesos.
 */

#ifndef Prioridad_hh
#define Prioridad_hh

#include "Cluster.hh"

#ifndef NO_DIAGRAM
#include <list>
#include <set>
#endif

class Prioridad {

private:
    list<Proceso> lp;
    set<int> sp;
    int enviados;
    int rechazos;

public:

//Constructoras

    /** @brief Creadora por defecto.
        \pre Cierto.
        \post El resultado es una prioridad vacía con enviados y rechazados igual a 0.
    */
    Prioridad();

//Modificadoras

    /** @brief Modificadora que añade un proceso a una prioridad.
        \pre No existe ningún proceso p en la lista lp.
        \post Se añade un proceso al final de la lista lp del parámetro implícito.
    */
    void guardar_proceso(const Proceso& p);

    /** @brief Modificadora que elimina los procesos de la prioridad que pueden enviarse al Clúster.
        \pre La lista lp no es vacía y n > 0.
        \post Se han eliminado los procesos que pudieron ser enviados y se han vuelto a añadir los rechazados.
    */
    void enviar_procesos(Cluster& c, int& n);

//Consultoras

    /** @brief Consultora que indica si la prioridad es vacia.
        \pre Cierto.
        \post Retorna true si lp no contiene ningún elemento, false en caso contrario.
    */
    bool vacia() const;

    /** @brief Consultora que indica si existe un proceso en la prioridad o no.
        \pre Cierto.
        \post Retorna true si en la lista lp ya existe el proceso, false en caso contrario.
    */
    bool existe_proceso(int id) const;

//Lectura y escritura

    /** @brief Escribe los procesos de una prioridad.
        \pre Cierto.
        \post Se han escrito por el canal estándar de salida la lista lp del parámetro implícito.
    */
    void imprimir_prioridad() const;

};
#endif
