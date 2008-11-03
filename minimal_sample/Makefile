
all : run_minimal_sample

clean :
	rm run_minimal_sample *.o

sample_object_test.o : sample_object.h sample_object_test.cpp
	g++ -c sample_object_test.cpp

run_minimal_sample : sample_object_test.o
	g++ -o run_minimal_sample sample_object_test.o -ltestpp

build : run_minimal_sample

run : build
	./run_minimal_sample

