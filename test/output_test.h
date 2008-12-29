#ifndef OUTPUT_TEST_H
#define OUTPUT_TEST_H

#include <testpp/output.h>


class output_test_1
: public testpp_output_i
{
public:
	output_test_1();
	virtual void begin( const testpp_id_c & );
	virtual void complete( const testpp_id_c &, const testpp_result_c & );
	virtual void summarize( int passed, int failed, int ignored
			, int not_implemented );
};


#endif

