SOURCE=source
HEADER=header
sebs: main.o filemanager.o
	g++ -o sebs main.o filemanager.o -lboost_system -lboost_filesystem

main.o: $(HEADER)/filemanager.h $(SOURCE)/main.cpp
	g++ -c $(SOURCE)/main.cpp

filemanager.o:	$(HEADER)/filemanager.h $(SOURCE)/filemanager.cpp
	g++ -c $(SOURCE)/filemanager.cpp