#
# make: all, clean, tar  
#
#=========================================================================
DIR = `basename $(CURDIR)`
#------------------------
NAME1 = 1_a
NAME2 = 1_b
NAME3 = 1_c
NAME4 = 1_d
NAME5 = 1_e
#----------------------
EXEC1 = $(NAME1)
OBJS1 = $(NAME1).o
#----------------------
EXEC2 = $(NAME2)
OBJS2 = $(NAME2).o
#----------------------
EXEC3 = $(NAME3)
OBJS3 = $(NAME3).o
#----------------------
EXEC4 = $(NAME4)
OBJS4 = $(NAME4).o
#----------------------
EXEC5 = $(NAME5)
OBJS5 = $(NAME5).o
#----------------------
#############################
COFLAGS = -Wall -O
LDFLAGS = -Wall -O
CO = gcc
LD = $(CO)
#############################
%.o: %.c
	$(CO) $(COFLAGS) -c $<
#############################
.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5)
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
$(EXEC4): $(OBJS4)
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
$(EXEC5): $(OBJS5)
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
.PHONY: runa
runa: $(EXEC1)
	./$(EXEC1)
#############################
.PHONY: runb
runb: $(EXEC2)
	./$(EXEC2)
#############################
.PHONY: runc
runc: $(EXEC3)
	./$(EXEC3)
#############################
.PHONY: rund
rund: $(EXEC4)
	./$(EXEC4)
#############################
.PHONY: rune
rune: $(EXEC5)
	./$(EXEC5)
#############################
.PHONY: clean tar
# Porzadki
EXECS = $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5)
clean:                                                     
	rm -f *.o  *~ $(EXECS)
#=========================================================================
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
#=========================================================================
