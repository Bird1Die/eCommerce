

#IDIR=../hdr
IDIR=../../../../con2redis/src
ODIR=../obj
BDIR=../bin

CC=g++
# use this when connecting to Postgresql (library lpq)
#CFLAGS=-std=c++11 -I. -I$(IDIR) -I/usr/include/postgresql -lpq -lm 
CFLAGS=-std=c++20 -g -ggdb -fpermissive -L/usr/local/lib -Wall -I. -I$(IDIR) -I/usr/include/postgresql -lpq -lm -lhiredis -lncurses

# use this when no connection to Postgresql (library lpq) is needed
#CFLAGS=-std=c++11 -I. -I$(IDIR) -lm 

DEPS = $(wildcard $(IDIR)/*.h)
#OBJ = $(wildcard $(ODIR)/*.o)
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, $(ODIR)/%.o, $(SRC))

con2redis_OBJ=$(wildcard ../../../../con2redis/obj/*.o)
con2db_OBJ=$(wildcard ../../../../con2db/*.o)

all:	clean con2redis con2db $(BDIR)/main
	cd ../bin; ./main
	$(MAKE) -C . clean

con2redis:
	$(MAKE) -C ../../../../con2redis/src
con2db:
	$(MAKE) -C ../../../../con2db


$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BDIR)/main: $(OBJ) $(DEPS)
	$(CC) -o $@ $(OBJ) $(con2redis_OBJ) $(con2db_OBJ) $(CFLAGS)


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(IDIR)/*~ core 
	rm -f ../../../../con2redis/obj/*.o *~ ../../../../con2redis/src/*~ core 
	rm -f ../../../../con2db/*.o *~ ../../../../con2db/src/*~ core 