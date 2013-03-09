// Copyright (c) 2013 Matthew Graham
// See LICENSE.txt for copying permission

#include "accertion.h"


int times2(int i) { return 2 * i; }
int triple(int i) { return 3 * i; }
int fault()
{
	(*(int *) 0) = 0;
	return 0;
}


CCTEST(test_times2)
{
	accert(times2(4)) == 8;
	accert(times2(7)) == 14;
}

CCTEST(test_triple)
{
	accert(triple(5)) == 14;
}

CCTEST(test_fault)
{
	accert(fault()) == 0;
}


int main(int argc, const char **argv)
{
	return accertion_main(argc, argv);
}
