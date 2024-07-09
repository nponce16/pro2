/**
    @file Cluster.cc
    @brief Código de la clase Cluster.
*/

#include "Cluster.hh"

//private

void Cluster::i_configurar_cluster(BinTree<string>& a) {
    string id_proc;
    int mem;
    cin >> id_proc;
    if (id_proc != "*") {
        cin >> mem;
        Procesador p(id_proc, mem);
        m.insert({id_proc, p});
        BinTree<string> a_izq;
        i_configurar_cluster(a_izq); // Llamada recursiva a la función con el árbol de la izquierda.
        BinTree<string> a_der;
        i_configurar_cluster(a_der); // Llamada recursiva a la función con el árbol de la derecha.
        a = BinTree<string> (id_proc, a_izq, a_der);
    }
}

void Cluster::i_imprimir_estructura_cluster(const BinTree<string>& a) const {
    if (a.empty()) cout << ' ';
    else {
        cout << '(' << a.value();
        i_imprimir_estructura_cluster(a.left()); // Llamada recursiva a la función con el árbol de la izquierda.
        i_imprimir_estructura_cluster(a.right()); // Llamada recursiva a la función con el árbol de la derecha.
        cout << ')';
    }
}

bool Cluster::i_proc_tiene_auxiliares(const string& id_proc, const BinTree<string>& a) const {
    if (not a.empty()) {
        if (a.value() == id_proc) return not (a.left().empty() and a.right().empty());
        return i_proc_tiene_auxiliares(id_proc, a.left()) or i_proc_tiene_auxiliares(id_proc, a.right()); // Llamada recursiva a la función con el árbol de la izquierda y luego el de la derecha.
    }
    return false;
}

void Cluster::i_modificar_cluster(string& rt, const string& id_proc, BinTree<string>& a, const BinTree<string>& a_new) {
    if (not a.empty()) {
        if (a.value() == id_proc) a = a_new;
        else {
            BinTree<string> a_izq = a.left();
            i_modificar_cluster(rt, id_proc, a_izq, a_new); // Llamada recursiva a la función con el árbol de la izquierda.
            BinTree<string> a_der = a.right();
            i_modificar_cluster(rt, id_proc, a_der, a_new); // Llamada recursiva a la función con el árbol de la derecha.
            rt = a.value();
            a = BinTree<string> (rt, a_izq, a_der);
        }
    }
}

void Cluster::mejor_procesador(const BinTree<string>& ar, stats& s, const Proceso& pr, int depth) {
    if (not ar.empty()) {
        map<string, Procesador>::const_iterator it = m.find(ar.value());
        if (not it->second.existe_proceso(pr.consultar_id())) { // Consulta si existe el proceso en el procesador al que apunta el iterador.
            if (it->second.tiene_espacio(pr.consultar_peso())) { // Consulta si el procesador al que apunta el iterador tiene espacio para añadir el proceso.
                if (not s.cabe) {
                    s.cabe = true;
                    s.hueco = it->second.hueco_menos_ajustado(); // Llamada a una función de la clase Procesador.
                    s.libre = it->second.memoria_libre() - pr.consultar_peso(); // Llamada a una función de la clase Procesador.
                    s.id_proc = ar.value();
                    s.depth = depth;
                }
                else if (s.hueco < it->second.hueco_menos_ajustado()) { // Consulta cuál és el hueco más ajustado.
                    s.hueco = it->second.hueco_menos_ajustado();
                    s.libre = it->second.memoria_libre() - pr.consultar_peso();
                    s.id_proc = ar.value();
                    s.depth = depth;
                }
                else if (s.hueco == it->second.hueco_menos_ajustado()) { // Caso de empate entre huecos ajustados.
                    if (s.libre > it->second.memoria_libre() - pr.consultar_peso()) { // Consulta qué procesador tiene más memoria libre.
                        s.libre = it->second.memoria_libre() - pr.consultar_peso();
                        s.id_proc = ar.value();
                        s.depth = depth;
                    }
                    else if (s.libre == it->second.memoria_libre() - pr.consultar_peso()) { // Caso de empate entre las memorias libres.
                        if (s.depth > depth) {  // Consulta qué procesador tiene menor profundidad.
                            s.id_proc = ar.value();
                            s.depth = depth;
                        }
                    }
                }
            }
        }
        mejor_procesador(ar.left(), s, pr, depth + 1); // Llamada recursiva a la función con el árbol de la izquierda.
        mejor_procesador(ar.right(), s, pr, depth + 1); // Llamada recursiva a la función con el árbol de la derecha.
    }

}

