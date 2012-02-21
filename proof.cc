#include "accertion.h"

int times2(int i) { return 2 * i; }
int triple(int i) { return 3 * i; }

CCTEST(test_times2)
{
	accert(times2(4)) == 8;
	accert(times2(7)) == 14;
}

CCTEST(test_triple)
{
	accert(triple(5)) == 14;
}


int main(int argc, const char **argv)
{
	return accertion_main(argc, argv);
}
