CC = g++ -std=c++11
LINK = g++

rumdom.exe: rumdom.o
	$(LINK) rumdom.o -o rumdom.exe
	rm rumdom.o
rumdom.o: main.cpp
	$(CC) -c main.cpp -o2 -o rumdom.o
