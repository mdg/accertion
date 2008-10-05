#include "testpp_project.h"
#include "testpp_output.h"
#include "default_output.h"


/**
 * The default project loader class.
 */
class default_testpp_project_loader_c
: public testpp_project_loader_i
{
public:
	virtual testpp_project_c * create_project()
	{
		return new testpp_project_c();
	}
};


testpp_project_c::testpp_project_c()
{
	add_output< human_testpp_output_c >();
	add_output< yaml_testpp_output_c >();
	// add_output< json_testpp_output_c >();
}

testpp_project_c::~testpp_project_c()
{
	std::list< testpp_output_i * >::iterator output;
	for ( output=m_output.begin(); output!=m_output.end(); ++output ) {
		delete *output;
	}
	m_output.clear();
}

testpp_output_i & testpp_project_c::output( const std::string &format )
{
	std::list< testpp_output_i * >::iterator it;
	for ( it=m_output.begin(); it!=m_output.end(); ++it ) {
		if ( (*it)->name() == format ) {
			return **it;
		}
	}
	// return the first output format as set in the constructor
	return *m_output.front();
}


testpp_project_loader_i * & testpp_project_loader_i::settable_loader()
{
	static default_testpp_project_loader_c default_loader;
	static testpp_project_loader_i * loader( &default_loader );
	return loader;
}

