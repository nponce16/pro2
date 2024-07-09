/**
 * @file Cluster.hh
 * @brief Conjunto de procesadores con forma de árbol binario.
 */

#ifndef Cluster_hh
#define Cluster_hh

#include "Procesador.hh"

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#endif

class Cluster {

private:

    BinTree<string> a;
    map<string, Procesador> m;
    struct stats { // Struct que servirá para guardar las características de un procesador.
        bool cabe = false;
        int hueco;
        int libre;
        int depth = 0;
        string id_proc;
    };

    /** @brief Operación recursiva de construcción de un clúster.
        \pre Cierto.
        \post Se ha añadido un string al arbol a del clúster y un procesador al mapa.
    */
    void i_configurar_cluster(BinTree<string>& a);

    /** @brief Operación recursiva de escritura de la estructura del clúster.
        \pre Cierto.
        \post Se ha escrito por el canal estándar de salida la estructura de a.
    */
    void i_imprimir_estructura_cluster(const BinTree<string>& a) const;

    /** @brief Operación recursiva que indica si un procesador del clúster tiene auxiliares.
        \pre Existe la key id_proc en el mapa m del clúster.
        \post El resultado es true si tiene auxiliares, false si no.
    */
    bool i_proc_tiene_auxiliares(const string& id_proc, const BinTree<string>& a) const;

    /** @brief Operación recursiva que modifica el árbol del clúster.
        \pre Existe la key id_proc en el mapa m del clúster.
        \post Se ha modificado el árbol del parámetro implícito.
    */
    void i_modificar_cluster(string& rt, const string& id_proc, BinTree<string>& a, const BinTree<string>& a_new);

    /** @brief Operación recursiva que mira el id del procesador con mejores características para guardar un proceso.
        \pre Cierto.
        \post Se han modificado los valores de los elementos del struct s.
    */
    void mejor_procesador(const BinTree<string>& a, stats& s, const Proceso& pr, int depth);

    /** @brief
        \pre
        \post
    */
    void eliminar_auxiliares(const BinTree<string>& a);

    /** @brief
        \pre k > 0
        \post
    */
    void i_podar_cluster(BinTree<string>& a, int k);

public:

//Constructoras

    /** @brief Constructora vacía.
        \pre Cierto.
        \post El resultado es un clúster vacío.
    */
    Cluster();

//Modificadoras

    /** @brief Modificadora de clúster.
        \pre Existe la key id_proc en el mapa m del parámetro implícito y corresponden a un procesador sin procesos en ejecución y sin procesadores auxiliares.
        \post Se ha sustituido el nodo id_proc por el árbol de c en el árbol del parámetro implícito. Se ha modificado el mapa m.
    */
    void modificar_cluster(const string& id_proc, const Cluster& c);

    /** @brief
        \pre k > 0 y el primer procesador tiene total Procesos > k.
        \post
    */
    void podar_cluster(int k);

    /** @brief Modificadora que añade un proceso a un procesador del clúster.
        \pre Existe la key id_proc en el mapa m del parámetro implícito que corresponde a un procesador que no contiene pr y tiene espacio en la memoria para colocarlo.
        \post Se ha añadido pr al procesador con ID = id_proc.
    */
    void alta_proceso_procesador(const string& id_proc, const Proceso& pr);

    /** @brief Modificadora que elimina un proceso de un procesador del clúster.
        \pre Existe la key id_proc en el mapa m del parámetro implícito que corresponde a un procesador y el proceso con ID = id_pr está contenido en él.
        \post Se ha eliminado el proceso del procesador.
    */
    void baja_proceso_procesador(const string& id_proc, int id_pr);

    /** @brief Modificadora que avanza el tiempo de ejecución.
        \pre t != 0
        \post Se ha reducido t unidades al tiempo de ejecución de los procesos de todos los procesadores en el clúster y se han eliminado los procesos con tiempo de ejecución = 0.
    */
    void avanzar_tiempo(uint t);

    /** @brief Modificadora que mueve los procesos al principio de la memoria de un procesador del clúster.
        \pre Existe la key id_proc en el mapa m del parámetro implícito.
        \post Se ha modificado el procesador con ID = id_proc
    */
    void compactar_memoria_procesador(const string& id_proc);

    /** @brief Modificadora que mueve los procesos de todos los procesadores al principio de la memoria.
        \pre Cierto.
        \post Se han modificado todos los procesadores del clúster.
    */
    void compactar_memoria_cluster();

    /** @brief Recibe un proceso de área de espera e intenta guardarlo en el procesador con mejores características.
        \pre Cierto.
        \post Si recibido = true, se ha modificado un procesador del clúster, en caso contrario se guarda recibido = false.
    */
    void recibir_proceso(const Proceso& pr, bool& recibido);

//Consultoras

    /** @brief Consultora que indica si existe un procesador en el clúster o no.
        \pre Cierto.
        \post El resultado es true si el existe la key id_proc en el mapa m del parámetro implícito, false en caso contrario.
    */
    bool existe_procesador(const string& id_proc) const;

    /** @brief Consultora que indica si existe un proceso en un procesador del clúster o no.
        \pre Cierto.
        \post El resultado es true si existe la key id_proc en el mapa m del parámetro implícito que corresponde a un procesador y éste contiene un proceso con ID = id_pr,
         false en caso contrario.
    */
    bool existe_proceso_procesador(const string& id_proc, int id_pr) const;

    /** @brief Consultora que indica si cabe un proceso en la memoria de un procesador o no.
        \pre Existe la key id_proc en el mapa m del parámetro implícito que corresponde a un procesador.
        \post Retorna true si se puede guardar el proceso con ID = id_pr en el procesador de la key id_proc, false en caso contrario.
    */
    bool procesador_tiene_espacio(const string& id_proc, int peso) const;

    /** @brief Consultora que indica si un procesador es vacío o no.
        \pre Existe la key id_proc en el mapa m del parámetro implícito que corresponde a un procesador.
        \post Retorna true si el procesador de la key id_proc no tiene procesos en ejecución, false en caso contrario.
    */
    bool procesador_vacio(const string& id_proc) const;

    /** @brief Consultora que indica si un procesador del clúster tiene auxiliares.
        \pre Existe la key id_proc en el mapa m del parámetro implícito que corresponde a un procesador.
        \post El resultado es true el procesador de la key id_proc tiene auxiliares, false en caso contrario.
    */
    bool proc_tiene_auxiliares(const string& id_proc) const;

    int pr_primer_proc() const;

//Lectura y escritura

    /** @brief Operación de lectura.
        \pre Cierto.
        \post Se ha leído un clúster.
    */
    void configurar_cluster();

    /** @brief Escribe un procesador del clúster.
        \pre Cierto.
        \post Se ha escrito por el canal estándar de salida el procesador con key id_proc del mapa m del parámetro implícito.
    */
    void imprimir_procesador_cluster(const string& id_proc) const;

    /** @brief Escribe los procesadores del clúster.
        \pre Cierto.
        \post Se han escrito por el canal estándar de salida los procesadores del parámetro implícito en orden creciente según el identificador.
    */
    void imprimir_procesadores_cluster() const;

    /** @brief Escribe la estructura del clúster.
        \pre Cierto.
        \post Se ha escrito por el canal estándar de salida la estructura del parámetro implícito.
    */
    void imprimir_estructura_cluster() const;

};
#endif
