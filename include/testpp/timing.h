#ifndef TESTPP_TIMING_H
#define TESTPP_TIMING_H
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


/**
 * Interface for a timer that is testable.  This interface should be used
 * in live classes.
 */
class testpp_timer_i
{
public:
	virtual time_t time() = 0;
};


/**
 * Fully implemented timer for running in live code.
 */
class testpp_timer_c
{
public:
	virtual time_t time();
};


/**
 * A mocked timer for manipulating time in tested code.
 */
class mock_timer_c
{
public:
	mock_timer_c();
	mock_timer_c( time_t );

	void operator = ( time_t t ) { m_time = t; }
	void operator += ( time_t t ) { m_time += t; }

	virtual time_t time() { return m_time; }

private:
	time_t m_time;
};


#endif

