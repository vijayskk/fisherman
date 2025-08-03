UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    THREAD_FLAG = -pthread
else ifeq ($(UNAME_S),Darwin)
    THREAD_FLAG = -pthreads
else
    THREAD_FLAG = -pthread
endif

CC=g++
CFLAGS = $(THREAD_FLAG) --std=c++11
EXEC=fisherman
MAIN=src/main.cpp

main:src/main.cpp
	$(CC) $? $(CFLAGS) -o build/$(EXEC) 

run:
	build/$(EXEC)


clear:
	rm build/*

uninstall:
	rm -f /usr/local/bin/$(EXEC)
	rm -f /usr/local/share/man/man1/$(EXEC).1
	@echo "Uninstalled fisherman from /usr/local/bin and man1"

install:
	install -m 755 build/$(EXEC) /usr/local/bin/$(EXEC)
	install -m 644 man/$(EXEC).1 /usr/local/share/man/man1/$(EXEC).1
	@echo "Installed fisherman to /usr/local/bin and manual to man1"

man:
	man fisherman
