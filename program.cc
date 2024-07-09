/**
    @file program.cc
    @brief Programa principal
    @mainpage Práctica PRO2. Simulación del rendimiento de procesadores interconectados.
    El proyecto consiste en simular el funcionamiento de una arquitectura multiprocesador en forma de árbol binario,
    donde cada procesador trabaja con su propia memoria y puede ejecutar múltiples procesos simultáneamente. El objetivo
    es desarrollar un sistema que permita la gestión de procesos pendientes, su ejecución en el clúster y el seguimiento del
    tiempo restante para la finalización de cada proceso.
*/

#include "Cluster.hh"
#include "AreaEspera.hh"

int main() {
    Cluster c;
    AreaEspera a;
    c.configurar_cluster();
    a.leer_area_espera();

    string comando; //Código de operación.
    cin >> comando;
    while(comando != "fin") {

        //configurar_cluster
        if (comando == "configurar_cluster" or comando == "cc") {
            cout << '#' << comando << endl;
            c.configurar_cluster();
        }

        //modificar_cluster
        else if (comando == "modificar_cluster" or comando == "mc") {
            string id_proc;
            cin >> id_proc;
            cout << '#' << comando << ' ' << id_proc << endl;
            Cluster c_new;
            c_new.configurar_cluster();
            if (not c.existe_procesador(id_proc)) cout << "error: no existe procesador" << endl;
            else if (not c.procesador_vacio(id_proc)) cout << "error: procesador con procesos" << endl;
            else if (c.proc_tiene_auxiliares(id_proc)) cout << "error: procesador con auxiliares" << endl;
            else c.modificar_cluster(id_proc, c_new);
        }

        //alta_prioridad
        else if (comando == "alta_prioridad" or comando == "ap") {
            string id_pri;
            cin >> id_pri;
            cout << '#' << comando << ' ' << id_pri << endl;
            if (a.existe_prioridad(id_pri)) cout << "error: ya existe prioridad" << endl;
            else a.alta_prioridad(id_pri);
        }

        //baja_prioridad
        else if (comando == "baja_prioridad" or comando == "bp") {
            string id_pri;
            cin >> id_pri;
            cout << '#' << comando << ' ' << id_pri << endl;
            if (not a.existe_prioridad(id_pri)) cout << "error: no existe prioridad" << endl;
            else if(not a.prioridad_vacia(id_pri)) cout << "error: prioridad con procesos" << endl;
            else a.baja_prioridad(id_pri);
        }

        //alta_proceso_espera
        else if (comando == "alta_proceso_espera" or comando == "ape") {
            string id_pri;
            cin >> id_pri;
            Proceso pr;
            pr.leer_proceso();
            cout << '#' << comando << ' ' << id_pri << ' ' << pr.consultar_id() << endl;
            if (not a.existe_prioridad(id_pri)) cout << "error: no existe prioridad" << endl;
            else if (a.existe_proceso_prioridad(id_pri, pr.consultar_id())) cout << "error: ya existe proceso" << endl;
            else a.alta_proceso_espera(pr, id_pri);
        }

        //alta_proceso_procesador
        else if (comando == "alta_proceso_procesador" or comando == "app") {
            string id_proc;
            cin >> id_proc;
            Proceso pr;
            pr.leer_proceso();
            cout << '#' << comando << ' ' << id_proc << ' ' << pr.consultar_id() << endl;
            if (not c.existe_procesador(id_proc)) cout << "error: no existe procesador" << endl;
            else if (c.existe_proceso_procesador(id_proc, pr.consultar_id())) cout << "error: ya existe proceso" << endl;
            else if (not c.procesador_tiene_espacio(id_proc, pr.consultar_peso())) cout << "error: no cabe proceso" << endl;
            else c.alta_proceso_procesador(id_proc, pr);
        }

        //baja_proceso_procesador
        else if (comando == "baja_proceso_procesador" or comando == "bpp") {
            string id_proc;
            int id_pr;
            cin >> id_proc >> id_pr;
            cout << '#' << comando << ' ' << id_proc << ' ' << id_pr << endl;
            if (not c.existe_procesador(id_proc)) cout << "error: no existe procesador" << endl;
            else if (not c.existe_proceso_procesador(id_proc, id_pr)) cout << "error: no existe proceso" << endl;
            else c.baja_proceso_procesador(id_proc, id_pr);
        }

        //enviar_proceso_cluster
        else if (comando == "enviar_procesos_cluster" or comando == "epc") {
            int n;
            cin >> n;
            cout << '#' << comando << ' ' << n << endl;
            a.enviar_procesos_cluster(c, n);
        }

        //avanzar_tiempo
        else if (comando == "avanzar_tiempo" or comando == "at") {
            uint t;
            cin >> t;
            cout << '#' << comando << ' ' << t << endl;
            c.avanzar_tiempo(t);
        }

        //imprimir_prioridad
        else if (comando == "imprimir_prioridad" or comando == "ipri") {
            string id_pri;
            cin >> id_pri;
            cout << '#' << comando << ' ' << id_pri << endl;
            if (not a.existe_prioridad(id_pri)) cout << "error: no existe prioridad" << endl;
            else a.imprimir_prioridad_ae(id_pri);
        }

        //imprimir_area_espera
        else if (comando == "imprimir_area_espera" or comando == "iae") {
            cout << '#' << comando << endl;
            a.imprimir_area_espera();
        }

        //imprimir_procesador
        else if (comando == "imprimir_procesador" or comando == "ipro") {
            string id_proc;
            cin >> id_proc;
            cout << '#' << comando << ' ' << id_proc << endl;
            if (not c.existe_procesador(id_proc)) cout << "error: no existe procesador" << endl;
            else c.imprimir_procesador_cluster(id_proc);
        }

        //imprimir_procesadores_cluster
        else if (comando == "imprimir_procesadores_cluster" or comando == "ipc") {
            cout << '#' << comando << endl;
            c.imprimir_procesadores_cluster();
        }

        //imprimir_estructura_cluster
        else if (comando == "imprimir_estructura_cluster" or comando == "iec") {
            cout << '#' << comando << endl;
            c.imprimir_estructura_cluster();
        }

        //compactar_memoria_procesador
        else if (comando == "compactar_memoria_procesador" or comando == "cmp") {
            string id_proc;
            cin >> id_proc;
            cout << '#' << comando << ' ' << id_proc << endl;
            if (not c.existe_procesador(id_proc)) cout << "error: no existe procesador" << endl;
            else c.compactar_memoria_procesador(id_proc);
        }

        //compactar_memoria_cluster
        else if (comando == "compactar_memoria_cluster" or comando == "cmc") {
            cout << '#' << comando << endl;
            c.compactar_memoria_cluster();
        }

        //podar_cluster
        else if (comando == "podar_cluster" or comando == "pc") {
            int k;
            cin >> k;
            cout << '#' << comando << ' ' << k << endl;
            if (c.pr_primer_proc() < k) cout << "error: se intenta borrar la raiz" << endl;
            else c.podar_cluster(k);
        }

        cin >> comando;
    }
}
