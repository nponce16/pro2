/**
 * @file AreaEspera.hh
 * @brief Conjunto de procesos pendientes clasificados por prioridades.
 */

#ifndef AreaEspera_hh
#define AreaEspera_hh

#include "Cluster.hh"
#include "Prioridad.hh"

#ifndef NO_DIAGRAM
#include <map>
#endif

class AreaEspera {

private:
    map<string, Prioridad> m;
    int total_procesos;

public:

//Constructoras

    /** @brief Constructora vacía.
        \pre Cierto.
        \post El resultado es un AreaEspera vacía.
    */
    AreaEspera();

//Modificadoras

    /** @brief Modificadora que añade una prioridad al área de espera.
        \pre No existe en m ninguna key = id.
        \post Se ha añadido a m una key de nombre id y una prioridad vacia.
    */
    void alta_prioridad(const string& id);

    /** @brief Modificadora que elimina una prioridad del área de espera.
        \pre Existe en m una key = id con una prioridad vacia.
        \post Se ha eliminado de m la key = id.
    */
    void baja_prioridad(const string& id);

    /** @brief Modificadora que añade un proceso al área de espera.
        \pre Existe la prioridad en m y no existe el proceso p en esa prioridad.
        \post El proceso se ha añadido a una prioridad con key = id.
    */
    void alta_proceso_espera(const Proceso& p, const string& id);

    /** @brief Modificadora que envía procesos al clúster y los elimina del área de espera.
        \pre n > 0.
        \post Se han enviado n procesos o, si n es mayor a los procesos pendientes, la cantidad de procesos pendientes totales.
    */
    void enviar_procesos_cluster(Cluster& c, int n);

//Consultoras

    /** @brief Consultora que indica si existe una prioridad en el área de espera o no.
        \pre Cierto.
        \post Retorna true si en el parámetro implícito ya existe la prioridad o false en caso contrario.
    */
    bool existe_prioridad(const string& id) const;
    
    /** @brief Consultora que indica si una prioridad es vacía o no.
        \pre Existe la key id_pri en el mapa m.
        \post Retorna true si la prioridad de ID = id_pri es vacia, false si no lo es.
    */
    bool prioridad_vacia(const string& id_pri) const;

    /** @brief Consultora que indica si existe un proceso en una prioridad o no.
        \pre Existe la key id_pri en el mapa m.
        \post Retorna true si el proceso de ID = id_pr existe en la prioridad de ID = id_pri.
    */
    bool existe_proceso_prioridad(const string& id_pri, int id_pr) const;

//Lectura y escritura

    /** @brief Operación de lectura.
        \pre Cierto.
        \post Lee un área de espera.
    */
    void leer_area_espera();

    /** @brief Escribe una prioridad del área de espera.
        \pre Existe la key id_pri en el mapa m.
        \post Se ha escrito por el canal estándar de salida el value con key = id_pri del mapa m del parámetro implícito.
    */
    void imprimir_prioridad_ae(const string& id_pri) const;

    /** @brief Escribe todos los procesos y prioridades del área de espera.
        \pre Cierto.
        \post Se han escrito por el canal estándar de salida los procesos de todas las prioridades del parámetro implícito.
    */
    void imprimir_area_espera() const;

};
#endif
