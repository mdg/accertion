
#include <testpp/test.h>
#include "sample_object.h"


TESTPP( test_sample_object_double )
{
	sample_object obj( 4 );

	assertpp( obj.doubled_value() ) == 8;
}

TESTPP( test_sample_object_triple )
{
	sample_object obj( 7 );

	assertpp( obj.tripled_value() ) == 22;
}

