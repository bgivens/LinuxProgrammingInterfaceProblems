#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int append_flag = 0;
	int option;
	extern int optind;

	while(( option = getopt(argc, argv, "a")) != -1){
		switch (option){
		case 'a':
			append_flag=1;
			break;
		default:
			fprintf(stderr, "Usage: %s [-a append] filenames...",
				       	argv[0]);
			exit(EXIT_FAILURE);
		}
	}

	int num_files = argc-optind;
	int fds[num_files];
	for(int i = optind ; i < argc; i++){
		fds[i-optind] = open(argv[i],
				O_RDWR | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR);
	}

	while(1){
		char str[1024];
		scanf("%s", str);
		int numChars = (int)strlen(str);
		for(int i=0; i<num_files; i++){
			int bytesWritten = write(fds[i], str, numChars);
			bytesWritten = bytesWritten + write(fds[i], "\n", 1);
		}
	}
	return 0;
}
