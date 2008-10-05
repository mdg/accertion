#ifndef TESTPP_PROJECT_H
#define TESTPP_PROJECT_H

#include <list>


/**
 * Declare a project to override various aspects of the tests.
 * This is the principle manner in which to get a project loaded.
 */
#define TESTPP_PROJECT() \
	class override_testpp_project_c : public testpp_project_c { \
		virtual void init(); \
	}; \
	testpp_project_loader_c< override_testpp_project_c > project_loader; \
	void override_testpp_project_c::init()



class testpp_output_i;

/**
 * The default project for testpp.  The init() function can be overridden
 * to customize the unit tests.
 */
class testpp_project_c
{
public:
	/**
	 * Construct the base project
	 */
	testpp_project_c();
	/**
	 * Destroy the project.
	 */
	~testpp_project_c();

	virtual void init() {}

	testpp_output_i & output( const std::string &format );

protected:
	template < class T >
	void add_output()
	{
		m_output.push_back( new T() );
	}

private:
	std::list< testpp_output_i * > m_output;
};


/**
 * Project loader base class
 */
class testpp_project_loader_i
{
public:
	/**
	 * Create the project associated with this loader.
	 */
	virtual testpp_project_c * create_project() = 0;

	/**
	 * Provide the project loader to use for these tests.
	 * This may be set with the testpp_project_loader_c class
	 * or preferably, with the TESTPP_PROJECT macro.
	 */
	static testpp_project_loader_i & project_loader()
	{
		return *settable_loader();
	}

	template < class T >
	static testpp_project_c * project()
	{
		return new testpp_project_c();
	}

protected:
	testpp_project_loader_i();

	/**
	 * Static function for clarifying initialization order.
	 */
	static testpp_project_loader_i * & settable_loader();
};

/**
 * Templated project loader.  Declaring one of these for a specific
 * project type will set that project as the project to use for all tests.
 * In most cases, this class won't be used directly, but through the
 * TESTPP_PROJECT macro. 
 */
template < class T >
class testpp_project_loader_c
: public testpp_project_loader_i
{
public:
	testpp_project_loader_c()
	{
		testpp_project_loader_i::settable_loader() = this;
	}
	virtual testpp_project_c * create_project() { return new T(); }
};


#endif

