CL65 = cl65
LD65 = ld65

CSOURCES = main.c
ASMSOURCES = startup.asm
OBJECTS = $(CSOURCES:.c=.o) $(ASMSOURCES:.asm=.o)

all : $(OBJECTS)
	$(LD65) -o main.nes --config main.cfg --obj $(OBJECTS) --lib nes.lib
	$(MAKE) clean

.SUFFIXES: .asm .o

.c.o :
	$(CL65) -t nes -o $*.o -c -O $*.c

.asm.o :
	$(CL65) -t nes -o $*.o -c $*.asm

.s.o :
	$(CL65) -t nes -o $*.o -c $*.s

.PHONY: clean
clean:
	rm -f *.o

	
