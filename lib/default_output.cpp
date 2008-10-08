
#include "default_output.h"
#include "testpp_id.h"
#include "testpp_result.h"


human_testpp_output_c::human_testpp_output_c()
: testpp_output_i( "human" )
{}

void human_testpp_output_c::begin( const testpp_id_c &id )
{
	stream() << "testpp( " << id.file_name() << ':' \
		<< id.test_name()
		<< ':' << id.line_number() << " )" << std::endl;
}

void human_testpp_output_c::complete( const testpp_id_c &id
		, const testpp_result_c &result )
{
	if ( ! result.failure() ) {
		return;
	}

	testpp_result_c::failure_iterator it;
	for ( it=result.begin(); it!=result.end(); ++it ) {
		stream() << "\t" << it->message() << " (";
		if ( 0 && it->file_name().empty() ) {
			// nothing to write
		} else if ( id.file_name() == it->file_name() ) {
			stream() << "line " << it->line_number();
		} else {
			stream() << it->file_name() << ":"
				<< it->line_number();
		}
		stream() << ")\n";
	}
}

void human_testpp_output_c::summarize( int passed, int failed )
{
	stream() << failed << " failures in " << passed + failed
		<< " tests\n";
}


yaml_testpp_output_c::yaml_testpp_output_c()
: testpp_output_i( "yaml" )
{}

void yaml_testpp_output_c::begin( const testpp_id_c &id )
{
	stream() << "  - file: " << id.file_name() << std::endl;
	stream() << "    test: " << id.test_name() << std::endl;
	stream() << "    line: " << id.line_number() << std::endl;
}

void yaml_testpp_output_c::complete( const testpp_id_c &id
		, const testpp_result_c &result )
{
	if ( result.failure() ) {
		stream() << "    success: f\n";
		stream() << "    failures:\n";
		testpp_result_c::failure_iterator it;
		for ( it=result.begin(); it!=result.end(); ++it ) {
			stream() << "      - message: " << it->message()
				<< std::endl;
			stream() << "        failure-file: "
				<< it->file_name()
				<< std::endl;
			stream() << "        failure-line: "
				<< it->line_number()
				<< std::endl;
		}
	} else {
		stream() << "    success: t\n";
	}
}

void yaml_testpp_output_c::summarize( int passed, int failed )
{
	stream() << "passed: " << passed << std::endl;
	stream() << "failed: " << failed << std::endl;
}

