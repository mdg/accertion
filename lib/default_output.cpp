
#include "default_output.h"


human_testpp_output_c::human_testpp_output_c()
: testpp_output_i( "human" )
{}

void human_testpp_output_c::begin( const testpp_id_c &id )
{
}

void human_testpp_output_c::complete( const testpp_id_c &id )
{
}

void human_testpp_output_c::summarize( int passed, int failed )
{
	stream() << failed << " failures in " << passed + failed
		<< " tests\n";
}

