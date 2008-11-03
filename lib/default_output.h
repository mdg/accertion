#ifndef DEFAULT_TESTPP_OUTPUT_H
#define DEFAULT_TESTPP_OUTPUT_H
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

#include <testpp/output.h>


/**
 * Write the testpp output in a human readable format
 */
class human_testpp_output_c
: public testpp_output_i
{
public:
	human_testpp_output_c();
	virtual void begin( const testpp_id_c & );
	virtual void complete( const testpp_id_c &, const testpp_result_c & );
	virtual void summarize( int passed, int failed );
};


/**
 * Write the testpp output in the default YAML format
 */
class yaml_testpp_output_c
: public testpp_output_i
{
public:
	yaml_testpp_output_c();
	virtual void begin( const testpp_id_c & );
	virtual void complete( const testpp_id_c &, const testpp_result_c & );
	virtual void summarize( int passed, int failed );
};


/**
 * Write the testpp output in the default JSON format
 */
class json_testpp_output_c
: public testpp_output_i
{
public:
	json_testpp_output_c();
	virtual void begin( const testpp_id_c & );
	virtual void complete( const testpp_id_c &, const testpp_result_c & );
	virtual void summarize( int passed, int failed );
};


#endif

