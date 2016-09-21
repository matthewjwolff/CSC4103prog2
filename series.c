#include <stdlib.h> // atoi
#include <stdio.h> // printf
#include <unistd.h> // fork
#include <sys/wait.h> //wait

int sigma(int n) {
	if(n==0)
		return 0;
	else return n+sigma(n-1);
}

/**
 * Simple factorial function
 * returns -1 if given a negative number
 * must use long long int for big numbers
 */
long long factorial(long long n) {
	if (n<0)
		return -1;
	if (n==0 || n==1)
		return 1;
	else return n*factorial(n-1);
}

// call as ./series n
// fork: parent creates product of numbers 1 - n, child creates sum of numbers 1 - n
// child prints, then parent prints
int main(int argc, char** argv) {
	if(argc!=2) {
		printf("Usage: ./series n\n");
		return -1;
	}
	int n = atoi(argv[1]);
	int pid = fork();
	if(pid==0) {
		// Child
		int sum = sigma(n);
		return sum;
	}
	else {
		//parent
		// do calculation
		long long product = factorial(n);
		//wait for child
		int child_status;
		// Linux feature, put status information into child_status
		wait(&child_status);
		// use Linux feature to get return value of child process
		int sum = WEXITSTATUS(child_status);
		printf("Sum: %d\n", sum);
		// remember that long long is actually long long int
		printf("Product: %lld\n", product);
		return 0;
	}
}
