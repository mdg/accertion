CC = g++
DBG = -g

all : lib

clean :
	rm -rf *.o test/*.o libtestpp.a

testpp.o : lib/testpp.cpp include/testpp/test.h include/testpp/assertion.h
	$(CC) $(DBG) -c -Iinclude lib/testpp.cpp

default_output.o : lib/default_output.cpp lib/default_output.h \
	include/testpp/test.h include/testpp/assertion.h
	$(CC) $(DBG) -c -Iinclude lib/default_output.cpp

main.o : lib/main.cpp lib/default_output.h include/testpp/test.h \
	include/testpp/assertion.h include/testpp/project.h
	$(CC) $(DBG) -c -Iinclude -Ilib lib/main.cpp

testpp_id.o : lib/testpp_id.cpp include/testpp/id.h \
	include/testpp/test.h include/testpp/assertion.h
	$(CC) $(DBG) -c -Iinclude lib/testpp_id.cpp

testpp_project.o : lib/testpp_project.cpp include/testpp/project.h \
	include/testpp/test.h include/testpp/assertion.h
	$(CC) $(DBG) -c -Iinclude lib/testpp_project.cpp

test/testpp_test.o : test/testpp_test.cpp include/testpp/test.h \
	include/testpp/id.h
	$(CC) $(DBG) -c -o test/testpp_test.o -Iinclude -Ilib \
		test/testpp_test.cpp

test/assertion_test.o : test/assertion_test.cpp include/testpp/assertion.h
	$(CC) $(DBG) -c -o test/assertion_test.o -Iinclude -Ilib \
		test/assertion_test.cpp

test/default_output_test.o : test/default_output_test.cpp
	$(CC) $(DBG) -c -o test/default_output_test.o -Iinclude -Ilib \
		test/default_output_test.cpp

test/output_test.o : test/output_test.cpp include/testpp/test.h \
	test/output_test.h
	$(CC) $(DBG) -c -o test/output_test.o -Iinclude test/output_test.cpp

test/project_test.o : test/project_test.cpp include/testpp/project.h \
	include/testpp/output.h test/output_test.h
	$(CC) $(DBG) -c -o test/project_test.o -Iinclude test/project_test.cpp

compile : testpp.o default_output.o main.o testpp_id.o \
	testpp_project.o

libtestpp.a : compile
	ar r libtestpp.a *.o

lib : libtestpp.a

compile_test : test/testpp_test.o test/assertion_test.o test/default_output_test.o \
	test/output_test.o \
	test/project_test.o

build_test : compile compile_test
	$(CC) $(DBG) -o run_testpp *.o test/*.o

test : build_test
	./run_testpp

install :
	cp libtestpp.a /usr/lib
	cp -r include/testpp /usr/include

