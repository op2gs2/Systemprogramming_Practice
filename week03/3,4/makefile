# Makefile

CC=gcc
CFLAGS=
OBJS=main.o
EXE=main
LIBS=

all : $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS) $(LIBS)
debug : 
	$(CC) $(CFLAGS) -o $(EXE) -DDEBUG main.c 
release : 
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS) $(LIBS)
clean:
	rm $(OBJS) $(EXE)
