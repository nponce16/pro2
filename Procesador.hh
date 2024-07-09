/**
 * @file Procesador.hh
 * @brief Almacenamiento de procesos con espacio limitado.
 */

#ifndef Procesador_hh
#define Procesador_hh

#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include <map>
#include <set>
#endif

class Procesador {

private:

    string ID;
    map<int, Proceso> mem; /** @brief map<direc_mem, Proceso> */
    map<int, int> direc; /** @brief map<id_pr, direc_mem> */
    map<int, set<int> > hueco; /** @brief map<tam(hueco), set<direc_memoria> > */
    int c_max; /** @brief capacidad máxima de memoria del procesador */

    /** @brief Operación que agreganda un hueco que deja un proceso al ser eliminado y junta los huecos contíguos en caso de que haya.
        \pre Existe dr_mem en el mapa mem y direc.
        \post Se ha modificado el mapa hueco. 
    */
    void evaluar_huecos(int dr_mem);

public:

//Constructoras

    /** @brief Constructora vacía.
        \pre Cierto.
        \post El resultado es un procesador vacío.
    */
    Procesador();

    /** @brief Constructora por parámetros.
        \pre Cierto.
        \post El resultado es un procesador con ID y c_max proporcionados.
    */
    Procesador(const string& id_proc, int c);

//Modificadoras

    /** @brief Modificadora que añade un proceso a un procesador.
        \pre No existe un proceso igual a pr y hay un hueco con el mismo tamaño en el mapa hueco.
        \post Se ha añadido el proceso pr al mapa mem y su dirección de memoria en el mapa direc, y se ha eliminado el hueco del mapa hueco.
    */
    void alta_proceso(const Proceso& pr);

    /** @brief Modificadora que elimina un proceso de un procesador cuando termina de ejecutarse.
        \pre Existe la key id_pr en el mapa mem y direc.
        \post Se ha eliminado la key id_pr del mapa mem y direc, también se ha modificado el mapa hueco.
    */
    void baja_proceso(int id_pr); 

    /** @brief Modificadora que mueve los procesos al principio de la memoria de un procesador.
        \pre Cierto.
        \post Se han modificado todos los mapas del parámetro implícito sin dejar huecos entre los procesos guardados en la memoria.
    */
    void compactar_memoria();

    /** @brief Modificadora que avanza el tiempo de los procesos.
        \pre Existe proceso p en el procesador y t > 0.
        \post Se ha modificado el tiempo de ejecución de todos los procesos del parámetro implícito.
    */
    void avanzar_tiempo_procesos(uint t);


//Consultoras

    /** @brief Consultora que indica si existe un proceso en el procesador o no.
        \pre Cierto.
        \post Retorna true si en el mapa mem existe la key id_pr, false en caso contrario.
    */
    bool existe_proceso(int id_pr) const;

    /** @brief Consultora que indica si cabe un proceso en la memoria o no.
        \pre Cierto.
        \post Retorna true si se puede guardar existe una key en el mapa hueco que sea mayor o igual a peso, false en caso contrario.
    */
    bool tiene_espacio(int peso) const;

    /** @brief Consultora que indica si el procesador es vacío.
        \pre Cierto.
        \post Retorna true si el mapa mem no contiene ningún elemento, false en caso contrario.
    */
    bool vacio() const;

    /** @brief Consultora que indica el tamaño del hueco menos ajustado al tamaño del proceso evaluado.
        \pre tam_pr > 0.
        \post Retorna la key con el elemento más grande que cumple ser más grande o igual que tam_pr.
    */
    int hueco_menos_ajustado() const;

    /** @brief Consultora que indica la memoria libre del procesador.
        \pre Cierto.
        \post Retorna un entero que es la suma de todos los elementos guardados en el mapa hueco.
    */
    int memoria_libre() const;

    /** @brief 
        \pre Cierto.
        \post Retorna los Procesos totales que hay guardados en el mapa mem.
    */
   int total_procesos() const;

//Lectura y escritura

    /** @brief Escribe los procesos de dicho procesador por orden creciente de primera posición de memoria.
        \pre Cierto.
        \post Se han escrito por el canal estándar de salida los procesos del parámetro implícito por orden ascendiente.
    */
    void imprimir_procesador() const;

};
#endif
