#include <stdlib.h> // atoi
#include <unistd.h> // read, write, pipe
#include <stdio.h> // printf
#include <sys/wait.h> //wait

/**
 * Simple factorial function
 * returns -1 if given a negative number
 * Must use long long, we're dealing with big numbers
 */
long long factorial(long long n) {
	if (n<0)
		return -1;
	if (n==0 || n==1)
		return 1;
	else return n*factorial(n-1);
}


// Call with ./choose m n
// Fork: parent calculates m!/((m-n)!n!) and prints out
// child calculates n!
int main(int argc, char** argv) {
	if(argc!=3) {
		printf("Usage: choose m n\n");
		return -1;
	}
	int m = atoi(argv[1]);
	int n = atoi(argv[2]);
	int pipe_fd[2];
	int pipe_create = pipe(pipe_fd);
	if(pipe_create==-1) {
		printf("Could not create pipe\n");
		return -1;
	}
	// If parent, pid=Process id of child
	// If child, pid=0
	pid_t pid = fork();
	if(pid<0) {
		printf("Could not fork\n");
		return -1;
	}
	if(pid==0) {
		// child
		// this is an inside joke referring to my old high school calc teacher
		// when reading a factorial, he would say "13 SURPRISE" instead of "13 factorial" because the ! makes the number EXCITING!! YAY!!
		long long surprise = factorial(n);
		// close the reading FD
		close(pipe_fd[0]);
		int write_success = write(pipe_fd[1], &fac, sizeof(long long));
		close(pipe_fd[1]);
		if(write_success < 0) {
			printf("Could not write to pipe\n");
			return -1;
		}
		return 0;
	} else {
		//parent
		wait(NULL);
		long long n_surprise;
		close(pipe_fd[1]);
		int read_success = read(pipe_fd[0], &n_surprise, sizeof(long long));
		close(pipe_fd[0]);
		if(read_success < 0) {
			printf("Could not read from pipe\n");
			return -1;
		}
		long long m_surprise = factorial(m);
		long long m_minus_n_surprise = factorial(m-n);
		long long result = m_surprise / (m_minus_n_surprise*n_surprise);
		printf("%lld\n", result);
		return 0;
	}
}
