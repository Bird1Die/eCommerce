IDIR=../../../../con2redis/src
ODIR=../obj
BDIR=../bin

CC=g++
CFLAGS=-std=c++20 -g -ggdb -fpermissive -L/usr/local/lib -Wall -I. -I$(IDIR) -I/usr/include/postgresql -lpq -lm -lhiredis

DEPS = $(wildcard $(IDIR)/*.h)
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, $(ODIR)/%.o, $(SRC))

con2redis_OBJ=$(wildcard ../../../con2redis/obj/*.o)

all: con2redis $(BDIR)/main
	clear
	cd ../bin; ./main
	$(MAKE) -C . clean

con2redis:
	$(MAKE) -C ../../../con2redis/src

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BDIR)/main: $(OBJ) $(DEPS)
	$(CC) -o $@ $(OBJ) $(con2redis_OBJ) $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(IDIR)/*~ core 
	rm -f ../bin/main
	rm -f ../../../con2redis/obj/*.o *~ ../../../con2redis/src/*~ core 

# Aggiungiamo un gestore di segnali per SIGINT (Ctrl+C)
# Questo assicura che quando viene interrotto manualmente con Ctrl+C, verrà eseguito il target "clean"

.PRECIOUS: $(BDIR)/main con2redis clean all
.SILENT:
.SHELLFLAGS = -ec
.PHONY: safe
safe:
	trap 'make clean' SIGINT; make all
