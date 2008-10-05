CC = g++

clean :
	rm -rf *.o test/*.o

testpp.o : lib/testpp.cpp include/testpp.h
	$(CC) -c -Iinclude lib/testpp.cpp

default_output.o : lib/default_output.cpp lib/default_output.h
	$(CC) -c -Iinclude lib/default_output.cpp

testpp_assertion.o : lib/testpp_assertion.cpp
	$(CC) -c -o testpp_assertion.o -Iinclude lib/testpp_assertion.cpp

testpp_output.o : lib/testpp_output.cpp include/testpp_output.h
	$(CC) -c -Iinclude lib/testpp_output.cpp

testpp_project.o : lib/testpp_project.cpp include/testpp_project.h
	$(CC) -c -Iinclude lib/testpp_project.cpp

test/testpp_test.o : test/testpp_test.cpp
	$(CC) -c -o test/testpp_test.o -Iinclude test/testpp_test.cpp

test/default_output_test.o : test/default_output_test.cpp
	$(CC) -c -o test/default_ouput_test.o -Iinclude -Ilib \
		test/default_output_test.cpp

test/project_test.o : test/project_test.cpp
	$(CC) -c -o test/project_test.o -Iinclude test/project_test.cpp

compile : testpp.o default_output.o testpp_assertion.o testpp_output.o \
	testpp_project.o

build : compile

compile_test : test/testpp_test.o test/default_output_test.o test/project_test.o

build_test : compile compile_test
	$(CC) -o run_testpp *.o test/*.o

build_full_test :
	$(CC) -g -o run_testpp -Iinclude lib/testpp.cpp \
		lib/testpp_assertion.cpp \
		lib/testpp_output.cpp lib/testpp_project.cpp \
		test/testpp_test.cpp

test : build_test
	./run_testpp

