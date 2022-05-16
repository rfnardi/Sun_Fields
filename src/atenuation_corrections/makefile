CC = g++
LIB1 = ../lib/bare_functions.cpp
LIB2 = $(LIB1) ../lib/transm_functions.cpp
LIBTABLE = ../lib/table_functions.cpp
LIB3 = $(LIB2) $(LIBTABLE)
LIBOBJ = bare_functions.o transm_functions.o table_functions.o

all : pow_one_mirror_intra_day_correction.bin aten_intra_day_sun_power.bin corrected_pow_dep_on_NDA.bin

pow_one_mirror_intra_day_correction.bin : pow_one_mirror_intra_day_correction.o $(LIBOBJ) 
	$(CC) pow_one_mirror_intra_day_correction.o $(LIBOBJ) -o pow_one_mirror_intra_day_correction.bin

pow_one_mirror_intra_day_correction.o : pow_one_mirror_intra_day_correction.cpp $(LIB3) 
	$(CC) -c pow_one_mirror_intra_day_correction.cpp $(LIB3)

aten_intra_day_sun_power.bin : aten_intra_day_sun_power.o $(LIBOBJ) 
	$(CC) aten_intra_day_sun_power.o $(LIBOBJ) -o aten_intra_day_sun_power.bin

aten_intra_day_sun_power.o : aten_intra_day_sun_power.cpp $(LIB3) 
	$(CC) -c aten_intra_day_sun_power.cpp $(LIB3)

corrected_pow_dep_on_NDA.bin : corrected_pow_dep_on_NDA.o $(LIBOBJ) 
	$(CC) corrected_pow_dep_on_NDA.o $(LIBOBJ) -o corrected_pow_dep_on_NDA.bin

corrected_pow_dep_on_NDA.o : corrected_pow_dep_on_NDA.cpp $(LIB3) 
	$(CC) -c corrected_pow_dep_on_NDA.cpp $(LIB3)

bare_functions.o : $(LIB1)
	$(CC) -c $(LIB1)

transm_functions.o : $(LIB3)
	$(CC) -c $(LIB3)

table_functions.o :  $(LIBTABLE) 
	$(CC) -c  $(LIBTABLE)

clean :
	rm *.o ../lib/*.gch
