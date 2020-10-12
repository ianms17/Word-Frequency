FLAGS = -g -std=c++11

all: driver.o HashedSplays.h SplayTree.h Node.o Util.o
	g++ -std=c++11 -g driver.o HashedSplays.h SplayTree.h Util.o Node.o -o Driver.out

driver.o: driver.cpp HashedSplays.h Exceptions.h
	g++ -std=c++11 -g -c driver.cpp 

HashedSplays.o: HashedSplays.h SplayTree.h Node.h Util.h dsexceptions.h
	g++ -std=c++11 -g -c HashedSplays.h SplayTree.h Node.h Util.h dsexceptions.h -o HashedSplays.o
	
SplayTree.o: SplayTree.h dsexceptions.h
	g++ -std=c++11 -g -c SplayTree.h -o SplayTree.o
	
Util.o: Util.cpp Util.h
	g++ -std=c++11 -g -c Util.cpp
	
Node.o: Node.cpp Node.h Util.h
	g++ -std=c++11 -g -c Node.cpp
	
clean: 
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#

val:
	valgrind ./Driver.out $(DATA)

run:
	./Driver.out $(DATA)