CC=g++

pow_one_mirror_intra_day_correction.bin : pow_one_mirror_intra_day_correction.o bare_functions.o transm_functions.o table_functions.o 
	$(CC) pow_one_mirror_intra_day_correction.o bare_functions.o transm_functions.o table_functions.o -o pow_one_mirror_intra_day_correction.bin

bare_functions.o : ../lib/bare_functions.cpp ../lib/bare_functions.h
	$(CC) -c ../lib/bare_functions.cpp ../lib/bare_functions.h 

transm_functions.o : ../lib/bare_functions.cpp ../lib/bare_functions.h ../lib/transm_functions.cpp ../lib/transm_functions.h 
	$(CC) -c ../lib/transm_functions.cpp ../lib/transm_functions.h ../lib/bare_functions.cpp ../lib/bare_functions.h 

table_functions.o : ../lib/bare_functions.cpp ../lib/bare_functions.h ../lib/transm_functions.cpp ../lib/transm_functions.h ../lib/table_functions.cpp ../lib/table_functions.h 
	$(CC) -c ../lib/transm_functions.cpp ../lib/transm_functions.h ../lib/bare_functions.cpp ../lib/bare_functions.h ../lib/table_functions.cpp ../lib/table_functions.h

pow_one_mirror_intra_day_correction.o : pow_one_mirror_intra_day_correction.cpp ../lib/bare_functions.cpp ../lib/bare_functions.h ../lib/transm_functions.cpp ../lib/table_functions.cpp ../lib/transm_functions.h ../lib/table_functions.h 
	$(CC) -c pow_one_mirror_intra_day_correction.cpp ../lib/bare_functions.cpp ../lib/bare_functions.h ../lib/transm_functions.cpp ../lib/table_functions.cpp ../lib/transm_functions.h ../lib/table_functions.h

clean :
	rm *.o
