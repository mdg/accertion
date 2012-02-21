#include "test.h"

using namespace std;

int times2(int i) { return 2 * i; }
int triple(int i) { return 3 * i; }

CCTEST(test_times2)
{
	accert(times2(4)) == 8;
	accert(times2(7)) == 14;
}

CCTEST(test_triple)
{
	accert(triple(5)) == 15;
}


int main(int argc, const char **argv)
{
	int result(0);
	if (argc == 1) {
		print_tests(cout);
	} else if (argc == 2) {
		bool success(run_test(argv[1]));
		if (success) {
			cout << "pass\n";
		} else {
			cout << "fail\n";
		}
		result = success ? 0 : 1;
	} else {
		cerr << "missing test\n";
		result = -1;
	}
	return result;
}
