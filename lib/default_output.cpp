
#include "default_output.h"
#include "testpp_id.h"


human_testpp_output_c::human_testpp_output_c()
: testpp_output_i( "human" )
{}

void human_testpp_output_c::begin( const testpp_id_c &id )
{
	stream() << "testpp( " << id.file_name() << ':' \
		<< id.test_name()
		<< ':' << id.line_number() << " )" << std::endl;
}

void human_testpp_output_c::complete( const testpp_id_c &id )
{
}

void human_testpp_output_c::summarize( int passed, int failed )
{
	stream() << failed << " failures in " << passed + failed
		<< " tests\n";
}

