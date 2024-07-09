OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o Cluster.o Procesador.o AreaEspera.o Prioridad.o Proceso.o
	g++ -o program.exe program.o Cluster.o Procesador.o AreaEspera.o Prioridad.o Proceso.o $(OPCIONS)
	rm *.o

program.o: program.cc Cluster.hh Procesador.hh AreaEspera.hh Prioridad.hh Proceso.hh
	g++ -c program.cc $(OPCIONS)

Cluster.o: Cluster.cc Cluster.hh Procesador.hh Proceso.hh BinTree.hh
	g++ -c Cluster.cc $(OPCIONS)

AreaEspera.o: AreaEspera.cc AreaEspera.hh Cluster.hh Prioridad.hh Proceso.hh
	g++ -c AreaEspera.cc $(OPCIONS)

Prioridad.o: Prioridad.cc Prioridad.hh Proceso.hh
	g++ -c Prioridad.cc $(OPCIONS)
	
Procesador.o: Procesador.cc Procesador.hh Proceso.hh
	g++ -c Procesador.cc $(OPCIONS)

Proceso.o: Proceso.cc Proceso.hh
	g++ -c Proceso.cc $(OPCIONS)

tar: program.cc Cluster.hh Cluster.cc Procesador.hh Procesador.cc AreaEspera.hh AreaEspera.cc Prioridad.hh Prioridad.cc Proceso.hh Proceso.cc Makefile
	tar -cvf practica.tar program.cc Cluster.hh Cluster.cc Procesador.hh Procesador.cc AreaEspera.hh AreaEspera.cc Prioridad.hh Prioridad.cc Proceso.hh Proceso.cc Makefile

clean:
	rm *.o
	rm *.exe
