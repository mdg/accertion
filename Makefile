CC = g++

obj :
	mkdir obj

clean :
	rm -rf obj

testpp.o : lib/testpp.cpp include/testpp.h
	$(CC) -c -Iinclude lib/testpp.cpp

testpp_assertion.o : lib/testpp_assertion.cpp
	$(CC) -c -o testpp_assertion.o -Iinclude lib/testpp_assertion.cpp

testpp_output.o : lib/testpp_output.cpp include/testpp_output.h
	$(CC) -c -Iinclude lib/testpp_output.cpp

testpp_project.o : lib/testpp_project.cpp include/testpp_project.h
	$(CC) -c -Iinclude lib/testpp_project.cpp

test/testpp_test.o : test/testpp_test.cpp
	$(CC) -c -o test/testpp_test.o -Iinclude test/testpp_test.cpp

compile : testpp.o testpp_assertion.o testpp_output.o testpp_project.o

build : compile

compile_test : test/testpp_test.o

build_test : compile compile_test
	$(CC) -o run_testpp testpp.o testpp_assertion.o testpp_output.o \
		testpp_project.o test/testpp_test.o

build_full_test :
	$(CC) -g -o run_testpp -Iinclude lib/testpp.cpp \
		lib/testpp_assertion.cpp \
		lib/testpp_output.cpp lib/testpp_project.cpp \
		test/testpp_test.cpp

test : build_test
	./run_testpp

