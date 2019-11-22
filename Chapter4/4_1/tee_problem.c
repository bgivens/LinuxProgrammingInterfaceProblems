#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

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

	int fds[argc];
	int num_files = argc-optind;
	for(int i = optind ; i < argc; i++){
		fds[i-optind] = open(argv[i],
				O_RDWR | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR);
		printf("File name: %s, File Descriptor: %d\n", 
				argv[i],
				fds[i-optind]);
	}

	//while(1){
	//	char str[256];
	//	scanf("%s", str);
	//	printf("%s\n", str);
	//}
	return 0;
}
