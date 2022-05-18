CCX = g++
FLAGS = -O3 -Wall
LIB = ../lib/*.cpp
LIBOBJ = bare_functions.o transm_functions.o table_functions.o
SRC = $(wildcard *.cpp)
OBJ_FILES = $(SRC:.cpp=.o)
MAIN_FILES = $(SRC:.cpp=.bin)
FILENAMES = $(SRC:.cpp='')

all : MAIN_BIN MAIN_OBJ $(LIBOBJ)

bare_functions.o : $(LIB)
	$(CCX) $(FLAGS) -c '../lib/'$*'.cpp' -o $*'.o'

transm_functions.o : $(LIB)
	$(CCX) $(FLAGS) -c '../lib/'$*'.cpp' -o $*'.o'

table_functions.o :  $(LIB) 
	$(CCX) $(FLAGS) -c '../lib/'$*'.cpp' -o $*'.o'

MAIN_OBJ : $(LIB) $(SRC)
	for file in $(SRC); do\
		$(CCX) $(FLAGS) -c $$file ;\
	done

MAIN_BIN : $(OBJ_FILES) $(LIBOBJ)
	for file in $(FILENAMES); do\
		$(CCX) $(FLAGS) $$file'.o' $(LIBOBJ) -o $$file'.bin';\
	done

clean :
	rm *.o 

