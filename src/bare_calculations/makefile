CC = g++
LIB = ../lib/bare_functions.cpp 
LIBOBJ = bare_functions.o
FILES1 = pow_dep_array_size.bin pow_dep_focal_z_pos.bin pow_dep_mirror_angular_pos.bin
FILES2 = $(FILES1) pow_dep_mirror_pos.bin pow_dep_NDA.bin pow_one_mirror_intra_day.bin
MAIN_FILES = $(FILES2)

all : $(MAIN_FILES)

$(LIBOBJ) : $(LIB)
	$(CC) -c $(LIB) 

pow_dep_array_size.bin : pow_dep_array_size.o $(LIBOBJ)
	$(CC) pow_dep_array_size.o $(LIBOBJ) -o pow_dep_array_size.bin

pow_dep_array_size.o : pow_dep_array_size.cpp $(LIB)
	$(CC) -c pow_dep_array_size.cpp $(LIB) 

pow_dep_focal_z_pos.bin : pow_dep_focal_z_pos.o $(LIBOBJ)
	$(CC) pow_dep_focal_z_pos.o $(LIBOBJ) -o pow_dep_focal_z_pos.bin 

pow_dep_focal_z_pos.o : pow_dep_focal_z_pos.cpp $(LIB)
	$(CC) -c pow_dep_focal_z_pos.cpp $(LIB)

pow_dep_mirror_angular_pos.bin : pow_dep_mirror_angular_pos.o $(LIBOBJ)
	$(CC) pow_dep_mirror_angular_pos.o $(LIBOBJ) -o pow_dep_mirror_angular_pos.bin 

pow_dep_mirror_angular_pos.o : pow_dep_mirror_angular_pos.cpp $(LIB)
	$(CC) -c pow_dep_mirror_angular_pos.cpp $(LIB)

pow_dep_mirror_pos.bin : pow_dep_mirror_pos.o $(LIBOBJ)
	$(CC) pow_dep_mirror_pos.o $(LIBOBJ) -o pow_dep_mirror_pos.bin 

pow_dep_mirror_pos.o : pow_dep_mirror_pos.cpp $(LIB)
	$(CC) -c pow_dep_mirror_pos.cpp $(LIB)

pow_dep_NDA.bin : pow_dep_NDA.o $(LIBOBJ)
	$(CC) pow_dep_NDA.o $(LIBOBJ) -o pow_dep_NDA.bin 

pow_dep_NDA.o : pow_dep_NDA.cpp $(LIB)
	$(CC) -c pow_dep_NDA.cpp $(LIB)

pow_one_mirror_intra_day.bin : pow_one_mirror_intra_day.o $(LIBOBJ)
	$(CC) pow_one_mirror_intra_day.o $(LIBOBJ) -o pow_one_mirror_intra_day.bin 

pow_one_mirror_intra_day.o : pow_one_mirror_intra_day.cpp $(LIB)
	$(CC) -c pow_one_mirror_intra_day.cpp $(LIB)

clean:
	rm *.o 
