#ifndef DEFAULT_TESTPP_OUTPUT_H
#define DEFAULT_TESTPP_OUTPUT_H

#include "testpp_output.h"


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
};


/**
 * Write the testpp output in the default JSON format
 */
class json_testpp_output_c
: public testpp_output_i
{
public:
};


#endif

