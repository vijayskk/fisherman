CC=g++
CFLAGS = -pthreads --std=c++11
EXEC=run
MAIN=src/main.cpp

main:src/main.cpp
	$(CC) $? $(CFLAGS) -o build/$(EXEC) 

run:
	build/$(EXEC)

clear:
	rm build/* 
