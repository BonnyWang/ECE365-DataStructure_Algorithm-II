shortPath.exe: shortPath.o heap.o hash.o graph.o
	g++ -o shortPath.exe shortPath.o heap.o hash.o graph.o

shortPath.o: shortPath.cpp heap.h hash.h graph.h
	g++ -c shortPath.cpp

graph.o: graph.cpp graph.h heap.h hash.h
	g++ -c graph.cpp

heap.o: heap.cpp heap.h hash.h
	g++ -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

debug:
	g++ -g -o shortPathDebug.exe useHeap.cpp heap.cpp hash.cpp graph.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups