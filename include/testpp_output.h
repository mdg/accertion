#ifndef TESTPP_OUTPUT_H
#define TESTPP_OUTPUT_H

#include <iostream>


class testpp_id_c;
class testpp_result_c;

/**
 * An interface for writing test events to be recovered later.
 */
class testpp_output_i
{
public:
	virtual ~testpp_output_i() {}
	void set_stream( std::ostream &out ) { m_out = &out; }

	const std::string & name() const { return m_name; }

	virtual void begin( const testpp_id_c & ) = 0;
	virtual void complete( const testpp_id_c &
			, const testpp_result_c & ) = 0;
	virtual void summarize( int passed, int failed ) = 0;

protected:
	testpp_output_i( const std::string &name )
	: m_name( name )
	{}
	std::ostream & stream() { return *m_out; }
private:
	std::string m_name;
	std::ostream *m_out;
};


#endif

