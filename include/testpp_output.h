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
	/**
	 * Virtual destructor for the output class
	 */
	virtual ~testpp_output_i() {}
	/**
	 * set the stream that this output object should write it.
	 */
	void set_stream( std::ostream &out ) { m_out = &out; }

	/**
	 * Get the name of this output class.
	 */
	const std::string & name() const { return m_name; }

	/**
	 * Write a test beginning to the output.
	 */
	virtual void begin( const testpp_id_c & ) = 0;
	/**
	 * Write a test completion to the output.
	 */
	virtual void complete( const testpp_id_c &
			, const testpp_result_c & ) = 0;
	/**
	 * Write test summary to the output.
	 */
	virtual void summarize( int passed, int failed ) = 0;

protected:
	/**
	 * Construct a test output base class with the given name for
	 * the test.
	 */
	testpp_output_i( const std::string &name )
	: m_name( name )
	{}
	/**
	 * Get the stream that this output should write to.
	 */
	std::ostream & stream() { return *m_out; }
private:
	std::string m_name;
	std::ostream *m_out;
};


#endif

