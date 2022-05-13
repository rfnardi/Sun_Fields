CC=g++

pow_dep_array_size.bin : pow_dep_array_size.o bare_functions.o
	$(CC) pow_dep_array_size.o bare_functions.o -o pow_dep_array_size.bin

bare_functions.o : ../lib/bare_functions.cpp ../lib/bare_functions.h
	$(CC) -c ../lib/bare_functions.cpp ../lib/bare_functions.h 

pow_dep_array_size.o : pow_dep_array_size.cpp ../lib/bare_functions.cpp ../lib/bare_functions.h
	$(CC) -c pow_dep_array_size.cpp ../lib/bare_functions.cpp ../lib/bare_functions.h 

pow_dep_focal_z_pos.bin : pow_dep_focal_z_pos.o bare_functions.o
	$(CC) pow_dep_focal_z_pos.o bare_functions.o -o pow_dep_focal_z_pos.bin 

pow_dep_focal_z_pos.o : pow_dep_focal_z_pos.cpp ../lib/bare_functions.cpp ../lib/bare_functions.h
	$(CC) -c pow_dep_focal_z_pos.cpp ../lib/bare_functions.cpp ../lib/bare_functions.h

pow_dep_mirror_angular_pos.bin : pow_dep_mirror_angular_pos.o bare_functions.o
	$(CC) pow_dep_mirror_angular_pos.o bare_functions.o -o pow_dep_mirror_angular_pos.bin 

pow_dep_mirror_angular_pos.o : pow_dep_mirror_angular_pos.cpp ../lib/bare_functions.cpp ../lib/bare_functions.cpp
	$(CC) -c pow_dep_mirror_angular_pos.cpp ../lib/bare_functions.cpp ../lib/bare_functions.h

pow_dep_mirror_pos.bin : pow_dep_mirror_pos.o bare_functions.o
	$(CC) pow_dep_mirror_pos.o bare_functions.o -o pow_dep_mirror_pos.bin 

pow_dep_mirror_pos.o : pow_dep_mirror_pos.cpp ../lib/bare_functions.cpp ../lib/bare_functions.cpp
	$(CC) -c pow_dep_mirror_pos.cpp ../lib/bare_functions.cpp ../lib/bare_functions.h

pow_dep_NDA.bin : pow_dep_NDA.o bare_functions.o
	$(CC) pow_dep_NDA.o bare_functions.o -o pow_dep_NDA.bin 

pow_dep_NDA.o : pow_dep_NDA.cpp ../lib/bare_functions.cpp ../lib/bare_functions.cpp
	$(CC) -c pow_dep_NDA.cpp ../lib/bare_functions.cpp ../lib/bare_functions.h

pow_one_mirror_intra_day.bin : pow_one_mirror_intra_day.o bare_functions.o
	$(CC) pow_one_mirror_intra_day.o bare_functions.o -o pow_one_mirror_intra_day.bin 

pow_one_mirror_intra_day.o : pow_one_mirror_intra_day.cpp ../lib/bare_functions.cpp ../lib/bare_functions.cpp
	$(CC) -c pow_one_mirror_intra_day.cpp ../lib/bare_functions.cpp ../lib/bare_functions.h

clean:
	rm *.o
