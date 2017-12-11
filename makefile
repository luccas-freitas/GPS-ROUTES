all: dcmaps

dcmaps: sd.o tree.o menu.o vias.o retangulos.o hash.o graph.o main.o
	gcc sd.o tree.o hash.o graph.o vias.o menu.o retangulos.o main.o -o dcmaps	

main.o: main.c tree.h retangulos.h hash.h menu.h vias.h graph.h
	gcc -c main.c

menu.o: menu.c
	gcc -c menu.c

vias.o: vias.c
	gcc -c vias.c

graph.o: graph.c
	gcc -c graph.c

hash.o: hash.c sd.h
	gcc -c hash.c

retangulos.o: retangulos.c tree.h
	gcc -c retangulos.c

tree.o: tree.c
	gcc -c tree.c

sd.o: sd.c
	gcc -c sd.c

clean:
	rm -rf *.o dcmaps