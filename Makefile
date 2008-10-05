CC = g++

clean :
	rm -rf *.o test/*.o

testpp.o : lib/testpp.cpp include/testpp.h
	$(CC) -c -Iinclude lib/testpp.cpp

default_output.o : lib/default_output.cpp lib/default_output.h
	$(CC) -c -Iinclude lib/default_output.cpp

testpp_id.o : lib/testpp_id.cpp include/testpp_id.h
	$(CC) -c -Iinclude lib/testpp_id.cpp

testpp_project.o : lib/testpp_project.cpp include/testpp_project.h
	$(CC) -c -Iinclude lib/testpp_project.cpp

testpp_result.o : lib/testpp_result.cpp include/testpp_result.h
	$(CC) -c -Iinclude lib/testpp_result.cpp

test/testpp_test.o : test/testpp_test.cpp
	$(CC) -c -o test/testpp_test.o -Iinclude test/testpp_test.cpp

test/default_output_test.o : test/default_output_test.cpp
	$(CC) -c -o test/default_ouput_test.o -Iinclude -Ilib \
		test/default_output_test.cpp

test/project_test.o : test/project_test.cpp include/testpp_project.h \
	include/testpp_output.h test/output_test.h
	$(CC) -c -o test/project_test.o -Iinclude test/project_test.cpp

compile : testpp.o default_output.o testpp_id.o \
	testpp_project.o \
	testpp_result.o

build : compile
	ar r libtestpp.a *.o

compile_test : test/testpp_test.o test/default_output_test.o test/project_test.o

build_test : compile compile_test
	$(CC) -o run_testpp *.o test/*.o

build_full_test :
	$(CC) -g -o run_testpp -Iinclude lib/testpp.cpp \
		lib/testpp_assertion.cpp \
		lib/testpp_project.cpp \
		test/testpp_test.cpp

test : build_test
	./run_testpp

