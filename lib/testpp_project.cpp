/**
 * Copyright 2008 Matthew Graham
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <testpp/project.h>
#include <testpp/output.h>
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


testpp_project_loader_i::testpp_project_loader_i()
{
}

testpp_project_loader_i * & testpp_project_loader_i::settable_loader()
{
	static default_testpp_project_loader_c default_loader;
	static testpp_project_loader_i * loader( &default_loader );
	return loader;
}

