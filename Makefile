SOURCE=source
HEADER=header
sebs: main.o filemanager.o scrambler.o md5.o
	g++ -o sebs main.o filemanager.o scrambler.o md5.o -lboost_system -lboost_filesystem

main.o: $(HEADER)/filemanager.h  $(SOURCE)/main.cpp 
	g++ -c $(SOURCE)/main.cpp

filemanager.o:	$(HEADER)/filemanager.h $(SOURCE)/filemanager.cpp $(HEADER)/scrambler.h $(HEADER)/md5.h
	g++ -c $(SOURCE)/filemanager.cpp -std=c++11

scrambler.o: $(HEADER)/scrambler.h $(SOURCE)/scrambler.cpp
	g++ -c $(SOURCE)/scrambler.cpp

md5.o: $(HEADER)/md5.h $(SOURCE)/md5.cpp
	g++ -c $(SOURCE)/md5.cpp
clean:
	rm ./*.o ./output/* ./clone/*