void Cluster::eliminar_auxiliares(const BinTree<string>& a) {
    if (not a.empty()) {
        m.erase(a.value());
        eliminar_auxiliares(a.left());
        eliminar_auxiliares(a.right());
    }
}

void Cluster::i_podar_cluster(BinTree<string>& a, int k) {
    if (not a.empty()) {
        map<string, Procesador>::const_iterator it = m.find(a.value());
        if (it->second.total_procesos() >= k) {
            BinTree<string> left = a.left();
            i_podar_cluster(left, k);
            BinTree<string> right = a.right();
            i_podar_cluster(right, k);
            string rt = a.value();
            a = BinTree<string> (rt, left, right);
        }
        else {
            eliminar_auxiliares(a);
            a = BinTree<string> ();
        }
    }
}

//public

Cluster::Cluster() {}

void Cluster::modificar_cluster(const string& id_proc, const Cluster& c) {
    m.erase(id_proc);
    map<string, Procesador>::const_iterator it = c.m.begin();
    while (it != c.m.end()) {
        m.insert({it->first, it->second});
        ++it;
    }
    string rt = a.value();
    i_modificar_cluster(rt, id_proc, a, c.a); // Llamada a función inmersiva.
}

void Cluster::podar_cluster(int k) {
    int old_size = m.size();
    i_podar_cluster(a, k);
    int poda = old_size - m.size();
    cout << "Poda " << poda << endl;
}

void Cluster::alta_proceso_procesador(const string& id_proc, const Proceso& pr) {
    m.find(id_proc)->second.alta_proceso(pr); // Llamada a una función de la clase Procesador.
}

void Cluster::baja_proceso_procesador(const string& id_proc, int id_pr) {
    m.find(id_proc)->second.baja_proceso(id_pr); // Llamada a una función de la clase Procesador.
}

void Cluster::avanzar_tiempo(uint t) {
    map<string, Procesador>::iterator it = m.begin();
    while (it != m.end()) {
        it->second.avanzar_tiempo_procesos(t); // Llamada a una función de la clase Procesador.
        ++it;
    }
}

void Cluster::compactar_memoria_procesador(const string& id_proc) {
    m.find(id_proc)->second.compactar_memoria(); // Llamada a una función de la clase Procesador.
}

void Cluster::compactar_memoria_cluster() {
    map<string, Procesador>::iterator it = m.begin();
    while (it != m.end()) {
        it->second.compactar_memoria(); // Llamada a una función de la clase Procesador.
        ++it;
    }
}

void Cluster::recibir_proceso(const Proceso& pr, bool& recibido) {
    stats s;
    mejor_procesador(a, s, pr, s.depth); // Llamada a una función privada.
    if (s.cabe) {
        alta_proceso_procesador(s.id_proc, pr); // Llamada a una función de la clase Procesador.
        recibido = true;
    }
}

bool Cluster::existe_procesador(const string& id_proc) const { 
    return m.find(id_proc) != m.end();
}

bool Cluster::existe_proceso_procesador(const string& id_proc, int id_pr) const {
    return m.find(id_proc)->second.existe_proceso(id_pr); // Llamada a una función de la clase Procesador.
}

bool Cluster::procesador_tiene_espacio(const string& id_proc, int peso) const {
    return m.find(id_proc)->second.tiene_espacio(peso); // Llamada a una función de la clase Procesador.
}

bool Cluster::procesador_vacio(const string& id_proc) const {
    return m.find(id_proc)->second.vacio(); // Llamada a una función de la clase Procesador.
}

bool Cluster::proc_tiene_auxiliares(const string& id_proc) const {
    return i_proc_tiene_auxiliares(id_proc, a); // Llamada a función inmersiva.
}

int Cluster::pr_primer_proc() const {
    map<string, Procesador>::const_iterator it = m.find(a.value());
    return it->second.total_procesos();
}

void Cluster::configurar_cluster() {
    m.clear();
    i_configurar_cluster(a); // Llamada a función inmersiva.
}

void Cluster::imprimir_procesador_cluster(const string& id_proc) const {
    m.find(id_proc)->second.imprimir_procesador(); // Llamada a una función de la clase Procesador.
}

void Cluster::imprimir_procesadores_cluster() const {
    map<string, Procesador>::const_iterator it = m.begin();
    while (it != m.end()) {
        cout << it->first << endl;
        it->second.imprimir_procesador(); // Llamada a una función de la clase Procesador.
        ++it;
    }
}

void Cluster::imprimir_estructura_cluster() const {
    i_imprimir_estructura_cluster(a); // Llamada a función inmersiva.
    cout << endl;
}