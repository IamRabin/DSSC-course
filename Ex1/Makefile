MF=	Makefile

CC=	gcc
CFLAGS=-fopenmp

LFLAGS=	-lm

EXE=	calculate_pi.x

SRC= \
	OMP_Exercise_1.1.c

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
