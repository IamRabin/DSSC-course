MF=	Makefile

CC=	mpicc
CFLAGS= -std=c99

LFLAGS=	-lm

EXE=	Idmatrix.x

SRC= \
	MPI_Ex_4_1.c

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
