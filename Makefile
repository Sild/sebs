SOURCE=source
HEADER=header
LIB=lib
sebs: main.o filemanager.o scrambler.o md5.o diff_match_patch.o
	g++ -o sebs main.o filemanager.o scrambler.o md5.o diff_match_patch.o -lboost_system -lboost_filesystem -lcryptopp -gwq

main.o: $(HEADER)/filemanager.h  $(LIB)/dtl/dtl.hpp $(HEADER)/main.h $(HEADER)/diff_match_patch.h $(SOURCE)/main.cpp 
	g++ -c $(SOURCE)/main.cpp -g

filemanager.o:	$(HEADER)/filemanager.h $(SOURCE)/filemanager.cpp $(HEADER)/scrambler.h $(HEADER)/md5.h
	g++ -c $(SOURCE)/filemanager.cpp -std=c++11 -g

scrambler.o: $(HEADER)/scrambler.h $(SOURCE)/scrambler.cpp
	g++ -c $(SOURCE)/scrambler.cpp -g

md5.o: $(HEADER)/md5.h $(SOURCE)/md5.cpp
	g++ -c $(SOURCE)/md5.cpp -g

diff_match_path.o: $(HEADER)/diff_match_patch.h $(SOURCE)/diff_match_patch.cpp
	g++ -c $(SOURCE)/diff_match_patch.cpp -g

clean:
	rm ./*.o ./output/* ./clone/*
