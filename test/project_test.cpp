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
#include "output_test.h"


/*
TESTPP_PROJECT()
{
	std::cerr << "add test project\n";
	add_output< output_test_1 >();
}
*/

class override_testpp_project_c
: public testpp_project_c
{
public:
	virtual void init();
};

testpp_project_loader_c< override_testpp_project_c > project_loader;

template <>
testpp_project_c * testpp_project_loader_i
		::project< override_testpp_project_c >()
{
	return new override_testpp_project_c();
}

void override_testpp_project_c::init()
{
	add_output< output_test_1 >();
}

