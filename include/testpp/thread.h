#ifndef TESTPP_THREAD_H
#define TESTPP_THREAD_H
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


class testpp_thread_i
{
public:
	void test()
	{
		int parent_pid = pid();
		int child_pid = fork();
		if ( pid() == parent_pid ) {
			test_parent_thread();
		} else {
			test_child_thread();
		}
	}

	virtual void test_parent_thread() = 0;
	virtual void test_child_thread() = 0;

};


class testpp_thread_c
{
public:
	testpp_thread_c();

	void add_concurrent_test( testpp_thread_i );
};


/**
 * Client Server test class.
 */
template < typename C, typename S >
class client_server_test_c
{
public:
	client_server_test_c()
	{
		add_concurrent_test( m_client );
		add_concurrent_test( m_server );
	}

private:
	C m_client;
	S m_server;
};

#define TESTPP_CLIENT_SERVER( client, server );


#endif

