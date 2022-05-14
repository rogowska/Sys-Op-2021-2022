###############################################################################
#							  Makefile do projektu							  #
#							   Semafory Zadanie 6							  #
#																			  #
###############################################################################

#==============================================================================
# Dostepne komendy: make all, run6, clean, tar

#==============================================================================
# Flagi, kompilator, rozszerzenia i inne:

Cflags = -O2 -Wall -std=c99 -pedantic -pthread -D_POSIX_SOURCE
Lflags = -Wall -std=c99 -pedantic -c -g
CO = gcc
.SUFFIXES: .c .cpp .o .x .h
DIR = $(notdir $(CURDIR))

#==============================================================================
# ZMIENNE:

R = exclusion.x
PROCNUM = 
SECTNUM = 


#==============================================================================
# ZALEZNOSCI:

library.o: library.h library.c
	$(CO) $(Lflags) library.c

exclusion.x: exclusion.c library.o
	$(CO) $(Cflags) -o $@ $^
	
duplicator.x: duplicator.c library.o exclusion.x
	$(CO) $(Cflags) -o $@ duplicator.c library.o


#==============================================================================
# KOMPILACJA calosci bez uruchomienia

.PHONY: all
all: duplicator.x exclusion.x library.o


#==============================================================================
# URUCHAMIANIE PROGRAMOW

.PHONY: run6
run6: duplicator.x
	./duplicator.x $(R) $(PROCNUM) $(SECTNUM)
	rm numer.txt


#==============================================================================
# Czyszczenie

.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out *.exe *.in *.out; rm -rf ${LIB_DIR}

# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )