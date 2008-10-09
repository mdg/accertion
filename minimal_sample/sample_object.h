#ifndef SAMPLE_OBJECT_H
#define SAMPLE_OBJECT_H


class sample_object
{
public:
	sample_object( int value )
	: m_value( value )
	{}

	int doubled_value() const { return 2 * m_value; }
	int tripled_value() const { return 3 * m_value; }

private:
	int m_value;
};


#endif

