# Source, Executable, Includes, Library Defines
INCL   =
SRC    = main.c readFile.c state.c run.c
OBJ    = $(SRC:.c=.o)
LIBS   =
EXE    = interpreter

# Compiler, Linker Defines
CC      = /usr/bin/gcc
WARN	= -pedantic -Wall -Wextra
CFLAGS  = -std=c11 $(WARN) -O3
LIBPATH = -L.
LDFLAGS = -std=c11 $(WARN) -o $(EXE) $(LIBPATH) $(LIBS)
CFDEBUG = $(LDFLAGS) -ggdb -DDEBUG
RM      = /bin/rm -f

all: $(EXE)
build: $(EXE) clean

# Compile and Assemble C Source Files into Object Files
%.o: %.c
	$(CC) -c $(CFLAGS) $*.c

# Link all Object Files with external Libraries into Binaries
$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ)

# Objects depend on these Libraries
$(OBJ): $(INCL)

# Create a gdb Capable Executable with DEBUG flags turned on
debug:
	$(CC) $(CFDEBUG) $(SRC)

# Clean Up Objects, Dumps out of source directory
clean:
	$(RM) $(OBJ)

.PHONY : clean debug
