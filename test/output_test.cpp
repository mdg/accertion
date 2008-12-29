
#include <testpp/test.h>
#include "output_test.h"


output_test_1::output_test_1()
: testpp_output_i( "test_1" )
{}

void output_test_1::begin( const testpp_id_c &id )
{
	stream() << "test_1 " << id.test_name() << std::endl;
}

void output_test_1::complete( const testpp_id_c &id
		, const testpp_result_c &result )
{
	if ( result.failure() ) {
		stream() << "\tfail " << id.test_name() << std::endl;
	} else {
		stream() << "\tpass " << id.test_name() << std::endl;
	}
}

void output_test_1::summarize( int passed, int failed, int ignored
			, int not_implemented )
{
	stream() << "test1, pass " << passed << ", failed " << failed
		<< std::endl;
}

