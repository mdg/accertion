#ifndef TESTPP_OUTPUT_H
#define TESTPP_OUTPUT_H

#include <iostream>


/**
 * An interface for writing test events to be recovered later.
 */
class testpp_output_i
{
public:
	virtual ~testpp_output_i();
	void set_stream( std::ostream &out ) { m_out = &out; }

	const std::string & name() const { return m_name; }

	virtual void begin_test( const testpp_id_i & ) = 0;
	virtual void complete_test( const testpp_id_i & ) = 0;

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

