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

#include <fstream>
#include "testpp/test.h"
#include "testpp/project.h"
#include "default_output.h"
#include <iostream>
#include <memory>


/**
 * There was a problem with usage, so print it out and exit.
 */
static void print_usage()
{
	std::cerr << "usage error\n";
}

/**
 * Print the available test suites or files to the stream.
 */
static void print_ls( std::ostream &out, const std::set< std::string > &ls )
{
	std::set< std::string >::const_iterator it( ls.begin() );
	for ( ; it!=ls.end(); ++it ) {
		out << *it << std::endl;
	}
}


/**
 * Implemented main function.
 */
int main( int argc, char **argv )
{
	bool usage_error( false );
	bool print_help( false );
	bool print_ls_files( false );
	bool print_ls_suites( false );

	std::string arg;
	std::string suite_name;
	std::string format;
	std::string file;
	// usage options
	std::string help_option( "--help" );
	std::string ls_files_option( "--ls-files" );
	std::string ls_suites_option( "--ls-suites" );
	std::string format_option( "--format=" );
	std::string file_option( "--file=" );

	// parse command line arguments
	for ( int i(1); i<argc; ++i ) {
		arg = argv[i];
		if ( arg[0] == '-' && arg[1] == '-' ) {
			if ( arg == help_option ) {
				// print the usage but no error
				print_help = true;
			} else if ( arg == ls_files_option ) {
				print_ls_files = true;
			} else if ( arg == ls_suites_option ) {
				print_ls_suites = true;
			} else if ( arg.find( format_option ) == 0 ) {
				format = arg.substr( format_option.length() );
			} else if ( arg.find( file_option ) == 0 ) {
				file = arg.substr( file_option.length() );
			}
		} else if ( arg[0] == '-' ) {
			usage_error = true;
		} else {
			if ( i + 1 == argc ) {
				suite_name = arg;
			} else {
				usage_error = true;
			}
		}
	}

	if ( usage_error ) {
		print_usage();
		return 1;
	}
	if ( print_help ) {
		print_usage();
		return 0;
	}

	testpp_project_loader_i &project_loader(
			testpp_project_loader_i::project_loader() );
	std::auto_ptr< testpp_project_c > project(
			project_loader.create_project() );
	/*
	std::auto_ptr< testpp_project_c > project(
			testpp_project_loader_i
			::project< testpp_project_c >() );
			*/
	project->init();

	testpp_set_c &tests( testpp_tests() );

	// print test info
	if ( print_ls_files ) {
		print_ls( std::cout, tests.test_files() );
		return 0;
	}
	if ( print_ls_suites ) {
		print_ls( std::cout, tests.test_suites() );
		return 0;
	}

	// set the output stream
	std::ostream *out( &std::cout );
	std::ofstream fout;
	if ( ! file.empty() ) {
		fout.open( file.c_str() );
		out = &fout;
	}

	testpp_output_i &output( project->output( format ) );
	output.set_stream( *out );

	if ( suite_name.empty() ) {
		tests.run( output );
	} else {
		tests.run( output, suite_name );
	}

	return 0;
}

