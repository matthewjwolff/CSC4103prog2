#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define FILE_SIZE 4096

int main(int argc, char** argv) {
	if(argc==2) {
		const char* file_to_open = argv[1];
		printf("opening: %s\n", file_to_open);
		// open the shared memory
		int open_descriptor = shm_open(file_to_open, O_RDONLY, 0644);
		// map the shared memory to process memory
		void* other_in_memory = mmap(0, FILE_SIZE, PROT_READ, MAP_PRIVATE, open_descriptor, 0);
		// print to that memory
		printf("%s\n", (char*) other_in_memory);
		// remove the shared memory object
		// shm_unlink(file_to_open);
		return 0;
	}
	if (argc>2) {
		printf("Usage: secret [PAWSID]\n");
		return -1;
	}
	//else was invoked like ./secret, so create the shared message
	const char* name = "mwolff3";
	// open up a shared file descriptor
	int shared_descriptor = shm_open(name, O_CREAT | O_RDWR, 0644);
	// truncate it to set the size
	ftruncate(shared_descriptor, FILE_SIZE);
	// map the shared memory object to process memory
	// mmap(start address, for how much memory, what protections on memory, how to handle when memory is changed, the file descriptor, offset within file descriptor)
	void* file_in_memory = mmap(0, FILE_SIZE, PROT_WRITE, MAP_SHARED, shared_descriptor, 0);
	//write message
	const char* message = "Call me Jerry Lewis.\n";
	sprintf(file_in_memory, "%s", message);
	return 0;
}
