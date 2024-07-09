/**
  @file Prioridad.cc
  @brief Código de la clase Prioridad.
*/

#include "Prioridad.hh"

Prioridad::Prioridad() {
    enviados = 0;
    rechazos = 0;
}

void Prioridad::guardar_proceso(const Proceso& p) {
    lp.push_back(p);
    sp.insert(p.consultar_id());
}

void Prioridad::enviar_procesos(Cluster& c, int& n) {
    list<Proceso>::const_iterator it = lp.begin();
    int size = lp.size();
    while (it != lp.end() and size != 0 and n != 0) { // Consulta si recibido es cierto o si no lo es.
        Proceso pr = *(it);
        bool recibido = false;
        c.recibir_proceso(pr, recibido); // Llamada a una función de la clase Cluster.
        if (not recibido) { // Consulta si recibido es cierto o si no lo es.
            ++rechazos;
            lp.push_back(pr); // Agrega el proceso al final de la lista.
        }
        else {
            ++enviados;
            --n;
            sp.erase(pr.consultar_id());
        }
        ++it;
        --size;
        lp.pop_front(); // Elimina el proceso más antiguo.
    }
}

bool Prioridad::vacia() const {
    return lp.empty(); 
}

bool Prioridad::existe_proceso(int id) const {
    set<int>::const_iterator it = sp.find(id);
    return it != sp.end();
}

void Prioridad::imprimir_prioridad() const {
    list<Proceso>::const_iterator it = lp.begin();
    while (it != lp.end()) { // Bucle que recorre la lista lp hasta que el iterador llegue a lp.end().
        (*it).imprimir_proceso();
        ++it;
    }
    cout << enviados << ' ' << rechazos << endl;
}