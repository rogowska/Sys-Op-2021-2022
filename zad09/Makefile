#
# make: all, clean, tar  
#
#=========================================================================
DIR = `basename $(CURDIR)`
#------------------------
NAME1 = threads
#----------------------
EXEC1 = $(NAME1)
OBJS1 = $(NAME1).o
#############################
COFLAGS = -Wall -O
LDFLAGS = -Wall -O
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
all: $(EXEC1)
#############################
$(EXEC1): $(OBJS1)
	 $(LD) -o $@ $(LDFLAGS) $^ -lpthread
#############################
.PHONY: run
run: $(EXEC1)
	./$(EXEC1) $(threads_num) $(loop_num)
#############################
.PHONY: clean tar
# Porzadki
EXECS = $(EXEC1)
clean:                                                     
	rm -f *.o *.x *~ $(EXECS)
#=========================================================================
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
#=========================================================================
