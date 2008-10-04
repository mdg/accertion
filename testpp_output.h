#ifndef TESTPP_OUTPUT_H
#define TESTPP_OUTPUT_H


/**
 * An interface for writing test events to be recovered later.
 */
class testpp_output_i
{
public:
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


class testpp_output_register_i
{
public:
	virtual testpp_output_type_i * create_output() = 0;

	static const std::list< testpp_output_type_i * > & registry();
protected:
	static std::list< testpp_output_type_i * > & output();
};

/**
 * Typed output registry
 */
template < class T >
class testpp_output_register_c
{
public:
	testpp_output_register_c()
	{
		testpp_output_register_i::output().push_back( this );
	}

	virtual testpp_output_type_i * create_output()
	{
		return new T();
	}
};


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


#endif

