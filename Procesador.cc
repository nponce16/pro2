/**
 * @file Procesador.cc
 * @brief Código de la clase Procesador.
 */

#include "Procesador.hh"

//private

void Procesador::evaluar_huecos(int dr_mem) {
    map<int, Proceso>::const_iterator it1 = mem.find(dr_mem);
    int pos_final = dr_mem + it1->second.consultar_peso(); // Variable que guarda la última posición que ocupa el proceso en la memoria.
    int pos_ini = dr_mem;
    int tam_hueco_izq = 0;
    int tam_hueco_der = 0;
    map<int, set<int> >::iterator it2 = hueco.begin();

    if (it1 != mem.begin()) { // Consulta si hay un proceso más a la izquierda.
        --it1;
        pos_ini = it1->first + it1->second.consultar_peso(); // Se actualiza la variable con la posición de memoria donde empieza el hueco a la izquierda.
        if (pos_ini != dr_mem) { // Consulta si hay un hueco entre un proceso a la izquierda y el proceso a eliminar.
            tam_hueco_izq = dr_mem - pos_ini;
            it2 = hueco.find(tam_hueco_izq);
            if (it2 != hueco.end()) { // Consulta si existe un hueco de tamaño tam_hueco_izq.
                it2->second.erase(pos_ini);
                if (it2->second.empty()) hueco.erase(it2); // Consulta si existe una dirección de memoria con el tamaño del hueco, si la hay, la borra.
            }
        }
        ++it1;
    }
    else { // Consulta si hay un hueco entre la posición de memoria 0 y el proceso a eliminar.
            if (dr_mem != 0) { // Consulta si la dirección de memoria es distina a 0.
                pos_ini = 0;
                tam_hueco_izq = dr_mem;
                it2 = hueco.find(tam_hueco_izq);
                if (it2 != hueco.end()) {
                    it2->second.erase(0);
                    if(it2->second.empty()) hueco.erase(it2);
                }
            }
    }

    if (pos_final != c_max) { // Consulta si hay un proceso a la derecha.
        ++it1;
        if (it1 != mem.end()) tam_hueco_der = it1->first - pos_final; // Si se cumple hay un hueco entre un proceso a la derecha y el proceso a eliminar.
        else tam_hueco_der = c_max - pos_final; // Hay un hueco entre la última posición de memoria y el proceso a eliminar.
        
        if (tam_hueco_der != 0) {
            it2 = hueco.find(tam_hueco_der);
            if (it2 != hueco.end()) {
                it2->second.erase(pos_final);
                if (it2->second.empty()) hueco.erase(it2);
            }
        }
        --it1;
    }

    int nuevo_hueco = it1->second.consultar_peso() + tam_hueco_izq + tam_hueco_der; // Variable que guarda la posición de memoria del hueco que deja el proceso eliminado.
    it2 = hueco.find(nuevo_hueco);
    if (it2 != hueco.end()) it2->second.insert(pos_ini);
    else hueco.insert({nuevo_hueco, {pos_ini}});
}

//public

Procesador::Procesador() {}

Procesador::Procesador(const string& id_proc, int c) {
    ID = id_proc;
    c_max = c;
    hueco.insert({c, {0}});
}

void Procesador::alta_proceso(const Proceso& pr) {
    map<int, set<int> >::iterator it = hueco.end();
    --it;
    int dr = *(it->second.begin());
    int espacio_libre = it->first - pr.consultar_peso(); // Variable que guarda el epacio que queda al añadir el proceso en el hueco.
    it->second.erase(dr);
    if (it->second.empty()) hueco.erase(it);
    if (espacio_libre != 0) { // Consulta si queda algún hueco despues de añadir el proceso.
        int dr_hueco_nuevo = dr + pr.consultar_peso();
        it = hueco.find(espacio_libre);
        if (it != hueco.end()) it->second.insert(dr_hueco_nuevo);
        else hueco.insert({espacio_libre, {dr_hueco_nuevo}});
    }
    direc.insert({pr.consultar_id(), dr});
    mem.insert({dr, pr});
}

void Procesador::baja_proceso(int id_pr) {
    map<int, int>::iterator it = direc.find(id_pr);
    int dr = it->second;
    evaluar_huecos(dr);
    direc.erase(id_pr);
    mem.erase(dr);
}

void Procesador::compactar_memoria() {
    if (not hueco.empty()) {
        map<int, Proceso>::iterator it = mem.begin();
        hueco.clear();
        int x = 0; // Variable que guarda la posición de memoria donde hay que mover un proceso.
        int peso;
        while (it != mem.end()) { // Bucle que recorre el mapa de la memoria del procesador.
            peso = it->second.consultar_peso();
            if (it->first != x) { // Consulta si la dirección de memoria es distinta a la dirección donde se ha de mover el proceso.
                Proceso p = it->second;
                int dr = it->first;
                int id = it->second.consultar_id();
                ++it;
                mem.erase(dr);
                direc.erase(id);
                mem.insert({x, p});
                direc.insert({id, x});
            }
            else ++it;
            x += peso;
        }
        hueco.insert({(c_max - x), set<int>{x}});
    }
}

void Procesador::avanzar_tiempo_procesos(uint t) {
    map<int, Proceso>::iterator it = mem.begin();
    while (it != mem.end()) { // Bucle que recorre el mapa de memoria modificando el tiempo de todos los procesos guardados.
        it->second.modificar_tiempo(t); // Llamada a una función de la clase Proceso.
        int t_aux = it->second.consultar_tiempo();
        int id_aux = it->second.consultar_id();
        ++it;
        if (t_aux <= 0) baja_proceso(id_aux);
    }
}

bool Procesador::existe_proceso(int id_pr) const {
    map<int, int>::const_iterator it = direc.find(id_pr);
    return it != direc.end();
}

bool Procesador::tiene_espacio(int peso) const {
    if (peso <= c_max) { // Consulta si el peso del proceso es menor o igual que la capacidad máxima del Procesador.
        if (hueco.empty()) return false;
        map<int, set<int> >::const_iterator it = hueco.end();
        --it;
        return not (it->first < peso);
    }
    return false;
}

bool Procesador::vacio() const {
    return mem.empty();
}

int Procesador::hueco_menos_ajustado() const {
    map<int, set<int> >::const_iterator it = hueco.end();
    --it;
    return it->first;
}

int Procesador::memoria_libre() const {
    map<int, set<int> >::const_iterator it = hueco.begin();
    int mem_libre = 0;
    while (it != hueco.end()) { // Bucle que suma todos los huecos en la memoria para saber el espacio libre que hay en el procesador.
        mem_libre = mem_libre + (it->first * it->second.size());
        ++it;
    }
    return mem_libre;
}

int Procesador::total_procesos() const {
    return mem.size();
}

void Procesador::imprimir_procesador() const {
    map<int, Proceso>::const_iterator it = mem.begin();
    while (it != mem.end()) {
        cout << it->first << ' ';
        it->second.imprimir_proceso();  // Llamada a una función de la clase Proceso.
        ++it;
    }
}