IDIR=.
CC=gcc
CFLAGS=-I$(IDIR)


DEPS= ctrl_terminal.h
OBJ = ctrl_terminal.o  


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


house_ctrl: $(OBJ)
	$(CC) -o $@ $<  $(CFLAGS)


clean:
	rm -rf *.o house_ctrl 
