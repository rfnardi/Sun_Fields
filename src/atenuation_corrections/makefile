CC = g++
LIB1 = ../lib/bare_functions.cpp
LIB2 = $(LIB1) ../lib/transm_functions.cpp
LIBTABLE = ../lib/table_functions.cpp
LIB3 = $(LIB2) $(LIBTABLE)
LIBOBJ = bare_functions.o transm_functions.o table_functions.o
FILES1 = corrected_one_mirror_intra_day.bin corrected_intra_day_sun_power.bin
FILES2 = $(FILES1) corrected_pow_dep_on_NDA.bin corrected_pow_dep_on_array_size.bin
FILES3 = $(FILES2) corrected_pow_dep_on_angular_pos.bin
MAIN_FILES = $(FILES3)

all : $(MAIN_FILES)

corrected_one_mirror_intra_day.bin : corrected_one_mirror_intra_day.o $(LIBOBJ) 
	$(CC) corrected_one_mirror_intra_day.o $(LIBOBJ) -o corrected_one_mirror_intra_day.bin

corrected_one_mirror_intra_day.o : corrected_one_mirror_intra_day.cpp $(LIB3) 
	$(CC) -c corrected_one_mirror_intra_day.cpp $(LIB3)

corrected_intra_day_sun_power.bin : corrected_intra_day_sun_power.o $(LIBOBJ) 
	$(CC) corrected_intra_day_sun_power.o $(LIBOBJ) -o corrected_intra_day_sun_power.bin

corrected_intra_day_sun_power.o : corrected_intra_day_sun_power.cpp $(LIB3) 
	$(CC) -c corrected_intra_day_sun_power.cpp $(LIB3)

corrected_pow_dep_on_NDA.bin : corrected_pow_dep_on_NDA.o $(LIBOBJ) 
	$(CC) corrected_pow_dep_on_NDA.o $(LIBOBJ) -o corrected_pow_dep_on_NDA.bin

corrected_pow_dep_on_NDA.o : corrected_pow_dep_on_NDA.cpp $(LIB3) 
	$(CC) -c corrected_pow_dep_on_NDA.cpp $(LIB3)

corrected_pow_dep_on_array_size.bin : corrected_pow_dep_on_array_size.o $(LIBOBJ) 
	$(CC) corrected_pow_dep_on_array_size.o $(LIBOBJ) -o corrected_pow_dep_on_array_size.bin

corrected_pow_dep_on_array_size.o : corrected_pow_dep_on_array_size.cpp $(LIB3) 
	$(CC) -c corrected_pow_dep_on_array_size.cpp $(LIB3)


corrected_pow_dep_on_angular_pos.bin : corrected_pow_dep_on_angular_pos.o $(LIBOBJ) 
	$(CC) corrected_pow_dep_on_angular_pos.o $(LIBOBJ) -o corrected_pow_dep_on_angular_pos.bin

corrected_pow_dep_on_angular_pos.o : corrected_pow_dep_on_angular_pos.cpp $(LIB3) 
	$(CC) -c corrected_pow_dep_on_angular_pos.cpp $(LIB3)

bare_functions.o : $(LIB1)
	$(CC) -c $(LIB1)

transm_functions.o : $(LIB3)
	$(CC) -c $(LIB3)

table_functions.o :  $(LIBTABLE) 
	$(CC) -c  $(LIBTABLE)

clean :
	rm *.o 
