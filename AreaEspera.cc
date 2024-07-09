/**
 * @file AreaEspera.cc
 * @brief Código de la clase AreaEspera.
 */

#include "AreaEspera.hh"

AreaEspera::AreaEspera() {}

void AreaEspera::alta_prioridad(const string& id) {
    Prioridad pri;
    m.insert({id, pri});
}

void AreaEspera::baja_prioridad(const string& id) {
    m.erase(id);
}

void AreaEspera::alta_proceso_espera(const Proceso& p, const string& id) {
    m.find(id)->second.guardar_proceso(p);
}

void AreaEspera::enviar_procesos_cluster(Cluster& c, int n) {
    map<string, Prioridad>::iterator it = m.begin();
    while (it != m.end() and n > 0) { // Bucle que recorre el mapa m hasta que no haya mas prioridades o hasta que se hayan enviado n procesos.
        if (not it->second.vacia()) it->second.enviar_procesos(c, n);
        ++it;
    } 
}

bool AreaEspera::existe_prioridad(const string& id) const {
    map<string, Prioridad>::const_iterator it = m.find(id);
    return it != m.end();
}

bool AreaEspera::prioridad_vacia(const string& id_pri) const {
    return m.find(id_pri)->second.vacia();
}

bool AreaEspera::existe_proceso_prioridad(const string& id_pri, int id_pr) const {
    return m.find(id_pri)->second.existe_proceso(id_pr);
}

void AreaEspera::leer_area_espera() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) { // Bucle que lee n prioridades y las guarda en el mapa m del área de espera.
        string key;
        cin >> key;
        Prioridad pri;
        m.insert({key, pri});
    }
}

void AreaEspera::imprimir_prioridad_ae(const string& id_pri) const {
    m.find(id_pri)->second.imprimir_prioridad();
}

void AreaEspera::imprimir_area_espera() const {
    map<string, Prioridad>::const_iterator it = m.begin();
    while (it != m.end()) { // Bucle que recorre el mapa m de área de espera e imprime todas las prioridades.
        cout << it->first << endl;
        it->second.imprimir_prioridad();
        ++it;
    }
}