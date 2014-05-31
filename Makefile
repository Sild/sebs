SOURCE=source
HEADER=header
LIB=lib
COMPILER=clang++
sebs: main.o filemanager.o scrambler.o md5.o metaworker.o updater.o
	$(COMPILER) -o sebs main.o filemanager.o scrambler.o md5.o metaworker.o updater.o -lboost_system -lboost_filesystem -lcryptopp -g

main.o: $(HEADER)/filemanager.h  $(HEADER)/main.h $(SOURCE)/main.cpp $(HEADER)/metaworker.h $(HEADER)/updater.h
	$(COMPILER) -c $(SOURCE)/main.cpp -g

filemanager.o:	$(HEADER)/filemanager.h $(SOURCE)/filemanager.cpp $(HEADER)/scrambler.h $(HEADER)/md5.h $(HEADER)/metaworker.h
	$(COMPILER) -c $(SOURCE)/filemanager.cpp -std=c++11 -g

scrambler.o: $(HEADER)/scrambler.h $(SOURCE)/scrambler.cpp
	$(COMPILER) -c $(SOURCE)/scrambler.cpp -g

md5.o: $(HEADER)/md5.h $(SOURCE)/md5.cpp
	$(COMPILER) -c $(SOURCE)/md5.cpp -g

metaworker.o: $(HEADER)/metaworker.h $(SOURCE)/metaworker.cpp $(HEADER)/md5.h
	$(COMPILER) -c $(SOURCE)/metaworker.cpp -std=c++11 -g

inotify.o: $(HEADER)/inotify.h $(SOURCE)/inotify.cpp
	$(COMPILER) -c $(SOURCE)/inotify.cpp -g

updater.o: $(HEADER)/updater.h $(SOURCE)/updater.cpp $(HEADER)/md5.h $(HEADER)/metaworker.h
	$(COMPILER) -c $(SOURCE)/updater.cpp -g

clean:
	rm ./*.o ./output/* ./clone/*
