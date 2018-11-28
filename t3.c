#include <time.h>
#include <stdio.h>
/*
Q2.
Consider the following function
Determine, by instrumenting the below code, the number of procedure
calls, maximum register window depth, the number of register window
overflows and the number of register window underflows that would
occur during the calculation of ackerman(3,6) given a RISC-I
processor with 6, 8 and 16 register sets respectively. You are NOT
asked to translate the ackermann function into RISC-1 code.
See http://en.wikipedia.org/wiki/Ackermann function for some
background on the Ackermann function.
*/
int ackermann_1(int x, int y) {
	if (x == 0) {
		return y+1;
	} else if (y == 0) {
		return ackermann_1(x-1, 1);
	} else {
		return ackermann_1(x-1, ackermann_1(x, y-1));
	}
}

/*
Q3 Determine how long it takes to calculate ackermann(3, 6) on your
computer. Make sure you time the release version of your code.
Briefly describe your approach and comment on its accuracy.
*/
int ackermann(int x, int y) {
	if (x == 0) {
		return y+1;
	} else if (y == 0) {
		return ackermann(x-1, 1);
	} else {
		return ackermann(x-1, ackermann(x, y-1));
	}
}

int main() {
	int runtimes = 10000;
	int i=0;
	time_t start = clock();
	for(; i<runtimes; i++) {
		ackermann(3,6);
	}
	time_t elapsed = clock() - start;
	long ns = elapsed*1000*1000 / (CLOCKS_PER_SEC);
	printf("Nanoseconds to run 10,000 times:\n%ld ns\n", ns);
	long avg = ns/runtimes;
	printf("Average time to run each function:\n%ld ns\n", avg);
	return 0;
}

/*
Length of time to run function 50,000 times: 20423648 ns
Average time to run each function: 2042 ns
*/
