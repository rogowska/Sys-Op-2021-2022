#
# make: all, clean, tar  
#
#=========================================================================
DIR = `basename $(CURDIR)`
#------------------------
FIFO = /tmp/myfifo
#------------------------
NAME1 = zad5a
NAME2 = producent
NAME3 = konsument
#----------------------
EXEC1 = $(NAME1)
OBJS1 = $(NAME1).o

EXEC2 = $(NAME2)
EXEX2 = $(NAME2).x
OBJS2 = $(NAME2).o

EXEC3 = $(NAME3)
EXEX3 = $(NAME3).x
OBJS3 = $(NAME3).o
#----------------------
#############################
COFLAGS = -Wall
LDFLAGS = -Wall
CO = gcc
LD = $(CO)
#############################
%.o: %.c
	$(CO) $(COFLAGS) -c $<
#############################
%.x: %.c
	$(CO) $(COFLAGS) -c $<
#############################
.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEX2) $(EXEX3)
#############################
$(EXEC1): $(OBJS1)
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
$(EXEC2): $(OBJS2)
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
$(EXEC3): $(OBJS3)
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
$(EXEX2): $(OBJS2)
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
$(EXEX3): $(OBJS3)
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
.PHONY: run_a
run_a: $(EXEC1)
	./$(EXEC1) $(src) $(dst)
	wait
	diff $(src) $(dst)
#############################
.PHONY: run_b
run_b: $(EXEX2) $(EXEX3)
	rm -f ./$(dst)
	mkfifo -m 0666 $(FIFO)
	xterm -hold -title $(NAME2) -e ./$(EXEX2) ./$(src) $(FIFO) &
	xterm -hold -title $(NAME3) -e ./$(EXEX3) ./$(dst) $(FIFO) 
	wait
	diff $(src) $(dst)
	rm $(FIFO)

#############################
.PHONY: clean tar
# Porzadki
EXECS := $(EXEC1) $(EXEC2) $(EXEC3) $(EXEX2) $(EXEX3)
clean:                                                     
	rm -f *.o  *~ $(EXECS)
#=========================================================================
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
#=========================================================================
