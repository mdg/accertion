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


/**
 * A base object for creating
 */
class testpp_output_type_i
{
public:
	virtual testpp_output_i * create_output() = 0;

	static const std::list< testpp_output_type_i * > & all_types();

protected:
	static std::list< testpp_output_type_i * > & types();
};

/**
 * Typed output register
 */
template < class T >
class testpp_output_type_c
: public testpp_output_type_i
{
public:
	virtual testpp_output_i * create_output() { return new T(); }
};

/**
 * Registered output type.  Separated from the testpp_output_type_c for
 * testing purposes.
 */
template < class T >
class registered_testpp_output_type_c
: public testpp_ouput_type_c< T >
{
public:
	registered_testpp_output_type_c()
	{
		types().push_back( this );
	}
};


class testpp_output_set_c
{
public:
	testpp_output_set( const std::list< testpp_output_type_i * > & );

	const std::vector< std::string > & names() const;
	testpp_output_i & output( const std::string &name );
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

