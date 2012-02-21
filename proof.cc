#include "test.h"
#include <iostream>

using namespace std;

int times2(int i) { return 2 * i; }

CCTEST(test_times2)
{
	accert(times2(4)) == 8;
}


int main(int argc, const char **argv)
{
	if (argc != 2) {
		cerr << "missing test\n";
		return -1;
	}
	bool success(run_test(argv[1]));
	if (success) {
		cout << "pass\n";
	} else {
		cout << "fail\n";
	}
	return success ? 0 : 1;
}
