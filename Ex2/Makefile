MF=	Makefile

CC=	gcc
CFLAGS=-fopenmp -std=c99

LFLAGS=	-lm

EXE=	print_usage.x

SRC= \
	OMP_Exercise_1.2.c

#################
.SUFFIXES:
.SUFFIXES: .c .o

OBJ=	$(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $<

all:	$(EXE)

$(EXE):	$(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LFLAGS)

$(OBJ):	$(MF)

clean:
	rm -f $(OBJ) $(EXE) core
