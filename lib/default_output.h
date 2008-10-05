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


class default_testpp_output_c
{
public:
private:
	registered_testpp_output_type< human_testpp_output_c > s_human;
	registered_testpp_output_type< yaml_testpp_output_c > s_yaml;
	registered_testpp_output_type< json_testpp_output_c > s_json;
};


#endif

