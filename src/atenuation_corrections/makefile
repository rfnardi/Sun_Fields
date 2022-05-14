CC = g++
LIB1 = ../lib/bare_functions.cpp ../lib/bare_functions.h
LIB2 = $(LIB1) ../lib/transm_functions.cpp ../lib/transm_functions.h
LIBTABLE = ../lib/table_functions.cpp ../lib/table_functions.h
LIB3 = $(LIB2) $(LIBTABLE)
LIBOBJ = bare_functions.o transm_functions.o table_functions.o

pow_one_mirror_intra_day_correction.bin : pow_one_mirror_intra_day_correction.o $(LIBOBJ) 
	$(CC) pow_one_mirror_intra_day_correction.o $(LIBOBJ) -o pow_one_mirror_intra_day_correction.bin

bare_functions.o : $(LIB1)
	$(CC) -c $(LIB1)

transm_functions.o : $(LIB3)
	$(CC) -c $(LIB3)

table_functions.o :  $(LIBTABLE) 
	$(CC) -c  $(LIBTABLE)

pow_one_mirror_intra_day_correction.o : pow_one_mirror_intra_day_correction.cpp $(LIB3) 
	$(CC) -c pow_one_mirror_intra_day_correction.cpp $(LIB3)

clean :
	rm *.o ../lib/*.gch
