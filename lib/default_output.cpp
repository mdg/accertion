/**
 * Copyright 2008 Matthew Graham
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "default_output.h"
#include <testpp/id.h>
#include <testpp/result.h>
#include <sstream>


human_testpp_output_c::human_testpp_output_c()
: testpp_output_i( "human" )
{}

void human_testpp_output_c::begin( const testpp_id_c &id )
{
	stream() << id.file_name() << ':' \
		<< id.test_name()
		<< ':' << id.line_number() << std::endl;
}

void human_testpp_output_c::complete( const testpp_id_c &id
		, const testpp_result_c &result )
{
	if ( result.ignore_failures() ) {
		stream() << "\tignored\n";
	} else if ( result.test_not_implemented() ) {
		stream() << "\tnot implemented\n";
	} else if ( ! result.failure() ) {
		// if not a failure, return
		return;
	}

	testpp_result_c::failure_iterator it;
	for ( it=result.begin(); it!=result.end(); ++it ) {
		stream() << "\t" << it->message();

		if ( it->file_name().empty() || it->line_number() == 0 ) {
			// nothing to write
		} else if ( id.file_name() == it->file_name() ) {
			// line is from the test file
			stream() << " (line " << it->line_number() << ")";
		} else {
			// file is different, include filename
			stream() << " (" << it->file_name() << ":"
				<< it->line_number() << ")";
		}
		stream() << "\n";
	}
}

void human_testpp_output_c::summarize( int passed, int failed, int ignored
		, int not_implemented )
{
	stream() << failed << " failures in " << passed + failed
		<< " tests\n";
	stream() << ignored << " ignored and " << not_implemented
		<< " not implemented\n";
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
	std::string result_text;
	bool write_failures( false );

	if ( result.ignore_failures() ) {
		result_text = "ignore";
	} else if ( result.test_not_implemented() ) {
		result_text = "not_implemented";
	} else if ( result.failure() ) {
		result_text = "failure";
		write_failures = true;
	} else {
		result_text = "success";
	}

	stream() << "    result: " << result_text << std::endl;
	if ( write_failures ) {
		stream() << "    failures:\n";
		testpp_result_c::failure_iterator it;
		for ( it=result.begin(); it!=result.end(); ++it ) {
			stream() << "      - message: \"" << it->message()
				<< "\"" << std::endl;
			stream() << "        failure-file: "
				<< it->file_name()
				<< std::endl;
			stream() << "        failure-line: "
				<< it->line_number()
				<< std::endl;
		}
	}
}

void yaml_testpp_output_c::summarize( int passed, int failed, int ignored
		, int not_implemented )
{
	stream() << "passed: " << passed << std::endl;
	stream() << "failed: " << failed << std::endl;
	stream() << "ignored: " << ignored << std::endl;
	stream() << "not_implemented: " << not_implemented << std::endl;
}

